#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <maya/MObject.h>
#include <maya/MObjectHandle.h>
#include "init.h"

namespace py = pybind11;

#define _doc_Object_isNull \
    "Return True if the internal Maya Object does not exist."

#define _doc_Object_hasFn \
    "Return True if the internal Maya Object is compatible with the\n"\
    "given Function Type."

#define _doc_Object_apiType \
    "Return the exact type of the internal Maya Object."

#define _doc_Object_apiTypeStr \
    "Return the type name of the internal Maya Object."

#define _doc_Object_kNullObj \
    "Used to indicate that an MObject instance does not refer to any\n"\
    "internal Maya object."


#define _doc_ObjectHandle_object \
    "Returns the Maya Object associated with this handle or Object.kNullObj\n"\
    "if object is invalid."

#define _doc_ObjectHandle_isValid \
    "Returns the validity of the associated Maya Object."

#define _doc_ObjectHandle_isAlive \
    "Returns the live state of the associated Maya Object. An object can\n"\
    "still be 'alive' but not 'valid' (eg. a deleted object that resides\n"\
    "in the undo queue)."

#define _doc_ObjectHandle_hashCode \
    "Returns a hash code for the internal Maya object referenced within this\n"\
    "ObjectHandle. If the Maya Object is null or no longer alive then 0 will\n"\
    "be returned, otherwise the hash code is guaranteed to be non-zero"


template <>
void init_class(py::class_<MObject> &Object) {
    Object
        .def_property_readonly_static("kNullObj", [](py::object /* self */)
        { return MObject::kNullObj; }, _doc_Object_kNullObj)

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
}

template <>
void init_class(py::class_<MObjectHandle> &ObjectHandle) {
    ObjectHandle
        .def(py::init<>())
        .def(py::init<const MObject &>(), py::arg("object"))

        .def("__repr__", [](const MObjectHandle &a) {
            return "<cmdc.ObjectHandle()>";
        })
        .def("object", &MObjectHandle::object, _doc_ObjectHandle_object)
        .def("isValid", &MObjectHandle::isValid, _doc_ObjectHandle_isValid)
        .def("isAlive", &MObjectHandle::isAlive, _doc_ObjectHandle_isAlive)
        .def("hashCode", &MObjectHandle::hashCode, _doc_ObjectHandle_hashCode) 
        ;
}
