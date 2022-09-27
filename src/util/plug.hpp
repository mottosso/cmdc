#include <maya/MPlug.h>
#include <maya/MString.h>

namespace plug {
    inline void assert_not_null(MPlug &p) {
        if (p.isNull()) {
            throw std::invalid_argument("Accessed a null Plug.");
        }
    }

    inline void assert_is_array(MPlug &p) {
        if (!p.isArray()) {
            MString error_msg("Plug '^1s' is not an array plug.");
                    error_msg.format(error_msg, p.name());

            throw pybind11::type_error(error_msg.asChar());
        }
    }

    inline void assert_is_not_array(MPlug &p) {
        if (p.isArray()) {
            MString error_msg("Plug '^1s' is an array plug.");
                    error_msg.format(error_msg, p.name());

            throw pybind11::type_error(error_msg.asChar());
        }
    }

    inline void assert_is_compound(MPlug &p) {
        if (!p.isCompound()) {
            MString error_msg("Plug '^1s' is not a compound plug.");
                    error_msg.format(error_msg, p.name());

            throw pybind11::type_error(error_msg.asChar());
        }
    }

    inline void assert_is_element(MPlug &p) {
        if (!p.isElement()) {
            MString error_msg("Plug '^1s' is not an array element plug.");
                    error_msg.format(error_msg, p.name());

            throw pybind11::type_error(error_msg.asChar());
        }
    }
}