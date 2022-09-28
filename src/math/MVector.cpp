#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <maya/MVector.h>
#include <maya/MPoint.h>
#include <maya/MQuaternion.h>
#include <maya/MEulerRotation.h>
#include <maya/MMatrix.h>

namespace py = pybind11;

void init_MVector(py::module_ &m) {
    py::class_<MVector> Vector(m, "Vector");

    Vector
        .def(py::init<>())
        .def(py::init<const double,
                    const double,
                    const double>(),
                    py::arg("x"),
                    py::arg("y"),
                    py::arg("z") = 0.0)
        .def(py::init<const MVector &>(), py::arg("src"))
        .def(py::init<const MPoint &>(), py::arg("src"))
        .def(py::init([](std::array<double, 3> seq) {
            return std::unique_ptr<MVector>(new MVector(seq[0], seq[1], seq[2]));
        }), py::arg("seq"), "Create a new vector from a seqence of 3 floats")
        .def(py::init([](std::array<double, 2> seq) {
            return std::unique_ptr<MVector>(new MVector(seq[0], seq[1]));
        }), py::arg("seq"), "Create a new vector from a seqence of 2 floats")

        .def_readwrite("x", &MVector::x)
        .def_readwrite("y", &MVector::y)
        .def_readwrite("z", &MVector::z)

        .def(py::self + py::self, py::arg("other"))
        .def(py::self - py::self, py::arg("other"))
        .def(py::self += py::self, py::arg("other"))
        .def(py::self -= py::self, py::arg("other"))
        .def(py::self *= double(), py::arg("other"))
        .def(py::self *= MMatrix(), py::arg("other"))
        .def(py::self /= double(), py::arg("other"))
        .def(py::self * double(), py::arg("other"))
        .def(py::self * MMatrix(), py::arg("other"))
        .def(py::self * py::self, py::arg("other"))
        .def(py::self / double(), py::arg("other"))
        .def(py::self == py::self, py::arg("other"))
        .def(py::self != py::self, py::arg("other"))
        .def(py::self ^ py::self, py::arg("other"))
        .def(-py::self)

        .def("angle", &MVector::angle, py::arg("other"),
            "Returns the angle, in radians, between this vector and another.")

        .def("isEquivalent", &MVector::isEquivalent, py::arg("other"), py::arg("tolerance"),
            "Returns True if this vector and another are within a given tolerance of being equal.")

        .def("isParallel", &MVector::isParallel,
            py::arg("other"), py::arg("tolerance"),
            "Returns True if this vector and another are within the given tolerance of being parallel.")

        .def("length", &MVector::length,
            "Returns the magnitude of this vector.")

        .def("normal", &MVector::normal,
            "Returns a new vector containing the normalized version of this one.")

        .def("normalize", &MVector::normalize,
            "Normalizes this vector in-place and returns a new reference to it.")

        .def("rotateBy", [](const MVector &self, const MQuaternion& rot){
            return self.rotateBy(rot);
        }, py::arg("rot"), "Returns the vector resulting from rotating this one by the given amount.")

        .def("rotateBy", [](const MVector &self, const MEulerRotation& rot){
            return self.rotateBy(rot);
        }, py::arg("rot"), "Returns the vector resulting from rotating this one by the given amount.")

        .def("rotateTo", &MVector::rotateTo, py::arg("target"),
            "Returns the quaternion which will rotate this vector into another.")

        .def("transformAsNormal", &MVector::transformAsNormal, py::arg("matrix"),
            "Returns a new vector which is calculated by postmultiplying this vector by the transpose of the given matrix's inverse and then normalizing the result.")

        .def_property_readonly_static("oneVector", [](py::object) { return MVector::one; },
            "The vector <1,1,1>")

        .def_property_readonly_static("zeroVector", [](py::object) { return MVector::zero; },
            "The vector <0,0,0>")

        .def_property_readonly_static("xAxisVector", [](py::object) { return MVector::xAxis; },
            "The vector <1,0,0>")

        .def_property_readonly_static("xNegAxisVector", [](py::object) { return MVector::xNegAxis; },
            "The vector <-1,0,0>")
        
        .def_property_readonly_static("yAxisVector", [](py::object) { return MVector::yAxis; },
            "The vector <0,1,0>")

        .def_property_readonly_static("yNegAxisVector", [](py::object) { return MVector::yNegAxis; },
            "The vector <0,-1,0>")

        .def_property_readonly_static("zAxisVector", [](py::object) { return MVector::zAxis; },
            "The vector <0,0,1>")

        .def_property_readonly_static("zNegAxisVector", [](py::object) { return MVector::zNegAxis; },
            "The vector <0,0,-1>")

        .def("__len__", [](const MVector &self) -> int {
            return 3;
        }, "Returns length of the vector, which is always 3.")
        
        // Support print()
        .def("__repr__", [](const MVector &a) {
            return "<cmdc.Vector( " +
                std::to_string(a.x) + ", " +
                std::to_string(a.y) + ", " +
                std::to_string(a.z) + " )>";
        }
    );
}