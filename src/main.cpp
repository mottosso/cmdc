#include <pybind11/pybind11.h>

// Types
#include <maya/MAngle.h>
#include <maya/MColor.h>
#include <maya/MDagModifier.h>
#include <maya/MDagPath.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MDistance.h>
#include <maya/MDGModifier.h>
#include <maya/MEulerRotation.h>
#include <maya/MFn.h>
#include <maya/MIntArray.h>
#include <maya/MMatrix.h>
#include <maya/MNodeClass.h>
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
#include <maya/MBoundingBox.h>
#include <maya/MDagPathArray.h>  // MFnDagNode
#include <maya/MObjectArray.h>  // MFnDagNode

// Function sets
#include <maya/MFnDependencyNode.h>
#include <maya/MFnDagNode.h>
#include <maya/MFnTransform.h>

#include "init.h"

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;


PYBIND11_MODULE(cmdc, m) {
    m.doc() = R"pbdoc(
        cmdc
        ----

        .. currentmodule:: cmdc

        .. autosummary::
           :toctree: _generate

    )pbdoc";

    #include "ForwardDeclarations.inl"

    init_enum(fn_type);
    init_class(TypeId);
    init_class(Status);
    init_class(String);
    init_class(Space);
    init_class(Object);
    init_class(DagPath);
    init_class(Plug);
    init_class(BoundingBox);
    init_class(DGModifier);
    init_class(DagModifier);
    init_class(SelectionList);
    init_class(EulerRotation);
    init_class(Matrix);
    init_class(Point);
    init_class(Quaternion);
    init_class(TransformationMatrix);
    init_class(Vector);
    init_class(FnDagNode);
    init_class(FnDependencyNode);
    init_class(FnTransform);

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}