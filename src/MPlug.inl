py::enum_<MPlug::MValueSelector>(plug, "ValueSelector")
    .value("kAll", MPlug::MValueSelector::kAll)
    .value("kNonDefault", MPlug::MValueSelector::kNonDefault)
    .value("kChanged", MPlug::MValueSelector::kChanged)
    .value("kLastAttrSelector", MPlug::MValueSelector::kLastAttrSelector)
    .export_values();

py::enum_<MPlug::FreeToChangeState>(plug, "FreeToChangeState")
    .value("kFreeToChange ", MPlug::FreeToChangeState::kFreeToChange)
    .value("kNotFreeToChange ", MPlug::FreeToChangeState::kNotFreeToChange)
    .value("kChildrenNotFreeToChange ", MPlug::FreeToChangeState::kChildrenNotFreeToChange)
    .export_values();

plug.def(py::init<>())

    .def(py::self == MPlug())

    .def("array", [](MPlug & self) -> MPlug {
        plug::assert_not_null(self);
        plug::assert_is_element(self);

        MStatus status;
        MPlug result = self.array(&status);

        CHECK_STATUS(status)

        return result;
    }, R"pbdoc(Returns a plug for the array of plugs of which this plug is an element.)pbdoc")

    .def("asBool", [](MPlug & self) -> bool {
        plug::assert_not_null(self);

        return self.asBool();
    }, R"pbdoc(Retrieves the plug's value, as a boolean.)pbdoc")

    .def("asChar", [](MPlug & self) -> int {
        plug::assert_not_null(self);

        return (self.asChar());
    }, R"pbdoc(Retrieves the plug's value, as a single-byte integer.)pbdoc")

    .def("asDouble", [](MPlug & self) -> double {
        plug::assert_not_null(self);

        return self.asDouble();
    }, R"pbdoc(Retrieves the plug's value, as a double-precision float.)pbdoc")

    .def("asFloat", [](MPlug & self) -> float {
        plug::assert_not_null(self);

        return self.asFloat();    
    }, R"pbdoc(Retrieves the plug's value, as a single-precision float.)pbdoc")

    .def("asInt", [](MPlug & self) -> int {
        plug::assert_not_null(self);

        return self.asInt(); 
    }, R"pbdoc(Retrieves the plug's value, as a regular integer.)pbdoc")

    .def("asMAngle", [](MPlug & self) -> MAngle {
        plug::assert_not_null(self);

        return self.asMAngle(); 
    }, R"pbdoc(Retrieves the plug's value, as an MAngle.)pbdoc")

    .def("asMDataHandle", [](MPlug & self) -> MDataHandle {
        plug::assert_not_null(self);

        return self.asMDataHandle(); 
    }, R"pbdoc(Retrieve the current value of the attribute this plug references.)pbdoc")

    .def("asMDistance", [](MPlug & self) -> MDistance {
        plug::assert_not_null(self);

        return self.asMDistance(); 
    }, R"pbdoc(Retrieves the plug's value, as an MDistance.)pbdoc")

    .def("asMObject", [](MPlug & self) -> MObject {
        plug::assert_not_null(self);

        return self.asMObject(); 
    }, R"pbdoc(Retrieves the plug's value, as as an MObject containing a direct reference to the plug's data.)pbdoc")

    .def("asMTime", [](MPlug & self) -> MTime {
        plug::assert_not_null(self);

        return self.asMTime(); 
    }, R"pbdoc(Retrieves the plug's value, as an MTime.)pbdoc")

    .def("asShort", [](MPlug & self) -> short {
        plug::assert_not_null(self);

        return self.asShort(); 
    }, R"pbdoc(Retrieves the plug's value, as a short integer.)pbdoc")

    .def("asString", [](MPlug & self) -> std::string {
        plug::assert_not_null(self);

        return std::string(self.asString().asChar()); 
    }, R"pbdoc(Retrieves the plug's value, as a string.)pbdoc")

    .def("attribute", [](MPlug & self) -> MObject {
        plug::assert_not_null(self);

        MStatus status;
        MObject result = self.attribute(&status);

        CHECK_STATUS(status)

        return result;    
    }, R"pbdoc(Returns the attribute currently referenced by this plug.)pbdoc")

    .def("child", [](MPlug & self, MObject attr) -> MPlug {
        plug::assert_not_null(self);
        plug::assert_is_compound(self);
        plug::assert_is_not_array(self);

        MStatus status;
        MPlug result;
        
        // You would think we could just call plug.child(attr), but that is not returning the 
        // correct status code for errors. So we'll do it the hard way.
        for (unsigned int i = 0; i < self.numChildren(); i++)
        {
            MPlug tmp = self.child(i, &status);

            if (!status) {
                break;
            }

            if (tmp.attribute() == attr) {
                result = tmp;
                break;
            }
        }

        if (result.isNull())
        {
            MString error_msg("The given attribute is not a child of plug '^1s'.");
                    error_msg.format(error_msg, self.name());

            throw std::invalid_argument(error_msg.asChar());
        }

        CHECK_STATUS(status)

        return result;
    }, R"pbdoc(Returns a plug for the specified child attribute of this plug.)pbdoc")

    .def("child", [](MPlug & self, unsigned int index) -> MPlug {
        plug::assert_not_null(self);
        plug::assert_is_compound(self);
        plug::assert_is_not_array(self);

        if (index >= self.numChildren()) {
            MString error_msg("Plug '^1s' only has '^2s' children.");
                    error_msg.format(error_msg, self.name(), MString("") + self.numChildren());
                
            throw std::out_of_range(error_msg.asChar());
        }

        MStatus status;
        MPlug result = self.child(index, &status);

        CHECK_STATUS(status)

        return result;    
    }, R"pbdoc(Returns a plug for the specified child attribute of this plug.)pbdoc")

    .def("connectedTo", [](MPlug & self, bool asDst, bool asSrc) -> std::vector<MPlug> {
        plug::assert_not_null(self);

        MStatus status;
        MPlugArray results;
        self.connectedTo(results, asDst, asSrc, &status);

        CHECK_STATUS(status)

        return atov::convert(results);   
    }, R"pbdoc(Returns an array of plugs which are connected to this one.)pbdoc")

    .def("connectionByPhysicalIndex", [](MPlug & self, unsigned int physicalIndex) -> MPlug {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns a plug for the index'th connected element of this plug.)pbdoc")

    .def("constructHandle", [](MPlug & self, MDataBlock) -> MDataHandle {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Constructs a data handle for the plug.)pbdoc")

    .def("destinations", [](MPlug & self) -> std::vector<MPlug> {
        plug::assert_not_null(self);

        MPlugArray results;
        MStatus status;

        self.destinations(results, &status);

        CHECK_STATUS(status)

        return atov::convert(results);  
    }, R"pbdoc(If this plug is a source, return the destination plugs connected to it.
If this plug is not a source, a null plug is returned.
This method will produce the networked version of the connected plug.)pbdoc")

    .def("destinationsWithConversions", [](MPlug & self) -> std::vector<MPlug> {
        plug::assert_not_null(self);
        
        MPlugArray results;
        MStatus status;

        self.destinationsWithConversions(results, &status);

        CHECK_STATUS(status)

        return atov::convert(results);  
    }, R"pbdoc(If this plug is a source, return the destination plugs connected to it.
This method is very similar to the destinations() method.  The only difference is that the destinations() method skips over any unit conversion node connected to this source, and returns the destination of the unit conversion node.
destinationsWithConversionNode() does not skip over unit conversion nodes, and returns the destination plug on a unit conversion node, if present.
Note that the behavior of connectedTo() is identical to destinationsWithConversions(), that is, do not skip over unit conversion nodes.)pbdoc")

    .def("destructHandle", [](MPlug & self, MDataHandle) -> void {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Destroys a data handle previously constructed using constructHandle().)pbdoc")

    .def("elementByLogicalIndex", [](MPlug & self, unsigned int index) -> MPlug {
        plug::assert_not_null(self);
        plug::assert_is_array(self);
        
        MStatus status;
        MPlug result = self.elementByLogicalIndex(index, &status);
        
        CHECK_STATUS(status)

        return result;
    }, R"pbdoc(Returns a plug for the element of this plug array having the specified logical index.)pbdoc")

    .def("elementByPhysicalIndex", [](MPlug & self, unsigned int index) -> MPlug {
        plug::assert_not_null(self);
        plug::assert_is_array(self);

        if (index >= self.numElements()) {
            MString error_msg("Plug '^1s' only has '^2s' elements.");
                    error_msg.format(error_msg, self.name(), MString("") + self.numElements());
                
            throw std::out_of_range(error_msg.asChar());
        }

        MStatus status;
        MPlug result = self.elementByPhysicalIndex(index, &status);

        CHECK_STATUS(status)

        return result;
    }, R"pbdoc(Returns a plug for the element of this plug array having the specified physical index. )pbdoc")

    .def("evaluateNumElements", [](MPlug & self) -> unsigned int {
        plug::assert_not_null(self);
        plug::assert_is_array(self);

        MStatus status;
        unsigned int result = self.evaluateNumElements(&status);

        CHECK_STATUS(status)

        return result;     
    }, R"pbdoc(Like numElements() but evaluates all connected elements first to ensure that they are included in the count.)pbdoc")

    .def("getExistingArrayAttributeIndices", [](MPlug & self) -> std::vector<int> {
        plug::assert_not_null(self);
        plug::assert_is_array(self);

        MStatus status;
        MIntArray results;
        
        self.getExistingArrayAttributeIndices(results, &status);

        CHECK_STATUS(status)

        return atov::convert(results);
    }, R"pbdoc(Returns an array of all the plug's logical indices which are currently in use.)pbdoc")

    .def("getSetAttrCmds", [](MPlug & self, MPlug::MValueSelector valueSelector = MPlug::MValueSelector::kAll, bool useLongNames = false) -> std::vector<std::string> {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns a list of strings containing the setAttr commands (in MEL syntax) for this plug and all of its descendents.)pbdoc")

    .def("info", [](MPlug & self) -> std::string {
        MString result = self.info();

        return std::string(result.asChar());
    }, R"pbdoc(Description of the plug for debugging purposes, in the form node:attr1.attr2[].attr3...)pbdoc")

    .def("isArray", [](MPlug & self) -> bool {
        return self.isArray();
    }, R"pbdoc(True if plug is an array of plugs.)pbdoc")

    .def("isChild", [](MPlug & self) -> bool {
        return self.isChild();
    }, R"pbdoc(True if plug is a child of a compound parent.)pbdoc")

    .def("isCompound", [](MPlug & self) -> bool {
        return self.isCompound();
    }, R"pbdoc(True if plug is compound parent with children.)pbdoc")

    .def("isConnected", [](MPlug & self) -> bool {
        return self.isConnected();
    }, R"pbdoc(True if plug has any connections.)pbdoc")

    .def("isDefaultValue", [](MPlug & self, bool forceEval = true) -> bool {
        return self.isDefaultValue(forceEval);
    }, R"pbdoc(Returns a value indicating if the plug's value is equivalent to the plug's default value.)pbdoc")

    .def("isDestination", [](MPlug & self) -> bool {
        return self.isDestination();
    }, R"pbdoc(True if plug is the destination of a connection.)pbdoc")

    .def("isDynamic", [](MPlug & self) -> bool {
        return self.isDynamic();
    }, R"pbdoc(True if plug is for a dynamic attribute.)pbdoc")

    .def("isElement", [](MPlug & self) -> bool {
        return self.isElement();
    }, R"pbdoc(True if plug is an element of an array of plugs.)pbdoc")

    .def("isFreeToChange", [](MPlug & self, bool checkParents = true, bool checkChildren = true) -> MPlug::FreeToChangeState {
        return self.isFreeToChange(checkParents, checkChildren);
    }, R"pbdoc(Returns a value indicating if the plug's value can be changed, after taking into account the effects of locking and connections.)pbdoc")

    .def("isFromReferencedFile", [](MPlug & self) -> bool {
        return self.isFromReferencedFile();
    }, R"pbdoc(True if plug is part of a connection from a referenced file.)pbdoc")

    .def("isIgnoredWhenRendering", [](MPlug & self) -> bool {
        return self.isIgnoredWhenRendering();
    }, R"pbdoc(True if connetions to plug are ignored during rendering.)pbdoc")

    .def("isKeyable", [](MPlug & self) -> bool {
        return self.isKeyable();
    }, R"pbdoc(True if keys can be set on plug from Maya's UI.)pbdoc")

    .def("isLocked", [](MPlug & self) -> bool {
        return self.isLocked();
    }, R"pbdoc(True if plug is locked against changes.)pbdoc")

    .def("isNetworked", [](MPlug & self) -> bool {
        return self.isNetworked();    
    }, R"pbdoc(True if plug is networked.)pbdoc")

    .def("isNull", [](MPlug & self) -> bool {
        return self.isNull();
    }, R"pbdoc(True if plug does not reference an attribute.)pbdoc")

    .def("isProcedural", [](MPlug & self) -> bool {
        return self.isProcedural();
    }, R"pbdoc(True if plug is procedural.)pbdoc")

    .def("isSource", [](MPlug & self) -> bool {
        return self.isSource();
    }, R"pbdoc(True if plug is the source of a connection.)pbdoc")

    .def("logicalIndex", [](MPlug & self) -> unsigned int {
        plug::assert_not_null(self);
        plug::assert_is_element(self);

        MStatus status;
        unsigned int result = self.logicalIndex(&status);

        CHECK_STATUS(status)

        return result; 
    }, R"pbdoc(Returns this plug's logical index within its parent array.)pbdoc")

    .def("name", [](MPlug & self) -> std::string {
        MString result = self.name();  // TODO: error handling

        return std::string(result.asChar());
    }, R"pbdoc(Returns the name of the plug.)pbdoc")

    .def("node", [](MPlug & self) -> MObject {
        MStatus status;
        MObject result = self.node(&status);

        CHECK_STATUS(status)

        return result; 
    }, R"pbdoc(Returns the node that this plug belongs to.)pbdoc")

    .def("numChildren", [](MPlug & self) -> unsigned int {
        plug::assert_not_null(self);
        plug::assert_is_compound(self);

        MStatus status;
        unsigned int result = self.numChildren(&status);

        CHECK_STATUS(status)

        return result;  
    }, R"pbdoc(Returns the number of children this plug has.)pbdoc")

    .def("numConnectedChildren", [](MPlug & self) -> int {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns the number of this plug's children which have connections.)pbdoc")

    .def("numConnectedElements", [](MPlug & self) -> int {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Returns the number of this plug's elements which have connections.)pbdoc")

    .def("numElements", [](MPlug & self) -> unsigned int {
        plug::assert_not_null(self);
        plug::assert_is_array(self);

        MStatus status;
        unsigned int result = self.numElements(&status);

        CHECK_STATUS(status)

        return result; 
    }, R"pbdoc(Returns the number of the plug's logical indices which are currently in use. Connected elements which have not yet been evaluated may not yet fully exist and may be excluded from the count.)pbdoc")

    .def("parent", [](MPlug & self) -> MPlug {
        plug::assert_not_null(self);

        if (!self.isChild()) {
            MString error_msg("Plug '^1s' is not a child plug.");
                    error_msg.format(error_msg, self.name());

            throw pybind11::type_error(error_msg.asChar());
        }

        MStatus status;
        MPlug result = self.parent(&status);

        CHECK_STATUS(status)

        return result;     
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
        plug::assert_not_null(self);

        self.setBool(value);
    }, R"pbdoc(Sets the plug's value as a boolean.)pbdoc")

    .def("setChar", [](MPlug & self, int value) {
        plug::assert_not_null(self);

        self.setChar(char(value));
    }, R"pbdoc(Sets the plug's value as a single-byte integer.)pbdoc")

    .def("setDouble", [](MPlug & self, double value) {
        plug::assert_not_null(self);

        self.setDouble(value);
    }, R"pbdoc(Sets the plug's value as a double-precision float.)pbdoc")

    .def("setFloat", [](MPlug & self, float value) {
        plug::assert_not_null(self);

        self.setFloat(value);
    }, R"pbdoc(Sets the plug's value as a single-precision float.)pbdoc")

    .def("setInt", [](MPlug & self, int value) {
        plug::assert_not_null(self);

        self.setInt(value);
    }, R"pbdoc(Sets the plug's value as a regular integer.)pbdoc")

    .def("setMAngle", [](MPlug & self, MAngle angle) {
        plug::assert_not_null(self);

        self.setMAngle(angle);
    }, R"pbdoc(Sets the plug's value as an MAngle.)pbdoc")

    .def("setMDataHandle", [](MPlug & self, MDataHandle dataHandle) {
        plug::assert_not_null(self);

        self.setMDataHandle(dataHandle);
    }, R"pbdoc(Sets the plug's value as a data handle.)pbdoc")

    .def("setMDistance", [](MPlug & self, MDistance distance) {
        plug::assert_not_null(self);

        self.setMDistance(distance);
    }, R"pbdoc(Sets the plug's value as an MDistance.)pbdoc")

    .def("setMObject", [](MPlug & self, MObject object) {
        plug::assert_not_null(self);

        self.setMObject(object);
    }, R"pbdoc(Sets the plug's value as an MObject.)pbdoc")

    .def("setMPxData", [](MPlug & self, MPxData *data) {
        plug::assert_not_null(self);

        self.setMPxData(data);
    }, R"pbdoc(Sets the plug's value using custom plug-in data.)pbdoc")

    .def("setMTime", [](MPlug & self, MTime time) {
        plug::assert_not_null(self);

        self.setMTime(time);
    }, R"pbdoc(Sets the plug's value as an MTime.)pbdoc")

    .def("setNumElements", [](MPlug & self, unsigned int num_elements) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Pre-allocates space for count elements in an array of plugs.)pbdoc")

    .def("setShort", [](MPlug & self, short value) {
        plug::assert_not_null(self);

        self.setShort(value);
    }, R"pbdoc(Sets the plug's value as a short integer.)pbdoc")

    .def("setString", [](MPlug & self, std::string value) {
        plug::assert_not_null(self);

        MString string(value.c_str());

        self.setString(string);
    }, R"pbdoc(Sets the plug's value as a string.)pbdoc")

    .def("source", [](MPlug & self) -> MPlug {
        plug::assert_not_null(self);

        MStatus status;
        MPlug result = self.source(&status);

        CHECK_STATUS(status)

        return result;      
    }, R"pbdoc(If this plug is a destination, return the source plug connected to it.
If this plug is not a destination, a null plug is returned.
This method will produce the networked version of the connectedplug.)pbdoc")

    .def("sourceWithConversion", [](MPlug & self) -> MPlug {
        plug::assert_not_null(self);

        MStatus status;
        MPlug result = self.sourceWithConversion(&status);

        CHECK_STATUS(status)

        return result;       
    }, R"pbdoc(If this plug is a destination, return the source plug connected to it.
This method is very similar to the source() method.  The only difference is that the source() method skips over any unit conversionnode connected to this destination, and returns the source of the unit conversion node.
sourceWithConversion() does not skip over unitconversion nodes, and returns the source plug on a unit conversionnode, if present.
Note that the behavior of connectedTo() is identical to sourceWithConversion(), that is, do not skip over unit conversion nodes.)pbdoc");
