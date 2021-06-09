#define _doc_SelectionList_len "Returns the number of items on the selection list."
#define _doc_SelectionList_add \
"The first version adds to the list any nodes, DAG paths, components\n"\
"or plugs which match the given the pattern string.\n"\
"\n"\
"The second version adds the specific item to the list, where the\n"\
"item can be a plug (MPlug), a node (MObject), a DAG path (MDagPath)\n"\
"or a component (tuple of (MDagPath, MObject) )."

#define _doc_SelectionList_getDagPath \
"Returns the DAG path associated with the index'th item of the list.\n"\
"Raises TypeError if the item is neither a DAG path nor a component.\n"\
"Raises IndexError if index is out of range."

#define _doc_SelectionList_getDependNode \
"Returns the node associated with the index'th item, whether it be a\n"\
"dependency node, DAG path, component or plug.\n"\
"\n"\
"Raises TypeError if there is no dependency node associated with the current item.\n"\
"Raises IndexError if index is out of range."

#define _doc_SelectionList_getPlug \
"Returns the index'th item of the list as a plug. \n"\
"\n"\
"Raises TypeError if the item is not a plug.\n"\
"Raises IndexError if index is out of range."

#define _doc_SelectionList_getSelectionStrings \
"Returns a tuple containing the string representation of the\n"\
"specified item. For nodes, DAG paths, plugs and contiguous\n"\
"components the tuple will only contain a single string, but for non-\n"\
"contiguous components there will be a separate string for each\n"\
"distinct block of contiguous elements. If index is not specified\n"\
"then the string representations of all the items in the selection\n"\
"list are returned. Raises IndexError if index is out of bounds."

#define _doc_SelectionList_hasItem \
"Returns True if the given item is on the selection list. For a\n"\
"component this means that all of the elements of the component must\n"\
"be on the list. A component is passed as a tuple containing the\n"\
"MDagPath of the DAG node and an MObject containing the component."

#define _doc_SelectionList_hasItemPartly \
"Returns True if at least one of the component's elements is on the\n"\
"selection list. Raises TypeError if dagPath is invalid or component\n"\
"does not contain a component."

#define _doc_SelectionList_intersect "Modify this list to contain the intersection of itself and the given list."

#define _doc_SelectionList_isEmpty "Returns True if the selection list is empty."

#define _doc_SelectionList_merge \
"The first version merges the items from another selection list in\n"\
"with those already on the list, using the given strategy.\n"\
"\n"\
"The second version merges the specified component with those already\n"\
"on the list."

#define _doc_SelectionList_remove \
"Removes the index'th item from the list. Raises IndexError if the\n"\
"index is out of range."

#define _doc_SelectionList_replace \
"Replaces the index'th item on the list with a new item. A component\n"\
"is passed as a tuple containing the MDagPath of the DAG node and an\n"\
"MObject containing the component. Raises IndexError if the index is\n"\
"out of range."

#define _doc_SelectionList_toggle \
"Removes from the list those elements of the given component which\n"\
"are already on it and adds those which are not."

py::enum_<MSelectionList::MergeStrategy>(SelectionList, "MergeStrategy")
    .value("kMergeNormal", MSelectionList::MergeStrategy::kMergeNormal)
    .value("kXORWithList", MSelectionList::MergeStrategy::kXORWithList)
    .value("kRemoveFromList", MSelectionList::MergeStrategy::kRemoveFromList)
    .export_values();

SelectionList
    .def(py::init<>())

    .def("__len__", [](MSelectionList & self) -> int {
        return self.length();
    }, _doc_SelectionList_len)

    .def("add", [](MSelectionList & self, MDagPath object, MObject component = MObject::kNullObj, bool mergeWithExisting = false) -> MSelectionList {
        throw std::logic_error{"Function not yet implemented."};
    }, py::arg("object"),
       py::arg_v("component", MObject::kNullObj, "Object.kNullObj"),
       py::arg("mergeWithExisting") = false,
       _doc_SelectionList_add)

    .def("add", [](MSelectionList & self, MObject object, bool mergeWithExisting = false) -> MSelectionList {
        throw std::logic_error{"Function not yet implemented."};
    }, py::arg("object"),
       py::arg("mergeWithExisting") = false,
       _doc_SelectionList_add)

    .def("add", [](MSelectionList & self, MPlug plug, bool mergeWithExisting = false) -> MSelectionList {
        throw std::logic_error{"Function not yet implemented."};
    }, py::arg("plug"),
       py::arg("mergeWithExisting") = false,
       _doc_SelectionList_add)

    .def("add", [](MSelectionList & self, std::string matchString) -> MSelectionList {
        MString match_string(matchString.c_str());
        MStatus status = self.add(match_string);

        if (!status)
        {
            MString error_msg("No object(s) match name '^1s'.");
                    error_msg.format(error_msg, match_string);

            throw std::invalid_argument(error_msg.asChar());
        }

        return self;
    }, py::arg("matchString"),
       _doc_SelectionList_add)

    .def("add", [](MSelectionList & self, std::string matchString, bool searchChildNamespacesToo = false) -> MSelectionList {
        throw std::logic_error{"Function not yet implemented."};
    }, py::arg("matchString"),
       py::arg("searchChildNamespacesToo") = false,
       _doc_SelectionList_add)

    .def("add", [](MSelectionList & self, MUuid uuid, bool mergeWithExisting = false) -> MSelectionList {
        throw std::logic_error{"Function not yet implemented."};
    }, py::arg("uuid"),
       py::arg("mergeWithExisting") = false,
       _doc_SelectionList_add)

    .def("clear", [](MSelectionList & self) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Empties the selection list.)pbdoc")

    .def("getDagPath", [](MSelectionList & self, unsigned int index) -> MDagPath {
        if (index >= self.length()) {
            MString error_msg;
                    error_msg += index;
            throw std::out_of_range(error_msg.asChar());
        }

        MDagPath result;

        MStatus status = self.getDagPath(index, result);

        if (!status) {
            throw pybind11::type_error("The specified item is not a DAG path.");
        }

        return result;
    }, py::arg("index"),
       _doc_SelectionList_getDagPath)

    .def("getDependNode", [](MSelectionList & self, unsigned int index) -> MObject {
        if (index >= self.length()) {
            MString error_msg;
                    error_msg += index;
            throw std::out_of_range(error_msg.asChar());
        }

        MObject result;
        MStatus status = self.getDependNode(index, result);

        if (!status) {
            throw pybind11::type_error("The specified item is not a dependency node.");
        }

        return result;
    }, py::arg("index"),
       _doc_SelectionList_getDependNode)

    .def("getPlug", [](MSelectionList & self, unsigned int index) -> MPlug {
        if (index >= self.length()) {
            MString error_msg;
                    error_msg += index;
            throw std::out_of_range(error_msg.asChar());
        }

        MStatus status;
        MPlug result;
        status = self.getPlug(index, result);

        if (!status) {
            throw pybind11::type_error("The specified item is not a plug.");
        }

        MObject attribute = result.attribute(&status);

        if (!status || attribute.isNull()) {
            throw pybind11::type_error("The specified item is not a plug.");
        }

        return result;    
    }, py::arg("index"),
       _doc_SelectionList_getPlug)

    .def("getSelectionStrings", [](MSelectionList & self) -> std::vector<std::string> {
        MStringArray strings;
        MStatus status = self.getSelectionStrings(strings);

        if (!status) {
            throw std::runtime_error("Failed to get selection strings.");
        }

        return atov::convert(strings);
    }, _doc_SelectionList_getSelectionStrings)

    .def("getSelectionStrings", [](MSelectionList & self, unsigned int index) -> std::vector<std::string> {
        if (index >= self.length()) {
            MString error_msg;
                    error_msg += index;
            throw std::out_of_range(error_msg.asChar());
        }
    
        MStringArray strings;
        MStatus status = self.getSelectionStrings(index, strings);

        if (!status) {
            throw std::runtime_error("Failed to get selection strings.");
        }

        return atov::convert(strings);
    }, py::arg("index"),
       _doc_SelectionList_getSelectionStrings)

    .def("hasItem", [](MSelectionList & self, MDagPath item, MObject component = MObject::kNullObj) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, py::arg("item"),
       py::arg_v("component", MObject::kNullObj, "Object.kNullObj"),
       _doc_SelectionList_hasItem)

    .def("hasItem", [](MSelectionList & self, MObject item) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, py::arg("item"),
       _doc_SelectionList_hasItem)

    .def("hasItem", [](MSelectionList & self, MPlug plug) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, py::arg("plug"),
       _doc_SelectionList_hasItem)

    .def("hasItemPartly", [](MSelectionList & self, MDagPath item, MObject component) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, py::arg("item"),
       py::arg("component"),
       _doc_SelectionList_hasItemPartly)

    .def("intersect", [](MSelectionList & self, MSelectionList other, bool expandToLeaves = false) {
        throw std::logic_error{"Function not yet implemented."};
    }, py::arg("other"),
       py::arg("expandToLeaves") = false,
       _doc_SelectionList_intersect)

    .def("isEmpty", [](MSelectionList & self) -> bool {
        return self.isEmpty();
    }, _doc_SelectionList_isEmpty)

    .def("merge", [](MSelectionList & self, MDagPath object, MObject component = MObject::kNullObj, MSelectionList::MergeStrategy strategy = MSelectionList::MergeStrategy::kMergeNormal) {
        throw std::logic_error{"Function not yet implemented."};
    }, py::arg("object"),
       py::arg_v("component", MObject::kNullObj, "Object.kNullObj"),
       py::arg("strategy ") = MSelectionList::MergeStrategy::kMergeNormal,
       _doc_SelectionList_merge)

    .def("merge", [](MSelectionList & self, MSelectionList other, MSelectionList::MergeStrategy strategy = MSelectionList::MergeStrategy::kMergeNormal) {
        throw std::logic_error{"Function not yet implemented."};
    }, py::arg("other"),
       py::arg("strategy") = MSelectionList::MergeStrategy::kMergeNormal,
       _doc_SelectionList_merge)

    .def("remove", [](MSelectionList & self, unsigned int index) {
        throw std::logic_error{"Function not yet implemented."};
    }, py::arg("index"),
       _doc_SelectionList_remove)

    .def("replace", [](MSelectionList & self, unsigned int index, MDagPath item, MObject component = MObject::kNullObj) {
        throw std::logic_error{"Function not yet implemented."};
    }, py::arg("index"),
       py::arg("item"),
       py::arg_v("component", MObject::kNullObj, "Object.kNullObj"),
       _doc_SelectionList_replace)

    .def("replace", [](MSelectionList & self, unsigned int index, MObject item) {
        throw std::logic_error{"Function not yet implemented."};
    }, py::arg("index"),
       py::arg("item"),
       _doc_SelectionList_replace)

    .def("replace", [](MSelectionList & self, unsigned int index, MPlug plug) {
        throw std::logic_error{"Function not yet implemented."};
    }, py::arg("index"),
       py::arg("plug"),
       _doc_SelectionList_replace)

    .def("toggle", [](MSelectionList & self, MDagPath item, MObject component = MObject::kNullObj) {
        throw std::logic_error{"Function not yet implemented."};
    }, py::arg("item"),
       py::arg_v("component", MObject::kNullObj, "Object.kNullObj"),
       _doc_SelectionList_toggle);