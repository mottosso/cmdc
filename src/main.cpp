#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

// Types
#include <maya/MAngle.h>
#include <maya/MColor.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MDistance.h>
#include <maya/MDagPath.h>
#include <maya/MEulerRotation.h>
#include <maya/MFn.h>
#include <maya/MIntArray.h>
#include <maya/MMatrix.h>
#include <maya/MObjectHandle.h>
#include <maya/MPoint.h>
#include <maya/MPlug.h>
#include <maya/MPlugArray.h>
#include <maya/MPxData.h>
#include <maya/MQuaternion.h>
#include <maya/MSelectionList.h>
#include <maya/MString.h>
#include <maya/MStringArray.h>
#include <maya/MTime.h>
#include <maya/MTypeId.h>
#include <maya/MVector.h>
#include <maya/MUuid.h>

// Function sets
#include <maya/MFnDependencyNode.h>

#include "util/atov.hpp"

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

    #include "Math.inl"
    #include "MDagPath.inl"
    #include "MFn.inl"
    #include "MFnDependencyNode.inl"
    #include "MObject.inl"
    #include "MPlug.inl"
    #include "MSelectionList.inl"
    #include "Types.inl"

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}