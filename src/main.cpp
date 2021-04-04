#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

// Types
#include <maya/MObjectHandle.h>
#include <maya/MVector.h>
#include <maya/MQuaternion.h>
#include <maya/MEulerRotation.h>
#include <maya/MMatrix.h>
#include <maya/MColor.h>
#include <maya/MPoint.h>
#include <maya/MTypeId.h>
#include <maya/MString.h>
#include <maya/MPlug.h>

// Function sets
#include <maya/MFnDependencyNode.h>

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)
#define CHECK_STATUS(status) if (!status) throw std::invalid_argument("Bad status")

namespace py = pybind11;

PYBIND11_MODULE(cmdc, m) {
    m.doc() = R"pbdoc(
        cmdc
        ----

        .. currentmodule:: cmdc

        .. autosummary::
           :toctree: _generate

    )pbdoc";

    #include "Types.inl"
    #include "Math.inl"
    #include "MFnDependencyNode.inl"
    #include "MPlug.inl"

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
