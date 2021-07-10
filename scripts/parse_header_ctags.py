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
import json
import logging
import os
import re
import shutil
import subprocess
import textwrap
from dataclasses import dataclass, field
from enum import Enum
from pathlib import Path
from typing import Any, Callable, Dict, List, Optional, Type, Tuple

try:
    import maya.standalone
except ImportError:
    raise RuntimeError("This script needs to run from Mayapy")
else:
    maya.standalone.initialize()

    import maya


logging.getLogger().setLevel(logging.DEBUG)
logger = logging.getLogger("parse_header")


class DeprecationError(Exception):
    """Raised when a method is deprecated."""


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
    classes: Dict[str, Class] = field(default_factory=dict)

    def __str__(self) -> str:
        docstrings = []
        classes = self.classes.values()
        for cls in classes:
            docstrings.extend(cls.unique_docstrings())

        docstrings = map(str, docstrings)
        classes = map(str, classes)

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

    cls: Class
    name: str
    arguments: List[Argument]
    return_type: Optional[str]
    body = 'throw std::logic_error{{"Function not yet implemented."}};'

    is_constructor: bool = field(init=False, default=False)
    is_destructor: bool = field(init=False, default=False)
    is_operator: bool = field(init=False, default=False)
    docstring: Docstring = field(init=False)
    maya_api1_method: Optional[Callable[[], Any]] = field(default=None, init=False)
    maya_api2_method: Optional[Callable[[], Any]] = field(default=None, init=False)

    def __post_init__(self):
        if self.name == self.cls.maya_class_name:
            self.is_constructor = True

        if self.name.startswith("~"):
            self.is_destructor = True

        try:
            api1_method = getattr(self.cls.maya_api1_class, self.name)
        except:
            self.maya_api1_method = None
        else:
            self.maya_api1_method = api1_method

        try:
            api2_method = getattr(self.cls.maya_api2_class, self.name)
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
                0, Argument.from_string(f"{self.cls.maya_class_name} & self")
            )

        docstring_str = "MISSING DOCSTRING"
        if hasattr(self.cls.maya_api2_class, self.name):
            maya_method = getattr(self.cls.maya_api2_class, self.name)
            if maya_method.__doc__:
                docstring_str = maya_method.__doc__
        self.docstring = Docstring(self, docstring_str)

    @classmethod
    def from_entry(
        cls,
        klass: Class,
        entry: Dict[str, str],
    ) -> Method:
        name = entry["name"]
        signature = entry["signature"]

        return_type = entry.get("typeref")
        if return_type:
            return_type = return_type.replace("typename:", "")

            if "OPENMAYA_DEPRECATED" in return_type:
                raise DeprecationError(
                    f"Method {klass.name}.{name} is deprecated -- skipping."
                )

        if return_type == "void":
            return_type = None

        if return_type == "MString":
            return_type = "std::string"

        if return_type == "MStatus":
            return_type = None
            has_out_args = True
        else:
            has_out_args = False

        in_args, out_args = cls._parse_signature(signature, has_out_args)

        if out_args:
            if len(out_args) == 1:
                return_type = out_args[0].type
            else:
                out_args_types = [arg.type for arg in out_args]
                return_type = "std::tuple<{}>".format(", ".join(out_args_types))

        return Method(
            arguments=in_args,
            cls=klass,
            name=name,
            return_type=return_type,
        )

    @classmethod
    def _parse_signature(
        cls,
        signature: str,
        has_out_args: bool,
    ) -> Tuple[List[Argument], List[Argument]]:
        signature_re = re.compile(r"\((?P<arguments_str>.*)\).*")

        match = signature_re.match(signature)

        if not match:
            raise ValueError(f"Invalid signature format: {signature}")

        in_args: List[Argument] = []
        out_args: List[Argument] = []

        arguments_str = match["arguments_str"]
        for argument_str in arguments_str.split(","):
            if not argument_str:
                continue
            try:
                argument = Argument.from_string(argument_str.strip())
            except re.error as e:
                logger.warning(e)
            else:
                if not argument.name or "MStatus" in argument.type:
                    continue

                if argument.is_const:
                    in_args.append(argument)
                elif argument.is_reference:
                    if has_out_args:
                        out_args.append(argument)
                    else:
                        in_args.append(argument)
                else:
                    in_args.append(argument)

        return (in_args, out_args)

    @property
    def arguments_str(self) -> str:
        return ", ".join([arg.source_string for arg in self.arguments])

    @property
    def pyargs_str(self) -> str:
        # self is the first argument, we don't want it in the pybind arguments
        arguments = [arg for arg in self.arguments[1:] if arg.name]

        if not arguments:
            return ""

        return ",\n    ".join([arg.pyarg_str for arg in arguments]) + ",\n    "

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
        self._strip_signature()
        self._escape_quotes()
        self._process_multilines()

    def _strip_signature(self) -> None:
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

    def _escape_quotes(self) -> None:
        self.docstring = self.docstring.replace('"', '\\"')

    def _process_multilines(self) -> None:
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
        return f"_doc_{self.method.cls.name}_{self.method.name}"

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

    source_string: str
    name: Optional[str]
    type: str
    value: Optional[str]
    is_pointer: bool
    is_reference: bool
    is_const: bool

    @classmethod
    def from_string(cls, argument_str: str) -> Argument:

        # https://regex101.com/r/99q0hk/2
        arguement_re = re.compile(
            r"^(?P<const>const)? ?(?P<type>(unsigned )?\S+) ?(?P<passed_by>\*|&)? ?(?P<name>\S+?)?( ?= ?(?P<value>\S+))?$"
        )
        argument_str = argument_str.strip()
        match = arguement_re.match(argument_str)

        if not match:
            raise re.error(f"Invalid argument pattern: {argument_str}")

        groups = match.groupdict()

        name = groups.get("name")

        type = groups["type"]
        if type == "MString":
            type = "std::string"

        value = groups.get("value", None)

        is_const = bool(groups.get("is_const"))

        passed_by = groups.get("passed_by")
        is_reference = False
        is_pointer = False
        if passed_by == "*":
            is_pointer = True
        if passed_by == "&":
            is_reference = True

        return Argument(
            source_string=argument_str,
            name=name,
            type=type,
            value=value,
            is_pointer=is_pointer,
            is_reference=is_reference,
            is_const=is_const,
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

    def __str__(self) -> str:
        argument_str = self.type

        if self.name:
            argument_str += f" {self.name}"

        if self.value:
            argument_str += f" = {self.value}"

        return argument_str


def find_header_file(header_name: str) -> Path:
    logger.debug(f"Searching header file for {header_name}")

    devkit_path = Path(os.environ["DEVKIT_LOCATION"])

    header_file = devkit_path / "include" / "maya" / header_name

    if not header_file.exists():
        raise FileNotFoundError(f"No '{header_name}' header in the devkit.")
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

    if tags_file.exists():
        tags_file.unlink()

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

    # register all the classes first
    for line in tag_file_content.splitlines():
        entry = json.loads(line)

        if entry["_type"] != "tag":
            continue

        name = entry["name"]
        kind = entry["kind"]
        scope = entry.get("scope")

        if kind == "class":
            module.classes[name] = Class(name)

    # then register all the methods.
    for line in tag_file_content.splitlines():
        entry = json.loads(line)

        if entry["_type"] != "tag":
            continue

        name = entry["name"]
        kind = entry["kind"]
        scope = entry.get("scope")

        if kind == "prototype":
            if not scope:
                # we likely have a function in our hands
                # TODO: Support function definitions.
                continue

            try:
                cls = module.classes[scope]
                if cls:
                    method = Method.from_entry(cls, entry)
            except KeyError as e:
                logger.warning(f"class {scope} not found for {name} -- skipping.")
            except DeprecationError as e:
                logger.warning(e)
            except Exception as e:
                raise e
            else:
                cls.add_method(method)
        else:
            # TODO: Support properties and probably more kinds
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
    except FileNotFoundError as e:
        logger.error(str(e))
    except OSError as e:
        logger.error(str(e))


if __name__ == "__main__":
    main()
    maya.standalone.uninitialize()
