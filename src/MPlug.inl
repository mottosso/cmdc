py::class_<MPlug> plug(m, "Plug");
py::enum_<MPlug::MValueSelector>(plug, "ValueSelector")
    .value("kAll", MPlug::MValueSelector::kAll)
    .value("kNonDefault", MPlug::MValueSelector::kNonDefault)
    .value("kChanged", MPlug::MValueSelector::kChanged)
    .value("kLastAttrSelector", MPlug::MValueSelector::kLastAttrSelector)
    .export_values();

plug.def(py::init<>())

    .def("array", [](MPlug & self) -> MPlug {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns a plug for the array of plugs of which this plug is an element.)pbdoc")

    .def("asBool", [](MPlug & self) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Retrieves the plug's value, as a boolean.)pbdoc")

    .def("asChar", [](MPlug & self) -> char {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Retrieves the plug's value, as a single-byte integer.)pbdoc")

    .def("asDouble", [](MPlug & self) -> double {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Retrieves the plug's value, as a double-precision float.)pbdoc")

    .def("asFloat", [](MPlug & self) -> float {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Retrieves the plug's value, as a single-precision float.)pbdoc")

    .def("asInt", [](MPlug & self) -> int {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Retrieves the plug's value, as a regular integer.)pbdoc")

    .def("asMAngle", [](MPlug & self) -> MAngle {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Retrieves the plug's value, as an MAngle.)pbdoc")

    .def("asMDataHandle", [](MPlug & self) -> MDataHandle {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Retrieve the current value of the attribute this plug references.)pbdoc")

    .def("asMDistance", [](MPlug & self) -> MDistance {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Retrieves the plug's value, as an MDistance.)pbdoc")

    .def("asMObject", [](MPlug & self) -> MObject {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Retrieves the plug's value, as as an MObject containing a direct reference to the plug's data.)pbdoc")

    .def("asMTime", [](MPlug & self) -> MTime {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Retrieves the plug's value, as an MTime.)pbdoc")

    .def("asShort", [](MPlug & self) -> short {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Retrieves the plug's value, as a short integer.)pbdoc")

    .def("asString", [](MPlug & self) -> MString {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Retrieves the plug's value, as a string.)pbdoc")

    .def("attribute", [](MPlug & self) -> MObject {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns the attribute currently referenced by this plug.)pbdoc")

    .def("child", [](MPlug & self, MObject attr) -> MPlug {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns a plug for the specified child attribute of this plug.)pbdoc")

    .def("child", [](MPlug & self, unsigned int index) -> MPlug {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns a plug for the specified child attribute of this plug.)pbdoc")

    .def("connectedTo", [](MPlug & self, std::vector<MPlug> array, bool asDst, bool asSrc) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns an array of plugs which are connected to this one.)pbdoc")

    .def("connectionByPhysicalIndex", [](MPlug & self, unsigned int physicalIndex) -> MPlug {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns a plug for the index'th connected element of this plug.)pbdoc")

    .def("constructHandle", [](MPlug & self, MDataBlock) -> MDataHandle {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Constructs a data handle for the plug.)pbdoc")

    .def("destinations", [](MPlug & self, std::vector<MPlug> theDestinations) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(If this plug is a source, return the destination plugs connected to it.
If this plug is not a source, a null plug is returned.
This method will produce the networked version of the connected plug.)pbdoc")

    .def("destinationsWithConversions", [](MPlug & self, std::vector<MPlug> theDestinations) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(If this plug is a source, return the destination plugs connected to it.
This method is very similar to the destinations() method.  The only difference is that the destinations() method skips over any unit conversion node connected to this source, and returns the destination of the unit conversion node.
destinationsWithConversionNode() does not skip over unit conversion nodes, and returns the destination plug on a unit conversion node, if present.
Note that the behavior of connectedTo() is identical to destinationsWithConversions(), that is, do not skip over unit conversion nodes.)pbdoc")

    .def("destructHandle", [](MPlug & self, MDataHandle) -> void {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Destroys a data handle previously constructed using constructHandle().)pbdoc")

    .def("elementByLogicalIndex", [](MPlug & self, unsigned int logicalIndex) -> MPlug {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns a plug for the element of this plug array having the specified logical index.)pbdoc")

    .def("elementByPhysicalIndex", [](MPlug & self, unsigned int physicalIndex) -> MPlug {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns a plug for the element of this plug array having the specified physical index. )pbdoc")

    .def("evaluateNumElements", [](MPlug & self) -> int {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Like numElements() but evaluates all connected elements first to ensure that they are included in the count.)pbdoc")

    .def("getExistingArrayAttributeIndices", [](MPlug & self, MIntArray indices) -> int {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns an array of all the plug's logical indices which are currently in use.)pbdoc")

    .def("getSetAttrCmds", [](MPlug & self, MPlug::MValueSelector valueSelector = MPlug::MValueSelector::kAll, bool useLongNames = false) -> std::vector<std::string> {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns a list of strings containing the setAttr commands (in MEL syntax) for this plug and all of its descendents.)pbdoc")

    .def("info", [](MPlug & self) -> MString {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Description of the plug for debugging purposes, in the form node:attr1.attr2[].attr3...)pbdoc")

    .def("isArray", [](MPlug & self) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(True if plug is an array of plugs.)pbdoc")

    .def("isChild", [](MPlug & self) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(True if plug is a child of a compound parent.)pbdoc")

    .def("isCompound", [](MPlug & self) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(True if plug is compound parent with children.)pbdoc")

    .def("isConnected", [](MPlug & self) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(True if plug has any connections.)pbdoc")

    .def("isDefaultValue", [](MPlug & self, bool forceEval = true) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns a value indicating if the plug's value is equivalent to the plug's default value.)pbdoc")

    .def("isDestination", [](MPlug & self) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(True if plug is the destination of a connection.)pbdoc")

    .def("isDynamic", [](MPlug & self) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(True if plug is for a dynamic attribute.)pbdoc")

    .def("isElement", [](MPlug & self) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(True if plug is an element of an array of plugs.)pbdoc")

    .def("isFreeToChange", [](MPlug & self, bool checkParents = true, bool checkChildren = true) -> MPlug::FreeToChangeState {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns a value indicating if the plug's value can be changed, after taking into account the effects of locking and connections.)pbdoc")

    .def("isFromReferencedFile", [](MPlug & self) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(True if plug is part of a connection from a referenced file.)pbdoc")

    .def("isIgnoredWhenRendering", [](MPlug & self) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(True if connetions to plug are ignored during rendering.)pbdoc")

    .def("isKeyable", [](MPlug & self) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(True if keys can be set on plug from Maya's UI.)pbdoc")

    .def("isLocked", [](MPlug & self) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(True if plug is locked against changes.)pbdoc")

    .def("isNetworked", [](MPlug & self) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(True if plug is networked.)pbdoc")

    .def("isNull", [](MPlug & self) -> bool {
        return self.isNull();
    }, R"pbdoc(True if plug does not reference an attribute.)pbdoc")

    .def("isProcedural", [](MPlug & self) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(True if plug is procedural.)pbdoc")

    .def("isSource", [](MPlug & self) -> bool {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(True if plug is the source of a connection.)pbdoc")

    .def("logicalIndex", [](MPlug & self) -> int {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns this plug's logical index within its parent array.)pbdoc")

    .def("name", [](MPlug & self) -> std::string {
        return std::string(self.asString().asChar());
    }, R"pbdoc(Returns the name of the plug.)pbdoc")

    .def("node", [](MPlug & self) -> MObject {
        MStatus status;
        MObject result = self.node(&status);

        if (!status) {
            throw std::exception(status.errorString().asChar());
        }

        return result; 
    }, R"pbdoc(Returns the node that this plug belongs to.)pbdoc")

    .def("numChildren", [](MPlug & self) -> int {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns the number of children this plug has.)pbdoc")

    .def("numConnectedChildren", [](MPlug & self) -> int {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns the number of this plug's children which have connections.)pbdoc")

    .def("numConnectedElements", [](MPlug & self) -> int {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns the number of this plug's elements which have connections.)pbdoc")

    .def("numElements", [](MPlug & self) -> int {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns the number of the plug's logical indices which are currently in use. Connected elements which have not yet been evaluated may not yet fully exist and may be excluded from the count.)pbdoc")

    .def("parent", [](MPlug & self) -> MPlug {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns a plug for the parent of this plug.)pbdoc")

    .def("partialName", [](MPlug & self, bool includeNodeName = false, bool includeNonMandatoryIndices = false, bool includeInstancedIndices = false, bool useAlias = false, bool useFullAttributePath = false, bool useLongNames = false) -> MString {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns the name of the plug, formatted according to various criteria.)pbdoc")

    .def("selectAncestorLogicalIndex", [](MPlug & self, unsigned int index, MObject attribute = MObject::kNullObj) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Changes the logical index of the specified attribute in the plug's path.)pbdoc")

    .def("setAttribute", [](MPlug & self) -> MObject {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Switches the plug to reference the given attribute of the same node as the previously referenced attribute.)pbdoc")

    .def("setBool", [](MPlug & self, bool value) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Sets the plug's value as a boolean.)pbdoc")

    .def("setChar", [](MPlug & self, char value) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Sets the plug's value as a single-byte integer.)pbdoc")

    .def("setDouble", [](MPlug & self, double value) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Sets the plug's value as a double-precision float.)pbdoc")

    .def("setFloat", [](MPlug & self, float value) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Sets the plug's value as a single-precision float.)pbdoc")

    .def("setInt", [](MPlug & self, int value) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Sets the plug's value as a regular integer.)pbdoc")

    .def("setMAngle", [](MPlug & self, MAngle angle) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Sets the plug's value as an MAngle.)pbdoc")

    .def("setMDataHandle", [](MPlug & self, MDataHandle dataHandle) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Sets the plug's value as a data handle.)pbdoc")

    .def("setMDistance", [](MPlug & self, MDistance distance) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Sets the plug's value as an MDistance.)pbdoc")

    .def("setMObject", [](MPlug & self, MObject object) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Sets the plug's value as an MObject.)pbdoc")

    .def("setMPxData", [](MPlug & self, MPxData *data) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Sets the plug's value using custom plug-in data.)pbdoc")

    .def("setMTime", [](MPlug & self, MTime time) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Sets the plug's value as an MTime.)pbdoc")

    .def("setNumElements", [](MPlug & self, unsigned int num_elements) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Pre-allocates space for count elements in an array of plugs.)pbdoc")

    .def("setShort", [](MPlug & self, short value) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Sets the plug's value as a short integer.)pbdoc")

    .def("setString", [](MPlug & self, MString value) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Sets the plug's value as a string.)pbdoc")

    .def("source", [](MPlug & self) -> MPlug {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(If this plug is a destination, return the source plug connected to it.
If this plug is not a destination, a null plug is returned.
This method will produce the networked version of the connectedplug.)pbdoc")

    .def("sourceWithConversion", [](MPlug & self) -> MPlug {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(If this plug is a destination, return the source plug connected to it.
This method is very similar to the source() method.  The only difference is that the source() method skips over any unit conversionnode connected to this destination, and returns the source of the unit conversion node.
sourceWithConversion() does not skip over unitconversion nodes, and returns the source plug on a unit conversionnode, if present.
Note that the behavior of connectedTo() is identical to sourceWithConversion(), that is, do not skip over unit conversion nodes.)pbdoc") 
.def("__repr__", [](const MPlug &a) {
        return "<cmdc.Plug()>";
    }
);
