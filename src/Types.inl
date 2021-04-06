
py::class_<MStatus>(m, "Status")
    .def(py::init<>())
    .def(py::init<const MStatus &>())

    .def("__repr__", [](const MStatus &a) {
        return "<cmdc.CStatus()>";
    }
);

py::class_<MTypeId>(m, "TypeId")
    .def(py::init<>())
    .def(py::init<const MTypeId &>())
    .def(py::init<const unsigned int>(),
         py::arg("id"))
    .def(py::init<const unsigned int, const unsigned int>(),
         py::arg("prefix"),
         py::arg("id"))

    .def("__repr__", [](const MTypeId &a) {
        MStatus status;
        unsigned int id = a.id(&status);

        if (status != MS::kSuccess) {
            // Throw exception!
            id = 0;
        }

        return "<cmdc.CTypeId( " + std::to_string(id) + ")>";
    }
);



py::class_<MObjectHandle>(m, "ObjectHandle")
    .def(py::init<>())
    .def(py::init<const MObject &>())

    .def("__repr__", [](const MObjectHandle &a) {
        return "<cmdc.CObjectHandle()>";
    }
);