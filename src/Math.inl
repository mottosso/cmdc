
String
    .def(py::init<>())
    .def(py::init<const MString &>())
    .def(py::init<const char*>())

    .def(py::self += MString())
    .def(py::self += char())
    .def(py::self += double())
    .def(py::self += int())
    // .def(py::self += unsigned int())  # Not supported with GCC?
    .def(py::self += float())

    .def("__repr__", [](const MString &a) {
        return "<cmdc.String()>";
    }
);

Vector
    .def(py::init<>())
    .def(py::init<const double,
                  const double,
                  const double>())
    .def(py::init<const MVector &>())
    .def_readwrite("x", &MVector::x)
    .def_readwrite("y", &MVector::y)
    .def_readwrite("z", &MVector::z)

    .def(py::self + py::self)
    .def(py::self - py::self)
    .def(py::self += py::self)
    .def(py::self -= py::self)
    .def(py::self *= double())
    .def(py::self /= double())
    .def(py::self * double())
    .def(py::self / double())

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
                  const double>())
    .def(py::init<const MPoint &>())
    .def_readwrite("x", &MPoint::x)
    .def_readwrite("y", &MPoint::y)
    .def_readwrite("z", &MPoint::z)
    .def_readwrite("w", &MPoint::w)

    .def(py::self + py::self)
    .def(py::self - py::self)
    .def(py::self += py::self)
    .def(py::self -= py::self)
    .def(py::self *= double())
    .def(py::self * double())
    .def(py::self / double())

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
    .def(py::init<const MMatrix &>())

    .def(py::self += MMatrix())
    .def(py::self + MMatrix())
    .def(py::self -= MMatrix())
    .def(py::self - MMatrix())
    .def(py::self *= MMatrix())
    .def(py::self * MMatrix())
    .def(py::self *= double()) 
    .def(py::self * double()) 
    .def(py::self == MMatrix())
    .def(py::self != MMatrix())

    .def(py::self *= MQuaternion())
    .def(py::self * MQuaternion())

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
                  const double>())
    .def(py::init<const MQuaternion&>())
    .def(py::init<const MVector&, const MVector&>())
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
