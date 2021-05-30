py::class_<MDGModifier>(m, "DGModifier")
    .def(py::init<>())

    .def("addAttribute", [](MDGModifier & self, MObject node, MObject attribute) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(addAttribute(MObject node, MObject attribute) -> self

Adds an operation to the modifier to add a new dynamic attribute to the
given dependency node. If the attribute is a compound its children will
be added as well, so only the parent needs to be added using this method.)pbdoc")

    .def("addExtensionAttribute", [](MDGModifier & self, MNodeClass nodeClass, MObject attribute) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(addExtensionAttribute(MNodeClass nodeClass, MObject attribute) -> self

Adds an operation to the modifier to add a new extension attribute to
the given node class. If the attribute is a compound its children will be
added as well, so only the parent needs to be added using this method.)pbdoc")

    .def("commandToExecute", [](MDGModifier & self, MString command) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(commandToExecute(command) -> self

Adds an operation to the modifier to execute a MEL command. The command
should be fully undoable otherwise unexpected results may occur. If 
the command contains no undoable portions whatsoever, the call to
doIt() may fail, but only after executing the command. It is best to
use multiple commandToExecute() calls rather than batching multiple
commands into a single call to commandToExecute(). They will still be
undone together, as a single undo action by the user, but Maya will
better be able to recover if one of the commands fails.)pbdoc")

    .def("connect", [](MDGModifier & self, MObject sourceNode, MObject sourceAttr, MObject destNode, MObject destAttr) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(connect(MPlug source, MPlug dest) -> self
connect(MObject sourceNode, MObject sourceAttr,
        MObject destNode,   MObject destAttr) -> self

Adds an operation to the modifier that connects two plugs in the
dependency graph. It is the user's responsibility to ensure that the
source and destination attributes are of compatible types. For instance,
if the source attribute is a nurbs surface then the destination must
also be a nurbs surface.
Plugs can either be specified with node and attribute MObjects or with
MPlugs.)pbdoc")

    .def("connect", [](MDGModifier & self, MPlug source, MPlug dest) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(connect(MPlug source, MPlug dest) -> self
connect(MObject sourceNode, MObject sourceAttr,
        MObject destNode,   MObject destAttr) -> self

Adds an operation to the modifier that connects two plugs in the
dependency graph. It is the user's responsibility to ensure that the
source and destination attributes are of compatible types. For instance,
if the source attribute is a nurbs surface then the destination must
also be a nurbs surface.
Plugs can either be specified with node and attribute MObjects or with
MPlugs.)pbdoc")

    .def("createNode", [](MDGModifier & self, MString type) -> MObject {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(createNode(typeName) -> MObject
createNode(MTypeId typeId) -> MObject

Adds an operation to the modifier to create a node of the given type.
The new node is created and returned but will not be added to the
Dependency Graph until the modifier's doIt() method is called. Raises
TypeError if the named node type does not exist or if it is a DAG node
type.)pbdoc")

    .def("createNode", [](MDGModifier & self, MTypeId typeId) -> MObject {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(createNode(typeName) -> MObject
createNode(MTypeId typeId) -> MObject

Adds an operation to the modifier to create a node of the given type.
The new node is created and returned but will not be added to the
Dependency Graph until the modifier's doIt() method is called. Raises
TypeError if the named node type does not exist or if it is a DAG node
type.)pbdoc")

    .def("deleteNode", [](MDGModifier & self, MObject node) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(deleteNode(MObject node) -> self

Adds an operation to the modifier which deletes the specified node from
the Dependency Graph. If deleteNode() is called to delete nodes in a graph
while other items are also in the queue, it might end up deleting the nodes
before all the other tasks in the queue.In order to prevent unexpected outcomes, the modifier's doIt() should be called
before the deleteNode operation is added so that the queue is emptied. Then,
deleteNode() can be called and added to the queue. doIt() should be called
immediately after to ensure that the queue is emptied before any other
operations are added to it.)pbdoc")

    .def("disconnect", [](MDGModifier & self, MObject sourceNode, MObject sourceAttr, MObject destNode, MObject destAttr) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(disconnect(MPlug source, MPlug dest) -> self
disconnect(MObject sourceNode, MObject sourceAttr,
           MObject destNode,   MObject destAttr) -> self

Adds an operation to the modifier that breaks a connection between two
plugs in the dependency graph.
Plugs can either be specified with node and attribute MObjects or with
MPlugs.)pbdoc")

    .def("disconnect", [](MDGModifier & self, MPlug source, MPlug dest) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(disconnect(MPlug source, MPlug dest) -> self
disconnect(MObject sourceNode, MObject sourceAttr,
           MObject destNode,   MObject destAttr) -> self

Adds an operation to the modifier that breaks a connection between two
plugs in the dependency graph.
Plugs can either be specified with node and attribute MObjects or with
MPlugs.)pbdoc")

    .def("doIt", [](MDGModifier & self) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(doIt() -> self

Executes the modifier's operations. If doIt() is called multiple times
in a row, without any intervening calls to undoIt(), then only the
operations which were added since the previous doIt() call will be
executed. If undoIt() has been called then the next call to doIt() will
do all operations.)pbdoc")

    .def("linkExtensionAttributeToPlugin", [](MDGModifier & self, MObject plugin, MObject attribute) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(linkExtensionAttributeToPlugin(MObject plugin, MObject attribute) -> self

The plugin can call this method to indicate that the extension attribute
defines part of the plugin, regardless of the node type to which it
attaches itself. This requirement is used when the plugin is checked to
see if it is in use or if is able to be unloaded or if it is required as
part of a stored file. For compound attributes only the topmost parent
attribute may be passed in and all of its children will be included,
recursively. Thus it's not possible to link a child attribute to a
plugin by itself. Note that the link is established immediately and is
not affected by the modifier's doIt() or undoIt() methods.)pbdoc")

    .def("newPlugValue", [](MDGModifier & self, MPlug plug) -> MObject {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(newPlugValue(MPlug plug, MObject value) -> self

Adds an operation to the modifier to set the value of a plug, where
value is an MObject data wrapper, such as created by the various
MFn*Data classes.)pbdoc")

    .def("newPlugValueBool", [](MDGModifier & self, MPlug plug, bool plugValue) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(newPlugValueBool(MPlug plug, bool value) -> self

Adds an operation to the modifier to set a value onto a bool plug.)pbdoc")

    .def("newPlugValueChar", [](MDGModifier & self, MPlug plug, char plugValue) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(newPlugValueChar(MPlug plug, int value) -> self

Adds an operation to the modifier to set a value onto a char (single
byte signed integer) plug.)pbdoc")

    .def("newPlugValueDouble", [](MDGModifier & self, MPlug plug, double plugValue) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(newPlugValueDouble(MPlug plug, float value) -> self

Adds an operation to the modifier to set a value onto a double-precision
float plug.)pbdoc")

    .def("newPlugValueFloat", [](MDGModifier & self, MPlug plug, float plugValue) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(newPlugValueFloat(MPlug plug, float value) -> self

Adds an operation to the modifier to set a value onto a single-precision
float plug.)pbdoc")

    .def("newPlugValueInt", [](MDGModifier & self, MPlug plug, int plugValue) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(newPlugValueInt(MPlug plug, int value) -> self

Adds an operation to the modifier to set a value onto an int plug.)pbdoc")

    .def("newPlugValueMAngle", [](MDGModifier & self, MPlug plug, MAngle plugValue) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(newPlugValueMAngle(MPlug plug, MAngle value) -> self

Adds an operation to the modifier to set a value onto an angle plug.)pbdoc")

    .def("newPlugValueMDistance", [](MDGModifier & self, MPlug plug, MDistance plugValue) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(newPlugValueMDistance(MPlug plug, MDistance value) -> self

Adds an operation to the modifier to set a value onto a distance plug.)pbdoc")

    .def("newPlugValueMTime", [](MDGModifier & self, MPlug plug, MTime plugValue) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(newPlugValueMTime(MPlug plug, MTime value) -> self

Adds an operation to the modifier to set a value onto a time plug.)pbdoc")

    .def("newPlugValueShort", [](MDGModifier & self, MPlug plug, short plugValue) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(newPlugValueShort(MPlug plug, int value) -> self

Adds an operation to the modifier to set a value onto a short
integer plug.)pbdoc")

    .def("newPlugValueString", [](MDGModifier & self, MPlug plug, MString plugValue) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(newPlugValueString(MPlug plug, string value) -> self

Adds an operation to the modifier to set a value onto a string plug.)pbdoc")

    .def("pythonCommandToExecute", [](MDGModifier & self, MString command) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(pythonCommandToExecute(callable) -> selfpythonCommandToExecute(commandString) -> self

Adds an operation to the modifier to execute a Python command, which
can be passed as either a Python callable or a string containing the
text of the Python code to be executed. The command should be fully
undoable otherwise unexpected results may occur. If the command
contains no undoable portions whatsoever, the call to doIt() may fail,
but only after executing the command. It is best to use multiple calls
rather than batching multiple commands into a single call to
pythonCommandToExecute(). They will still be undone together, as a
single undo action by the user, but Maya will better be able to
recover if one of the commands fails.)pbdoc")

    .def("removeAttribute", [](MDGModifier & self, MObject node, MObject attribute) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(removeAttribute(MObject node, MObject attribute) -> self

Adds an operation to the modifier to remove a dynamic attribute from the
given dependency node. If the attribute is a compound its children will
be removed as well, so only the parent needs to be removed using this
method. The attribute MObject passed in will be set to kNullObj. There
should be no function sets attached to the attribute at the time of the
call as their behaviour may become unpredictable.)pbdoc")

    .def("removeExtensionAttribute", [](MDGModifier & self, MNodeClass nodeClass, MObject attribute) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(removeExtensionAttribute(MNodeClass nodeClass, MObject attribute) -> self

Adds an operation to the modifier to remove an extension attribute from
the given node class. If the attribute is a compound its children will
be removed as well, so only the parent needs to be removed using this
method. The attribute MObject passed in will be set to kNullObj. There
should be no function sets attached to the attribute at the time of the
call as their behaviour may become unpredictable.)pbdoc")

    .def("removeExtensionAttributeIfUnset", [](MDGModifier & self, MNodeClass nodeClass, MObject attribute) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(removeExtensionAttributeIfUnset(MNodeClass nodeClass,
                                MObject attribute) -> self

Adds an operation to the modifier to remove an extension attribute from
the given node class, but only if there are no nodes in the graph with
non-default values for this attribute. If the attribute is a compound
its children will be removed as well, so only the parent needs to be
removed using this method. The attribute MObject passed in will be set
to kNullObj. There should be no function sets attached to the attribute
at the time of the call as their behaviour may become unpredictable.)pbdoc")

    .def("removeMultiInstance", [](MDGModifier & self, MPlug plug, bool breakConnections) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(removeMultiInstance(MPlug plug, bool breakConnections) -> self

Adds an operation to the modifier to remove an element of a multi (array) plug.)pbdoc")

    .def("renameAttribute", [](MDGModifier & self, MObject node, MObject attribute, MString shortName, MString longName) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(renameAttribute(MObject node, MObject attribute, 
string newShortName, string newShortName) -> self

Adds an operation to the modifer that renames a dynamic attribute on the given dependency node.)pbdoc")

    .def("renameNode", [](MDGModifier & self, MObject node, MString newName) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(renameNode(MObject node, string newName) -> self

Adds an operation to the modifer to rename a node.)pbdoc")

    .def("setNodeLockState", [](MDGModifier & self, MObject node, bool newState) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(setNodeLockState(MObject node, bool newState) -> self

Adds an operation to the modifier to set the lockState of a node.)pbdoc")

    .def("undoIt", [](MDGModifier & self) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(undoIt() -> self

Undoes all of the operations that have been given to this modifier. It
is only valid to call this method after the doIt() method has been
called.)pbdoc")

    .def("unlinkExtensionAttributeFromPlugin", [](MDGModifier & self, MObject mPlugin, MObject mAttribute) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(unlinkExtensionAttributeFromPlugin(MObject plugin,
                                   MObject attribute) -> self

The plugin can call this method to indicate that it no longer requires
an extension attribute for its operation. This requirement is used when
the plugin is checked to see if it is in use or if is able to be unloaded
or if it is required as part of a stored file. For compound attributes
only the topmost parent attribute may be passed in and all of its
children will be unlinked, recursively. Thus it's not possible to unlink
a child attribute from a plugin by itself. Note that the link is broken
immediately and is not affected by the modifier's doIt() or undoIt()
methods.)pbdoc");