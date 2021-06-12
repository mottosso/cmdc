#ifndef DGMODIFIER_INL
#define DGMODIFIER_INL
#define _doc_DGModifier_addAttribute \
    "Adds an operation to the modifier to add a new dynamic attribute to\n"\
    "the given dependency node.\n"\
    "If the attribute is a compound its children will ae added as well, so\n"\
    "only the parent needs to be added using this method."

#define _doc_DGModifier_addExtensionAttribute \
    "Adds an operation to the modifier to add a new extension attribute to\n"\
    "the given node class.\n"\
    "If the attribute is a compound its children will be added as well, so\n"\
    "only the parent needs to be added using this method."

#define _doc_DGModifier_commandToExecute \
    "Adds an operation to the modifier to execute a MEL command.\n"\
    "The command should be fully undoable otherwise unexpected results\n"\
    "may occur.\n"\
    "If  the command contains no undoable portions whatsoever, the call to\n"\
    "doIt() may fail, but only after executing the command. It is best to\n"\
    "use multiple commandToExecute() calls rather than batching multiple\n"\
    "commands into a single call to commandToExecute().\n"\
    "They will still be undone together, as a single undo action by\n"\
    "the user but Maya will better be able to recover if one of the\n"\
    "commands fails."

#define _doc_DGModifier_connect \
    "Adds an operation to the modifier that connects two plugs in\n"\
    "the dependency graph.\n"\
    "It is the user's responsibility to ensure that the source and\n"\
    "destination attributes are of compatible types.\n"\
    "For instance, if the source attribute is a nurbs surface then the\n"\
    "destination must also be a nurbs surface."

#define _doc_DGModifier_createNode \
    "Adds an operation to the modifier to create a node of the given type.\n"\
    "The new node is created and returned but will not be added to\n"\
    "the dependency graph until the modifier's doIt() method is called.\n"\
    "\n"\
    "Raises TypeError if the named node type does not exist or if it is a DAG\n"\
    "node type."

#define _doc_DGModifier_deleteNode \
    "Adds an operation to the modifier which deletes the specified node\n"\
    "from the dependency graph.\n"\
    "\n"\
    "If deleteNode() is called to delete nodes in a graph while other items\n"\
    "are also in the queue, it might end up deleting the nodes before all\n"\
    "the other tasks in the queue.\n"\
    "\n"\
    "In order to prevent unexpected outcomes, the modifier's doIt() should\n"\
    "be called before the deleteNode operation is added so that the queue\n"\
    "is emptied. Then, deleteNode() can be called and added to the queue.\n"\
    "doIt() should be called immediately after to ensure that the queue is\n"\
    "emptied before any other operations are added to it."

#define _doc_DGModifier_disconnect \
    "Adds an operation to the modifier that breaks a connection between\n"\
    "two plugs in the dependency graph."

#define _doc_DGModifier_doIt \
    "Executes the modifier's operations.\n"\
    "\n"\
    "If doIt() is called multiple times in a row, without any\n"\
    "intervening calls to undoIt(), then only the operations which were\n"\
    "added since the previous doIt() call will be executed.\n"\
    "\n"\
    "If undoIt() has been called then the next call to doIt() will do\n"\
    "all operations."

#define _doc_DGModifier_linkExtensionAttributeToPlugin \
    "The plugin can call this method to indicate that the extension\n"\
    "attribute defines part of the plugin, regardless of the node type\n"\
    "to which it attaches itself.\n"\
    "\n"\
    "This requirement is used when the plugin is checked to see if it is\n"\
    "in use or if is able to be unloaded or if it is required as part of\n"\
    "a stored file.\n"\
    "For compound attributes only the topmost parent attribute may be\n"\
    "passed in and all of its children will be included, recursively.\n"\
    "Thus it's not possible to link a child attribute to a plugin by itself.\n"\
    "\n"\
    "Note that the link is established immediately and is not affected by\n"\
    "the modifier's doIt() or undoIt() methods."

#define _doc_DGModifier_newPlugValue \
    "Adds an operation to the modifier to set the value of a plug, where\n"\
    "value is an MObject data wrapper, such as created by the various\n"\
    "MFn*Data classes."

#define _doc_DGModifier_newPlugValueBool \
    "Adds an operation to the modifier to set a value onto a bool plug."

#define _doc_DGModifier_newPlugValueChar \
    "Adds an operation to the modifier to set a value onto a char\n"\
    "(single byte signed integer) plug."

#define _doc_DGModifier_newPlugValueDouble \
    "Adds an operation to the modifier to set a value onto a\n"\
    "double-precision float plug."

#define _doc_DGModifier_newPlugValueFloat \
    "Adds an operation to the modifier to set a value onto a\n"\
    "single-precision float plug."

#define _doc_DGModifier_newPlugValueInt \
    "Adds an operation to the modifier to set a value onto an int plug."

#define _doc_DGModifier_newPlugValueMAngle \
    "Adds an operation to the modifier to set a value onto an angle plug."

#define _doc_DGModifier_newPlugValueMDistance \
    "Adds an operation to the modifier to set a value onto a distance plug."

#define _doc_DGModifier_newPlugValueMTime \
    "Adds an operation to the modifier to set a value onto a time plug."

#define _doc_DGModifier_newPlugValueShort \
    "Adds an operation to the modifier to set a value onto a short integer plug."

#define _doc_DGModifier_newPlugValueString \
    "Adds an operation to the modifier to set a value onto a string plug."

#define _doc_DGModifier_pythonCommandToExecute \
    "Adds an operation to the modifier to execute a Python command, which\n"\
    "can be passed as either a Python callable or a string containing the\n"\
    "text of the Python code to be executed.\n"\
    "\n"\
    "The command should be fully undoable otherwise unexpected results\n"\
    "may occur.\n"\
    "\n"\
    "If the command contains no undoable portions whatsoever, the call\n"\
    "to doIt() may fail, but only after executing the command.\n"\
    "It is best to use multiple calls rather than batching multiple\n"\
    "commands into a single call to pythonCommandToExecute().\n"\
    "They will still be undone together, as a single undo action by the user,\n"\
    "but Maya will better be able to recover if one of the commands fails."

#define _doc_DGModifier_removeAttribute \
    "Adds an operation to the modifier to remove a dynamic attribute from\n"\
    "the given dependency node.\n"\
    "If the attribute is a compound its children will be removed as well,\n"\
    "so only the parent needs to be removed using this method.\n"\
    "The attribute MObject passed in will be set to kNullObj.\n"\
    "\n"\
    "There should be no function sets attached to the attribute at the time\n"\
    "of the call as their behaviour may become unpredictable."

#define _doc_DGModifier_removeExtensionAttribute \
    "Adds an operation to the modifier to remove an extension attribute\n"\
    "from the given node class.\n"\
    "If the attribute is a compound its children will be removed as well,\n"\
    "so only the parent needs to be removed using this method.\n"\
    "The attribute MObject passed in will be set to kNullObj.\n"\
    "\n"\
    "There should be no function sets attached to the attribute at the time\n"\
    "of the call as their behaviour may become unpredictable."

#define _doc_DGModifier_removeExtensionAttributeIfUnset \
    "Adds an operation to the modifier to remove an extension attribute\n"\
    "from the given node class, but only if there are no nodes in the\n"\
    "graph with non-default values for this attribute.\n"\
    "If the attribute is a compound its children will be removed as well,\n"\
    "so only the parent needs to be removed using this method.\n"\
    "The attribute MObject passed in will be set to kNullObj.\n"\
    "\n"\
    "There should be no function sets attached to the attribute at the time\n"\
    "of the call as their behaviour may become unpredictable."

#define _doc_DGModifier_removeMultiInstance \
    "Adds an operation to the modifier to remove an element of a multi\n"\
    "(array) plug."

#define _doc_DGModifier_renameAttribute \
    "Adds an operation to the modifer that renames a dynamic attribute on\n"\
    "the given dependency node."

#define _doc_DGModifier_renameNode \
    "Adds an operation to the modifer to rename a node."

#define _doc_DGModifier_setNodeLockState \
    "Adds an operation to the modifier to set the lockState of a node."

#define _doc_DGModifier_undoIt \
    "Undoes all of the operations that have been given to this modifier.\n"\
    "It is only valid to call this method after the doIt() method has been called."

#define _doc_DGModifier_unlinkExtensionAttributeFromPlugin \
    "The plugin can call this method to indicate that it no longer requires\n"\
    "an extension attribute for its operation.\n"\
    "This requirement is used when the plugin is checked to see if it is\n"\
    "in use, or if is able to be unloaded, or if it is required as part of a stored file.\n"\
    "For compound attributes only the topmost parent attribute may be\n"\
    "passed in and all of its children will be unlinked, recursively.\n"\
    "Thus it's not possible to unlink a child attribute from a plugin\n"\
    "by itself.\n"\
    "\n"\
    "Note that the link is broken immediately and is not affected by\n"\
    "the modifier's doIt() or undoIt() methods."

DGModifier
    .def(py::init<>())

    .def("addAttribute", [](MDGModifier & self, MObject node, MObject attribute) {
        validate::is_not_null(node, "Cannot add attribute to a null object.");
        validate::has_fn(
            node, MFn::kDependencyNode, 
            "Cannot add attribute - 'node' must be a 'kDependencyNode' object, not a(n) '^1s' object."
        );

        validate::is_not_null(attribute, "Cannot add null attribute to a node.");
        validate::has_fn(
            attribute, MFn::kAttribute, 
            "Cannot add attribute - 'attribute' must be a 'kAttribute' object, not a(n) '^1s' object."
        );
    
        MStatus status = self.addAttribute(node, attribute);

        CHECK_STATUS(status)
    }, py::arg("node"),
       py::arg("attribute"),
       _doc_DGModifier_addAttribute)

    .def("addExtensionAttribute", [](MDGModifier & self, MNodeClass nodeClass, MObject attribute) {
        validate::is_not_null(attribute, "Cannot add null extension attribute.");
        validate::has_fn(
            attribute, MFn::kAttribute, 
            "Cannot add extension attribute - 'attribute' must be a 'kAttribute' object, not a(n) '^1s' object."
        );

        MStatus status = self.addExtensionAttribute(nodeClass, attribute);

        CHECK_STATUS(status)
    }, py::arg("nodeClass"),
       py::arg("attribute"),
       _doc_DGModifier_addExtensionAttribute)

    .def("commandToExecute", [](MDGModifier & self, std::string command) {
        if (command.empty())
        {
            throw std::invalid_argument("Cannot execute an empty MEL command.");
        }

        MStatus status = self.commandToExecute(MString(command.c_str()));

        CHECK_STATUS(status);
    }, py::arg("command"),
       _doc_DGModifier_commandToExecute)

    .def("connect", [](MDGModifier & self, MObject sourceNode, MObject sourceAttr, MObject destNode, MObject destAttr) {
        validate::is_not_null(sourceNode, "Cannot connect - sourceNode is null.");
        validate::has_fn(
            sourceNode, MFn::kDependencyNode, 
            "Cannot connect - 'sourceNode' must be a 'node' object , not a '^1s' object."
        );

        validate::is_not_null(sourceAttr, "Cannot connect - 'sourceAttr' is null.");
        validate::has_fn(
            sourceAttr, MFn::kAttribute, 
            "Cannot connect - 'sourceAttr' must be a 'kAttribute' object, not a(n) '^1s' object."
        );

        validate::is_not_null(destNode, "Cannot connect - 'destNode' is null.");
        validate::has_fn(
            destNode, MFn::kDependencyNode, 
            "Cannot connect - 'destNode' must be a 'kDependencyNode' object , not a '^1s' object."
        );
    
        validate::is_not_null(destAttr, "Cannot connect - 'destAttr' is null.");
        validate::has_fn(
            destAttr, MFn::kAttribute, 
            "Cannot connect - 'destAttr' must be a 'kAttribute' object, not a(n) '^1s' object."
        );
        
        // TODO: Once the MFnAttribute classes are implemented, 
        // add additional validation to ensure that the attributes can be connected  
        MStatus status = self.connect(sourceNode, sourceAttr, destNode, destAttr);

        CHECK_STATUS(status)
        }, py::arg("sourceNode"),
           py::arg("sourceAttr"),
           py::arg("destNode"),
           py::arg("destAttr"),
           _doc_DGModifier_connect)

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
    }, py::arg("source"),
       py::arg("dest"),
       _doc_DGModifier_connect)

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
    }, py::arg("type"),
       _doc_DGModifier_createNode)

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
    }, py::arg("typeId"),
       _doc_DGModifier_createNode)

    .def("deleteNode", [](MDGModifier & self, MObject node) {
        validate::is_not_null(node, "Cannot delete a null object.");
        validate::has_fn(node, MFn::kDependencyNode, "Cannot delete a(n) '^1s' object.");
        
        if (node.hasFn(MFn::kDagNode)) {
            MString error_msg("Cannot delete a(n) DAG object - use DAGModifier instead.");
                    error_msg.format(error_msg, node.apiTypeStr());
            throw pybind11::type_error(error_msg.asChar());
        }
    
        MStatus status = self.deleteNode(node);

        CHECK_STATUS(status)
    }, py::arg("node"),
       _doc_DGModifier_deleteNode)

    .def("disconnect", [](MDGModifier & self, MObject sourceNode, MObject sourceAttr, MObject destNode, MObject destAttr) {
        validate::is_not_null(sourceNode, "Cannot disconnect - sourceNode is null.");
        validate::has_fn(
            sourceNode, MFn::kDependencyNode, 
            "Cannot disconnect - 'sourceNode' must be a 'node' object , not a '^1s' object."
        );

        validate::is_not_null(sourceAttr, "Cannot disconnect - 'sourceAttr' is null.");
        validate::has_fn(
            sourceAttr, MFn::kAttribute, 
            "Cannot disconnect - 'sourceAttr' must be a 'kAttribute' object, not a(n) '^1s' object."
        );

        validate::is_not_null(destNode, "Cannot disconnect - 'destNode' is null.");
        validate::has_fn(
            destNode, MFn::kDependencyNode, 
            "Cannot disconnect - 'destNode' must be a 'kDependencyNode' object , not a '^1s' object."
        );
    
        validate::is_not_null(destAttr, "Cannot disconnect - 'destAttr' is null.");
        validate::has_fn(
            destAttr, MFn::kAttribute, 
            "Cannot disconnect - 'destAttr' must be a 'kAttribute' object, not a(n) '^1s' object."
        );  
        
        MStatus status = self.disconnect(sourceNode, sourceAttr, destNode, destAttr);
        CHECK_STATUS(status)
    }, py::arg("sourceNode"),
       py::arg("sourceAttr"),
       py::arg("destNode"),
       py::arg("destAttr"), 
       _doc_DGModifier_disconnect)

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
    }, py::arg("source"),
       py::arg("dest"), 
       _doc_DGModifier_disconnect)

    .def("doIt", [](MDGModifier & self) {
        MStatus status = self.doIt();

        CHECK_STATUS(status)
    }, _doc_DGModifier_doIt)

    .def("linkExtensionAttributeToPlugin", [](MDGModifier & self, MObject plugin, MObject attribute) {        
        validate::is_not_null(plugin, "Cannot link extension attribute to a null plugin.");
        validate::has_fn(
            plugin, MFn::kPlugin, 
            "Cannot link extension attribute to plugin - must specify a 'kPlugin' object, not a '^1s' object."
        );
    
        validate::is_not_null(attribute, "Cannot link null extension attribute from a plugin.");
        validate::has_fn(
            attribute, MFn::kAttribute, 
            "Cannot link extension attribute - 'attribute' must be a 'kAttribute' object, not a(n) '^1s' object."
        );

        MStatus status = self.linkExtensionAttributeToPlugin(plugin, attribute);

        CHECK_STATUS(status)
    }, py::arg("plugin"),
       py::arg("attribute"),
       _doc_DGModifier_linkExtensionAttributeToPlugin)

    .def("newPlugValue", [](MDGModifier & self, MPlug plug, MObject value) {
        plug::assert_not_null(plug);

        MStatus status = self.newPlugValue(plug, value);

        CHECK_STATUS(status);
    }, py::arg("plug"),
       py::arg("value"), 
       _doc_DGModifier_newPlugValue)

    .def("newPlugValueBool", [](MDGModifier & self, MPlug plug, bool value) {
        plug::assert_not_null(plug);

        MStatus status = self.newPlugValueBool(plug, value);

        CHECK_STATUS(status);
    }, py::arg("plug"),
       py::arg("value"),
       _doc_DGModifier_newPlugValueBool)

    .def("newPlugValueChar", [](MDGModifier & self, MPlug plug, int value) {
        plug::assert_not_null(plug);

        MStatus status = self.newPlugValueChar(plug, value);

        CHECK_STATUS(status);
    }, py::arg("plug"),
       py::arg("value"), 
       _doc_DGModifier_newPlugValueChar)

    .def("newPlugValueDouble", [](MDGModifier & self, MPlug plug, double value) {
        plug::assert_not_null(plug);

        MStatus status = self.newPlugValueDouble(plug, value);

        CHECK_STATUS(status);
    }, py::arg("plug"),
       py::arg("value"),
       _doc_DGModifier_newPlugValueDouble)

    .def("newPlugValueFloat", [](MDGModifier & self, MPlug plug, float value) {
        plug::assert_not_null(plug);

        MStatus status = self.newPlugValueFloat(plug, value);

        CHECK_STATUS(status);
    }, py::arg("plug"),
       py::arg("value"),
       _doc_DGModifier_newPlugValueFloat)

    .def("newPlugValueInt", [](MDGModifier & self, MPlug plug, int value) {
        plug::assert_not_null(plug);

        MStatus status = self.newPlugValueInt(plug, value);

        CHECK_STATUS(status);
    }, py::arg("plug"),
       py::arg("value"),
    _doc_DGModifier_newPlugValueInt)

    .def("newPlugValueMAngle", [](MDGModifier & self, MPlug plug, MAngle value) {
        plug::assert_not_null(plug);

        MStatus status = self.newPlugValueMAngle(plug, value);

        CHECK_STATUS(status);
    }, py::arg("plug"),
       py::arg("value"),
       _doc_DGModifier_newPlugValueMAngle)

    .def("newPlugValueMDistance", [](MDGModifier & self, MPlug plug, MDistance value) {
        plug::assert_not_null(plug);

        MStatus status = self.newPlugValueMDistance(plug, value);

        CHECK_STATUS(status);
    }, py::arg("plug"),
       py::arg("value"),
       _doc_DGModifier_newPlugValueMDistance)

    .def("newPlugValueMTime", [](MDGModifier & self, MPlug plug, MTime value) {
        plug::assert_not_null(plug);

        MStatus status = self.newPlugValueMTime(plug, value);

        CHECK_STATUS(status);
    }, py::arg("plug"),
       py::arg("value"),
       _doc_DGModifier_newPlugValueMTime)

    .def("newPlugValueShort", [](MDGModifier & self, MPlug plug, short value) {
        plug::assert_not_null(plug);

        MStatus status = self.newPlugValueShort(plug, value);

        CHECK_STATUS(status)
    }, py::arg("plug"),
       py::arg("value"),
       _doc_DGModifier_newPlugValueShort)

    .def("newPlugValueString", [](MDGModifier & self, MPlug plug, std::string value) {
        plug::assert_not_null(plug);

        MStatus status = self.newPlugValueString(plug, MString(value.c_str()));

        CHECK_STATUS(status);
    }, py::arg("plug"),
       py::arg("value"),
       _doc_DGModifier_newPlugValueString)

    .def("pythonCommandToExecute", [](MDGModifier & self, std::string command) {
        if (command.empty())
        {
            throw std::invalid_argument("Cannot execute an empty Python command.");
        }

        MStatus status = self.pythonCommandToExecute(MString(command.c_str()));

        CHECK_STATUS(status);
    }, py::arg("command"),
       _doc_DGModifier_pythonCommandToExecute)

    .def("removeAttribute", [](MDGModifier & self, MObject node, MObject attribute) {            
        validate::is_not_null(node, "Cannot remove an attribute from a null node.");
        validate::has_fn(
            node, MFn::kDependencyNode, 
            "Cannot remove attribute - node must be a 'node' object , not a '^1s' object."
        );

        validate::is_not_null(attribute, "Cannot remove a null attribute.");
        validate::has_fn(
            attribute, MFn::kAttribute, 
            "Cannot remove attribute - 'attribute' must be a 'kAttribute' object, not a(n) '^1s' object."
        );

        MStatus status = self.removeAttribute(node, attribute);

        CHECK_STATUS(status)
    }, py::arg("node"),
       py::arg("attribute"),
       _doc_DGModifier_removeAttribute)

    .def("removeExtensionAttribute", [](MDGModifier & self, MNodeClass nodeClass, MObject attribute) {
        validate::is_not_null(attribute, "Cannot remove null extension attribute.");
        validate::has_fn(
            attribute, MFn::kAttribute, 
            "Cannot remove extension attribute - 'attribute' must be a 'kAttribute' object, not a(n) '^1s' object."
        );

        MStatus status = self.removeExtensionAttribute(nodeClass, attribute);

        CHECK_STATUS(status)
    }, py::arg("nodeClass"), py::arg("attribute"),
    _doc_DGModifier_removeExtensionAttribute)

    .def("removeExtensionAttributeIfUnset", [](MDGModifier & self, MNodeClass nodeClass, MObject attribute) {
        validate::is_not_null(attribute, "Cannot remove null extension attribute (if unset).");
        validate::has_fn(
            attribute, MFn::kAttribute, 
            "Cannot remove extension attribute (if unset) - 'attribute' must be a 'kAttribute' object, not a(n) '^1s' object."
        );

        MStatus status = self.removeExtensionAttribute(nodeClass, attribute);

        CHECK_STATUS(status)    
    }, py::arg("nodeClass"),
       py::arg("attribute"),
       _doc_DGModifier_removeExtensionAttributeIfUnset)

    .def("removeMultiInstance", [](MDGModifier & self, MPlug plug, bool breakConnections) {
        plug::assert_not_null(plug);
        plug::assert_is_element(plug);

        MStatus status = self.removeMultiInstance(plug, breakConnections);

        CHECK_STATUS(status);
    }, py::arg("plug"),
       py::arg("breakConnections"),
       _doc_DGModifier_removeMultiInstance)

    .def("renameAttribute", [](MDGModifier & self, MObject node, MObject attribute, std::string shortName, std::string longName) {
        validate::is_not_null(node, "Cannot rename an attribute from a null node.");
        validate::has_fn(
            node, MFn::kDependencyNode, 
            "Cannot rename attribute - node must be a 'node' object , not a '^1s' object."
        );
 
        validate::is_not_null(attribute, "Cannot rename a null attribute.");
        validate::has_fn(
            attribute, MFn::kAttribute, 
            "Cannot rename attribute - 'attribute' must be a 'kAttribute' object, not a(n) '^1s' object."
        );

        if (shortName.empty() || longName.empty())
        {
            throw std::invalid_argument("Cannot rename an attribute to an empty string.");
        }

        // TODO: When MFnAttribute is implement, raise a TypeError if `attribute` is not dynamic.
        // TODO: Regex to restrict names to [a-zA-Z0-9_]?
        // TODO: Do short/long name have length constraints?

        MStatus status = self.renameAttribute(node, attribute, MString(shortName.c_str()), MString(longName.c_str()));

        CHECK_STATUS(status)

    }, py::arg("node"),
       py::arg("attribute"),
       py::arg("shortName"),
       py::arg("longName"),
       _doc_DGModifier_renameAttribute)

    .def("renameNode", [](MDGModifier & self, MObject node, std::string newName) {
        validate::is_not_null(node, "Cannot rename a null node.");
        validate::has_fn(
            node, MFn::kDependencyNode, 
            "Cannot rename object - 'node' must be a 'kDependencyNode' object , not a '^1s' object."
        );

        if (newName.empty())
        {
            throw std::invalid_argument("Cannot rename a node to an empty string.");
        }

        MStatus status = self.renameNode(node, MString(newName.c_str()));

        CHECK_STATUS(status)
    }, py::arg("node"),
       py::arg("newName"),
       _doc_DGModifier_renameNode)

    .def("setNodeLockState", [](MDGModifier & self, MObject node, bool newState) {
        validate::is_not_null(node, "Cannot un/lock a null node.");
        validate::has_fn(
            node, MFn::kDependencyNode, 
            "Cannot un/lock object - 'node' must be a 'kDependencyNode' object , not a '^1s' object."
        );

        MStatus status = self.setNodeLockState(node, newState);

        CHECK_STATUS(status)
    }, py::arg("node"),
       py::arg("newState"),
       _doc_DGModifier_setNodeLockState)

    .def("undoIt", [](MDGModifier & self) {
        MStatus status = self.undoIt();

        CHECK_STATUS(status)
    }, _doc_DGModifier_undoIt)

    .def("unlinkExtensionAttributeFromPlugin", [](MDGModifier & self, MObject plugin, MObject attribute) {
        validate::is_not_null(plugin, "Cannot unlink extension attribute from a null plugin.");
        validate::has_fn(
            plugin, MFn::kPlugin, 
            "Cannot unlink extension attribute from plugin - must specify a 'kPlugin' object, not a '^1s' object."
        );

        validate::is_not_null(attribute, "Cannot unlink null extension attribute from a plugin.");
        validate::has_fn(
            attribute, MFn::kAttribute, 
            "Cannot unlink extension attribute - 'attribute' must be a 'kAttribute' object, not a(n) '^1s' object."
        );

        MStatus status = self.unlinkExtensionAttributeFromPlugin(plugin, attribute);

        CHECK_STATUS(status);
    }, py::arg("plugin"),
       py::arg("attribute"),
       _doc_DGModifier_unlinkExtensionAttributeFromPlugin);
#endif DGMODIFIER_INL