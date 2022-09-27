#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <maya/MObject.h>
#include <maya/MObjectHandle.h>

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

void init_MObject(py::module_ &m) {
    py::class_<MObject> Object(m, "Object");
    py::class_<MObjectHandle> ObjectHandle(m, "ObjectHandle");

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
}