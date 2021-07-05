"""
This script generates a Python binding stub from a Maya devkit header.

pre-requisites:
1. universal ctags installed and in the PATH.
    universal-ctags is available in most package managers,
    including choco or scoop (in the extras repo) on Windows
    pre-built binaries for windows can also be found here: https://github.com/universal-ctags/ctags-win32/releases
3. $DEVKIT_LOCATION has to be set to the root of the devkit

To run the script:
>>> mayapy parse_headers.py MDagPath

Notes:
- The script runs on python 3 only
- It needs to run from mayapy as it retrieves the docstrings from OpenMaya 2
    and compares the classes content with OpenMaya 1

If you wish to manually run ctags:
>>> ctags --C++-kinds=+p --format=2 --sort=no $DEVKIT_LOCATION/include/maya/MDagPath.h
"""

from __future__ import annotations

import argparse
import logging
import os
import re
import shutil
import subprocess
import textwrap
from dataclasses import dataclass, field
from enum import Enum
from pathlib import Path
from typing import Any, Callable, List, Optional, Type


try:
    import maya.standalone
except ImportError:
    raise RuntimeError("This script needs to run from Mayapy")
else:
    maya.standalone.initialize()

    import maya


logging.getLogger().setLevel(logging.DEBUG)
logger = logging.getLogger("parse_header")
# logger.setLevel(logging.DEBUG)


MODULE_TEMPLATE = """\
{docstring_definitions}

{classes}"""


CLASS_TEMPLATE = """\
py::class_<{maya_class_name}>(m, "{class_name}")
{body};"""


METHOD_TEMPLATE = """\

.def(
    "{name}", []({arguments}){return_type}
    {{ {body} }},
    {py_args}{docstring_variable})
"""

CONSTRUCTOR_TEMPLATE = """\

.def(py::init<{arguments}>())
"""

DOCSTRING_TEMPLATE = """\
#define {variable_name} \\
{docstring}
"""


@dataclass
class Module:
    classes: List[Class] = field(default_factory=list)

    def __str__(self) -> str:
        docstrings = []
        for cls in self.classes:
            docstrings.extend(cls.unique_docstrings())

        docstrings = map(str, docstrings)
        classes = map(str, self.classes)

        docstrings_str = "\n".join(docstrings)
        classes_str = "\n".join(classes)

        return MODULE_TEMPLATE.format(
            docstring_definitions=docstrings_str,
            classes=classes_str,
        )


@dataclass
class Class:
    maya_class_name: str
    name: str = field(init=False)
    methods: List[Method] = field(default_factory=list)

    maya_api1_class: Optional[Type] = None
    maya_api2_class: Optional[Type] = None

    def __post_init__(self) -> None:
        self.name = self.maya_class_name.strip("M")

        self.maya_api1_class = self.find_maya_api1_class()
        self.maya_api2_class = self.find_maya_api2_class()

    def find_maya_api1_class(self):
        for module in (
            maya.OpenMaya,
            maya.OpenMayaAnim,
            maya.OpenMayaRender,
            # maya.OpenMayaFX,  # not available in mayapy?
            maya.OpenMayaUI,
            maya.OpenMayaMPx,
            # maya.OpenMayaCloth,  # not available in mayapy?
        ):
            if hasattr(module, self.maya_class_name):
                return getattr(module, self.maya_class_name)

    def find_maya_api2_class(self):
        for module in (
            maya.api.OpenMaya,
            # maya.api.OpenMayaAnim,  # not available in mayapy?
            maya.api.OpenMayaRender,
            maya.api.OpenMayaUI,
        ):
            if hasattr(module, self.maya_class_name):
                return getattr(module, self.maya_class_name)

    def add_method(self, method: Method):
        if not method.is_destructor and method.maya_api1_method:
            # if not method.is_destructor:
            self.methods.append(method)

    @property
    def body_str(self) -> str:
        body_str = ""

        for method in self.methods:
            body_str += str(method)

        return body_str

    def unique_docstrings(self) -> List[Docstring]:
        docstrings = []
        for method in self.methods:
            if method.docstring not in docstrings:
                docstrings.append(method.docstring)
        return docstrings

    def __str__(self) -> str:
        return CLASS_TEMPLATE.format(
            maya_class_name=self.maya_class_name,
            class_name=self.name,
            body=textwrap.indent(self.body_str, "    "),
        )


@dataclass
class Method:

    arguments: List[Argument]
    klass: Class
    name: str
    return_type: Optional[str]
    body = 'throw std::logic_error{{"Function not yet implemented."}};'
    is_constructor = False
    is_destructor = False
    is_operator = False
    docstring: Docstring = field(init=False)
    maya_api1_method: Optional[Callable[[], Any]] = field(default=None, init=False)
    maya_api2_method: Optional[Callable[[], Any]] = field(default=None, init=False)

    def __post_init__(self):
        if self.name == self.klass.maya_class_name:
            self.is_constructor = True

        if self.name.startswith("~"):
            self.is_destructor = True

        try:
            api1_method = getattr(self.klass.maya_api1_class, self.name)
        except:
            self.maya_api1_method = None
        else:
            self.maya_api1_method = api1_method

        try:
            api2_method = getattr(self.klass.maya_api2_class, self.name)
        except:
            self.maya_api2_method = None
        else:
            self.maya_api2_method = api2_method

        if self.name in [
            "=",
            "+",
            "+=",
            "-",
            "-=",
            "*",
            "*=",
            "/",
            "/=",
            "==",
            "!=",
        ]:
            self.is_operator = True

        if not self.is_constructor:
            self.arguments.insert(
                0, Argument.from_string(f"{self.klass.maya_class_name} & self")
            )

        docstring_str = "MISSING DOCSTRING"
        if hasattr(self.klass.maya_api2_class, self.name):
            maya_method = getattr(self.klass.maya_api2_class, self.name)
            if maya_method.__doc__:
                docstring_str = maya_method.__doc__
        self.docstring = Docstring(self, docstring_str)

        self._filter_mstatus()

    def _filter_mstatus(self):
        arguments = self.arguments
        for argument in arguments:
            if "MStatus" in argument.type:
                self.arguments.remove(argument)

        if self.return_type and "MStatus" in self.return_type:
            self.return_type = None

    @classmethod
    def new(
        cls,
        klass: Class,
        name: str,
        arguments_str: str,
        return_type: Optional[str],
    ) -> Method:

        arguments = []
        for argument_str in arguments_str.split(","):
            if not argument_str:
                continue

            try:
                argument = Argument.from_string(argument_str.strip())
            except RuntimeError as e:
                logger.warning(e)
            else:
                arguments.append(argument)

        return Method(
            arguments=arguments,
            klass=klass,
            name=name,
            return_type=return_type,
        )

    @property
    def arguments_str(self) -> str:
        return ", ".join([arg.source_string for arg in self.arguments])

    @property
    def pyargs_str(self) -> str:
        # self is the first argument, we don't want it in the pybind arguments
        arguments = self.arguments[1:]

        if not arguments:
            return ""

        return ",\n    ".join([arg.pyarg_str for arg in arguments if arg.name]) + ",\n    "

    @property
    def return_type_str(self) -> str:
        if self.return_type:
            return f" -> {self.return_type} "
        else:
            return " "

    def __str__(self) -> str:
        if self.is_constructor:
            return CONSTRUCTOR_TEMPLATE.format(arguments=self.arguments_str)

        if self.is_operator:
            # not supported yet
            return ""

        return METHOD_TEMPLATE.format(
            name=self.name,
            arguments=self.arguments_str,
            py_args=self.pyargs_str,
            return_type=self.return_type_str,
            body=self.body,
            docstring_variable=self.docstring.variable_name,
        )


@dataclass(eq=False)
class Docstring:
    method: Method
    docstring: str

    def __post_init__(self) -> None:
        self._process_docstring()

    def _process_docstring(self):
        self.strip_signature()
        self.process_multilines()

    def strip_signature(self) -> None:
        signature_regex = re.compile(r".*\(.*\) -> .*")

        lines = self.docstring.splitlines()

        while lines:
            line = lines[0]

            # Exclude signatures and empty lines
            if signature_regex.match(line) or not line:
                lines.pop(0)
                continue

            # we've reached the first documentation line.
            if line:
                break

        filtered_docstring = "\n".join(lines)

        self.docstring = filtered_docstring

    def process_multilines(self) -> None:
        lines = self.docstring.splitlines()
        line_template = '"{line}\\n"\\\n'
        last_line_template = '"{line}"'

        multiline_docstring = ""
        for i, line in enumerate(lines):
            if i < len(lines) - 1:
                formatted_line = line_template.format(line=line)
            else:
                formatted_line = last_line_template.format(line=line)
            multiline_docstring += formatted_line

        self.docstring = multiline_docstring

    @property
    def variable_name(self) -> str:
        return f"_doc_{self.method.klass.name}_{self.method.name}"

    @property
    def define_statement(self) -> str:
        return DOCSTRING_TEMPLATE.format(
            variable_name=self.variable_name,
            docstring=textwrap.indent(self.docstring, "    "),
        )

    def __str__(self) -> str:
        return self.define_statement

    def __eq__(self, o: object) -> bool:
        if isinstance(o, Docstring):
            return self.variable_name == o.variable_name
        else:
            return False


@dataclass
class Argument:
    # To make sense of the regex: https://regex101.com/r/7O6yVV/1
    _regex_pattern = re.compile(
        r"^(?P<type>.+?(\s?(\*|&)\s?)*)(?P<name>\S+)?( = (?P<value>\S+))?$"
    )

    name: Optional[str]
    source_string: str
    type: str
    value: Optional[str]

    @classmethod
    def from_string(cls, string: str) -> Argument:
        string = string.strip()
        match = cls._regex_pattern.match(string)

        if not match:
            raise RuntimeError(f"Invalid argument pattern: {string}")

        groups = match.groupdict()

        name = groups["name"]
        type = groups["type"]
        value = groups.get("value", None)

        return Argument(
            name=name,
            source_string=string,
            type=type,
            value=value,
        )

    @property
    def pyarg_str(self) -> Optional[str]:
        if self.name:
            pyarg_str = f'py::arg("{self.name}")'

            if self.value:
                pyarg_str += f" = {self.value}"

            return pyarg_str
        else:
            return None
    
    @property
    def is_reference(self):
        return "&" in self.type

    @property
    def is_pointer(self):
        return "*" in self.type

    @property
    def is_const(self):
        return "const" in self.type



class EntryKind(Enum):
    Class = "c"
    Member = "m"
    Prototype = "p"  # A prototype method is a method with no implementation


def find_header_file(header_name: str) -> Path:
    logger.debug(f"Searching header file for {header_name}")

    devkit_path = Path(os.environ["DEVKIT_LOCATION"])

    header_file = devkit_path / "include" / "maya" / header_name

    if not header_file.exists():
        raise LookupError(f"No '{header_name}' header in the devkit.")
    else:
        logger.info(f"Header file found: {header_file}")

    return header_file


def generate_tags(header_file: Path) -> Path:
    logger.debug(f"Generating Tags from Header file: {header_file}")

    if shutil.which("ctags") is None:
        raise RuntimeError(
            "ctags not found.\n"
            "              universal-ctags is available in most package managers.\n"
            "              binaries for windows can also be found here: https://github.com/universal-ctags/ctags-win32/releases"
        )

    tags_dir = Path(__file__).parent.resolve() / "tags"
    tags_dir.mkdir(exist_ok=True)
    tags_file = tags_dir / header_file.name.replace(".h", ".tags")

    args = [
        "ctags",
        "--C++-kinds=+p-d",
        "--sort=no",
        f"-f {tags_file}",
        "--fields=+S",
        "--excmd=number",
        "--output-format=json",
        str(header_file),
    ]
    subprocess.check_call(args)

    logger.info(f"Generated tag file: {tags_file}")

    return tags_file


def parse_tags(tag_file: Path) -> Module:
    logger.debug(f"Parsing tag file: {tag_file}")

    with tag_file.open("r") as f:
        tag_file_content = f.read()

    module = Module()

    # https://regex101.com/r/dPC7VE/1
    # I'm sorry...
    line_re = re.compile(
        r"^(?P<name>[^!]\S+)\s*(?P<file>\S+)\s*(?P<line_number>\d+);\"\s(?P<kind>d|c|p)((\sclass:(?P<class>\S+))?(\styperef:typename:(?P<return_type>\S+))?(\ssignature:\((?P<arguments>.*)\))?)?"
    )

    current_class = None
    for line in tag_file_content.splitlines():
        match = line_re.match(line)

        if not match:
            continue

        entry = match.groupdict()

        name = entry["name"]
        kind = EntryKind(entry["kind"])

        if kind is EntryKind.Class:
            current_class = Class(name)
            module.classes.append(current_class)
        elif kind is EntryKind.Prototype:

            cls = entry["class"]
            if cls is None:
                continue

            arguments = entry["arguments"] or ""
            return_type = entry["return_type"]
            try:
                method = Method.new(current_class, name, arguments, return_type)
            except RuntimeError as e:
                logger.info(e)
            else:
                current_class.add_method(method)
        else:
            continue

    return module


def write_inl_file(header_name: str, module: Module, overwrite: bool):
    src_dir = Path(__file__).parent.parent / "src"
    filename = header_name.replace(".h", ".inl")
    inl_file = (src_dir / filename).resolve()

    if inl_file.exists() and not overwrite:
        raise OSError(
            f"File '{inl_file}' already exist. "
            "Use --overwrite if you want to overwrite the existing file."
        )

    with inl_file.open("w") as f:
        f.write(str(module))

    logger.info(f"Generated inl file: {inl_file}")


def parse_header(header_name: str, overwrite: bool):
    if not header_name.endswith(".h"):
        header_name = f"{header_name}.h"

    header_file = find_header_file(header_name)
    tag_file = generate_tags(header_file)
    module = parse_tags(tag_file)
    write_inl_file(header_name, module, overwrite)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("header", help="Name of Maya header, e.g. MPlug.h")
    parser.add_argument(
        "--overwrite",
        type=bool,
        nargs="?",
        default=False,
        const=True,
        help="Whether to overwrite the existing inl file.",
    )

    opts = parser.parse_args()
    try:
        parse_header(opts.header, opts.overwrite)
    except LookupError as e:
        logger.error(str(e))
    except OSError as e:
        logger.error(str(e))


if __name__ == "__main__":
    main()
    maya.standalone.uninitialize()
