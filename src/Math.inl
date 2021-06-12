Vector
    .def(py::init<>())
    .def(py::init<const double,
                  const double,
                  const double>(),
                  py::arg("x"),
                  py::arg("y"),
                  py::arg("z"))
    .def(py::init<const MVector &>(), py::arg("src"))
    .def_readwrite("x", &MVector::x)
    .def_readwrite("y", &MVector::y)
    .def_readwrite("z", &MVector::z)

    .def(py::self + py::self, py::arg("other"))
    .def(py::self - py::self, py::arg("other"))
    .def(py::self += py::self, py::arg("other"))
    .def(py::self -= py::self, py::arg("other"))
    .def(py::self *= double(), py::arg("other"))
    .def(py::self /= double(), py::arg("other"))
    .def(py::self * double(), py::arg("other"))
    .def(py::self / double(), py::arg("other"))

    .def("__neg__",   [](MVector v) { return -v; }, py::is_operator())

    // Support print()
    .def("__repr__", [](const MVector &a) {
        return "<cmdc.Vector( " +
               std::to_string(a.x) + ", " +
               std::to_string(a.y) + ", " +
               std::to_string(a.z) + " )>";
    }
);

Point
    .def(py::init<>())
    .def(py::init<const double,
                  const double,
                  const double,
                  const double>(),
                  py::arg("x"),
                  py::arg("y"),
                  py::arg("z"),
                  py::arg("w"))
    .def(py::init<const MPoint &>(), py::arg("src"))
    .def_readwrite("x", &MPoint::x)
    .def_readwrite("y", &MPoint::y)
    .def_readwrite("z", &MPoint::z)
    .def_readwrite("w", &MPoint::w)

    .def(py::self + py::self, py::arg("other"))
    .def(py::self - py::self, py::arg("other"))
    .def(py::self += py::self, py::arg("other"))
    .def(py::self -= py::self, py::arg("other"))
    .def(py::self *= double(), py::arg("other"))
    .def(py::self * double(), py::arg("other"))
    .def(py::self / double(), py::arg("other"))

    // Support print()
    .def("__repr__", [](const MPoint &a) {
        return "<cmdc.Point( " +
               std::to_string(a.x) + ", " +
               std::to_string(a.y) + ", " +
               std::to_string(a.z) + ", " +
               std::to_string(a.w) + " )>";
    }
);

Matrix
    .def(py::init<>())
    .def(py::init<const MMatrix &>(), py::arg("src"))

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

    // Support print()
    .def("__repr__", [](const MMatrix &a) {

        return "<cmdc.Matrix( " + std::to_string(a(0, 0)) + ", " + std::to_string(a(0, 1)) + ", " + std::to_string(a(0, 2)) + ", " + std::to_string(a(0, 3)) + "\n" +
            "              " + std::to_string(a(1, 0)) + ", " + std::to_string(a(1, 1)) + ", " + std::to_string(a(1, 2)) + ", " + std::to_string(a(1, 3)) + "\n" +
            "              " + std::to_string(a(2, 0)) + ", " + std::to_string(a(2, 1)) + ", " + std::to_string(a(2, 2)) + ", " + std::to_string(a(2, 3)) + "\n" +
            "              " + std::to_string(a(3, 0)) + ", " + std::to_string(a(3, 1)) + ", " + std::to_string(a(3, 2)) + ", " + std::to_string(a(3, 3)) +
        " )>";
    }
);

Quaternion
    .def(py::init<const double,
                  const double,
                  const double,
                  const double>(),
                  py::arg("x"),
                  py::arg("y"),
                  py::arg("z"),
                  py::arg("w"))
    .def(py::init<const MQuaternion&>(), py::arg("src"))
    .def(py::init<const MVector&, const MVector&>(),
         py::arg("a"),
         py::arg("b"))
    .def(py::init<const double, const MVector>(),
         py::arg("angle"),
         py::arg("axis"))
    .def_readwrite("x", &MQuaternion::x)
    .def_readwrite("y", &MQuaternion::y)
    .def_readwrite("z", &MQuaternion::z)
    .def_readwrite("w", &MQuaternion::w)

    .def("__repr__", [](const MQuaternion& q) {
        return "<cmdc.Quaternion( " +
               std::to_string(q.x) + ", " +
               std::to_string(q.y) + ", " +
               std::to_string(q.z) + ", " +
               std::to_string(q.w) + " )>";
    }
);
