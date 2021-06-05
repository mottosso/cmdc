py::class_<MDGModifier>(m, "DGModifier")
    .def(py::init<>())

    .def("addAttribute", [](MDGModifier & self, MObject node, MObject attribute) {
        if (node.isNull()) 
        {
            throw std::invalid_argument("Cannot add attribute to a null object.");
        } else if (!node.hasFn(MFn::kDependencyNode)) {
            MString error_msg("Cannot add attribute - 'node' must be a 'kDependencyNode' object, not a '^1s' object.");
                    error_msg.format(error_msg, node.apiTypeStr());
            throw pybind11::type_error(error_msg.asChar());
        } 

        if (attribute.isNull())
        {
            throw std::invalid_argument("Cannot add null attribute to an object.");
        } else if (!node.hasFn(MFn::kAttribute)) {
            MString error_msg("Cannot add attribute - 'attribute' must be a 'kAttribute' object, not a(n) '^1s' object.");
                    error_msg.format(error_msg, attribute.apiTypeStr());
            throw pybind11::type_error(error_msg.asChar());
        }

        MStatus status = self.addAttribute(node, attribute);

        CHECK_STATUS(status)
    }, 
R"pbdoc(Adds an operation to the modifier to add a new dynamic attribute to the given dependency node. 
If the attribute is a compound its children will ae added as well, so only the parent needs to be added using this method.)pbdoc")

    .def("addExtensionAttribute", [](MDGModifier & self, MNodeClass nodeClass, MObject attribute) {
        throw std::logic_error{"Function not yet implemented."};
    }, 
R"pbdoc(Adds an operation to the modifier to add a new extension attribute to the given node class. 
If the attribute is a compound its children will be added as well, so only the parent needs to be added using this method.)pbdoc")

    .def("commandToExecute", [](MDGModifier & self, MString command) {
        throw std::logic_error{"Function not yet implemented."};
    }, 
R"pbdoc(Adds an operation to the modifier to execute a MEL command. 
The command should be fully undoable otherwise unexpected results may occur. 
If  the command contains no undoable portions whatsoever, the call to doIt() may fail, 
but only after executing the command. It is best to use multiple commandToExecute() calls 
rather than batching multiple commands into a single call to commandToExecute(). 
They will still be undone together, as a single undo action by the user, 
but Maya will better be able to recover if one of the commands fails.)pbdoc")

    .def("connect", [](MDGModifier & self, MObject sourceNode, MObject sourceAttr, MObject destNode, MObject destAttr) {
        if (sourceNode.isNull()) 
        {
            throw std::invalid_argument("Cannot connect - sourceNode is null.");
        } else if (!sourceNode.hasFn(MFn::kDependencyNode)) {
            MString error_msg("Cannot connect - sourceNode must be a 'node' object , not a '^1s' object.");
                    error_msg.format(error_msg, sourceNode.apiTypeStr());
            throw pybind11::type_error(error_msg.asChar());
        }

        if (sourceAttr.isNull())
        {
            throw std::invalid_argument("Cannot connect - sourceAttr is null.");
        } else if (!sourceAttr.hasFn(MFn::kAttribute)) {
            MString error_msg("Cannot add attribute - sourceAttr must be a 'kAttribute' object, not a(n) '^1s' object.");
                    error_msg.format(error_msg, sourceAttr.apiTypeStr());
            throw pybind11::type_error(error_msg.asChar());
        } 

        if (destNode.isNull()) 
        {
            throw std::invalid_argument("Cannot connect - destNode is null.");
        } else if (!destNode.hasFn(MFn::kDependencyNode)) {
            MString error_msg("Cannot connect - destNode must be a 'kDependencyNode' object , not a '^1s' object.");
                    error_msg.format(error_msg, destNode.apiTypeStr());
            throw pybind11::type_error(error_msg.asChar());
        } 

        if (destAttr.isNull())
        {
            throw std::invalid_argument("Cannot connect - destAttr is null.");
        } else if (!destAttr.hasFn(MFn::kAttribute)) {
            MString error_msg("Cannot add attribute - destAttr must be a 'kAttribute' object, not a(n) '^1s' object.");
                    error_msg.format(error_msg, destAttr.apiTypeStr());
            throw pybind11::type_error(error_msg.asChar());
        }    
        
        // TODO: Once the MFnAttribute classes are implemented, 
        // add additional validation to ensure that the attributes can be connected  
        MStatus status = self.connect(sourceNode, sourceAttr, destNode, destAttr);

        CHECK_STATUS(status)
        }, 
R"pbdoc(Adds an operation to the modifier that connects two plugs in the dependency graph. 
It is the user's responsibility to ensure that the source and destination attributes are of compatible types. 
For instance, if the source attribute is a nurbs surface then the destination must also be a nurbs surface.)pbdoc")

    .def("connect", [](MDGModifier & self, MPlug source, MPlug dest) {
        if (source.isNull()) 
        {
            throw std::invalid_argument("Cannot connect - source is null.");
        } 

        if (dest.isNull()) 
        {
            throw std::invalid_argument("Cannot connect - dest is null.");
        }   

        // TODO: Once the MFnAttribute classes are implemented, 
        // add additional validation to ensure that the attributes can be connected
        MStatus status = self.connect(source, dest);

        CHECK_STATUS(status)
    }, 
R"pbdoc(Adds an operation to the modifier that connects two plugs in the dependency graph. 
It is the user's responsibility to ensure that the source and destination attributes are of compatible types. 
For instance, if the source attribute is a nurbs surface then the destination must also be a nurbs surface.)pbdoc")

    .def("createNode", [](MDGModifier & self, std::string type) -> MObject {
        MString type_name(type.c_str());

        MStatus status;
        MObject result = self.createNode(type_name, &status);

        if (result.isNull())
        {
            MString error_msg("Cannot create unknown node type '^1s'.");
                    error_msg.format(error_msg, type_name);
            throw pybind11::type_error(error_msg.asChar());
        } else if (result.hasFn(MFn::kDagNode)) { 
            MString error_msg("Cannot create DAG node '^1s' - use DAGModifier instead.");
                    error_msg.format(error_msg, type_name);
            throw pybind11::type_error(error_msg.asChar());
        }

        return result;
    }, 
R"pbdoc(Adds an operation to the modifier to create a node of the given type.
The new node is created and returned but will not be added to the dependency graph until the modifier's doIt() method is called. 
Raises TypeError if the named node type does not exist or if it is a DAG node type.)pbdoc")

    .def("createNode", [](MDGModifier & self, MTypeId typeId) -> MObject {
        MString type_id_str = MString() + typeId.id();

        MStatus status;
        MObject result = self.createNode(typeId, &status);

        if (result.isNull())
        {
            MString error_msg("Cannot create unknown node with type ID '^1s'.");
                    error_msg.format(error_msg, type_id_str);
            throw pybind11::type_error(error_msg.asChar());
        } else if (result.hasFn(MFn::kDagNode)) { 
            MString error_msg("Cannot create DAG node with type ID '^1s' - use DAGModifier instead.");
                    error_msg.format(error_msg, type_id_str);
            throw pybind11::type_error(error_msg.asChar());
        }

        return result;
    }, 
R"pbdoc(Adds an operation to the modifier to create a node of the given type. 
The new node is created and returned but will not be added to the dependency graph until the modifier's doIt() method is called. 
Raises TypeError if the named node type does not exist or if it is a DAG node type.)pbdoc")

    .def("deleteNode", [](MDGModifier & self, MObject node) {
        if (node.isNull()) 
        {
            throw std::invalid_argument("Cannot delete a null object.");
        } else if (!node.hasFn(MFn::kDependencyNode)) {
            MString error_msg("Cannot delete a(n) '^1s' object.");
                    error_msg.format(error_msg, node.apiTypeStr());
            throw pybind11::type_error(error_msg.asChar());
        } else if (node.hasFn(MFn::kDagNode)) {
            MString error_msg("Cannot delete a(n) DAG object - use DAGModifier instead.");
                    error_msg.format(error_msg, node.apiTypeStr());
            throw pybind11::type_error(error_msg.asChar());
        }
    
        MStatus status = self.deleteNode(node);

        CHECK_STATUS(status)
    }, 
R"pbdoc(Adds an operation to the modifier which deletes the specified node from the dependency graph. 

If deleteNode() is called to delete nodes in a graph while other items are also in the queue, 
it might end up deleting the nodes before all the other tasks in the queue. 

In order to prevent unexpected outcomes, the modifier's doIt() should be called before the deleteNode 
operation is added so that the queue is emptied. Then, deleteNode() can be called and added to the queue. 
doIt() should be called immediately after to ensure that the queue is emptied before any other operations are added to it.)pbdoc")

    .def("disconnect", [](MDGModifier & self, MObject sourceNode, MObject sourceAttr, MObject destNode, MObject destAttr) {
        if (sourceNode.isNull()) 
        {
            throw std::invalid_argument("Cannot disconnect - sourceNode is null.");
        } else if (!sourceNode.hasFn(MFn::kDependencyNode)) {
            MString error_msg("Cannot disconnect - sourceNode must be a 'node' object , not a '^1s' object.");
                    error_msg.format(error_msg, sourceNode.apiTypeStr());
            throw pybind11::type_error(error_msg.asChar());
        }

        if (sourceAttr.isNull())
        {
            throw std::invalid_argument("Cannot disconnect - sourceAttr is null.");
        } else if (!sourceAttr.hasFn(MFn::kAttribute)) {
            MString error_msg("Cannot add attribute - sourceAttr must be a 'kAttribute' object, not a(n) '^1s' object.");
                    error_msg.format(error_msg, sourceAttr.apiTypeStr());
            throw pybind11::type_error(error_msg.asChar());
        } 

        if (destNode.isNull()) 
        {
            throw std::invalid_argument("Cannot disconnect - destNode is null.");
        } else if (!destNode.hasFn(MFn::kDependencyNode)) {
            MString error_msg("Cannot disconnect - destNode must be a 'kDependencyNode' object , not a '^1s' object.");
                    error_msg.format(error_msg, destNode.apiTypeStr());
            throw pybind11::type_error(error_msg.asChar());
        } 

        if (destAttr.isNull())
        {
            throw std::invalid_argument("Cannot disconnect - destAttr is null.");
        } else if (!destAttr.hasFn(MFn::kAttribute)) {
            MString error_msg("Cannot add attribute - destAttr must be a 'kAttribute' object, not a(n) '^1s' object.");
                    error_msg.format(error_msg, destAttr.apiTypeStr());
            throw pybind11::type_error(error_msg.asChar());
        }    
        
        MStatus status = self.disconnect(sourceNode, sourceAttr, destNode, destAttr);
        CHECK_STATUS(status)
    }, R"pbdoc(Adds an operation to the modifier that breaks a connection between two plugs in the dependency graph.)pbdoc")

    .def("disconnect", [](MDGModifier & self, MPlug source, MPlug dest) {
        if (source.isNull()) 
        {
            throw std::invalid_argument("Cannot disconnect - source is null.");
        } 

        if (dest.isNull()) 
        {
            throw std::invalid_argument("Cannot disconnect - dest is null.");
        }   

        MStatus status = self.disconnect(source, dest);
        CHECK_STATUS(status)    
    }, R"pbdoc(Adds an operation to the modifier that breaks a connection between two plugs in the dependency graph.)pbdoc")

    .def("doIt", [](MDGModifier & self) {
        MStatus status = self.doIt();

        if (!status)
        {
            throw std::runtime_error(status.errorString().asChar());
        }
    }, 
R"pbdoc(Executes the modifier's operations. 
    
If doIt() is called multiple times in a row, without any intervening calls to undoIt(), 
then only the operations which were added since the previous doIt() call will be executed. 

If undoIt() has been called then the next call to doIt() will do all operations.)pbdoc")

    .def("linkExtensionAttributeToPlugin", [](MDGModifier & self, MObject plugin, MObject attribute) {        
        if (plugin.isNull())
        {
            throw std::invalid_argument("Cannot link extension attribute from a null plugin.");
        } else if (!plugin.hasFn(MFn::kPlugin))
        {
            MString error_msg("Cannot link extension attribute from plugin - must specify a 'kPlugin' object, not a '^1s' object.");
                    error_msg.format(error_msg, plugin.apiTypeStr());
            throw pybind11::type_error(error_msg.asChar());
        }

        if (attribute.isNull())
        {
            throw std::invalid_argument("Cannot link null extension attribute from a plugin.");
        } else if (!attribute.hasFn(MFn::kAttribute)) {
            MString error_msg("Cannot link extension attribute - 'attribute' must be a 'kAttribute' object, not a(n) '^1s' object.");
                    error_msg.format(error_msg, attribute.apiTypeStr());
            throw pybind11::type_error(error_msg.asChar());
        }

        MStatus status = self.linkExtensionAttributeToPlugin(plugin, attribute);

        CHECK_STATUS(status)
    }, 
R"pbdoc(The plugin can call this method to indicate that the extension attribute defines part of the plugin, regardless of the node type to which it attaches itself. 

This requirement is used when the plugin is checked to see if it is in use or if is able to be unloaded or if it is required as part of a stored file. 
For compound attributes only the topmost parent attribute may be passed in and all of its children will be included, recursively. 
Thus it's not possible to link a child attribute to a plugin by itself. 

Note that the link is established immediately and is not affected by the modifier's doIt() or undoIt() methods.)pbdoc")

    .def("newPlugValue", [](MDGModifier & self, MPlug plug, MObject value) {
        plug::assert_not_null(plug);

        MStatus status = self.newPlugValue(plug, value);

        CHECK_STATUS(status);
    }, R"pbdoc(Adds an operation to the modifier to set the value of a plug, where value is an MObject data wrapper, such as created by the various MFn*Data classes.)pbdoc")

    .def("newPlugValueBool", [](MDGModifier & self, MPlug plug, bool value) {
        plug::assert_not_null(plug);

        MStatus status = self.newPlugValueBool(plug, value);

        CHECK_STATUS(status);
    }, R"pbdoc(Adds an operation to the modifier to set a value onto a bool plug.)pbdoc")

    .def("newPlugValueChar", [](MDGModifier & self, MPlug plug, int value) {
        plug::assert_not_null(plug);

        MStatus status = self.newPlugValueChar(plug, value);

        CHECK_STATUS(status);
    }, R"pbdoc(Adds an operation to the modifier to set a value onto a char (single byte signed integer) plug.)pbdoc")

    .def("newPlugValueDouble", [](MDGModifier & self, MPlug plug, double value) {
        plug::assert_not_null(plug);

        MStatus status = self.newPlugValueDouble(plug, value);

        CHECK_STATUS(status);
    }, R"pbdoc(Adds an operation to the modifier to set a value onto a double-precision float plug.)pbdoc")

    .def("newPlugValueFloat", [](MDGModifier & self, MPlug plug, float value) {
        plug::assert_not_null(plug);

        MStatus status = self.newPlugValueFloat(plug, value);

        CHECK_STATUS(status);
    }, R"pbdoc(Adds an operation to the modifier to set a value onto a single-precision float plug.)pbdoc")

    .def("newPlugValueInt", [](MDGModifier & self, MPlug plug, int value) {
        plug::assert_not_null(plug);

        MStatus status = self.newPlugValueInt(plug, value);

        CHECK_STATUS(status);
    }, R"pbdoc(Adds an operation to the modifier to set a value onto an int plug.)pbdoc")

    .def("newPlugValueMAngle", [](MDGModifier & self, MPlug plug, MAngle value) {
        plug::assert_not_null(plug);

        MStatus status = self.newPlugValueMAngle(plug, value);

        CHECK_STATUS(status);
    }, R"pbdoc(Adds an operation to the modifier to set a value onto an angle plug.)pbdoc")

    .def("newPlugValueMDistance", [](MDGModifier & self, MPlug plug, MDistance value) {
        plug::assert_not_null(plug);

        MStatus status = self.newPlugValueMDistance(plug, value);

        CHECK_STATUS(status);
    }, R"pbdoc(Adds an operation to the modifier to set a value onto a distance plug.)pbdoc")

    .def("newPlugValueMTime", [](MDGModifier & self, MPlug plug, MTime value) {
        plug::assert_not_null(plug);

        MStatus status = self.newPlugValueMTime(plug, value);

        CHECK_STATUS(status);
    }, R"pbdoc(Adds an operation to the modifier to set a value onto a time plug.)pbdoc")

    .def("newPlugValueShort", [](MDGModifier & self, MPlug plug, short value) {
        plug::assert_not_null(plug);

        MStatus status = self.newPlugValueShort(plug, value);

        CHECK_STATUS(status);
    }, R"pbdoc(Adds an operation to the modifier to set a value onto a short integer plug.)pbdoc")

    .def("newPlugValueString", [](MDGModifier & self, MPlug plug, std::string value) {
        plug::assert_not_null(plug);

        MStatus status = self.newPlugValueString(plug, MString(value.c_str()));

        CHECK_STATUS(status);
    }, R"pbdoc(Adds an operation to the modifier to set a value onto a string plug.)pbdoc")

    .def("pythonCommandToExecute", [](MDGModifier & self, MString command) {
        throw std::logic_error{"Function not yet implemented."};
    },     
R"pbdoc(Adds an operation to the modifier to execute a Python command, 
which can be passed as either a Python callable or a string containing the text of the Python code to be executed. 

The command should be fully undoable otherwise unexpected results may occur. 

If the command contains no undoable portions whatsoever, the call to doIt() may fail, but only after executing the command. 
It is best to use multiple calls rather than batching multiple commands into a single call to pythonCommandToExecute(). 
They will still be undone together, as a single undo action by the user, 
but Maya will better be able to recover if one of the commands fails.)pbdoc")

    .def("removeAttribute", [](MDGModifier & self, MObject node, MObject attribute) {        
        if (node.isNull()) 
        {
            throw std::invalid_argument("Cannot remove an attribute from a null node.");
        } else if (!node.hasFn(MFn::kDependencyNode)) {
            MString error_msg("Cannot remove attribute - node must be a 'node' object , not a '^1s' object.");
                    error_msg.format(error_msg, node.apiTypeStr());
            throw pybind11::type_error(error_msg.asChar());
        }

        if (attribute.isNull())
        {
            throw std::invalid_argument("Cannot remove a null attribute.");
        } else if (!attribute.hasFn(MFn::kAttribute)) {
            MString error_msg("Cannot remove attribute - 'attribute' must be a 'kAttribute' object, not a(n) '^1s' object.");
                    error_msg.format(error_msg, attribute.apiTypeStr());
            throw pybind11::type_error(error_msg.asChar());
        } 

        MStatus status = self.removeAttribute(node, attribute);

        CHECK_STATUS(status)
    }, 
R"pbdoc(Adds an operation to the modifier to remove a dynamic attribute from the given dependency node. 
If the attribute is a compound its children will be removed as well, so only the parent needs to be removed using this method.  
The attribute MObject passed in will be set to kNullObj. 

There should be no function sets attached to the attribute at the time of the call as their behaviour may become unpredictable.)pbdoc")

    .def("removeExtensionAttribute", [](MDGModifier & self, MNodeClass nodeClass, MObject attribute) {
        if (attribute.isNull())
        {
            throw std::invalid_argument("Cannot remove null extension attribute.");
        } else if (!attribute.hasFn(MFn::kAttribute)) {
            MString error_msg("Cannot remove extension attribute - 'attribute' must be a 'kAttribute' object, not a(n) '^1s' object.");
                    error_msg.format(error_msg, attribute.apiTypeStr());
            throw pybind11::type_error(error_msg.asChar());
        }

        MStatus status = self.removeExtensionAttribute(nodeClass, attribute);

        CHECK_STATUS(status)
    }, 
R"pbdoc(Adds an operation to the modifier to remove an extension attribute from the given node class. 
If the attribute is a compound its children will be removed as well, so only the parent needs to be removed using this method. 
The attribute MObject passed in will be set to kNullObj. 

There should be no function sets attached to the attribute at the time of the call as their behaviour may become unpredictable.)pbdoc")

    .def("removeExtensionAttributeIfUnset", [](MDGModifier & self, MNodeClass nodeClass, MObject attribute) {
        if (attribute.isNull())
        {
            throw std::invalid_argument("Cannot remove null extension attribute (if unset).");
        } else if (!attribute.hasFn(MFn::kAttribute)) {
            MString error_msg("Cannot remove extension attribute (if unset) - 'attribute' must be a 'kAttribute' object, not a(n) '^1s' object.");
                    error_msg.format(error_msg, attribute.apiTypeStr());
            throw pybind11::type_error(error_msg.asChar());
        }

        MStatus status = self.removeExtensionAttribute(nodeClass, attribute);

        CHECK_STATUS(status)    }, 
R"pbdoc(Adds an operation to the modifier to remove an extension attribute from the given node class,
but only if there are no nodes in the graph with non-default values for this attribute. 
If the attribute is a compound its children will be removed as well, so only the parent needs to be removed using this method. 
The attribute MObject passed in will be set to kNullObj. 

There should be no function sets attached to the attribute at the time of the call as their behaviour may become unpredictable.)pbdoc")

    .def("removeMultiInstance", [](MDGModifier & self, MPlug plug, bool breakConnections) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Adds an operation to the modifier to remove an element of a multi (array) plug.)pbdoc")

    .def("renameAttribute", [](MDGModifier & self, MObject node, MObject attribute, MString shortName, MString longName) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Adds an operation to the modifer that renames a dynamic attribute on the given dependency node.)pbdoc")

    .def("renameNode", [](MDGModifier & self, MObject node, MString newName) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Adds an operation to the modifer to rename a node.)pbdoc")

    .def("setNodeLockState", [](MDGModifier & self, MObject node, bool newState) {
        if (node.isNull()) 
        {
            throw std::invalid_argument("Cannot un/lock a null node.");
        } else if (!node.hasFn(MFn::kDependencyNode)) {
            MString error_msg("Cannot un/lock object - 'node' must be a 'kDependencyNode' object , not a '^1s' object.");
                    error_msg.format(error_msg, node.apiTypeStr());
            throw pybind11::type_error(error_msg.asChar());
        }

        MStatus status = self.setNodeLockState(node, newState);

        CHECK_STATUS(status)
    }, R"pbdoc(Adds an operation to the modifier to set the lockState of a node.)pbdoc")

    .def("undoIt", [](MDGModifier & self) {
        MStatus status = self.undoIt();

        if (!status)
        {
            throw std::runtime_error(status.errorString().asChar());
        }
    }, R"pbdoc(Undoes all of the operations that have been given to this modifier. It is only valid to call this method after the doIt() method has been called.)pbdoc")

    .def("unlinkExtensionAttributeFromPlugin", [](MDGModifier & self, MObject plugin, MObject attribute) {
        if (plugin.isNull())
        {
            throw std::invalid_argument("Cannot unlink extension attribute from a null plugin.");
        } else if (!plugin.hasFn(MFn::kPlugin))
        {
            MString error_msg("Cannot unlink extension attribute from plugin - must specify a 'kPlugin' object, not a '^1s' object.");
                    error_msg.format(error_msg, plugin.apiTypeStr());
            throw pybind11::type_error(error_msg.asChar());
        }

        if (attribute.isNull())
        {
            throw std::invalid_argument("Cannot unlink null extension attribute from a plugin.");
        } else if (!attribute.hasFn(MFn::kAttribute)) {
            MString error_msg("Cannot unlink extension attribute - 'attribute' must be a 'kAttribute' object, not a(n) '^1s' object.");
                    error_msg.format(error_msg, attribute.apiTypeStr());
            throw pybind11::type_error(error_msg.asChar());
        }

        MStatus status = self.unlinkExtensionAttributeFromPlugin(plugin, attribute);

        CHECK_STATUS(status)
    }, 
R"pbdoc(The plugin can call this method to indicate that it no longer requires an extension attribute for its operation. 
This requirement is used when the plugin is checked to see if it is in use, or if is able to be unloaded, or if it is required as part of a stored file. 
For compound attributes only the topmost parent attribute may be passed in and all of its children will be unlinked, recursively. 
Thus it's not possible to unlink a child attribute from a plugin by itself. 

Note that the link is broken immediately and is not affected by the modifier's doIt() or undoIt() methods.)pbdoc");