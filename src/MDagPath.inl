py::class_<MDagPath>(m, "DagPath")
    .def(py::init<>())

    .def("apiType", [](MDagPath & self) -> MFn::Type {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns the type of the object at the end of the path.)pbdoc")

    .def("child", [](MDagPath & self, unsigned int i) -> MObject {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns the specified child of the object at the end of the path.)pbdoc")

    .def("childCount", [](MDagPath & self) -> int {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns the number of objects parented directly beneath the object at the end of the path.)pbdoc")

    .def("exclusiveMatrix", [](MDagPath & self) -> MMatrix {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns the matrix for all transforms in the path, excluding the end object.)pbdoc")

    .def("exclusiveMatrixInverse", [](MDagPath & self) -> MMatrix {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns the inverse of exclusiveMatrix().)pbdoc")

    .def("extendToShape", [](MDagPath & self) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Extends the path to the specified shape node parented directly beneath the transform at the current end of the path.)pbdoc")

    .def("fullPathName", [](MDagPath & self) -> MString {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns a string representation of the path from the DAG root to the path's last node.)pbdoc")

    .def_static("getAPathTo", [](MObject node) -> MDagPath {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns the first path found to the given node.)pbdoc")

    .def_static("getAPathTo", [](MObject node) -> MDagPath {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns the first path found to the given node.)pbdoc")

    .def_static("getAllPathsTo", [](MObject node) -> std::vector<MDagPath> {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns all paths to the given node.)pbdoc")

    .def("getDisplayStatus", [](MDagPath & self) -> int {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns the display status for this path.)pbdoc")

    .def("getDrawOverrideInfo", [](MDagPath & self) -> MDAGDrawOverrideInfo {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns the draw override information for this path.)pbdoc")

    .def("getPath", [](MDagPath & self, unsigned int i = 0) -> MDagPath {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns the specified sub-path of this path.)pbdoc")

    .def("hasFn", [](MDagPath & self, MFn::Type type) -> bool {
        return self.hasFn(type);
    }, R"pbdoc(Returns True if the object at the end of the path supports the given function set.)pbdoc")

    .def("inclusiveMatrix", [](MDagPath & self) -> MMatrix {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns the matrix for all transforms in the path, including the end object, if it is a transform.)pbdoc")

    .def("inclusiveMatrixInverse", [](MDagPath & self) -> MMatrix {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns the inverse of inclusiveMatrix().)pbdoc")

    .def("instanceNumber", [](MDagPath & self) -> int {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns the instance number of this path to the object at the end.)pbdoc")

    .def("isInstanced", [](MDagPath & self) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns True if the object at the end of the path can be reached by more than one path.)pbdoc")

    .def("isTemplated", [](MDagPath & self) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns true if the DAG Node at the end of the path is templated.)pbdoc")

    .def("isValid", [](MDagPath & self) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns True if this is a valid path.)pbdoc")

    .def("isVisible", [](MDagPath & self) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns true if the DAG Node at the end of the path is visible.)pbdoc")

    .def("length", [](MDagPath & self) -> int {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns the number of nodes on the path, not including the DAG's root node.)pbdoc")

    .def("node", [](MDagPath & self) -> MObject {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns the DAG node at the end of the path.)pbdoc")

    .def("numberOfShapesDirectlyBelow", [](MDagPath & self) -> unsigned int {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns the number of shape nodes parented directly beneath the transform at the end of the path.)pbdoc")

    .def("partialPathName", [](MDagPath & self) -> MString {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns the minimum string representation which will uniquely identify the path.)pbdoc")

    .def("pathCount", [](MDagPath & self) -> int {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns the number of sub-paths which make up this path.)pbdoc")

    .def("pop", [](MDagPath & self, unsigned int num = 1) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Removes objects from the end of the path.)pbdoc")

    .def("push", [](MDagPath & self, MObject child) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Extends the path to the specified child object, which must be parented directly beneath the object currently at the end of the path.)pbdoc")

    .def("set", [](MDagPath & self, MDagPath src) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Replaces the current path held by this object with another.)pbdoc")

    .def("transform", [](MDagPath & self) -> MObject {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns the last transform node on the path.)pbdoc");