#include "MFn.Types.inl"

py::class_<MFn> fn(m, "Fn");
py::enum_<MFn::Type> fn_type(fn, "Type");

for (int x = MFn::Type::kInvalid; x <= MFn::Type::kLast; x++) {
    MFn::Type type = static_cast<MFn::Type>(x);
    fn_type.value(type_names[x].c_str(), type);
}

fn_type.export_values();
