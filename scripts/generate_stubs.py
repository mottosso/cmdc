import inspect
from itertools import count
import sys
import time

import cmdc
import pybind11_stubgen


class InvalidSignatureError(Exception):
    """Raised when one or more signatures are invalid."""


class UnnamedArgumentError(Exception):
    """Raised when one or more signatures contain unnamed arguments."""


def count_unnamed_args(lines):
    """Count all the signatures that have unnamed arguments.

    This ignores property setters as these will always have unnamed arguments.
    """

    unnamed_signatures = []
    for line in lines:
        if "arg0" in line and "setter" not in previous_line:
            unnamed_signatures.append(line)
        previous_line = line

    if unnamed_signatures:
        print("These signatures contain unnamed arguments:")
        for signature in unnamed_signatures:
            print(f"    {signature.strip(' ')}")

    return len(unnamed_signatures)


def main(outStubFile, *args):

    print("Generating stubs")
    t0 = time.time()

    module = pybind11_stubgen.ModuleStubsGenerator(cmdc)
    module.write_setup_py = False

    print("(1) Parsing module..")

    module.parse()

    invalid_signatures_count = pybind11_stubgen.FunctionSignature.n_invalid_signatures
    if invalid_signatures_count > 0:
        raise InvalidSignatureError(
            f"Module contains {invalid_signatures_count} invalid signature(s)"
        )

    t1 = time.time()
    print("(1) Finished in {0:0.3} s".format(t1 - t0))
    print("(1) ----------------------------")

    print("(2) Generating stubs content..")

    lines = module.to_lines()
    unnamed_args_count = count_unnamed_args(lines)

    if unnamed_args_count > 0:
        raise UnnamedArgumentError(
            f"Module contains {unnamed_args_count} signatures with unnamed arguments."
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
