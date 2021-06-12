#include "MFn.Types.inl"

for (int x = MFn::Type::kInvalid; x <= MFn::Type::kLast; x++) {
    MFn::Type type = static_cast<MFn::Type>(x);
    fn_type.value(type_names[x].c_str(), type);
}

fn_type.export_values();
