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
