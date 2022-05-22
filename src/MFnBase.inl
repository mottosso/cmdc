#define _doc_FnBase_type \
    "Returns the type of the function set."

#define _doc_FnBase_hasObj \
    "Returns True if the function set is compatible with the specified Maya object."

#define _doc_FnBase_object \
    "Returns a reference to the object to which the function set is currently attached, or MObject.kNullObj if none."

#define _doc_FnBase_setObject \
    "Attaches the function set to the specified Maya object."

#define _doc_FnBase_className \
    "Returns the name of this class."

#define _doc_FnBase_typeString \
    "Returns the type string for a given type."

#define _doc_FnBase_isValid \
    "Returns true if type is in the range of valid types."


FnBase
    .def("type", &MFnBase::type, _doc_FnBase_type)

    .def("hasObj", [](MFnBase& self, MFn::Type mtype) -> bool 
        { return self.hasObj(mtype); },
        py::arg("mtype"), _doc_FnBase_hasObj)

    .def("hasObj", [](MFnBase& self, const MObject& object) -> bool 
        { return self.hasObj(object); },
        py::arg("object"), _doc_FnBase_hasObj)

    .def("object", [](MFnBase& self) -> MObject {
        MStatus status;
        MObject result = self.object(&status);
        CHECK_STATUS(status);
        return result;
    }, _doc_FnBase_object)

    .def("setObject", [](MFnBase& self, const MObject & object) -> void {
        if (!self.setObject(object)) throw std::runtime_error(
            "Invalid parameter passed for node - "
            "not a DAG Node, "
            "Node does not exist or "
            "no valid pointer to Node"
        );
    }, py::arg("object"), _doc_FnBase_setObject)

    .def("className", &MFnBase::className, _doc_FnBase_className)

    // These methods are new in maya 2020+
    #if MAYA_APP_VERSION >= 2020
        .def_static( "typeString", &MFnBase::typeString, py::arg("mtype"), _doc_FnBase_typeString)
        .def_static("isValid", &MFnBase::isValid, py::arg("mtype"), _doc_FnBase_isValid)
    #endif
;