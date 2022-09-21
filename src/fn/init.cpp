
#include "init.h"

void init_MFnDependencyNode(py::module_ &);
void init_MFnDagNode(py::module_ &);
void init_MFnTransform(py::module_ &);

void init_fn_classes(py::module_ &m) {
    init_MFnDependencyNode(m);
    init_MFnDagNode(m);
    init_MFnTransform(m);
}