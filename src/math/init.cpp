#include "init.h"

void init_MEulerRotation(py::module_ &);
void init_MVector(py::module_ &);
void init_MPoint(py::module_ &);
void init_MMatrix(py::module_ &);
void init_MTransformationMatrix(py::module_ &);
void init_MQuaternion(py::module_ &);

void init_math_classes(py::module_ &m) {
    init_MVector(m);
    init_MPoint(m);
    init_MMatrix(m);
    init_MTransformationMatrix(m);
    init_MQuaternion(m);
    init_MEulerRotation(m);
}