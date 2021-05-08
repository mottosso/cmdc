namespace atov {
    std::vector<MPlug> convert(MPlugArray& plug_array)
    {
        std::vector<MPlug> result(plug_array.length());

        for (unsigned int i = 0; i < plug_array.length(); i++) {
            result[i] = plug_array[i];
        }

        return result;
    }
}