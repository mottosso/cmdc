### Bullet Points

- No returning of MStatus, instead throw an exception

<br>

### Style Guide

- [80 character line width](#80-characters-wide)
- [Formatting](formatting)

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