import sys
import time

import cmdc
import pybind11_stubgen


class InvalidSignatureError(Exception):
    """Raised when one or more signatures are invalid."""


class UnnamedArgumentError(Exception):
    """Raised when one or more signatures contain unnamed arguments."""


def count_unnamed_args(content):
    """Count all the signatures that have unnamed arguments.

    This ignores property setters as these will always have unnamed arguments.
    """
    lines = content.split("\n")

    unnamed_signatures = []

    previous_line = ""
    for i, line in enumerate(lines):
        if "arg0" in line and "setter" not in previous_line:
            print(f"Invalid signature line {i + 1}: {line.strip(' ')}")
            unnamed_signatures.append(line)
        previous_line = line

    return len(unnamed_signatures)


def main(outStubFile, *args):
    print("Generating stubs")
    t0 = time.time()

    raise_on_invalid_stub = True
    if "--no-raise" in args:
        raise_on_invalid_stub = False

    module = pybind11_stubgen.ModuleStubsGenerator(cmdc)
    module.write_setup_py = False

    print("(1) Parsing module..")

    module.parse()

    invalid_signatures_count = pybind11_stubgen.FunctionSignature.n_invalid_signatures
    if invalid_signatures_count > 0 and raise_on_invalid_stub:
        raise InvalidSignatureError(
            f"Module contains {invalid_signatures_count} invalid signature(s). "
            "Use `--no-raise` if you want to generate the stubs anyway."
        )

    t1 = time.time()
    print("(1) Finished in {0:0.3} s".format(t1 - t0))
    print("(1) ----------------------------")

    print("(2) Generating stubs content..")

    content = "\n".join(module.to_lines())
    unnamed_args_count = count_unnamed_args(content)

    if unnamed_args_count > 0 and raise_on_invalid_stub:
        raise UnnamedArgumentError(
            f"Module contains {unnamed_args_count} signatures with unnamed arguments. "
            "Use `--no-raise` if you want to generate the stubs anyway."
        )

    t2 = time.time()
    print(f"(2) Finished in {t2 - t1:0.3} s")
    print("f(2) ----------------------------")

    print("(3) Writing stubs file...")

    with open(outStubFile, "w") as handle:
        handle.write(content)

    t3 = time.time()
    print(f"(3) Finished in {t3 - t2:0.3} s")
    print("(3) ----------------------------")

    print(f"Succesfully created .{outStubFile} in {t3 - t0:0.3} s")


if __name__ == "__main__":
    main(*sys.argv[1:])
