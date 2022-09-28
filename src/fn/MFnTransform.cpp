#include <pybind11/pybind11.h>
#include <maya/MDagPath.h>
#include <maya/MObject.h>
#include <maya/MPlug.h>
#include <maya/MFnTransform.h>
#include <maya/MEulerRotation.h>
#include <maya/MQuaternion.h>
#include <maya/MMatrix.h>
#include <maya/MPoint.h>
#include <maya/MVector.h>

namespace py = pybind11;

#define _doc_FnTransform_create \
    "Creates a new transform node and attaches it to the function set."

#define _doc_FnTransform_transformation \
    "Returns the transformation matrix represented by this transform."

#define _doc_FnTransform_setTranslation \
    "Sets the transform's translation."

#define _doc_FnTransform_translateBy \
    "Adds an MVector to the transform's translation."

#define _doc_FnTransform_setScale \
    "Sets the transform's scale components."

#define _doc_FnTransform_scaleBy \
    "Multiplies the transform's XYZ scale components by a sequence of three floats."

#define _doc_FnTransform_scalePivot \
    "Returns the transform's scale pivot."

#define _doc_FnTransform_setScalePivot \
    "Sets the transform's scale pivot."

#define _doc_FnTransform_scalePivotTranslation \
    "Returns the transform's scale pivot translation."

#define _doc_FnTransform_setScalePivotTranslation \
    "Sets the transform's scale pivot translation."

#define _doc_FnTransform_setShear \
    "Sets the transform's shear."

#define _doc_FnTransform_shearBy \
    "Multiplies the transform's shear components by a sequence of three floats."

#define _doc_FnTransform_setRotation \
    "Sets the transform's rotation using an MEulerRotation or MQuaternion."

#define _doc_FnTransform_rotateBy \
    "Adds an MEulerRotation or MQuaternion to the transform's rotation."

#define _doc_FnTransform_rotatePivot \
    "Returns the transform's rotate pivot."

#define _doc_FnTransform_setRotatePivot \
    "Sets the transform's rotate pivot."

#define _doc_FnTransform_rotatePivotTranslation \
    "Returns the transform's rotate pivot translation."

#define _doc_FnTransform_setRotatePivotTranslation \
    "Sets the transform's rotate pivot translation."

#define _doc_FnTransform_rotateOrientation \
    "Returns the MQuaternion which orients the local rotation space."

#define _doc_FnTransform_setRotateOrientation \
    "Sets the MQuaternion which orients the local rotation space."

#define _doc_FnTransform_rotationOrder \
    "Returns the order of rotations when the transform's rotation is expressed as an MEulerRotation."

#define _doc_FnTransform_setRotationOrder \
    "Sets the transform's rotation order."

#define _doc_FnTransform_restPosition \
    "Returns the transform's rest position matrix."

#define _doc_FnTransform_setRestPosition \
    "Sets the transform's rest position matrix."

#define _doc_FnTransform_resetFromRestPosition \
    "Resets the transform from its rest position matrix."

#define _doc_FnTransform_clearRestPosition \
    "Clears the transform's rest position matrix."

#define _doc_FnTransform_isLimited \
    "Returns True if the specified limit type is enabled."

#define _doc_FnTransform_limitValue \
    "Returns the value of the specified limit."

#define _doc_FnTransform_setLimit \
    "Sets the value of the specified limit."

#define _doc_FnTransform_enableLimit \
    "Enables or disables a specified limit type."

void init_MFnTransform(py::module_ &m) {
    py::class_<MFnTransform, MFnDagNode> FnTransform(m, "FnTransform");

    py::enum_<MFnTransform::LimitType>(FnTransform, "LimitType")
        .value("kScaleMinX", MFnTransform::kScaleMinX)
        .value("kScaleMaxX", MFnTransform::kScaleMaxX)
        .value("kScaleMinY", MFnTransform::kScaleMinY)
        .value("kScaleMaxY", MFnTransform::kScaleMaxY)
        .value("kScaleMinZ", MFnTransform::kScaleMinZ)
        .value("kScaleMaxZ", MFnTransform::kScaleMaxZ)

        .value("kShearMinXY", MFnTransform::kShearMinXY)
        .value("kShearMaxXY", MFnTransform::kShearMaxXY)
        .value("kShearMinXZ", MFnTransform::kShearMinXZ)
        .value("kShearMaxXZ", MFnTransform::kShearMaxXZ)
        .value("kShearMinYZ", MFnTransform::kShearMinYZ)
        .value("kShearMaxYZ", MFnTransform::kShearMaxYZ)

        .value("kRotateMinX", MFnTransform::kRotateMinX)
        .value("kRotateMaxX", MFnTransform::kRotateMaxX)
        .value("kRotateMinY", MFnTransform::kRotateMinY)
        .value("kRotateMaxY", MFnTransform::kRotateMaxY)
        .value("kRotateMinZ", MFnTransform::kRotateMinZ)
        .value("kRotateMaxZ", MFnTransform::kRotateMaxZ)

        .value("kTranslateMinX", MFnTransform::kTranslateMinX)
        .value("kTranslateMaxX", MFnTransform::kTranslateMaxX)
        .value("kTranslateMinY", MFnTransform::kTranslateMinY)
        .value("kTranslateMaxY", MFnTransform::kTranslateMaxY)
        .value("kTranslateMinZ", MFnTransform::kTranslateMinZ)
        .value("kTranslateMaxZ", MFnTransform::kTranslateMaxZ)
        .export_values();

    FnTransform
        .def(py::init<>())

        .def(py::init([](MObject& object) {
            MStatus status;
            auto result = std::unique_ptr<MFnTransform>(new MFnTransform(object, &status));

            if (!status) {
                throw std::runtime_error(
                    "Invalid parameter passed for object - "
                    "not a Transform Node, "
                    "Node does not exist or "
                    "no valid pointer to Node"
                );
            }

            return result;
        }), py::arg("object"))

        .def(py::init([](MDagPath& dagPath) {
            MStatus status;
            auto result = std::unique_ptr<MFnTransform>(new MFnTransform(dagPath, &status));

            if (!status) {
                throw std::runtime_error(
                    "Invalid parameter passed for object - "
                    "not a Transform Node, "
                    "Node does not exist or "
                    "no valid pointer to Node"
                );
            }

            return result;
        }), py::arg("dagPath"))

        .def("clearRestPosition", [](MFnTransform & self) {
            MStatus status = self.clearRestPosition();

            if (!status) {
                throw std::logic_error(status.errorString().asChar());
            }
        }, _doc_FnTransform_clearRestPosition)

        .def("create", [](MFnTransform & self, MObject parent = MObject::kNullObj) -> MObject {
            MStatus status;
            MObject transform = self.create(parent, &status);

            if (!status) {
                throw std::runtime_error(status.errorString().asChar());
            }

            return transform;
        }, py::arg_v("parent", MObject::kNullObj, "Object.kNullObj"), _doc_FnTransform_create)

        .def("enableLimit", [](MFnTransform & self, MFnTransform::LimitType limitType, bool enable) {
            MStatus status = self.enableLimit(limitType, enable);

            if (!status) {
                throw std::logic_error(status.errorString().asChar());
            }
        }, py::arg("limitType"), py::arg("enable"), _doc_FnTransform_enableLimit)

        .def("isLimited", [](MFnTransform & self, MFnTransform::LimitType limitType) -> bool {
            MStatus status;
            bool result = self.isLimited(limitType, &status);

            if (!status) {
                throw std::logic_error(status.errorString().asChar());
            }

            return result;
        }, py::arg("limitType"), _doc_FnTransform_isLimited)

        .def("limitValue", [](MFnTransform & self, MFnTransform::LimitType limitType) -> double {
            MStatus status;
            double limit = self.limitValue(limitType, &status);

            if (!status) {
                throw std::logic_error(status.errorString().asChar());
            }
            
            return limit;
        }, py::arg("limitType"), _doc_FnTransform_limitValue)

        .def("resetFromRestPosition", [](MFnTransform & self) {
            MStatus status = self.resetFromRestPosition();

            if (!status) {
                throw std::logic_error(status.errorString().asChar());
            }
        }, _doc_FnTransform_resetFromRestPosition)

        .def("restPosition", [](MFnTransform & self) -> MTransformationMatrix {
            MStatus status;
            MTransformationMatrix matrix = self.restPosition(&status);

            if (! status) {
                throw std::logic_error(status.errorString().asChar());
            }

            return matrix;
        }, _doc_FnTransform_restPosition)

        .def("rotateBy", [](MFnTransform & self, MEulerRotation rotation, MSpace::Space space = MSpace::kTransform) {
            MStatus status = self.rotateBy(rotation, space);

            if (! status) {
                throw std::logic_error(status.errorString().asChar());
            }
        }, py::arg("rotation"), py::arg("space") = MSpace::kTransform, _doc_FnTransform_rotateBy)

        .def("rotateBy", [](MFnTransform & self, MQuaternion quaternion, MSpace::Space space = MSpace::kTransform) {
            MStatus status = self.rotateBy(quaternion, space);

            if (! status) {
                throw std::logic_error(status.errorString().asChar());
            }
        }, py::arg("quaternion"), py::arg("space") = MSpace::kTransform, _doc_FnTransform_rotateBy)

        .def("rotateBy", [](MFnTransform & self, const py::list & rotation, MTransformationMatrix::RotationOrder order, MSpace::Space space = MSpace::kTransform) {
            if (rotation.size() != 3)
            {
                throw std::invalid_argument("You must provide a list of 3 floats for rotate.");
            }
            double tmp[3];
            std::transform(std::begin(rotation), std::end(rotation), std::begin(tmp),
                    [](pybind11::handle handle) -> double { return handle.cast<double>(); });
            
            MStatus status = self.rotateBy(tmp, order, space);

            if (! status) {
                throw std::logic_error(status.errorString().asChar());
            }
        }, py::arg("rotation"), py::arg("order"), py::arg("space") = MSpace::kTransform, _doc_FnTransform_rotateBy)

        .def("rotateOrientation", [](MFnTransform & self, MSpace::Space space) -> MQuaternion {
            MStatus status;
            MQuaternion orient = self.rotateOrientation(space, &status);

            if (!status) {
                throw std::logic_error(status.errorString().asChar());
            }

            return orient;
        }, py::arg("space"), _doc_FnTransform_rotateOrientation)

        .def("rotatePivot", [](MFnTransform & self, MSpace::Space space) -> MPoint {
            MStatus status;
            MPoint pivot = self.rotatePivot(space, &status);

            if (!status) {
                throw std::logic_error(status.errorString().asChar());
            }

            return pivot;
        }, py::arg("space"), _doc_FnTransform_rotatePivot)

        .def("rotatePivotTranslation", [](MFnTransform & self, MSpace::Space space) -> MVector {
            MStatus status;
            MVector pivot = self.rotatePivotTranslation(space, &status);

            if (!status) {
                throw std::logic_error(status.errorString().asChar());
            }

            return pivot;
        }, py::arg("space"), _doc_FnTransform_rotatePivotTranslation)

        .def_property_readonly("rotationOrder", [](MFnTransform & self) -> MTransformationMatrix::RotationOrder {
            MStatus status;
            auto result = self.rotationOrder(&status);

            if (!status) {
                throw std::logic_error(status.errorString().asChar());
            }

            return result;
        }, _doc_FnTransform_rotationOrder)

        .def("scaleBy", [](MFnTransform & self, const py::list & scale) {
            if (scale.size() != 3)
            {
                throw std::invalid_argument("You must provide a list of 3 floats for scale.");
            }
            double tmp[3];
            std::transform(std::begin(scale), std::end(scale), std::begin(tmp),
                    [](pybind11::handle handle) -> double { return handle.cast<double>(); });
            
            MStatus status = self.scaleBy(tmp);

            if (! status) {
                throw std::logic_error(status.errorString().asChar());
            }
        }, py::arg("scale"), _doc_FnTransform_scaleBy)

        .def("scalePivot", [](MFnTransform & self, MSpace::Space space) -> MPoint {
            MStatus status;
            MPoint pivot = self.scalePivot(space, &status);

            if (!status) {
                throw std::logic_error(status.errorString().asChar());
            }

            return pivot;
        }, py::arg("space"), _doc_FnTransform_scalePivot)

        .def("scalePivotTranslation", [](MFnTransform & self, MSpace::Space space) -> MVector {
            MStatus status;
            MVector pivot = self.scalePivotTranslation(space, &status);

            if (!status) {
                throw std::logic_error(status.errorString().asChar());
            }

            return pivot;
        }, py::arg("space"), _doc_FnTransform_scalePivotTranslation)

        .def("setLimit", [](MFnTransform & self, MFnTransform::LimitType limitType, double value) {
            MStatus status = self.setLimit(limitType, value);

            if (!status) {
                throw std::logic_error(status.errorString().asChar());
            }
        }, py::arg("limitType"), py::arg("value"), _doc_FnTransform_setLimit)

        .def("setRestPosition", [](MFnTransform & self, const MTransformationMatrix & matrix) {
            MStatus status = self.setRestPosition(matrix);

            if (!status) {
                throw std::logic_error(status.errorString().asChar());
            }
        }, py::arg("matrix"), _doc_FnTransform_setRestPosition)

        .def("setRotateOrientation", [](MFnTransform & self, const MQuaternion& quat, MSpace::Space space, bool balance) {
            MStatus status = self.setRotateOrientation(quat, space, balance);

            if (!status) {
                throw std::logic_error(status.errorString().asChar());
            }
        }, py::arg("quat"), py::arg("space"), py::arg("balance"), _doc_FnTransform_setRotateOrientation)

        .def("setRotatePivot", [](MFnTransform & self, const MPoint& point, MSpace::Space space, bool balance) {
            MStatus status = self.setRotatePivot(point, space, balance);

            if (!status) {
                throw std::logic_error(status.errorString().asChar());
            }
        }, py::arg("point"), py::arg("space"), py::arg("balance"), _doc_FnTransform_setRotatePivot)

        .def("setRotatePivotTranslation", [](MFnTransform & self, const MVector & vec, MSpace::Space space) {
            MStatus status = self.setRotatePivotTranslation(vec, space);

            if (!status) {
                throw std::logic_error(status.errorString().asChar());
            }
        }, py::arg("vec"), py::arg("space"), _doc_FnTransform_setRotatePivotTranslation)

        .def("setRotation", [](MFnTransform & self, MEulerRotation rotation) {
            MStatus status = self.setRotation(rotation);

            if (!status) {
                throw std::logic_error(status.errorString().asChar());
            }
        }, py::arg("rotation"), _doc_FnTransform_setRotation)

        .def("setRotation", [](MFnTransform & self, MQuaternion quaternion, MSpace::Space space = MSpace::kTransform) {
            MStatus status = self.setRotation(quaternion, space);

            if (!status) {
                throw std::logic_error(status.errorString().asChar());
            }
        }, py::arg("quaternion"), py::arg("space") = MSpace::kTransform, _doc_FnTransform_setRotation)

        .def("setRotation", [](MFnTransform & self, const py::list & rotation, MTransformationMatrix::RotationOrder order) {
            if (rotation.size() != 3)
            {
                throw std::invalid_argument("You must provide a list of 3 floats for rotation.");
            }
            double tmp[3];
            std::transform(std::begin(rotation), std::end(rotation), std::begin(tmp),
                    [](pybind11::handle handle) -> double { return handle.cast<double>(); });

            MStatus status = self.setRotation(tmp);

            if (!status) {
                throw std::logic_error(status.errorString().asChar());
            }
        }, py::arg("rotation"), py::arg("order"), _doc_FnTransform_setRotation)

        .def("setRotationOrder", [](MFnTransform & self, MTransformationMatrix::RotationOrder order, bool reorder) {
            MStatus status = self.setRotationOrder(order, reorder);

            if (!status) {
                throw std::logic_error(status.errorString().asChar());
            }
        }, py::arg("order"), py::arg("reorder"), _doc_FnTransform_setRotationOrder)

        .def("setScale", [](MFnTransform & self, const py::list & scale) {
            if (scale.size() != 3)
            {
                throw std::invalid_argument("You must provide a list of 3 floats for scale.");
            }
            double tmp[3];
            std::transform(std::begin(scale), std::end(scale), std::begin(tmp),
                    [](pybind11::handle handle) -> double { return handle.cast<double>(); });

            MStatus status = self.setScale(tmp);

            if (!status) {
                throw std::logic_error(status.errorString().asChar());
            }
        }, py::arg("scale"), _doc_FnTransform_setScale)

        .def("setScalePivot", [](MFnTransform & self, const MPoint & point, MSpace::Space space, bool balance) {
            MStatus status = self.setScalePivot(point, space, balance);

            if (!status) {
                throw std::logic_error(status.errorString().asChar());
            }
        }, py::arg("point"), py::arg("space"), py::arg("balance"), _doc_FnTransform_setScalePivot)

        .def("setScalePivotTranslation", [](MFnTransform & self, const MVector & vec, MSpace::Space space) {
            MStatus status = self.setScalePivotTranslation(vec, space);

            if (!status) {
                throw std::logic_error(status.errorString().asChar());
            }
        }, py::arg("vec"), py::arg("space"), _doc_FnTransform_setScalePivotTranslation)

        .def("setShear", [](MFnTransform & self, const py::list & shear) {
            if (shear.size() != 3)
            {
                throw std::invalid_argument("You must provide a list of 3 floats for shear.");
            }
            double tmp[3];
            std::transform(std::begin(shear), std::end(shear), std::begin(tmp),
                    [](pybind11::handle handle) -> double { return handle.cast<double>(); });

            MStatus status = self.setShear(tmp);

            if (!status) {
                throw std::logic_error(status.errorString().asChar());
            }
        }, py::arg("shear"), _doc_FnTransform_setShear)

        .def("setTranslation", [](MFnTransform & self, const MVector & vec, MSpace::Space space) {
            MStatus status = self.setTranslation(vec, space);

            if (!status) {
                throw std::logic_error(status.errorString().asChar());
            }
        }, py::arg("vec"), py::arg("space"), _doc_FnTransform_setTranslation)

        .def("shearBy", [](MFnTransform & self, const py::list & shear) {
            if (shear.size() != 3)
            {
                throw std::invalid_argument("You must provide a list of 3 floats for shear.");
            }
            double tmp[3];
            std::transform(std::begin(shear), std::end(shear), std::begin(tmp),
                    [](pybind11::handle handle) -> double { return handle.cast<double>(); });

            MStatus status = self.shearBy(tmp);

            if (!status) {
                throw std::logic_error(status.errorString().asChar());
            }
        }, py::arg("shear"), _doc_FnTransform_shearBy)

        .def_property_readonly("transformation", [](MFnTransform & self) -> MTransformationMatrix {
            MStatus status;
            MTransformationMatrix matrix = self.transformation(&status);

            if (!status) {
                throw std::logic_error(status.errorString().asChar());
            }
            
            return matrix;
        }, _doc_FnTransform_transformation)

        .def("translateBy", [](MFnTransform & self, const MVector & vec, MSpace::Space space) {
            MStatus status = self.translateBy(vec, space);

            if (!status) {
                throw std::logic_error(status.errorString().asChar());
            }
        }, py::arg("vec"), py::arg("space"), _doc_FnTransform_translateBy);
}