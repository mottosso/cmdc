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


String
    .def(py::init<>())
    .def(py::init<const MString &>())
    .def(py::init<const char*>())

    .def(py::self += MString())
    .def(py::self += char())
    .def(py::self += double())
    .def(py::self += int())
    // .def(py::self += unsigned int())  # Not supported with GCC?
    .def(py::self += float())

    .def("__repr__", [](const MString &a) {
        return "<cmdc.String()>";
    }
);
