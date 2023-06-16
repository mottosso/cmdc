#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <maya/MTypeId.h>
#include <maya/MString.h>
#include <maya/MString.h>
#include <maya/MFn.h>
#include "MFn.Types.inl"
#include "init.h"

namespace py = pybind11;

template <>
void init_class(py::class_<MTypeId> &TypeId) {
    TypeId
        .def(py::init<>())
        .def(py::init<const MTypeId &>(), py::arg("src"))
        .def(py::init<const unsigned int>(), py::arg("id"))
        .def(py::init<const unsigned int, const unsigned int>(), py::arg("prefix"), py::arg("id"))

        .def("__repr__", [](const MTypeId &a) {
            MStatus status;
            unsigned int id = a.id(&status);

            if (status != MS::kSuccess) {
                // Throw exception!
                id = 0;
            }

            return "<cmdc.TypeId( " + std::to_string(id) + ")>";
        }
    );
}

template <>
void init_class(py::class_<MStatus> &Status) {
    Status
        .def(py::init<>())
        .def(py::init<const MStatus &>(), py::arg("status"))

        .def("__repr__", [](const MStatus &a) {
            return "<cmdc.Status()>";
        }
    );
}

template <>
void init_class(py::class_<MString> &String) {
    String
        .def(py::init<>())
        .def(py::init<const MString &>(), py::arg("other"))
        .def(py::init<const char*>(), py::arg("charString"))

        .def(py::self += MString(), py::arg("other"))
        .def(py::self += char(), py::arg("other"))
        .def(py::self += double(), py::arg("other"))
        .def(py::self += int(), py::arg("other"))
        // .def(py::self += unsigned int())  # Not supported with GCC?
        .def(py::self += float(), py::arg("other"))

        .def("__repr__", [](const MString &a) {
            return "<cmdc.String()>";
        }
    );
}

template <>
void init_class(py::class_<MSpace> &Space) {
    py::enum_<MSpace::Space>(Space, "Space")
        .value("kInvalid", MSpace::Space::kInvalid) 
        .value("kTransform", MSpace::Space::kTransform)
        .value("kPreTransform", MSpace::Space::kPreTransform)
        .value("kPostTransform", MSpace::Space::kPostTransform)
        .value("kWorld", MSpace::Space::kWorld)
        .value("kObject", MSpace::Space::kObject)
        .value("kLast", MSpace::Space::kLast)
        .export_values();
}

template <>
void init_enum(py::enum_<MFn::Type> &fn_type) {
    for (int x = MFn::Type::kInvalid; x <= MFn::Type::kLast; x++) {
        MFn::Type type = static_cast<MFn::Type>(x);
        fn_type.value(type_names[x].c_str(), type);
    }
    fn_type.export_values();
}
