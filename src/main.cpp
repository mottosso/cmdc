#include <pybind11/pybind11.h>

// Types
#include <maya/MAngle.h>
#include <maya/MColor.h>
#include <maya/MDagPath.h> // MDAGDrawOverrideInfo
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MDistance.h>
#include <maya/MPxData.h>
#include <maya/MTime.h>
#include <maya/MUuid.h>
#include <maya/MDagPathArray.h>  // MFnDagNode
#include <maya/MObjectArray.h>
#include <maya/MNodeClass.h>

#include "fn/init.h"
#include "math/init.h"

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)
#define DECLARE_INIT(x) void init_##x(py::module_ &);
#define CALL_INIT(x) init_##x(m);

namespace py = pybind11;

// declare the init functions here that live in the cpp files
DECLARE_INIT(types)
DECLARE_INIT(MObject)
DECLARE_INIT(MBoundingBox)
DECLARE_INIT(MDagModifier)
DECLARE_INIT(MDGModifier)
DECLARE_INIT(MPlug)
DECLARE_INIT(MSelectionList)
DECLARE_INIT(MDagPath)


PYBIND11_MODULE(cmdc, m) {
    m.doc() = R"pbdoc(
        cmdc
        ----

        .. currentmodule:: cmdc

        .. autosummary::
           :toctree: _generate

    )pbdoc";

    #include "ForwardDeclarations.inl"

    CALL_INIT(types)
    CALL_INIT(MObject)
    CALL_INIT(MDagPath)
    CALL_INIT(MPlug)
    CALL_INIT(MBoundingBox)
    CALL_INIT(MDGModifier)
    CALL_INIT(MDagModifier)
    CALL_INIT(MSelectionList)
    CALL_INIT(math_classes)
    CALL_INIT(fn_classes)

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}