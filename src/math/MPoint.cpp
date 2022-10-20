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
void init_class(py::class_<MPoint> &Point) {
    Point
        .def(py::init<>())
        .def(py::init<double, double, double, double>(),
            py::arg("x"), py::arg("y"), py::arg("z") = 0.0, py::arg("w") = 1.0)
        .def(py::init<const MPoint &>(), py::arg("src"))
        .def(py::init<const MVector &>(), py::arg("src"))
        .def(py::init([](std::array<double, 4> seq) {
            return std::unique_ptr<MPoint>(new MPoint(seq[0], seq[1], seq[2], seq[3]));
        }), py::arg("seq"), "Create a new point from a seqence of 4 floats.")
        .def(py::init([](std::array<double, 3> seq) {
            return std::unique_ptr<MPoint>(new MPoint(seq[0], seq[1], seq[2]));
        }), py::arg("seq"), "Create a new point from a seqence of 3 floats.`w` will be set to 1.0")
        .def(py::init([](std::array<double, 2> seq) {
            return std::unique_ptr<MPoint>(new MPoint(seq[0], seq[1]));
        }), py::arg("seq"), "Create a new point from a seqence of 2 floats. `z` will be set to 0.0 and `w` will be set to 1.0")

        .def_readwrite("x", &MPoint::x)
        .def_readwrite("y", &MPoint::y)
        .def_readwrite("z", &MPoint::z)
        .def_readwrite("w", &MPoint::w)

        .def(py::self + MVector(), py::arg("other"))
        .def(py::self - MVector(), py::arg("other"))
        .def(py::self - py::self, py::arg("other"))
        .def(py::self += MVector(), py::arg("other"))
        .def(py::self -= MVector(), py::arg("other"))
        .def(py::self *= double(), py::arg("other"))
        .def(py::self * double(), py::arg("other"))
        .def(py::self * MMatrix(), py::arg("other"))
        .def(py::self *= MMatrix(), py::arg("other"))
        .def(py::self / double(), py::arg("other"))
        .def(py::self == py::self, py::arg("other"))
        .def(py::self != py::self, py::arg("other"))

        .def("cartesianize", &MPoint::cartesianize)
        .def("rationalize", &MPoint::rationalize)
        .def("homogenize", &MPoint::homogenize)
        .def("distanceTo", &MPoint::distanceTo, py::arg("other"))
        .def("isEquivalent", &MPoint::isEquivalent, py::arg("other"), py::arg("tol") = MPoint_kTol)

        .def_property_readonly_static("origin", [](py::object) { return MPoint::origin; },
            "The point <0,0,0,1>")

        .def("__len__", [](const MPoint &self) -> int {
            return 4;
        }, "Returns length of the point, which is always 4.")

        // Support print()
        .def("__repr__", [](const MPoint &a) {
            return "<cmdc.Point( " +
                std::to_string(a.x) + ", " +
                std::to_string(a.y) + ", " +
                std::to_string(a.z) + ", " +
                std::to_string(a.w) + " )>";
        }
    );
}