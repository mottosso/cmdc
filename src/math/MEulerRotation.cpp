#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <maya/MVector.h>
#include <maya/MPoint.h>
#include <maya/MQuaternion.h>
#include <maya/MEulerRotation.h>
#include <maya/MMatrix.h>
#include "../init.h"

namespace py = pybind11;

#define _doc_EulerRotation_setValue \
    "Set the rotation."

#define _doc_EulerRotation_asQuaternion \
    "Returns the rotation as an equivalent quaternion."

#define _doc_EulerRotation_asMatrix \
    "Returns the rotation as an equivalent matrix."

#define _doc_EulerRotation_asVector \
    "Returns the X, Y and Z rotations as a vector."

#define _doc_EulerRotation_isEquivalent \
    "Returns true if this rotation has the same order as another and their X, Y and Z components are within a tolerance of each other."

#define _doc_EulerRotation_isZero \
    "Returns true if the X, Y and Z components are each within a tolerance of 0.0."

#define _doc_EulerRotation_incrementalRotateBy \
    "Increase this rotation by a given angle around the specified axis. The update is done in series of small increments to avoid flipping."

#define _doc_EulerRotation_inverse \
    "Returns a new MEulerRotation containing the inverse rotation of this one and reversed rotation order."

#define _doc_EulerRotation_invertIt \
    "In-place inversion of the rotation. Rotation order is also reversed."

#define _doc_EulerRotation_reorder \
    "Returns a new MEulerRotation having this rotation, reordered to use the given rotation order."

#define _doc_EulerRotation_reorderIt \
    "In-place reordering to use the given rotation order."

#define _doc_EulerRotation_bound \
    "Returns a new MEulerRotation having this rotation, but with each rotation component bound within +/- PI."

#define _doc_EulerRotation_boundIt \
    "In-place bounding of each rotation component to lie wthin +/- PI."

#define _doc_EulerRotation_alternateSolution \
    "Returns an equivalent rotation which is not simply a multiple."

#define _doc_EulerRotation_setToAlternateSolution \
    "Replace this rotation with an alternate solution."

#define _doc_EulerRotation_closestSolution \
    "Returns the equivalent rotation which comes closest to a target."

#define _doc_EulerRotation_setToClosestSolution \
    "Replace this rotation with the closest solution to a target."

#define _doc_EulerRotation_closestCut \
    "Returns the rotation which is full spin multiples of this one and comes closest to target."

#define _doc_EulerRotation_setToClosestCut \
    "Replace this rotation with the closest cut to a target."

#define _doc_EulerRotation_decompose \
    "Extracts a rotation from a matrix."

template <>
void init_class(py::class_<MEulerRotation> &EulerRotation) {
    py::enum_<MEulerRotation::RotationOrder>(EulerRotation, "RotationOrder")
        .value("kXYZ", MEulerRotation::RotationOrder::kXYZ)
        .value("kYZX", MEulerRotation::RotationOrder::kYZX)
        .value("kZXY", MEulerRotation::RotationOrder::kZXY)
        .value("kXZY", MEulerRotation::RotationOrder::kXZY)
        .value("kYXZ", MEulerRotation::RotationOrder::kYXZ)
        .value("kZYX", MEulerRotation::RotationOrder::kZYX)
        .export_values();

    EulerRotation
        .def(py::init<>())
        .def(py::init<const MEulerRotation&>(), py::arg("src"))
        .def(py::init<const MVector&, MEulerRotation::RotationOrder>(),
            py::arg("vec"), py::arg("order") = MEulerRotation::kXYZ)
        .def(py::init<double, double, double, MEulerRotation::RotationOrder>(),
        py::arg("x"), py::arg("y"), py::arg("x"), py::arg("order") = MEulerRotation::kXYZ)
        .def(py::init([](std::array<double, 3> seq, MEulerRotation::RotationOrder order)
            {
                return std::unique_ptr<MEulerRotation>(new MEulerRotation(seq[0], seq[1], seq[2], order));
            }
            ), py::arg("seq"), py::arg("order") = MEulerRotation::kXYZ)

        .def_readwrite("x", &MEulerRotation::x)
        .def_readwrite("y", &MEulerRotation::y)
        .def_readwrite("z", &MEulerRotation::z)
        .def_readwrite("order", &MEulerRotation::order)

        .def(py::self + MEulerRotation(), py::arg("other"))
        .def(py::self - MEulerRotation(), py::arg("other"))
        .def(py::self * MEulerRotation(), py::arg("other"))
        .def(py::self *= MEulerRotation(), py::arg("other"))
        .def(py::self * MQuaternion(), py::arg("other"))
        .def(py::self *= MQuaternion(), py::arg("other"))
        .def(py::self * double(), py::arg("other"))
        .def(py::self *= double(), py::arg("other"))
        .def(py::self == MEulerRotation(), py::arg("other"))
        .def(py::self != MEulerRotation(), py::arg("other"))
        .def(-py::self)

        .def("__repr__", [](const MEulerRotation &a) {
            return "<cmdc.EulerRotation( " +
                std::to_string(a.x) + ", " +
                std::to_string(a.y) + ", " +
                std::to_string(a.z) + ", " +
                std::to_string(a.order) + " )>";
                }
            )

        .def("alternateSolution", [](const MEulerRotation& self) {
            return self.alternateSolution();
        }, _doc_EulerRotation_alternateSolution)

        .def("asMatrix", &MEulerRotation::asMatrix, _doc_EulerRotation_asMatrix)

        .def("asQuaternion", &MEulerRotation::asQuaternion, _doc_EulerRotation_asQuaternion)

        .def("asVector", &MEulerRotation::asVector, _doc_EulerRotation_asVector)

        .def("bound", [](const MEulerRotation& self) {
            return self.bound();
        }, _doc_EulerRotation_bound)

        .def("boundIt", [](MEulerRotation & self) -> MEulerRotation& {
            return self.boundIt();
        }, _doc_EulerRotation_boundIt)

        .def("boundIt", [](MEulerRotation & self, MEulerRotation src) -> MEulerRotation& {
            return self.boundIt(src);
        }, py::arg("src"), _doc_EulerRotation_boundIt)

        .def("closestCut", [](MEulerRotation & self, MEulerRotation target) -> MEulerRotation {
            return self.closestCut(target);
        }, py::arg("target"), _doc_EulerRotation_closestCut)

        .def("closestSolution", [](MEulerRotation & self, MEulerRotation target) -> MEulerRotation {
            return self.closestSolution(target);
        }, py::arg("dst"), _doc_EulerRotation_closestSolution)

        .def_static("decompose", &MEulerRotation::decompose,
            py::arg("matrix"), py::arg("ord"), _doc_EulerRotation_decompose)

        .def("incrementalRotateBy", &MEulerRotation::incrementalRotateBy,
            py::arg("axis"), py::arg("angle"), _doc_EulerRotation_incrementalRotateBy)

        .def("inverse", [](MEulerRotation & self) -> MEulerRotation {
            return self.inverse();
        }, _doc_EulerRotation_inverse)

        .def("invertIt", &MEulerRotation::invertIt, _doc_EulerRotation_invertIt)

        .def("isEquivalent", [](MEulerRotation & self, MEulerRotation other, double tolerance = kEulerRotationEpsilon) -> bool {
            return self.isEquivalent(other, tolerance);
        }, py::arg("other"), py::arg("tolerance") = kEulerRotationEpsilon, _doc_EulerRotation_isEquivalent)

        .def("isZero", [](MEulerRotation & self, double tolerance = kEulerRotationEpsilon) -> bool {
            return self.isZero(tolerance);
        }, py::arg("tolerance") = kEulerRotationEpsilon, _doc_EulerRotation_isZero)

        .def("reorder", [](MEulerRotation & self, MEulerRotation::RotationOrder order) -> MEulerRotation {
            return self.reorder(order);
        }, py::arg("order"), _doc_EulerRotation_reorder)

        .def("reorderIt", [](MEulerRotation & self, MEulerRotation::RotationOrder order) -> MEulerRotation& {
            return self.reorderIt(order);
        }, py::arg("order"), _doc_EulerRotation_reorderIt)

        .def("setToAlternateSolution", [](MEulerRotation & self) -> MEulerRotation& {
            return self.setToAlternateSolution();
        }, _doc_EulerRotation_setToAlternateSolution)

        .def("setToAlternateSolution", [](MEulerRotation & self, MEulerRotation rot) -> MEulerRotation& {
            return self.setToAlternateSolution(rot);
        }, py::arg("rot"), _doc_EulerRotation_setToAlternateSolution)

        .def("setToClosestCut", [](MEulerRotation & self, MEulerRotation target) -> MEulerRotation& {
            return self.setToClosestCut(target);
        }, py::arg("target"), _doc_EulerRotation_setToClosestCut)

        .def("setToClosestCut", [](MEulerRotation & self, MEulerRotation src, MEulerRotation target) -> MEulerRotation& {
            return self.setToClosestCut(src, target);
        }, py::arg("src"), py::arg("target"), _doc_EulerRotation_setToClosestCut)

        .def("setToClosestSolution", [](MEulerRotation & self, MEulerRotation target) -> MEulerRotation& {
            return self.setToClosestSolution(target);
        }, py::arg("target"), _doc_EulerRotation_setToClosestSolution)

        .def("setToClosestSolution", [](MEulerRotation & self, MEulerRotation src, MEulerRotation target) -> MEulerRotation& {
            return self.setToClosestSolution(src, target);
        }, py::arg("src"), py::arg("target"), _doc_EulerRotation_setToClosestSolution)

        .def("setValue", [](MEulerRotation & self, const MEulerRotation & rot) -> MEulerRotation& {
            return self.setValue(rot.x, rot.y, rot.z, rot.order);
        }, py::arg("rot"), _doc_EulerRotation_setValue)

        .def("setValue", [](MEulerRotation & self, MVector vec, MEulerRotation::RotationOrder order = MEulerRotation::kXYZ) -> MEulerRotation& {
            return self.setValue(vec, order);
        }, py::arg("v"), py::arg("order") = MEulerRotation::kXYZ, _doc_EulerRotation_setValue)

        .def("setValue", [](MEulerRotation & self, double xx, double yy, double zz, MEulerRotation::RotationOrder order = MEulerRotation::kXYZ) -> MEulerRotation& {
            return self.setValue(xx, yy, zz, order);
        }, py::arg("xx"), py::arg("yy"), py::arg("zz"), py::arg("order") = MEulerRotation::kXYZ, _doc_EulerRotation_setValue);
}