Vector
    .def(py::init<>())
    .def(py::init<const double,
                  const double,
                  const double>(),
                  py::arg("x"),
                  py::arg("y"),
                  py::arg("z"))
    .def(py::init<const MVector &>(), py::arg("src"))
    .def(py::init([](const py::sequence & seq) {
        if (seq.size() < 2 || seq.size() > 3)
        {
            throw std::invalid_argument("You must provide a list of 2 or 3 floats.");
        }
        double tmp[3] = {0.0, 0.0, 0.0};
        std::transform(std::begin(seq), std::end(seq), std::begin(tmp),
                [](pybind11::handle handle) -> double { return handle.cast<double>(); });
        
        return std::unique_ptr<MVector>(new MVector(tmp[0], tmp[1], tmp[2]));
    }), py::arg("d"), "Create a new vector from a seqence or 2 or 3 floats")

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
    .def(py::init<const MVector&, const MVector&>(),
         py::arg("a"),
         py::arg("b"))
    .def(py::init<const double, const MVector>(),
         py::arg("angle"),
         py::arg("axis"))

    .def(py::self + MQuaternion(), py::arg("other"))
    .def(py::self - MQuaternion(), py::arg("other"))
    .def(py::self * MQuaternion(), py::arg("other"))
    .def(py::self *= MQuaternion(), py::arg("other"))
    .def(py::self == MQuaternion(), py::arg("other"))
    .def(py::self != MQuaternion(), py::arg("other"))
    .def(-py::self)

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
