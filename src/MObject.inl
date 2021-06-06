py::class_<MObject>(m, "Object")
    .def_property_readonly_static("kNullObj", [](py::object /* self */) { return MObject::kNullObj; })

    .def(py::init<>())
    .def(py::init<const MObject &>())

    .def(py::self == MObject())

    .def("isNull", &MObject::isNull, 
        R"pbdoc(Return True if the internal Maya Object does not exist.)pbdoc")
    .def("hasFn", [](MObject& self, MFn::Type type) -> bool {
        return self.hasFn(type);
    }, R"pbdoc(Return True if the internal Maya Object is compatible with the given Function Type.)pbdoc",
        py::arg("type"))
    .def("apiType", [](MObject& self) -> MFn::Type {
        return self.apiType();
    }, R"pbdoc(Return the exact type of the internal Maya Object.)pbdoc")
    .def("apiTypeStr", [](MObject& self) -> std::string {
        return self.apiTypeStr();
    }, R"pbdoc(Return the type name of the internal Maya Object.)pbdoc")

    .def("__repr__", [](const MObject &self) {
        std::string ret = "<cmdc.Object(";
        ret += self.apiTypeStr();
        ret += ")>";
        return ret;
    }
);

py::class_<MObjectHandle>(m, "ObjectHandle")
    .def(py::init<>())
    .def(py::init<const MObject &>())

    .def("__repr__", [](const MObjectHandle &a) {
        return "<cmdc.ObjectHandle()>";
    }
);
