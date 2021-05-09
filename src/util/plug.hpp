namespace plug {
    inline void assert_not_null(MPlug &p) {
        if (p.isNull()) {
            throw std::invalid_argument("Accessed a null Plug.");
        }
    }
}