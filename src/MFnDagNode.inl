py::class_<MFnDagNode>(m, "FnDagNode")
    .def(py::init<>())

    .def("addChild", [](MFnDagNode& self,
                        MObject& child,
                        unsigned int index = MFnDagNode::kNextPos,
                        bool keepExistingParents = false) {
        MStatus status = self.addChild(child, index, keepExistingParents);

        if (!status) {
            /**
             * There are three know possible reasons this might not work.
             * 
             */

            // 1. Not a valid pointer
            if (child.isNull()) {
                throw std::runtime_error("MObject was null.");
            }

            // 2. Not a DAG node
            if (!child.hasFn(MFn::kDagNode)) {
                MFnDagNode fn { child };
                MString message = fn.partialPathName();
                message += " was not a DAG node.";
                throw std::runtime_error(message.asChar());
            }

            // 3. Node does not exist
            MObjectHandle handle { child };
            if (!(handle.isValid() && handle.isAlive())) {
                throw std::runtime_error("MObject did not exist");
            }

            // 4. The docs don't say why this happens
            throw std::runtime_error("Undefined error occurred");
        }

    }, R"pbdoc(addChild(node, index=kNextPos, keepExistingParents=False)

Makes a node a child of this one.)pbdoc")

    .def("boundingBox", [](MFnDagNode& self) -> MBoundingBox {
        return self.boundingBox();
    }, R"pbdoc(Node's bounding box, in object space.)pbdoc")

    .def("child", [](MFnDagNode& self, unsigned int i) -> MObject {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(child(index) -> MObject

Returns the specified child of this node.)pbdoc")

    .def("childCount", [](MFnDagNode& self) -> int {
        return self.childCount();
    }, R"pbdoc(childCount() -> int

Returns the number of nodes which are children of this one.)pbdoc")

    .def("create", [](MFnDagNode& self, MString type, MObject parent = MObject::kNullObj) -> MObject {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(create(type, name=None, parent=MObject.kNullObj) -> MObject

Creates a new DAG node of the specified type, with the given name.
The type may be either a type name or a type ID. If no name is given
then a unique name will be generated by combining the type name with
an integer.

If a parent is given then the new node will be parented under it and
the functionset will be attached to the newly-created node. The
newly-created node will be returned.

If no parent is given and the new node is a transform, it will be
parented under the world and the functionset will be attached to the
newly-created transform. The newly-created transform will be returned.

If no parent is given and the new node is not a transform then a
transform node will be created under the world, the new node will be
parented under it, and the functionset will be attached to the
transform. The transform will be returned.)pbdoc")

    .def("create", [](MFnDagNode& self, MString type, MString name, MObject parent = MObject::kNullObj) -> MObject {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(create(type, name=None, parent=MObject.kNullObj) -> MObject

Creates a new DAG node of the specified type, with the given name.
The type may be either a type name or a type ID. If no name is given
then a unique name will be generated by combining the type name with
an integer.

If a parent is given then the new node will be parented under it and
the functionset will be attached to the newly-created node. The
newly-created node will be returned.

If no parent is given and the new node is a transform, it will be
parented under the world and the functionset will be attached to the
newly-created transform. The newly-created transform will be returned.

If no parent is given and the new node is not a transform then a
transform node will be created under the world, the new node will be
parented under it, and the functionset will be attached to the
transform. The transform will be returned.)pbdoc")

    .def("create", [](MFnDagNode& self, MTypeId typeId, MObject parent = MObject::kNullObj) -> MObject {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(create(type, name=None, parent=MObject.kNullObj) -> MObject

Creates a new DAG node of the specified type, with the given name.
The type may be either a type name or a type ID. If no name is given
then a unique name will be generated by combining the type name with
an integer.

If a parent is given then the new node will be parented under it and
the functionset will be attached to the newly-created node. The
newly-created node will be returned.

If no parent is given and the new node is a transform, it will be
parented under the world and the functionset will be attached to the
newly-created transform. The newly-created transform will be returned.

If no parent is given and the new node is not a transform then a
transform node will be created under the world, the new node will be
parented under it, and the functionset will be attached to the
transform. The transform will be returned.)pbdoc")

    .def("create", [](MFnDagNode& self, MTypeId typeId, MString name, MObject parent = MObject::kNullObj) -> MObject {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(create(type, name=None, parent=MObject.kNullObj) -> MObject

Creates a new DAG node of the specified type, with the given name.
The type may be either a type name or a type ID. If no name is given
then a unique name will be generated by combining the type name with
an integer.

If a parent is given then the new node will be parented under it and
the functionset will be attached to the newly-created node. The
newly-created node will be returned.

If no parent is given and the new node is a transform, it will be
parented under the world and the functionset will be attached to the
newly-created transform. The newly-created transform will be returned.

If no parent is given and the new node is not a transform then a
transform node will be created under the world, the new node will be
parented under it, and the functionset will be attached to the
transform. The transform will be returned.)pbdoc")

    .def("dagPath", [](MFnDagNode& self) -> MDagPath {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(dagPath() -> MDagPath

Returns the DAG path to which this function set is attached. Raises a TypeError if the function set is attached to an MObject rather than a path.)pbdoc")

    .def("dagRoot", [](MFnDagNode& self) -> MObject {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(dagRoot() -> MObject

Returns the root node of the first path leading to this node.)pbdoc")

    .def("duplicate", [](MFnDagNode& self, bool instance = false, bool instanceLeaf = false) -> MObject {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(duplicate(instance=False, instanceLeaf=False) -> MObject

Duplicates the DAG hierarchy rooted at the current node.)pbdoc")

    .def("fullPathName", [](MFnDagNode& self) -> MString {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(fullPathName() -> string

Returns the full path of the attached object, from the root of the DAG on down.)pbdoc")

    .def("getAllPaths", [](MFnDagNode& self) -> MDagPathArray {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(getAllPaths() -> MDagPathArray

Returns all of the DAG paths which lead to the object to which this function set is attached.)pbdoc")

    .def("getConnectedSetsAndMembers", [](MFnDagNode& self, unsigned int instanceNumber, bool renderableSetsOnly) -> std::tuple<MObjectArray, MObjectArray> {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(getConnectedSetsAndMembers(instance, renderableSetsOnly) -> (MObjectArray, MObjectArray)

Returns a tuple containing an array of sets and an array of the
components of the DAG object which are in those sets. If the entire object is in a set, then the corresponding entry in the comps array will have no elements in it.
)pbdoc")

    .def("getPath", [](MFnDagNode& self) -> MDagPath {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(getPath() -> MDagPath

Returns the DAG path to which this function set is attached, or the first path to the node if the function set is attached to an MObject.)pbdoc")

    .def("hasChild", [](MFnDagNode& self, MObject node) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(hasChild(node) -> bool

Returns True if the specified node is a child of this one.)pbdoc")

    .def("hasParent", [](MFnDagNode& self, MObject node) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(hasParent(node) -> bool

Returns True if the specified node is a parent of this one.)pbdoc")

    .def("inModel", [](MFnDagNode& self) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(True if the node has been added to the model.)pbdoc")

    .def("inUnderWorld", [](MFnDagNode& self) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(True if this node is in the underworld of another node (e.g. a curve on surface is in the underworld of the surface).)pbdoc")

    .def("instanceCount", [](MFnDagNode& self, bool total) -> int {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(instanceCount(indirect) -> int

Returns the number of instances for this node.)pbdoc")

    .def("isChildOf", [](MFnDagNode& self, MObject node) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(isChildOf(node) -> bool

Returns True if the specified node is a parent of this one.)pbdoc")

    .def("isInstanceable", [](MFnDagNode& self) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(True if instancing is allowed for this node.)pbdoc")

    .def("isInstanced", [](MFnDagNode& self, bool indirect = true) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(isInstanced(indirect=True) -> bool

Returns True if this node is instanced.)pbdoc")

    .def("isInstancedAttribute", [](MFnDagNode& self, MObject attr) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(isInstancedAttribute(attr) -> bool

Returns True if the specified attribute is an instanced attribute of this node.)pbdoc")

    .def("isIntermediateObject", [](MFnDagNode& self) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(True if this node is just an intermediate in part of a larger calculation (e.g. input to a deformer).)pbdoc")

    .def("isParentOf", [](MFnDagNode& self, MObject node) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(isParentOf(node) -> bool

Returns True if the specified node is a child of this one.)pbdoc")

    .def("objectColorRGB", [](MFnDagNode& self) -> MColor {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(RGB value indicating the color in which the node is to be drawn when inactive, assuming that it is drawable.)pbdoc")

    .def("objectColorType", [](MFnDagNode& self) -> MFnDagNode::MObjectColorType {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Determines whether the default color, indexed object color, orRGB object color is used for this object.)pbdoc")

    .def("parent", [](MFnDagNode& self, unsigned int i) -> MObject {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(parent(index) -> MObject

Returns the specified parent of this node.)pbdoc")

    .def("parentCount", [](MFnDagNode& self) -> int {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(parentCount() -> int

Returns the number of parents this node has.)pbdoc")

    .def("partialPathName", [](MFnDagNode& self) -> MString {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(partialPathName() -> string

Returns the minimum path string necessary to uniquely identify the attached object.)pbdoc")

    .def("removeChild", [](MFnDagNode& self) -> MObject {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(removeChild(node) -> self

Removes the child, specified by MObject, reparenting it under the world.)pbdoc")

    .def("removeChildAt", [](MFnDagNode& self, unsigned int index) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(removeChildAt(index) -> self

Removes the child, specified by index, reparenting it under the world.)pbdoc")

    .def("setObject", [](MFnDagNode& self) -> MObject {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(setObject(MObject or MDagPath) -> self

Attaches the function set to the specified node or DAG path.)pbdoc")

    .def("setObject", [](MFnDagNode& self, MDagPath path) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(setObject(MObject or MDagPath) -> self

Attaches the function set to the specified node or DAG path.)pbdoc")

    .def("transformationMatrix", [](MFnDagNode& self) -> MMatrix {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(transformationMatrix() -> MMatrix

Returns the object space transformation matrix for this DAG node.)pbdoc");