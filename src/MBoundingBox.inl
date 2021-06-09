BoundingBox
    .def(py::init<>())

    .def("center", [](MBoundingBox& self) -> MPoint {
        return self.center();
    }, R"pbdoc(Center point)pbdoc")

    .def("clear", [](MBoundingBox& self) -> void {
        self.clear();
    }, R"pbdoc(Empties the bounding box, setting its corners to (0, 0, 0).)pbdoc")

    .def("contains", [](MBoundingBox& self, MPoint point) -> bool {
        return self.contains(point);
    },
    py::arg("point"),
    R"pbdoc(Returns True if a point lies within the bounding box.)pbdoc")

    .def("depth", [](MBoundingBox& self) -> double {
        return self.depth();
    }, R"pbdoc(Size in Z)pbdoc")

    .def("expand", [](MBoundingBox& self, MBoundingBox box) -> void {
        self.expand(box);
    }, py::arg("box"), 
       R"pbdoc(Expands the bounding box to include a point or other bounding box.)pbdoc")

    .def("expand", [](MBoundingBox& self, MPoint point) -> void {
        self.expand(point);
    }, py::arg("point"), 
       R"pbdoc(Expands the bounding box to include a point or other bounding box.)pbdoc")

    .def("height", [](MBoundingBox& self) -> double {
        return self.height();
    }, R"pbdoc(Size in Y)pbdoc")

    .def("intersects", [](MBoundingBox& self, MBoundingBox box, double tol = 0.0) -> bool {
        return self.intersects(box, tol);
    }, py::arg("box"),
       py::arg("tol") = 0.0,
       R"pbdoc(Returns True if any part of a given bounding box lies within this one.)pbdoc")

    .def("transformUsing", [](MBoundingBox& self, MMatrix matrix) -> void {
        self.transformUsing(matrix);
    }, py::arg("matrix"),
       R"pbdoc(Multiplies the bounding box's corners by a matrix.)pbdoc")

    .def("width", [](MBoundingBox& self) -> double {
        return self.width();
    }, R"pbdoc(Size in X)pbdoc");