Status
    .def(py::init<>())
    .def(py::init<const MStatus &>())

    .def("__repr__", [](const MStatus &a) {
        return "<cmdc.Status()>";
    }
);

TypeId
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

        return "<cmdc.TypeId( " + std::to_string(id) + ")>";
    }
);


ObjectHandle
    .def(py::init<>())
    .def(py::init<const MObject &>())

    .def("__repr__", [](const MObjectHandle &a) {
        return "<cmdc.ObjectHandle()>";
    }
);