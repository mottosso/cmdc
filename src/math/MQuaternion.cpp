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

template <>
void init_class(py::class_<MQuaternion> &Quaternion) {
    Quaternion
        .def(py::init<>())
        .def(py::init<const double,
                    const double,
                    const double,
                    const double>(),
                    py::arg("x"),
                    py::arg("y"),
                    py::arg("z"),
                    py::arg("w"))
        .def(py::init<const MQuaternion&>(), py::arg("src"))
        .def(py::init<const MVector&, const MVector&, const double>(),
            py::arg("a"),
            py::arg("b"),
            py::arg("factor") = 1.0)
        .def(py::init<const double, const MVector>(),
            py::arg("angle"),
            py::arg("axis"))
        .def(py::init([](std::array<double, 4> seq) {
            return std::unique_ptr<MQuaternion>(new MQuaternion(seq[0], seq[1], seq[2], seq[3]));
        }), py::arg("seq"), "Create a new quaternion from a seqence of 4 floats")

        .def(py::self + MQuaternion(), py::arg("other"))
        .def(py::self - MQuaternion(), py::arg("other"))
        .def(py::self * MQuaternion(), py::arg("other"))
        .def(double() * py::self, py::arg("scale"))
        .def(py::self *= MQuaternion(), py::arg("other"))
        .def(py::self == MQuaternion(), py::arg("other"))
        .def(py::self != MQuaternion(), py::arg("other"))
        .def(-py::self)

        .def_readwrite("x", &MQuaternion::x)
        .def_readwrite("y", &MQuaternion::y)
        .def_readwrite("z", &MQuaternion::z)
        .def_readwrite("w", &MQuaternion::w)

        .def("asAxisAngle", [](const MQuaternion& self) -> std::pair<MVector, double> {
            MVector axis;
            double theta;
            self.getAxisAngle(axis, theta);

            return std::make_pair(axis, theta);
        }, "Returns the rotation as a tuple containing an axis vector and an angle in radians about that axis.")

        .def("asEulerRotation", &MQuaternion::asEulerRotation)
        .def("asMatrix", &MQuaternion::asMatrix)
        .def("conjugate", &MQuaternion::conjugate)
        .def("conjugateIt", &MQuaternion::conjugateIt)
        .def("exp", &MQuaternion::exp)
        .def("inverse", &MQuaternion::inverse)
        .def("invertIt", &MQuaternion::invertIt)
        .def("log", &MQuaternion::log)
        .def("isEquivalent", &MQuaternion::isEquivalent, py::arg("other"), py::arg("tol") = kQuaternionEpsilon)
        .def("negateIt", &MQuaternion::negateIt)
        .def("normal", &MQuaternion::normal)
        .def("normalizeIt", &MQuaternion::normalizeIt)
        .def("setToXAxis", &MQuaternion::setToXAxis, py::arg("angle"))
        .def("setToYAxis", &MQuaternion::setToYAxis, py::arg("angle"))
        .def("setToZAxis", &MQuaternion::setToZAxis, py::arg("angle"))
        .def("setValue", [](MQuaternion& self, const MQuaternion& quat) {
            self = quat;
        }, py::arg("quat"))

        .def("setValue", [](MQuaternion& self, const MEulerRotation& rot) {
            self = rot;
        }, py::arg("rot"))

        .def("setValue", [](MQuaternion& self, const MMatrix& matrix) {
            self = matrix;
        }, py::arg("matrix"))

        .def("setValue", [](MQuaternion& self, const MVector& axis, double angle) {
            self.setAxisAngle(axis, angle);
        }, py::arg("axis"), py::arg("angle"))

        .def_static("slerp", [](const MQuaternion& p, const MQuaternion& q, double t, short spin) {
            return slerp(p, q, t, spin);
        }, py::arg("p"), py::arg("q"), py::arg("t"), py::arg("spin"))

        .def_static("squad", [](const MQuaternion& p, const MQuaternion& a, const MQuaternion& b,
                                const MQuaternion& q, double t, short spin) {
            return squad(p, a, b, q, t, spin);

        }, py::arg("p"), py::arg("a"), py::arg("b"), py::arg("q"), py::arg("t"), py::arg("spin"))

        .def_static("squadPt", [](const MQuaternion& q0, const MQuaternion& q1, const MQuaternion& q2)	{
            return squadPt(q0, q1, q2);
        }, py::arg("q0"), py::arg("q1"), py::arg("q2"))

        .def("__len__", [](const MQuaternion &self) -> int {
            return 4;
        }, "Returns length of the quaternion, which is always 4.")

        .def("__repr__", [](const MQuaternion& q) {
            return "<cmdc.Quaternion( " +
                std::to_string(q.x) + ", " +
                std::to_string(q.y) + ", " +
                std::to_string(q.z) + ", " +
                std::to_string(q.w) + " )>";
        }
    );
}