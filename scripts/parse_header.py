#!/usr/bin/python

"""Parse Header.

This script generates a Python binding stub from a Maya devkit header.
"""

import re
import os
import logging
import argparse
import collections
import textwrap

from maya.api import (
    OpenMaya,
    OpenMayaUI,
    OpenMayaAnim,
    OpenMayaRender,
)

log = logging.getLogger('parse_header')
handler = logging.StreamHandler()
handler.setFormatter(logging.Formatter('%(message)s'))
log.handlers.append(handler)
log.setLevel(logging.INFO)


TEMP_DOCSTRING = (
    'Lorem ipsum dolor sit amet, consectetur adipiscing elit'
)

IGNORED_METHODS = (
    'className',
)

IGNORED_CPP_TOKENS = (
    '*',
    '&',
    'const',
)

TEMPLATE_STR = """\
{docstring_definitions}

py::class_<M{class_name}>(m, "{class_name}")
{class_body}\
"""

INSTANCE_METHOD = """\
    .def("{method_name}", []({class_name} & self{arguments}){return_type} {{
        throw std::logic_error{{"Function not yet implemented."}};
    }}, {pybind_arguments}{doctstring_variable})\
"""

STATIC_METHOD = """\
    .def_static("{method_name}", []({arguments}){return_type} {{
        throw std::logic_error{{"Function not yet implemented."}};
    }}, {pybind_arguments}{doctstring_variable})\
"""

class Docstring(object):
    def __init__(self, class_name, method_name, docstring):
        # type: (str, str, str) -> None
        self.class_name = class_name.strip("M")
        self.method_name = method_name
        self.docstring = docstring

        self._process_docstring()

    def _process_docstring(self):
        # type: () -> None
        self.strip_signature()
        self.process_multilines()

    def strip_signature(self):
        # type: () -> None
        signature_regex = re.compile(r".*\(.*\) -> .*")

        lines = self.docstring.splitlines()

        while lines:
            line = lines[0]

            # Exclude signature lines and empty lines
            if signature_regex.match(line) or not line:
                lines.pop(0)
                continue

            # Stop trying to pop as soon as we encounter a real doc line.
            if line:
                break

        filtered_docstring = "\n".join(lines)
            
        self.docstring = filtered_docstring

    def process_multilines(self):
        # type: () -> None
        lines = self.docstring.splitlines()
        line_template = "    \"{line}\\n\"\\\n"
        last_line_template = "    \"{line}\""

        multiline_docstring = ""
        for i, line in enumerate(lines):
            if i < len(lines) - 1:
                formatted_line = line_template.format(line=line)
            else:
                formatted_line = last_line_template.format(line=line)
            multiline_docstring += formatted_line

        self.docstring = multiline_docstring

    @property
    def variable_name(self):
        # type: () -> str
        return "_doc_{class_name}_{method_name}".format(
            class_name=self.class_name,
            method_name=self.method_name,
        )

    @property
    def define_statement(self):
        # type: () -> str
        return textwrap.dedent(
            "#define {variable_name} \\\n"
            "{docstring}\n".format(
                variable_name=self.variable_name,
                docstring=self.docstring,
            )
        )
    
    def __str__(self):
        # type: () -> str
        return self.define_statement

    def __eq__(self, other):
        # type: (Docstring) -> bool
        return (
            self.class_name == other.class_name
            and self.method_name == other.method_name
            and self.docstring == other.docstring
        )


def parse_header(header_name):
    """Parse the given header.

    Args:
        header_name (str): Name of the header to parse (eg, 'MDagPath')
    """

    if header_name.endswith('.h'):
        class_name, __ = header_name.split('.')
    else:
        class_name = header_name
        header_name = '{}.h'.format(header_name)

    header_path = os.path.join(
        os.environ['DEVKIT_LOCATION'],
        'include', 'maya', header_name
    )

    if not os.path.exists(header_path):
        raise LookupError("No '{}' header in the devkit.".format(header_name))

    with open(header_path, 'r') as fp:
        lines = fp.readlines()

    lines = filter_header_lines(class_name, lines)

    class_methods = collections.defaultdict(list)
    class_methods['__init__'].append('    .def(py::init<>())')

    m_class = find_maya_class(class_name)

    docstrings = []

    for (signature, arguments) in filter_function_lines(lines):
        method_name, arguments, return_type = parse_method(signature,
                                                           arguments)

        if method_name in IGNORED_METHODS:
            continue

        if not hasattr(m_class, method_name):
            continue

        pybind_arguments = generate_pybind_args(arguments)

        if signature.startswith('static'):
            method_str_fmt = STATIC_METHOD
        else:
            method_str_fmt = INSTANCE_METHOD

            if arguments:
                arguments = ', {}'.format(arguments)

        m_method = getattr(m_class, method_name)
        docstring = Docstring(
            m_class.__name__,
            m_method.__name__,
            m_method.__doc__
        )
        if docstring not in docstrings:
            docstrings.append(docstring)

            
        method_str = method_str_fmt.format(
            arguments=arguments,
            class_name=class_name,
            doctstring_variable=docstring.variable_name,
            method_name=method_name,
            pybind_arguments=pybind_arguments,
            return_type=return_type,
        )

        class_methods[method_name].append(method_str)

    class_body = []

    for name in sorted(class_methods):
        class_body.extend(sorted(class_methods[name]))

    class_body[-1] += ';'
    class_body_str = '\n\n'.join(class_body)

    docstring_definitions = "\n".join([d.define_statement for d in docstrings])

    code_str = (
        TEMPLATE_STR.format(
            docstring_definitions=docstring_definitions,
            class_name=class_name[1:],
            class_body=class_body_str
        )
    )

    out_dir = os.path.join(
        os.path.dirname(os.path.abspath(__file__)), "..", "src"
    )
    out_dir = os.path.abspath(out_dir)

    file_name = '{}.inl'.format(class_name)
    file_path = os.path.join(out_dir, file_name)

    if os.path.exists(file_path):
        raise OSError("File '%s' already exist" % file_path)

    with open(file_path, 'w') as fp:
        fp.write(code_str)

    log.info("Successfully generated '%s'" % file_path)

def generate_pybind_args(arguments):
    # type: (str) -> str

    if not arguments:
        return ""

    # matches a single argument with a type, name and optional value
    # some examples:
    #     MPlug plug
    #     unsigned int i
    #     bool mergeWithExisting = false
    argument_re = re.compile(r"^(?P<type>.*?) (?P<name>\S+)( = (?P<value>.*))?$")

    pybind_arg_template = "py::arg(\"{arg_name}\")"

    pybind_args = []
    for arg in arguments.split(","):
        match = argument_re.match(arg)

        if not match:
            continue

        arg_name = match["name"]
        arg_value = match["value"]
        arg_str = pybind_arg_template.format(arg_name=arg_name)

        if arg_value:
            arg_str += " = {}".format(arg_value)
        
        pybind_args.append(arg_str)

    pybind_args_str = ", ".join(pybind_args)
    if pybind_args:
        pybind_args_str += ", "

    return pybind_args_str


def parse_method(signature, arguments):
    """Parse the given method components.

    Args:
        signature (str): Method C++ signature string.
        arguments (str): Method C++ arguments string.

    Returns:
        tuple[str]
            - Name, arguments, return type
    """

    argument_list = list(map(str.strip, arguments.split(',')))

    signature_list = signature.split()

    method_name = None
    return_type = None

    if len(signature_list) == 1:
        method_name, = signature_list

    elif len(signature_list) == 2:
        if signature_list[0] == 'virtual':
            method_name = signature_list[-1][1:]
        else:
            return_type, method_name = signature_list

    elif len(signature_list) == 3:
        __, return_type, method_name = signature_list
    elif len(signature_list) == 4:
        __, __, return_type, method_name = signature_list
    else:
        raise RuntimeError("Cannot parse signature: {}".format(signature))

    in_args, out_args = parse_arguments(
        argument_list, has_outs=return_type == 'MStatus')

    if out_args:
        if len(out_args) == 1:
            return_type, = out_args
        else:
            return_type = 'std::tuple<{}>'.format(', '.join(out_args))

    if return_type == 'MStatus':
        return_type = ''
    else:
        return_type = ' -> {}'.format(return_type)

    return method_name, ', '.join(in_args), return_type


def parse_arguments(argument_list, has_outs):
    """Parse the given method arguments.

    Args:
        argument_list (list[str]): C++ argument strings.
        has_outs (bool): True if the method has an out argument
            (mutable value passed by reference).

    Returns:
        tuple[list]
            - In arguments, out arguments
    """

    in_args = []
    out_args = []

    for arg_str in argument_list:
        if arg_str in [
            'MStatus* ReturnStatus = nullptr',
            'MStatus* ReturnStatus = NULL',
            'MStatus * ReturnStatus = nullptr',
            'MStatus * ReturnStatus = NULL',
            'MStatus *ReturnStatus = nullptr',
            'MStatus *ReturnStatus = NULL',
            'MStatus ReturnStatus = NULL',
        ]:
            continue

        arg = sanitize_argument(arg_str).strip()

        if 'const' in arg_str:
            in_args.append(arg)
        elif '&' in arg_str:
            if has_outs:
                if arg == 'unsigned int':
                    pass
                else:
                    try:
                        arg, __ = arg.split(' ')
                    except ValueError:
                        pass

                out_args.append(arg)
            else:
                in_args.append(arg)
        else:
            in_args.append(arg)

    return in_args, out_args


def sanitize_argument(arg_str):
    """Return the argument string, sans C++ specific tokens."""

    parts = arg_str.split()
    parts = [p for p in parts if p not in IGNORED_CPP_TOKENS]

    for i, _ in enumerate(parts):
        parts[i] = ''.join([
            c for c in parts[i]
            if c not in IGNORED_CPP_TOKENS
        ])

    return ' '.join(parts)


def find_maya_class(class_name):
    """Return the maya.api class (for docstrings)."""

    for module in (OpenMaya,
                   OpenMayaAnim,
                   OpenMayaRender,
                   OpenMayaUI):
        if hasattr(module, class_name):
            return getattr(module, class_name)

    return type('NoModule', (), {'__doc__': 'TODO: Add docstring'})


def filter_function_lines(lines):
    """Yield the lines that appear to be C++ function declarations."""

    func_re = re.compile(r'.*\(.*\).*;')

    signature_re = re.compile(r'(.*)\(.*\).*;')
    arguments_re = re.compile(r'.*\((.*)\).*;')

    for line in lines:
        match = func_re.match(line)

        if match:
            yield (
                signature_re.match(line).groups(0)[0].strip(),
                arguments_re.match(line).groups(0)[0].strip(),
            )


def filter_header_lines(class_name, lines):
    """Yield the lines in the class definition."""

    skip_next_statement = False
    no_script = False
    in_class_definition = False

    class_def_re = re.compile(r'^class OPENMAYA_EXPORT {}'.format(class_name))

    statements = []

    for line in lines:
        line = line.strip()

        if line == 'BEGIN_NO_SCRIPT_SUPPORT:':
            no_script = True
            continue

        if line == 'END_NO_SCRIPT_SUPPORT:':
            no_script = False
            continue

        if no_script:
            continue

        if line.startswith('OPENMAYA_DEPRECATED'):
            skip_next_statement = True
            continue

        # OPENMAYA_PRIVATE appears to aways be at the endo f a header
        if line.startswith('OPENMAYA_PRIVATE'): 
            break

        try:
            # Remove trailing comments
            line = line[:line.index('//')].strip()
        except ValueError:
            pass

        if not in_class_definition:
            in_class_definition = class_def_re.match(line) is not None

        if in_class_definition:
            statements.append(line)

            if line.endswith(','):
                continue

            statement = ' '.join(statements)

            if not _is_complete_statement(statement):
                continue

            if skip_next_statement:
                skip_next_statement = False
            else:
                yield statement

            statements = []

            if line == '};\n':
                in_class_definition = False

def _is_complete_statement(statement):
    if '(' in statement:
        return (
            '(' in statement and
            ')' in statement and
            statement.endswith(';')
        )

    return True


def main():
    """Parse the given header"""

    parser = argparse.ArgumentParser()
    parser.add_argument("header", help="Name of Maya header, e.g. MPlug.h")

    opts = parser.parse_args()

    try:
        parse_header(opts.header)

    except OSError as e:
        log.error(str(e))

    except LookupError as e:
        log.error(str(e))


if __name__ == '__main__':
    main()
