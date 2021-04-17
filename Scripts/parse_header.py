#/usr/bin/python

"""Parse Header.

This script generate a Pythong binding stub from a Maya devkit header.
"""

import collections
import logging 
import re 
import os 
import sys 
import textwrap

import maya.api.OpenMaya 
import maya.api.OpenMayaAnim
import maya.api.OpenMayaRender
import maya.api.OpenMayaUI

LOG = logging.getLogger('parse_header')
LOG.setLevel(logging.INFO)
logging.basicConfig()

TEMP_DOCSTRING = 'Lorem ipsum dolor sit amet, consectetur adipiscing elit'

IGNORED_METHODS = [
    'className',
]

IGNORED_CPP_TOKENS = [
    '*',
    '&',
    'const',
]

TEMPLATE_STR = (
"""\
py::class_<M{class_name}>(m, "{class_name}")
{class_body}\
"""
)

INSTANCE_METHOD = (
"""\
    .def("{method_name}", []({class_name} & self{arguments}){return_type} {{
        throw std::logic_error{{"Function not yet implemented."}};
    }}, R"pbdoc({doctstring})pbdoc")\
"""
)

STATIC_METHOD = (
"""\
    .def_static("{method_name}", []({arguments}){return_type} {{
        throw std::logic_error{{"Function not yet implemented."}};
    }}, R"pbdoc({doctstring})pbdoc")\
"""
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
    
    header_path = os.path.join(os.environ['DEVKIT_LOCATION'], 'include', 'maya', header_name)

    if not os.path.exists(header_path):
        raise LookupError("No '{}' header in the devkit.".format(header_name))

    with open(header_path, 'r') as fp:
        lines = fp.readlines()

    lines = filter_header_lines(class_name, lines)

    class_methods = collections.defaultdict(list)
    class_methods['__init__'].append('    .def(py::init<>())')

    m_class = find_maya_class(class_name)

    for (signature, arguments) in filter_function_lines(lines):
        method_name, arguments, return_type = parse_method(signature, arguments)

        if method_name in IGNORED_METHODS:
            continue

        if not hasattr(m_class, method_name):
            continue 

        if signature.startswith('static'):
            method_str_fmt = STATIC_METHOD
        else:
            method_str_fmt = INSTANCE_METHOD

            if arguments:
                arguments = ', {}'.format(arguments)

        m_method = getattr(m_class, method_name)

        method_str = method_str_fmt.format(
            class_name=class_name,
            arguments=arguments,
            doctstring=m_method.__doc__,
            method_name=method_name,
            return_type=return_type,
        )

        class_methods[method_name].append(method_str)

    class_body = []

    for name in sorted(class_methods):
        class_body.extend(sorted(class_methods[name]))

    class_body[-1] += ';'
    class_body_str = '\n\n'.join(class_body)

    code_str = (
        TEMPLATE_STR.format(
           class_name=class_name[1:],
           class_body=class_body_str
        )
    )

    tmp_dir = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'tmp')

    file_name = '{}.inl'.format(class_name)
    file_path = os.path.join(tmp_dir, file_name)

    if not os.path.isdir(tmp_dir):
        os.mkdir(tmp_dir)

    with open(file_path, 'w') as fp:
        fp.write(code_str)


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

    in_args, out_args = parse_arguments(argument_list, has_outs=return_type=='MStatus')

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
        has_outs (bool): True if the method has an out argument (mutable value passed by reference).

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
        parts[i] = ''.join([c for c in parts[i] if c not in IGNORED_CPP_TOKENS])

    return ' '.join(parts)


def find_maya_class(class_name):
    """Return the maya.api class (for docstrings)."""

    for module in [
        maya.api.OpenMaya,
        maya.api.OpenMayaAnim,
        maya.api.OpenMayaRender,
        maya.api.OpenMayaUI
    ]:
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
        return '(' in statement and ')' in statement and statement.endswith(';')
    else:
        return True 


def main(*argv):
    """Parse the given headers."""

    for name in argv:
        try:
            parse_header(name)
        except LookupError as e:
            LOG.error(str(e))


if __name__ == '__main__':
    main(*sys.argv[1:])