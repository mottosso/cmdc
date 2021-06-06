namespace validate {
    namespace object {
        inline void assert_not_null(MObject &o, std::string error_message) {
            if (o.isNull()) {
                throw std::invalid_argument(error_message.c_str());
            }
        }

        inline void assert_has_fn(MObject &o, MFn::Type type, std::string error_message) {
            if (!o.hasFn(type)) {
                MString msg(error_message.c_str());
                        msg.format(msg, o.apiTypeStr());

                throw pybind11::type_error(msg.asChar());
            }
        }
    }
}