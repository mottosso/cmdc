#define _doc_DagModifier_createNode \
    "Adds an operation to the modifier to create a DAG node of the\n"\
    "specified type.\n"\
    "\n"\
    "If a parent DAG node is provided the new node will be parented\n"\
    "under it.\n"\
    "If no parent is provided and the new DAG node is a transform type then\n"\
    "it will be parented under the world.\n"\
    "In both of these cases the method returns the new DAG node.\n"\
    "\n"\
    "If no parent is provided and the new DAG node is not a transform type\n"\
    "then a transform node will be created and the child parented under that.\n"\
    "The new transform will be parented under the world and it is\n"\
    "the transform node which will be returned by the method, not the child.\n"\
    "\n"\
    "None of the newly created nodes will be added to the DAG until\n"\
    "the modifier's doIt() method is called.\n"\

#define _doc_DagModifier_reparentNode \
    "Adds an operation to the modifier to reparent a DAG node under\n"\
    "a specified parent.\n"\
    "\n"\
    "If no parent is provided then the DAG node will be reparented under\n"\
    "the world, so long as it is a transform type.\n"\
    "If it is not a transform type then the doIt() will raise a RuntimeError."


DagModifier
    .def(py::init<>())

    .def("createNode", [](MDagModifier & self, std::string type, MObject parent = MObject::kNullObj) -> MObject {
        if (!parent.isNull())
        {
            validate::has_fn(
                parent, MFn::kDagNode, 
                "Cannot createNode - 'parent' must be a 'kDagNode' object , not a '^1s' object."
            );
        }

        MString type_name(type.c_str());
        MStatus status;
        MObject result = self.createNode(type_name, parent, &status);

        if (status == MS::kInvalidParameter)
        {
            MString error_msg("Cannot create dependency node '^1s' - use DGModifier instead.");
                    error_msg.format(error_msg, type_name);
            throw pybind11::type_error(error_msg.asChar());
        } else if (result.isNull()) {
            MString error_msg("Cannot create unknown node type '^1s'.");
                    error_msg.format(error_msg, type_name);
            throw pybind11::type_error(error_msg.asChar());
        }

        CHECK_STATUS(status)

        return result;
    }, py::arg("type"),
       py::arg_v("parent", MObject::kNullObj, "Object.kNullObj"),
       _doc_DagModifier_createNode)

    .def("createNode", [](MDagModifier & self, MTypeId typeId, MObject parent = MObject::kNullObj) -> MObject {
        if (!parent.isNull())
        {
            validate::has_fn(
                parent, MFn::kDagNode, 
                "Cannot createNode - 'parent' must be a 'kDagNode' object , not a '^1s' object."
            );
        }

        MString type_id_str = MString() + typeId.id();

        MStatus status;
        MObject result = self.createNode(typeId, parent, &status);
        
        if (status == MS::kInvalidParameter)
        {
            MString error_msg("Cannot create dependency node with type ID '^1s'' - use DGModifier instead.");
                    error_msg.format(error_msg, type_id_str);
            throw pybind11::type_error(error_msg.asChar());
        } else if (result.isNull()) {
            MString error_msg("Cannot create unknown node with type ID '^1s'.");
                    error_msg.format(error_msg, type_id_str);
            throw pybind11::type_error(error_msg.asChar());
        }

        CHECK_STATUS(status)

        return result;
    }, py::arg("typeId"),
       py::arg_v("parent", MObject::kNullObj, "Object.kNullObj"),
       _doc_DagModifier_createNode)

    .def("reparentNode", [](MDagModifier & self, MObject node, MObject newParent = MObject::kNullObj) {
        validate::is_not_null(node, "Cannot reparent a null object.");

        if (!node.hasFn(MFn::kDagNode))
        {
            MString error_msg("Cannot parent '^1s' to '^2s' - must specify a 'kDagNode' object , not a '^3s' object.");
                    error_msg.format(
                        error_msg,
                        MFnDependencyNode(node).name(), 
                        newParent.isNull() ? "the world" : MFnDependencyNode(newParent).name(),
                        node.apiTypeStr()
                    );
            throw pybind11::type_error(error_msg.asChar());
        }
        if (!newParent.isNull())
        {
            if (!newParent.hasFn(MFn::kDagNode))
            {
                MString error_msg("Cannot parent '^1s' to '^2s' - must specify a 'kDagNode' object , not a '^3s' object.");
                        error_msg.format(
                            error_msg,
                            MFnDependencyNode(node).name(), 
                            newParent.isNull() ? "the world" : MFnDependencyNode(newParent).name(),
                            newParent.apiTypeStr()
                        );
                throw pybind11::type_error(error_msg.asChar());
            }
            
            MFnDagNode fn(newParent);

            if (fn.isChildOf(node))
            {
                MString error_msg("Cannot parent '^1s' to one of its children, '^2s'.");
                        error_msg.format(
                            error_msg,
                            MFnDagNode(node).partialPathName(), 
                            MFnDagNode(newParent).partialPathName()
                        );
                throw std::invalid_argument(error_msg.asChar());
            }
        }

        if (node == newParent)
        {
            MString error_msg("Cannot parent '^1s' to itself.");
                    error_msg.format(
                        error_msg,
                        MFnDagNode(node).partialPathName()
                    );
            throw std::invalid_argument(error_msg.asChar());
        }

        MStatus status = self.reparentNode(node, newParent);

        CHECK_STATUS(status)
    }, py::arg("node"),
       py::arg_v("newParent", MObject::kNullObj, "Object.kNullObj"),
       _doc_DagModifier_reparentNode);