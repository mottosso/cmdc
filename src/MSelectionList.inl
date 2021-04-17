py::class_<MSelectionList> sel(m, "SelectionList");
py::enum_<MSelectionList::MergeStrategy>(sel, "MergeStrategy")
    .value("kMergeNormal", MSelectionList::MergeStrategy::kMergeNormal)
    .value("kXORWithList", MSelectionList::MergeStrategy::kXORWithList)
    .value("kRemoveFromList", MSelectionList::MergeStrategy::kRemoveFromList)
    .export_values();

 sel.def(py::init<>())

    .def("__len__", [](MSelectionList & self) -> int {
        return self.length();
    }, R"pbdoc(length() -> int

Returns the number of items on the selection list.)pbdoc")

    .def("add", [](MSelectionList & self, MDagPath object, MObject component = MObject::kNullObj, bool mergeWithExisting = false) -> MSelectionList {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(add(pattern, searchChildNamespaces=False) -> self
add(item, mergeWithExisting=True) -> self


The first version adds to the list any nodes, DAG paths, components
or plugs which match the given the pattern string.

The second version adds the specific item to the list, where the
item can be a plug (MPlug), a node (MObject), a DAG path (MDagPath)
or a component (tuple of (MDagPath, MObject) ).)pbdoc")

    .def("add", [](MSelectionList & self, MObject object, bool mergeWithExisting = false) -> MSelectionList {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(add(pattern, searchChildNamespaces=False) -> self
add(item, mergeWithExisting=True) -> self


The first version adds to the list any nodes, DAG paths, components
or plugs which match the given the pattern string.

The second version adds the specific item to the list, where the
item can be a plug (MPlug), a node (MObject), a DAG path (MDagPath)
or a component (tuple of (MDagPath, MObject) ).)pbdoc")

    .def("add", [](MSelectionList & self, MPlug plug, bool mergeWithExisting = false) -> MSelectionList {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(add(pattern, searchChildNamespaces=False) -> self
add(item, mergeWithExisting=True) -> self


The first version adds to the list any nodes, DAG paths, components
or plugs which match the given the pattern string.

The second version adds the specific item to the list, where the
item can be a plug (MPlug), a node (MObject), a DAG path (MDagPath)
or a component (tuple of (MDagPath, MObject) ).)pbdoc")

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
    }, R"pbdoc(add(Add the specified object(s) to the selection list.)pbdoc")

    .def("add", [](MSelectionList & self, std::string matchString, bool searchChildNamespacesToo = false) -> MSelectionList {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(add(pattern, searchChildNamespaces=False) -> self
add(item, mergeWithExisting=True) -> self


The first version adds to the list any nodes, DAG paths, components
or plugs which match the given the pattern string.

The second version adds the specific item to the list, where the
item can be a plug (MPlug), a node (MObject), a DAG path (MDagPath)
or a component (tuple of (MDagPath, MObject) ).)pbdoc")

    .def("add", [](MSelectionList & self, MUuid uuid, bool mergeWithExisting = false) -> MSelectionList {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(add(pattern, searchChildNamespaces=False) -> self
add(item, mergeWithExisting=True) -> self


The first version adds to the list any nodes, DAG paths, components
or plugs which match the given the pattern string.

The second version adds the specific item to the list, where the
item can be a plug (MPlug), a node (MObject), a DAG path (MDagPath)
or a component (tuple of (MDagPath, MObject) ).)pbdoc")

    .def("clear", [](MSelectionList & self) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(clear() -> self

Empties the selection list.)pbdoc")

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
    }, R"pbdoc(Returns the DAG path associated with the index'th item of the list.
Raises TypeError if the item is neither a DAG path nor a component.
Raises IndexError if index is out of range.)pbdoc")

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
    }, R"pbdoc(Returns the node associated with the index'th item, whether it be a
dependency node, DAG path, component or plug.

Raises TypeError if there is no dependency node associated with the current item.
Raises IndexError if index is out of range.)pbdoc")

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
    }, R"pbdoc(Returns the index'th item of the list as a plug. 
    
Raises TypeError if the item is not a plug. 
Raises IndexError if index is out of range.)pbdoc")

    .def("getSelectionStrings", [](MSelectionList & self) -> std::vector<std::string> {
        MStringArray strings;
        MStatus status = self.getSelectionStrings(strings);

        if (!status) {
            throw std::exception("Failed to get selection strings.");
        }

        std::vector<std::string> result(strings.length());

        for (unsigned int i = 0; i < strings.length(); i++) {
            result[i] = std::string(strings[i].asChar());
        }

        return result;
    }, R"pbdoc(getSelectionStrings(index=None) -> (string, string, ...)

Returns a tuple containing the string representation of the
specified item. For nodes, DAG paths, plugs and contiguous
components the tuple will only contain a single string, but for non-
contiguous components there will be a separate string for each
distinct block of contiguous elements. If index is not specified
then the string representations of all the items in the selection
list are returned. Raises IndexError if index is out of bounds.)pbdoc")

    .def("getSelectionStrings", [](MSelectionList & self, unsigned int index) -> std::vector<std::string> {
        if (index >= self.length()) {
            MString error_msg;
                    error_msg += index;
            throw std::out_of_range(error_msg.asChar());
        }
    
        MStringArray strings;
        MStatus status = self.getSelectionStrings(index, strings);

        if (!status) {
            throw std::exception("Failed to get selection strings.");
        }

        std::vector<std::string> result(strings.length());

        for (unsigned int i = 0; i < strings.length(); i++) {
            result[i] = std::string(strings[i].asChar());
        }

        return result;
    }, R"pbdoc(getSelectionStrings(index=None) -> (string, string, ...)

Returns a tuple containing the string representation of the
specified item. For nodes, DAG paths, plugs and contiguous
components the tuple will only contain a single string, but for non-
contiguous components there will be a separate string for each
distinct block of contiguous elements. If index is not specified
then the string representations of all the items in the selection
list are returned. Raises IndexError if index is out of bounds.)pbdoc")

    .def("hasItem", [](MSelectionList & self, MDagPath item, MObject component = MObject::kNullObj) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(hasItem(item) -> bool

Returns True if the given item is on the selection list. For a
component this means that all of the elements of the component must
be on the list. A component is passed as a tuple containing the
MDagPath of the DAG node and an MObject containing the component.)pbdoc")

    .def("hasItem", [](MSelectionList & self, MObject item) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(hasItem(item) -> bool

Returns True if the given item is on the selection list. For a
component this means that all of the elements of the component must
be on the list. A component is passed as a tuple containing the
MDagPath of the DAG node and an MObject containing the component.)pbdoc")

    .def("hasItem", [](MSelectionList & self, MPlug plug) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(hasItem(item) -> bool

Returns True if the given item is on the selection list. For a
component this means that all of the elements of the component must
be on the list. A component is passed as a tuple containing the
MDagPath of the DAG node and an MObject containing the component.)pbdoc")

    .def("hasItemPartly", [](MSelectionList & self, MDagPath item, MObject component) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(hasItemPartly(dagPath, component) -> bool

Returns True if at least one of the component's elements is on the
selection list. Raises TypeError if dagPath is invalid or component
does not contain a component.)pbdoc")

    .def("intersect", [](MSelectionList & self, MSelectionList other, bool expandToLeaves = false) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(intersect(other, expandToLeaves=False) -> self

Modify this list to contain the intersection of itself and the given list.)pbdoc")

    .def("isEmpty", [](MSelectionList & self) -> bool {
        return self.isEmpty();
    }, R"pbdoc(isEmpty() -> bool

Returns True if the selection list is empty.)pbdoc")

    .def("merge", [](MSelectionList & self, MDagPath object, MObject component = MObject::kNullObj, MSelectionList::MergeStrategy strategy = MSelectionList::MergeStrategy::kMergeNormal) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(merge(other, strategy=kMergeNormal) -> self
merge(dagPath, component, strategy=kMergeNormal) -> self

The first version merges the items from another selection list in
with those already on the list, using the given strategy.

The second version merges the specified component with those already
on the list.)pbdoc")

    .def("merge", [](MSelectionList & self, MSelectionList other, MSelectionList::MergeStrategy strategy = MSelectionList::MergeStrategy::kMergeNormal) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(merge(other, strategy=kMergeNormal) -> self
merge(dagPath, component, strategy=kMergeNormal) -> self

The first version merges the items from another selection list in
with those already on the list, using the given strategy.

The second version merges the specified component with those already
on the list.)pbdoc")

    .def("merge", [](MSelectionList & self, void, MSelectionList::MergeStrategy strategy) -> void {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(merge(other, strategy=kMergeNormal) -> self
merge(dagPath, component, strategy=kMergeNormal) -> self

The first version merges the items from another selection list in
with those already on the list, using the given strategy.

The second version merges the specified component with those already
on the list.)pbdoc")

    .def("remove", [](MSelectionList & self, unsigned int index) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(remove(index) -> self

Removes the index'th item from the list. Raises IndexError if the
index is out of range.)pbdoc")

    .def("replace", [](MSelectionList & self, unsigned int index, MDagPath item, MObject component = MObject::kNullObj) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(replace(index, newItem) -> self

Replaces the index'th item on the list with a new item. A component
is passed as a tuple containing the MDagPath of the DAG node and an
MObject containing the component. Raises IndexError if the index is
out of range.)pbdoc")

    .def("replace", [](MSelectionList & self, unsigned int index, MObject item) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(replace(index, newItem) -> self

Replaces the index'th item on the list with a new item. A component
is passed as a tuple containing the MDagPath of the DAG node and an
MObject containing the component. Raises IndexError if the index is
out of range.)pbdoc")

    .def("replace", [](MSelectionList & self, unsigned int index, MPlug plug) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(replace(index, newItem) -> self

Replaces the index'th item on the list with a new item. A component
is passed as a tuple containing the MDagPath of the DAG node and an
MObject containing the component. Raises IndexError if the index is
out of range.)pbdoc")

    .def("toggle", [](MSelectionList & self, MDagPath item, MObject component = MObject::kNullObj) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(toggle(dagPath, component) -> self

Removes from the list those elements of the given component which
are already on it and adds those which are not.)pbdoc");