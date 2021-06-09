DagPath
    .def(py::init<>())

    .def(py::self == MDagPath())

    .def("apiType", [](MDagPath & self) -> MFn::Type {
        // Not throwing anything here since apiType returns kInvalid when it fails.
        return self.apiType();
    }, R"pbdoc(Returns the type of the object at the end of the path.)pbdoc")

    .def("child", [](MDagPath & self, unsigned int i) -> MObject {
        if (!self.isValid()) {
            throw std::logic_error("Call on invalid DagPath.");
        } else if (i >= self.childCount()) {
            throw std::out_of_range("Index out of range.");
        }

        MStatus status;
        MObject result = self.child(i, &status);

        if (!status) {
            throw std::logic_error(status.errorString().asChar());
        }

        return result;
    }, R"pbdoc(Returns the specified child of the object at the end of the path.)pbdoc")

    .def("childCount", [](MDagPath & self) -> int {
        if (!self.isValid()) {
            throw std::logic_error("Call on invalid DagPath.");
        }

        MStatus status;
        int result = self.childCount(&status);

        if (!status) {
            throw std::logic_error(status.errorString().asChar());
        }

        return result;
    }, R"pbdoc(Returns the number of objects parented directly beneath the object at the end of the path.)pbdoc")

    .def("exclusiveMatrix", [](MDagPath & self) -> MMatrix {
        if (!self.isValid()) {
            throw std::logic_error("Call on invalid DagPath.");
        }

        MStatus status;
        MMatrix result = self.exclusiveMatrix(&status);

        if (!status) {
            throw std::logic_error(status.errorString().asChar());
        }

        return result;
    }, R"pbdoc(Returns the matrix for all transforms in the path, excluding the end object.)pbdoc")

    .def("exclusiveMatrixInverse", [](MDagPath & self) -> MMatrix {
        if (!self.isValid()) {
            throw std::logic_error("Call on invalid DagPath.");
        }
        MStatus status;
        MMatrix result = self.exclusiveMatrixInverse(&status);

        if (!status) {
            throw std::logic_error(status.errorString().asChar());
        }

        return result;
    }, R"pbdoc(Returns the inverse of exclusiveMatrix().)pbdoc")

    .def("extendToShape", [](MDagPath & self) {
        if (!self.isValid()) {
            throw std::logic_error("Call on invalid DagPath.");
        }

        MStatus status = self.extendToShape();

        if (!status) {
            throw std::logic_error(status.errorString().asChar());
        }
    }, R"pbdoc(If the object at the end of this path is a transform and there is a shape node directly beneath it in the hierarchy, then the path is extended to that geometry node.

NOTE: This method will fail if there multiple shapes below the transform.)pbdoc")

    .def("extendToShapeDirectlyBelow", [](MDagPath & self, unsigned int index) {
        if (!self.isValid()) {
            throw std::logic_error("Call on invalid DagPath.");
        } 

        unsigned int number_of_shapes;
        self.numberOfShapesDirectlyBelow(number_of_shapes);
        if (index >= number_of_shapes) {
            throw std::out_of_range("Index out of range.");
        }

        MStatus status = self.extendToShapeDirectlyBelow(index);

        if (!status) {
            throw std::logic_error(status.errorString().asChar());
        }
    }, R"pbdoc(This method is used if the end of the path is a transform and there are shapes directly below the transform.
The shape to extend to is set by passing in an appropriate index parameter.
Use the `numberOfShapesDirectlyBelow()` method to determine how many shapes are below)pbdoc")

    .def("fullPathName", [](MDagPath & self) -> std::string {
        if (!self.isValid()) {
            throw std::logic_error("Call on invalid Dag Path.");
        }

        MStatus status;
        std::string result = self.fullPathName(&status).asChar();

        if (!status) {
            throw std::logic_error(status.errorString().asChar());
        }

        return result;
    }, R"pbdoc(Returns a string representation of the path from the DAG root to the path's last node.)pbdoc")

    .def_static("getAPathTo", [](MObject node) -> MDagPath {
        if (node.isNull()) {
            throw std::logic_error("Passed Object is null.");
        } else if (!node.hasFn(MFn::Type::kDagNode)) {
            std::string error_msg = "Passed Object has Fn ";
            error_msg += node.apiTypeStr();
            error_msg += ". Should be kDagNode or subclass.";
            throw pybind11::type_error(error_msg);
        }

        MDagPath path;
        MStatus status = MDagPath::getAPathTo(node, path);

        if (!status) {
            throw std::logic_error(status.errorString().asChar());
        }

        return path;
    }, R"pbdoc(Returns the first path found to the given node.)pbdoc")

    .def_static("getAllPathsBelow", [](MObject node) -> std::vector<MDagPath> {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns all paths to the given node.)pbdoc")

    .def_static("getAllPathsTo", [](MObject node) -> std::vector<MDagPath> {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns all paths to the given node.)pbdoc")

    .def("getDrawOverrideInfo", [](MDagPath & self) -> MDAGDrawOverrideInfo {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns the draw override information for this path.)pbdoc")

    .def("getPath", [](MDagPath & self, unsigned int i = 0) -> MDagPath {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns the specified sub-path of this path.)pbdoc")

    .def("hasFn", [](MDagPath & self, MFn::Type type) -> bool {
        if (!self.isValid()) {
            throw std::logic_error("Call on invalid DagPath.");
        }

        MStatus status;
        bool result = self.hasFn(type, &status);

        if (!status) {
            throw std::logic_error(status.errorString().asChar());
        }

        return result;
    }, R"pbdoc(Returns True if the object at the end of the path supports the given function set.)pbdoc")

    .def("inclusiveMatrix", [](MDagPath & self) -> MMatrix {
        if (!self.isValid()) {
            throw std::logic_error("Call on invalid DagPath.");
        }
        return self.inclusiveMatrix();
    }, R"pbdoc(Returns the matrix for all transforms in the path, including the end object, if it is a transform.)pbdoc")

    .def("inclusiveMatrixInverse", [](MDagPath & self) -> MMatrix {
        if (!self.isValid()) {
            throw std::logic_error("Call on invalid DagPath.");
        }

        MStatus status;
        MMatrix result = self.inclusiveMatrixInverse(&status);

        if (!status) {
            throw std::logic_error(status.errorString().asChar());
        }

        return result;
    }, R"pbdoc(Returns the inverse of inclusiveMatrix().)pbdoc")

    .def("instanceNumber", [](MDagPath & self) -> int {
        if (!self.isValid()) {
            throw std::logic_error("Call on invalid DagPath.");
        } else if (!self.isInstanced()) {
            throw pybind11::type_error("Call on a non instanced DagPath.");
        }

        MStatus status;
        int result = self.instanceNumber(&status);

        if (!status) {
            throw std::logic_error(status.errorString().asChar());
        }

        return result;
    }, R"pbdoc(Returns the instance number of this path to the object at the end.)pbdoc")

    .def("isInstanced", [](MDagPath & self) -> bool {
        if (!self.isValid()) {
            throw std::logic_error("Call on invalid DagPath.");
        }

        MStatus status;
        bool result = self.isInstanced(&status);

        if (!status) {
            throw std::logic_error(status.errorString().asChar());
        }

        return result;
    }, R"pbdoc(Returns True if the object at the end of the path can be reached by more than one path.)pbdoc")

    .def("isTemplated", [](MDagPath & self) -> bool {
        if (!self.isValid()) {
            throw std::logic_error("Call on invalid DagPath.");
        }

        MStatus status;
        bool result = self.isTemplated(&status);

        if (!status) {
            throw std::logic_error(status.errorString().asChar());
        }

        return result;
    }, R"pbdoc(Returns true if the DAG Node at the end of the path is templated.)pbdoc")

    .def("isValid", [](MDagPath & self) -> bool {
        MStatus status;
        bool result = self.isValid(&status);

        if (!status) {
            throw std::logic_error(status.errorString().asChar());
        }

        return result;
    }, R"pbdoc(Returns True if this is a valid path.)pbdoc")

    .def("isVisible", [](MDagPath & self) -> bool {
        if (!self.isValid()) {
            throw std::logic_error("Call on invalid DagPath.");
        }

        MStatus status;
        bool result = self.isVisible(&status);

        if (!status) {
            throw std::logic_error(status.errorString().asChar());
        }

        return result;
    }, R"pbdoc(Returns true if the DAG Node at the end of the path is visible.)pbdoc")

    .def("length", [](MDagPath & self) -> int {
        if (!self.isValid()) {
            throw std::logic_error("Call on invalid DagPath.");
        }

        MStatus status;
        int result = self.length(&status);

        if (!status) {
            throw std::logic_error(status.errorString().asChar());
        }

        return result;
    }, R"pbdoc(Returns the number of nodes on the path, not including the DAG's root node.)pbdoc")

    .def("matchTransform", [](MDagPath & self) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Extends the path to the specified shape node parented directly beneath the transform at the current end of the path.)pbdoc")

    .def("node", [](MDagPath & self) -> MObject {
        if (!self.isValid()) {
            throw std::logic_error("Call on invalid DagPath.");
        }

        MStatus status;
        MObject result = self.node(&status);

        if (!status) {
            throw std::logic_error(status.errorString().asChar());
        }

        return result;
    }, R"pbdoc(Returns the DAG node at the end of the path.)pbdoc")

    .def("numberOfShapesDirectlyBelow", [](MDagPath & self) -> unsigned int {
        if (!self.isValid()) {
            throw std::logic_error("Call on invalid DagPath.");
        }

        unsigned int result;

        MStatus status = self.numberOfShapesDirectlyBelow(result);

        if (!status) {
            throw std::logic_error(status.errorString().asChar());
        }

        return result;
    }, R"pbdoc(Returns the number of shape nodes parented directly beneath the transform at the end of the path.)pbdoc")

    .def("partialPathName", [](MDagPath & self) -> std::string {
        if (!self.isValid()) {
            throw std::logic_error("Call on invalid DagPath.");
        }

        MStatus status;
        MString result = self.partialPathName(&status);

        if (!status) {
            throw std::logic_error(status.errorString().asChar());
        }

        return std::string(result.asChar());
    }, R"pbdoc(Returns the minimum string representation which will uniquely identify the path.)pbdoc")

    .def("pathCount", [](MDagPath & self) -> int {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns the number of sub-paths which make up this path.)pbdoc")

    .def("pop", [](MDagPath & self, unsigned int num = 1) {
        if (!self.isValid()) {
            throw std::logic_error("Call on invalid DagPath.");
        } else if (num > self.length()) {
            throw pybind11::value_error("");
        }

        MStatus status = self.pop(num);

        if (!status) {
            throw std::logic_error(status.errorString().asChar());
        }

    }, R"pbdoc(Removes objects from the end of the path.)pbdoc", py::arg("num") = 1)

    .def("push", [](MDagPath & self, MObject child) {
        if (!self.isValid()) {
            throw std::logic_error("Call on invalid DagPath.");
        }

        MStatus status = self.push(child);

        if (!status) {
            throw std::logic_error(status.errorString().asChar());
        }

    }, R"pbdoc(Extends the path to the specified child object, which must be parented directly beneath the object currently at the end of the path.)pbdoc")

    .def("set", [](MDagPath & self, MDagPath src) {
        MStatus status = self.set(src);

        if (!status) {
            throw std::logic_error(status.errorString().asChar());
        }
    }, R"pbdoc(Replaces the current path held by this object with another.)pbdoc")

    .def("transform", [](MDagPath & self) -> MObject {
        if (!self.isValid()) {
            throw std::logic_error("Call on invalid DagPath.");
        }

        MStatus status;
        MObject result = self.transform();

        if (!status) {
            throw std::logic_error(status.errorString().asChar());
        }

        return result;
    }, R"pbdoc(Returns the last transform node on the path.)pbdoc");