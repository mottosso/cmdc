#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <maya/MVector.h>
#include <maya/MPoint.h>
#include <maya/MQuaternion.h>
#include <maya/MEulerRotation.h>
#include <maya/MMatrix.h>

namespace py = pybind11;

void init_MMatrix(py::module_ &m) {
    py::class_<MMatrix> Matrix(m, "Matrix");

    Matrix
        .def(py::init<>())
        .def(py::init<const MMatrix &>(), py::arg("src"))
        .def(py::init([](std::array<double, 16> seq) {
            double tmp[4][4] = {{seq[0], seq[1], seq[2], seq[3]},
                                {seq[4], seq[5], seq[6], seq[7]},
                                {seq[8], seq[9], seq[10], seq[11]},
                                {seq[12], seq[13], seq[14], seq[15]}
                                };

            return std::unique_ptr<MMatrix>(new MMatrix(tmp));
        }), py::arg("seq"), "Create a new matrix from a sequence of 16 float values.")
        .def(py::init([](std::array<std::array<double, 4>, 4> seq) {
            double tmp[4][4] = {{seq[0][0], seq[0][1], seq[0][2], seq[0][3]},
                                {seq[1][0], seq[1][1], seq[1][2], seq[1][3]},
                                {seq[2][0], seq[2][1], seq[2][2], seq[2][3]},
                                {seq[3][0], seq[3][1], seq[3][2], seq[3][3]},
                                };

            return std::unique_ptr<MMatrix>(new MMatrix(tmp));
        }), py::arg("seq"), "Create a new matrix from a sequence of 4 tuples of 4 float values each.")

        .def(py::self += MMatrix(), py::arg("other"))
        .def(py::self + MMatrix(), py::arg("other"))
        .def(py::self -= MMatrix(), py::arg("other"))
        .def(py::self - MMatrix(), py::arg("other"))
        .def(py::self *= MMatrix(), py::arg("other"))
        .def(py::self * MMatrix(), py::arg("other"))
        .def(py::self *= double(), py::arg("other"))
        .def(py::self * double(), py::arg("other"))
        .def(py::self == MMatrix(), py::arg("other"))
        .def(py::self != MMatrix(), py::arg("other"))

        .def(py::self *= MQuaternion(), py::arg("other"))
        .def(py::self * MQuaternion(), py::arg("other"))

        .def("inverse", &MMatrix::inverse)
        .def("adjoint", &MMatrix::adjoint)
        .def("homogenize", &MMatrix::homogenize)
        .def("transpose", &MMatrix::transpose)
        .def("det3x3", &MMatrix::det3x3)
        .def("det4x4", &MMatrix::det4x4)
        .def("setToIdentity", &MMatrix::setToIdentity)

        .def_property_readonly("isSingular", &MMatrix::isSingular)

        .def("__len__", [](const MMatrix &self) -> int {
            return 16;
        }, "Returns length of the matrix, which is always 16.")

        // Support print()
        .def("__repr__", [](const MMatrix &a) {

            return "<cmdc.Matrix( " + std::to_string(a(0, 0)) + ", " + std::to_string(a(0, 1)) + ", " + std::to_string(a(0, 2)) + ", " + std::to_string(a(0, 3)) + "\n" +
                "              " + std::to_string(a(1, 0)) + ", " + std::to_string(a(1, 1)) + ", " + std::to_string(a(1, 2)) + ", " + std::to_string(a(1, 3)) + "\n" +
                "              " + std::to_string(a(2, 0)) + ", " + std::to_string(a(2, 1)) + ", " + std::to_string(a(2, 2)) + ", " + std::to_string(a(2, 3)) + "\n" +
                "              " + std::to_string(a(3, 0)) + ", " + std::to_string(a(3, 1)) + ", " + std::to_string(a(3, 2)) + ", " + std::to_string(a(3, 3)) +
            " )>";
        }
    );
}