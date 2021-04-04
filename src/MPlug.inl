
py::class_<MPlug>(m, "Plug")
    .def(py::init<>())
    .def(py::init<const MPlug &>())

    .def("__repr__", [](const MPlug &a) {
        return "<cmdc.CPlug()>";
    }
);
