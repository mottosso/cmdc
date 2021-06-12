import time
import pybind11_stubgen

STUBS_LOCATION = "build/cmdc.pyi"

print("Generating stubs")
t0 = time.time()

module = pybind11_stubgen.ModuleStubsGenerator("cmdc")
module.write_setup_py = False

print("(1) Parsing module..")

module.parse()

t1 = time.time()
print("(1) Finished in {0:0.3} s".format(t1-t0))
print("(1) ----------------------------")

print("(2) Writing stubs..")

with open(STUBS_LOCATION, "w") as handle:
    content = "\n".join(module.to_lines())

    handle.write(content)

t2 = time.time()
print("(2) Finished in {0:0.3} s".format(t2-t1))
print("(2) ----------------------------")

print("Succesfully created .{0} in {1:0.3} s".format(STUBS_LOCATION, t2-t0))

