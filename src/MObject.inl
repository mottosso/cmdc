#define _doc_Object_isNull R"pbdoc(Return True if the internal Maya Object does not exist.)pbdoc"
#define _doc_Object_hasFn R"pbdoc(Return True if the internal Maya Object is compatible with the given Function Type.)pbdoc"
#define _doc_Object_apiType R"pbdoc(Return the exact type of the internal Maya Object.)pbdoc"
#define _doc_Object_apiTypeStr R"pbdoc(Return the type name of the internal Maya Object.)pbdoc"

Object
    .def_property_readonly_static("kNullObj", [](py::object /* self */) { return MObject::kNullObj; })
    .def(py::init<>())
    .def(py::init<const MObject &>(), py::arg("other"))

    .def(py::self == MObject(), py::arg("other"))

    .def("isNull", &MObject::isNull, _doc_Object_isNull)
    .def("hasFn", [](MObject& self, MFn::Type type) -> bool {
        return self.hasFn(type);
    }, py::arg("type"), _doc_Object_hasFn)
    .def("apiType", [](MObject& self) -> MFn::Type {
        return self.apiType();
    }, _doc_Object_apiType)
    .def("apiTypeStr", [](MObject& self) -> std::string {
        return self.apiTypeStr();
    }, _doc_Object_apiTypeStr)

    .def("__repr__", [](const MObject &self) {
        std::string ret = "<cmdc.Object(";
        ret += self.apiTypeStr();
        ret += ")>";
        return ret;
    }
);

ObjectHandle
    .def(py::init<>())
    .def(py::init<const MObject &>(), py::arg("object"))

    .def("__repr__", [](const MObjectHandle &a) {
        return "<cmdc.ObjectHandle()>";
    }
);
