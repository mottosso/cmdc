<a href=/cmda/><p align=center><img width=90 src=https://user-images.githubusercontent.com/2152766/113510233-ca120400-9551-11eb-9a34-b8846a2c959c.png></p></a>

<p align=center>a.k.a. "Maya Python API 3.0"</p>

<br>

Another set of bindings for the C++ API of Maya 2018-2022, 

**Why?**

- What if Maya's Python bindings were open source?
- What if whenever Maya crashed, you'd get more than an opaque stack trace?
- What if you were able to see why a crash occurred, and what line it occurred on?
- What if you could address bugs in the bindings yourself?
- What if you could *add* missing members yourself?
- What if there were bindings for Maya that made it impossible to crash Maya from Python?

That's what this repository is for.

<br>

### Example

The bindings should aim to match Maya Python API 2.0 as closely as possible, with the exception of being open source and to *never* allow Maya to crash as a result of calling any function or method.

```py
import cmdc

typ = cmdc.TypeId(16)

mat4 = cmdc.Matrix()
mat4 *= cmdc.Matrix().inverse()

vec3 = cmdc.Vector()
vec3.x = 6

quat = cmdc.Quaternion(angle=0.5, axis=cmdc.Vector(1, 0, 0))
mat4 *= quat

# No need for MString
string = str()

# Modify the Maya scene graph
from maya import standalone
standalone.initialize()
fn = cmdc.FnDependencyNode()
r = fn.create("reverse", name="myReverse")
print(fn.name())

# This next line really shouldn't work, should require MFnDagNode
t = fn.create("transform", name="myTransform")
print(fn.name())

print("Success")
```

<br>

### Goal

`cmdc` should have the same advantages over 1.0 as 2.0, and more.

- Array types are full Python sequences, including slice support.
- Methods which take Maya array parameters will *always* also take native Python sequences, such as arrays and tuples.
- The outputs of methods are *always* returned in their return values, not through their parameter lists.
- Methods which return multiple values (e.g. MFnFluid.getResolution) return them as a tuple or list, eliminating the need for MScriptUtil.
- Object attributes are preferred over rather than set/get methods. For example you can now write array.sizeIncrement=64.
- There are more types of exceptions used when methods fail. Not everything is a RuntimeError, as was the case in the old API.
- `cmdc` should be faster or as fast as API 2.0

> [Reference](https://help.autodesk.com/view/MAYAUL/2020/ENU/?guid=__py_ref_index_html)

<br>

### Status

![](https://img.shields.io/badge/prototype-0.1-brightgreen)

It'll work, but won't have half the things you'll need to do anything of use in Maya. The current source is enough to illustrate (1) how to expose types, (2) how to expose function sets and (3) how to deal with passing MObject references around.

**How can I help?**

It's easy but tedious.

- Add more members
- Add more tests

<br>

### Repository

| File | Description
|:-----|:-------------
| `src/`      | C++ source for the pybind11 bindings
| `install/`  | Destination of the compiled binding, e.g. `cmdc.pyd`
| `build.ps1` | Example build script for Maya 2020 on Windows
| `pyproject.toml` | `setup.py` uses this ahead of building
| `setup.py` | Let pip handle actually compiling the extension
| `test.py`  | Tests for bound methods and types

<br>

### Build

This should build on any platform, for any Maya with Python available. Including 2022. Included is an example build script for Maya 2020 on Windows.

- C++11 compatible compiler, e.g. Visual Studio 2015
- Maya 2020
- pip 19+

```pwsh
# Prerequisities the script cannot figure out on its own
$env:DEVKIT_LOCATION="C:\github\maya-devkit\2020.2\windows"
$env:MAYA_LOCATION="C:\Program Files\Autodesk\Maya2020"

# Go!
.\build.ps1
```

**How can I help?**

More easy but tedious things.

- Add more Maya versions
- Add more platforms
