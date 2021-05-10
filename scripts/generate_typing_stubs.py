"""Generate stubs for cmdc

For the script to run it needs the following:
1. `pybind11-stubgen` has been installed in mayapy.
    `mayapy -m pip install pybind11-stubgen`
2. All the generated Types and functions to be declared 
    before any of them are implemented. Or at least before being used as type arguments
3. cmdc to be in the PYTHONPATH
"""
import pybind11_stubgen

module = pybind11_stubgen.ModuleStubsGenerator("cmdc")

module.parse() # this throws a bunch of warning and then freezes after some point.

with open("build/cmdc.pyi", "w") as handle:
    handle.write("\n".join(module.to_lines()))
