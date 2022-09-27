#include <string>
#include <vector>
#include <maya/MIntArray.h>
#include <maya/MPlugArray.h>
#include <maya/MPlug.h>
#include <maya/MString.h>
#include <maya/MStringArray.h>

namespace atov {
    inline std::vector<int> convert(MIntArray& array)
    {
        std::vector<int> result(array.length());

        for (unsigned int i = 0; i < array.length(); i++) {
            result[i] = array[i];
        }

        return result;
    }

    inline std::vector<MPlug> convert(MPlugArray& array)
    {
        std::vector<MPlug> result(array.length());

        for (unsigned int i = 0; i < array.length(); i++) {
            result[i] = array[i];
        }

        return result;
    }

    inline std::vector<std::string> convert(MStringArray& array)
    {
        std::vector<std::string> result(array.length());

        for (unsigned int i = 0; i < array.length(); i++) {
            result[i] = std::string(array[i].asChar());
        }

        return result;
    }
}