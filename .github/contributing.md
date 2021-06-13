The goal of cmdc is to not to be a drop-in replacement of Maya Python API 2.0, but a better version of it.

In practice, it means you will be able to drop-in replace it, but will likely require tweaks to your code in order to get it running. Hopefully, you should never again have to suffer the Maya Python API 2.0 and instead gain complete control over what and how the Python API works.

<br>

### Functional

- No M-prefix
- No MString arguments or return values, instead use std::string
- No MStatus arguments or return values, instead throw an exception
- Keyword arguments SHALL be preserved, via e.g. `py::arg`
- Default argument values SHALL be preserved, via e.g. `py::arg("name") = 1.0`
- [Properties SHALL NOT Compute](#properties-cannot-compute)
- [Anonymous enums SHALL be cast to unsigned int](anonymous-enums-shall-be-cast-to-unsigned-int)

> [Reference](https://developer.lsst.io/pybind11/style.html#id37)

<br>

### Properties Cannot Compute

The Maya Python API 2.0 uses Python `@property` for any function call that takes no arguments, returns a value and cannot throw an exception.

```py
bbox = mesh.boundingBox()

# C++
print(bbox.width())

# Python property
print(bbox.width)
```

But this not only differs from the C++ documentation it also makes it ambiguous what is a function and what is not. How is the user to know whether whether it takes any optional arguments or is able to throw an exception?

As such, `@property` is reserved to *static* attributes only, and cannot compute. Not even the `width` of a bounding box.

### Anonymous enums SHALL be cast to unsigned int

Maya uses anonymous enums in places.

```cpp
// MFnDagNode.h
class MFnDagNode : public MFnDependencyNode {
public:
    enum {
        kNextPos = 0xff
    };
```

These should be `static_cast` to an `unsigned int`, as they cannot (?) be wrapped to Python.

```cpp
py::class_<MFnDagNode>(m, "FnDagNode")
    .def_property_readonly_static("kNextPos", [](py::object /* self */) {
        return static_cast<unsigned int>(MFnDagNode::kNextPos); 
    })
```


### Ensuring good stubs generation.

To ensure the quality of the generated stubs, here are a few things to keep in mind:
1. There should be no function signature as part of the docstrings.
2. All methods and functions should specify their argument names (and default values) with Pybind's [py::arg](https://pybind11.readthedocs.io/en/stable/basics.html#keyword-arguments) syntax.  
In the case where the default value results in an invalid signature, use [py::arg_v](https://pybind11.readthedocs.io/en/stable/advanced/functions.html?highlight=arg_v#default-arguments-revisited) instead.  
3. All types should be declared before being used in any signature.
`ForwardDeclarations.inl` is a good place for that as it is included before any other file. Not doing this causes the C++ Types to be used in the signature instead of the Python types, resulting in invalid stubs.

```c++
// MSelectionList.inl
SelectionList
    .def("add", [](MSelectionList & self, MDagPath object, MObject component = MObject::kNullObj, bool mergeWithExisting = false) -> MSelectionList {
        throw std::logic_error{"Function not yet implemented."};
    }, py::arg("object"),
       py::arg_v("component", MObject::kNullObj, "Object.kNullObj"),
       py::arg("mergeWithExisting") = false,
       _doc_SelectionList_add)

```

Which results in the following python signature:
```python
class SelectionList:
    def add(self, object: DagPath, component: Object = Object.kNullObj, mergeWithExisting: bool = False) -> SelectionList: ...
```

Not using `py::arg` and `py::arg_v` and would have resulted in this invalid signature and the stubs generation would have failed.

```python
class SelectionList:
    def add(self, arg0: DagPath, arg1: Object = <Object(kInvalid)>, arg2: bool = False) -> SelectionList: ...
#                                               ^--- Invalid Syntax
```

<br>

### Style Guide

- [80 character line width](#80-characters-wide)
- [Formatting](formatting)
- [Docstrings](docstrings)

<br>

#### 80 Characters Wide

Maximise screen realestate and let users with big screens work with multiple vertical panes of code. No line should exceed 80 characters wide.

<br>

#### Formatting

It's primarily a pybind11 project, so let's stick to the pybind11 formatting.

- https://github.com/pybind/pybind11/blob/master/.github/CONTRIBUTING.md#formatting

In a nutshell, it's basically Python-esque.

```cpp
void good_function_name() {}
void BadFunctionName() {}
void badFunctionName() {}

class GoodClass {};
class badClass {};
class bad_class {};

obj.good_variable = true;
obj.goodVariable = false;
obj.GoodVariable = false;
```

<br>

### Docstrings

Docstrings are defined at the top of the file with `#define` statements with a variable name following this template `_doc_ClassName_methodName`
The actual content of the docstring is placed on the line after the `#define` statement, indented once.

Here's an example taken from `MDagPath.inl`

```c++

#define _doc_DagPath_exclusiveMatrix \
    "Returns the matrix for all transforms in the path, excluding the\n"\
    "end object."

#define _doc_DagPath_exclusiveMatrixInverse \
    "Returns the inverse of exclusiveMatrix()."

#define _doc_DagPath_extendToShape \
    "If the object at the end of this path is a transform and there is a\n"\
    "shape node directly beneath it in the hierarchy, then the path is\n"\
    "extended to that geometry node.\n"\
    "\n"\
    "NOTE: This method will fail if there multiple shapes below the transform."\
```

<br>

### FAQ

> Are we aiming to be more consistent with the C++ API or OpenMaya2?

Good question. There are subtle and not-so-subtle differences between the two, some of which I don't understand.

```py
# C++
MTransformationMatrix::addTranslation()
MTransformationMatrix::rotation() -> MQuaternion

# Python
MTransformationMatrix.translateBy()
MTransformationMatrix.rotation() -> MEulerRotation

# But whyyyy?
```

They've made a few creative choices here, presumably to make it more user-friendly but it's so subjective..

I think we should stick to the C++ documentation as closely as possible and leave creative choices to the user. When that is not possible, such as..

```c++
// C++
MDagPath dagPath;
MFnDagNode(mobj).getPath(dagPath);
```

..where it's modifying a variable from a function rather than return a value (classic C++), we'll need to make some less-creative choices that I expect to become a predictable pattern anywhere this happens in C++.

```py
# Python
dagPath = MFnDagNode(mobj).getPath(dagPath)
```

In this case, the reason they're doing it the way that they are in C++ is because they choose not to throw exceptions. Instead, they return a `MStatus` value expecting the user to handle it.

```c++
MDagPath dagPath;
MStatus status = MFnDagNode(mobj).getPath(dagPath);
if (status == MS::kSuccess) {
  // It's ok to use dagPath
}
```

With Python, I expect we'll be able to completely replace MStatus with exceptions.

> Do we have a standardized format for the error messages? I've just copied OM2's messages so far.

Let's start there. I think it's hard to know until we have enough of a foundation to actually start using cmdc for actual code and experience what messages make the most sense given the context. At this point, some message is better than no message.

> I was expecting exclusiveMatrix and exclusiveMatrixInverse to fail when called from an invalid DagPath but they return an identity matrix instead.

Yes, the API loves this. It's perfectly happy letting you continue working with bad memory and chooses to randomly crash on you whenever it feels like it instead. This is one of the things I'd like cmdc to get rid of. It's a bad habit.

In this case, if the API isn't returning a bad MStatus, but we know for certain the value is bad, we should throw an exception ourselves to prevent the user from experiencing a crash.
