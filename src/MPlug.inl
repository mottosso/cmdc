#define _doc_Plug_array \
    "Returns a plug for the array of plugs of which this plug is an element."

#define _doc_Plug_asBool \
    "Retrieves the plug's value, as a boolean."

#define _doc_Plug_asChar \
    "Retrieves the plug's value, as a single-byte integer."

#define _doc_Plug_asDouble \
    "Retrieves the plug's value, as a double-precision float."

#define _doc_Plug_asFloat \
    "Retrieves the plug's value, as a single-precision float."

#define _doc_Plug_asInt \
    "Retrieves the plug's value, as a regular integer."

#define _doc_Plug_asMAngle \
    "Retrieves the plug's value, as an MAngle."

#define _doc_Plug_asMDataHandle \
    "Retrieve the current value of the attribute this plug references."

#define _doc_Plug_asMDistance \
    "Retrieves the plug's value, as an MDistance."

#define _doc_Plug_asMObject \
    "Retrieves the plug's value, as as an MObject containing a\n"\
    "direct reference to the plug's data."

#define _doc_Plug_asMTime \
    "Retrieves the plug's value, as an MTime."

#define _doc_Plug_asShort \
    "Retrieves the plug's value, as a short integer."

#define _doc_Plug_asString \
    "Retrieves the plug's value, as a string."

#define _doc_Plug_attribute \
    "Returns the attribute currently referenced by this plug."

#define _doc_Plug_child \
    "Returns a plug for the specified child attribute of this plug."

#define _doc_Plug_child \
    "Returns a plug for the specified child attribute of this plug."

#define _doc_Plug_connectedTo \
    "Returns an array of plugs which are connected to this one."

#define _doc_Plug_connectionByPhysicalIndex \
    "Returns a plug for the index'th connected element of this plug."

#define _doc_Plug_constructHandle \
    "Constructs a data handle for the plug."

#define _doc_Plug_destinations \
    "If this plug is a source, return the destination plugs connected to it.\n"\
    "If this plug is not a source, a null plug is returned.\n"\
    "This method will produce the networked version of the connected plug."

#define _doc_Plug_destinationsWithConversions \
    "If this plug is a source, return the destination plugs connected to it.\n"\
    "This method is very similar to the destinations() method.\n"\
    "The only difference is that the destinations() method skips over any\n"\
    "unit conversion node connected to this source, and returns\n"\
    "the destination of the unit conversion node.\n"\
    "destinationsWithConversionNode() does not skip over unit\n"\
    "conversion nodes, and returns the destination plug on a unit\n"\
    "conversion node, if present.\n"\
    "Note that the behavior of connectedTo() is identical\n"\
    "to destinationsWithConversions(), that is, do not skip over\n"\
    "unit conversion nodes."

#define _doc_Plug_destructHandle \
    "Destroys a data handle previously constructed using constructHandle()."

#define _doc_Plug_elementByLogicalIndex \
    "Returns a plug for the element of this plug array having the\n"\
    "specified logical index."

#define _doc_Plug_elementByPhysicalIndex \
    "Returns a plug for the element of this plug array having the\n"\
    "specified physical index. "

#define _doc_Plug_evaluateNumElements \
    "Like numElements() but evaluates all connected elements first to\n"\
    "ensure that they are included in the count."

#define _doc_Plug_getExistingArrayAttributeIndices \
    "Returns an array of all the plug's logical indices which are currently\n"\
    "in use."

#define _doc_Plug_getSetAttrCmds \
    "Returns a list of strings containing the setAttr commands\n"\
    "(in MEL syntax) for this plug and all of its descendents."

#define _doc_Plug_info \
    "Description of the plug for debugging purposes, in the\n"\
    "form node:attr1.attr2[].attr3..."

#define _doc_Plug_isArray \
    "True if plug is an array of plugs."

#define _doc_Plug_isChild \
    "True if plug is a child of a compound parent."

#define _doc_Plug_isCompound \
    "True if plug is compound parent with children."

#define _doc_Plug_isConnected \
    "True if plug has any connections."

#define _doc_Plug_isDefaultValue \
    "Returns a value indicating if the plug's value is equivalent to\n"\
    "the plug's default value."

#define _doc_Plug_isDestination \
    "True if plug is the destination of a connection."

#define _doc_Plug_isDynamic \
    "True if plug is for a dynamic attribute."

#define _doc_Plug_isElement \
    "True if plug is an element of an array of plugs."

#define _doc_Plug_isFreeToChange \
    "Returns a value indicating if the plug's value can be changed,\n"\
    "after taking into account the effects of locking and connections."

#define _doc_Plug_isFromReferencedFile \
    "True if plug is part of a connection from a referenced file."

#define _doc_Plug_isIgnoredWhenRendering \
    "True if connetions to plug are ignored during rendering."

#define _doc_Plug_isKeyable \
    "True if keys can be set on plug from Maya's UI."

#define _doc_Plug_isLocked \
    "True if plug is locked against changes."

#define _doc_Plug_isNetworked \
    "True if plug is networked."

#define _doc_Plug_isNull \
    "True if plug does not reference an attribute."

#define _doc_Plug_isProcedural \
    "True if plug is procedural."

#define _doc_Plug_isSource \
    "True if plug is the source of a connection."

#define _doc_Plug_logicalIndex \
    "Returns this plug's logical index within its parent array."

#define _doc_Plug_name \
    "Returns the name of the plug."

#define _doc_Plug_node \
    "Returns the node that this plug belongs to."

#define _doc_Plug_numChildren \
    "Returns the number of children this plug has."

#define _doc_Plug_numConnectedChildren \
    "Returns the number of this plug's children which have connections."

#define _doc_Plug_numConnectedElements \
    "Returns the number of this plug's elements which have connections."

#define _doc_Plug_numElements \
    "Returns the number of the plug's logical indices which are currently\n"\
    "in use. Connected elements which have not yet been evaluated may not\n"\
    "yet fully exist and may be excluded from the count."

#define _doc_Plug_parent \
    "Returns a plug for the parent of this plug."

#define _doc_Plug_partialName \
    "Returns the name of the plug, formatted according to various criteria."

#define _doc_Plug_selectAncestorLogicalIndex \
    "Changes the logical index of the specified attribute in the plug's path."

#define _doc_Plug_setAttribute \
    "Switches the plug to reference the given attribute of the same node\n"\
    "as the previously referenced attribute."

#define _doc_Plug_setBool \
    "Sets the plug's value as a boolean."

#define _doc_Plug_setChar \
    "Sets the plug's value as a single-byte integer."

#define _doc_Plug_setDouble \
    "Sets the plug's value as a double-precision float."

#define _doc_Plug_setFloat \
    "Sets the plug's value as a single-precision float."

#define _doc_Plug_setInt \
    "Sets the plug's value as a regular integer."

#define _doc_Plug_setMAngle \
    "Sets the plug's value as an MAngle."

#define _doc_Plug_setMDataHandle \
    "Sets the plug's value as a data handle."

#define _doc_Plug_setMDistance \
    "Sets the plug's value as an MDistance."

#define _doc_Plug_setMObject \
    "Sets the plug's value as an MObject."

#define _doc_Plug_setMPxData \
    "Sets the plug's value using custom plug-in data."

#define _doc_Plug_setMTime \
    "Sets the plug's value as an MTime."

#define _doc_Plug_setNumElements \
    "Pre-allocates space for count elements in an array of plugs."

#define _doc_Plug_setShort \
    "Sets the plug's value as a short integer."

#define _doc_Plug_setString \
    "Sets the plug's value as a string."

#define _doc_Plug_source \
    "If this plug is a destination, return the source plug connected to it.\n"\
    "If this plug is not a destination, a null plug is returned.\n"\
    "This method will produce the networked version of the connectedplug."

#define _doc_Plug_sourceWithConversion \
    "If this plug is a destination, return the source plug connected to it.\n"\
    "This method is very similar to the source() method.\n"\
    "The only difference is that the source() method skips over any\n"\
    "unit conversionnode connected to this destination, and returns the\n"\
    "source of the unit conversion node.\n"\
    "sourceWithConversion() does not skip over unitconversion nodes,\n"\
    "and returns the source plug on a unit conversionnode, if present.\n"\
    "Note that the behavior of connectedTo() is identical\n"\
    "to sourceWithConversion(), that is, do not skip over unit conversion nodes."

py::enum_<MPlug::MValueSelector>(Plug, "ValueSelector")
    .value("kAll", MPlug::MValueSelector::kAll)
    .value("kNonDefault", MPlug::MValueSelector::kNonDefault)
    .value("kChanged", MPlug::MValueSelector::kChanged)
    .value("kLastAttrSelector", MPlug::MValueSelector::kLastAttrSelector)
    .export_values();

py::enum_<MPlug::FreeToChangeState>(Plug, "FreeToChangeState")
    .value("kFreeToChange ", MPlug::FreeToChangeState::kFreeToChange)
    .value("kNotFreeToChange ", MPlug::FreeToChangeState::kNotFreeToChange)
    .value("kChildrenNotFreeToChange ", MPlug::FreeToChangeState::kChildrenNotFreeToChange)
    .export_values();

Plug
    .def(py::init<>())

    .def(py::self == MPlug(), py::arg("other"))

    .def("array", [](MPlug & self) -> MPlug {
        plug::assert_not_null(self);
        plug::assert_is_element(self);

        MStatus status;
        MPlug result = self.array(&status);

        CHECK_STATUS(status)

        return result;
    }, _doc_Plug_array)

    .def("asBool", [](MPlug & self) -> bool {
        plug::assert_not_null(self);

        return self.asBool();
    }, _doc_Plug_asBool)

    .def("asChar", [](MPlug & self) -> int {
        plug::assert_not_null(self);

        return (self.asChar());
    }, _doc_Plug_asChar)

    .def("asDouble", [](MPlug & self) -> double {
        plug::assert_not_null(self);

        return self.asDouble();
    }, _doc_Plug_asDouble)

    .def("asFloat", [](MPlug & self) -> float {
        plug::assert_not_null(self);

        return self.asFloat();    
    }, _doc_Plug_asFloat)

    .def("asInt", [](MPlug & self) -> int {
        plug::assert_not_null(self);

        return self.asInt(); 
    }, _doc_Plug_asInt)

    .def("asMAngle", [](MPlug & self) -> MAngle {
        plug::assert_not_null(self);

        return self.asMAngle(); 
    }, _doc_Plug_asMAngle)

    .def("asMDataHandle", [](MPlug & self) -> MDataHandle {
        plug::assert_not_null(self);

        return self.asMDataHandle(); 
    }, _doc_Plug_asMDataHandle)

    .def("asMDistance", [](MPlug & self) -> MDistance {
        plug::assert_not_null(self);

        return self.asMDistance(); 
    }, _doc_Plug_asMDistance)

    .def("asMObject", [](MPlug & self) -> MObject {
        plug::assert_not_null(self);

        return self.asMObject(); 
    }, _doc_Plug_asMObject)

    .def("asMTime", [](MPlug & self) -> MTime {
        plug::assert_not_null(self);

        return self.asMTime(); 
    }, _doc_Plug_asMTime)

    .def("asShort", [](MPlug & self) -> short {
        plug::assert_not_null(self);

        return self.asShort(); 
    }, _doc_Plug_asShort)

    .def("asString", [](MPlug & self) -> std::string {
        plug::assert_not_null(self);

        return std::string(self.asString().asChar()); 
    }, _doc_Plug_asString)

    .def("attribute", [](MPlug & self) -> MObject {
        plug::assert_not_null(self);

        MStatus status;
        MObject result = self.attribute(&status);

        CHECK_STATUS(status)

        return result;    
    }, _doc_Plug_attribute)

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
    }, py::arg("attr"),
       _doc_Plug_child)

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
    }, py::arg("index"),
       _doc_Plug_child)

    .def("connectedTo", [](MPlug & self, bool asDst, bool asSrc) -> std::vector<MPlug> {
        plug::assert_not_null(self);

        MStatus status;
        MPlugArray results;
        self.connectedTo(results, asDst, asSrc, &status);

        CHECK_STATUS(status)

        return atov::convert(results);   
    }, py::arg("asDst"), py::arg("asSrc"), _doc_Plug_connectedTo)

    .def("connectionByPhysicalIndex", [](MPlug & self, unsigned int physicalIndex) -> MPlug {
        throw std::logic_error{"Function not yet implemented."};
    }, py::arg("physicalIndex"), _doc_Plug_connectionByPhysicalIndex)

    .def("constructHandle", [](MPlug & self, MDataBlock & mBlock) -> MDataHandle {
        throw std::logic_error{"Function not yet implemented."};
    }, py::arg("mBlock"),
       _doc_Plug_constructHandle)

    .def("destinations", [](MPlug & self) -> std::vector<MPlug> {
        plug::assert_not_null(self);

        MPlugArray results;
        MStatus status;

        self.destinations(results, &status);

        CHECK_STATUS(status)

        return atov::convert(results);  
    }, _doc_Plug_destinations)

    .def("destinationsWithConversions", [](MPlug & self) -> std::vector<MPlug> {
        plug::assert_not_null(self);
        
        MPlugArray results;
        MStatus status;

        self.destinationsWithConversions(results, &status);

        CHECK_STATUS(status)

        return atov::convert(results);  
    }, _doc_Plug_destinationsWithConversions)

    .def("destructHandle", [](MPlug & self, MDataHandle handle) -> void {
        throw std::logic_error{"Function not yet implemented."};
    }, py::arg("handle"), 
       _doc_Plug_destructHandle)

    .def("elementByLogicalIndex", [](MPlug & self, unsigned int index) -> MPlug {
        plug::assert_not_null(self);
        plug::assert_is_array(self);
        
        MStatus status;
        MPlug result = self.elementByLogicalIndex(index, &status);
        
        CHECK_STATUS(status)

        return result;
    }, py::arg("index"), _doc_Plug_elementByLogicalIndex)

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
    }, py::arg("index"), _doc_Plug_elementByPhysicalIndex)

    .def("evaluateNumElements", [](MPlug & self) -> unsigned int {
        plug::assert_not_null(self);
        plug::assert_is_array(self);

        MStatus status;
        unsigned int result = self.evaluateNumElements(&status);

        CHECK_STATUS(status)

        return result;     
    }, _doc_Plug_evaluateNumElements)

    .def("getExistingArrayAttributeIndices", [](MPlug & self) -> std::vector<int> {
        plug::assert_not_null(self);
        plug::assert_is_array(self);

        MStatus status;
        MIntArray results;
        
        self.getExistingArrayAttributeIndices(results, &status);

        CHECK_STATUS(status)

        return atov::convert(results);
    }, _doc_Plug_getExistingArrayAttributeIndices)

    .def("getSetAttrCmds", [](MPlug & self, MPlug::MValueSelector valueSelector = MPlug::MValueSelector::kAll, bool useLongNames = false) -> std::vector<std::string> {
        throw std::logic_error{"Function not yet implemented."};
    }, py::arg("valueSelector") = MPlug::MValueSelector::kAll,
       py::arg("useLongNames") = false,
       _doc_Plug_getSetAttrCmds)

    .def("info", [](MPlug & self) -> std::string {
        MString result = self.info();

        return std::string(result.asChar());
    }, _doc_Plug_info)

    .def("isArray", [](MPlug & self) -> bool {
        return self.isArray();
    }, _doc_Plug_isArray)

    .def("isChild", [](MPlug & self) -> bool {
        return self.isChild();
    }, _doc_Plug_isChild)

    .def("isCompound", [](MPlug & self) -> bool {
        return self.isCompound();
    }, _doc_Plug_isCompound)

    .def("isConnected", [](MPlug & self) -> bool {
        return self.isConnected();
    }, _doc_Plug_isConnected)

    .def("isDefaultValue", [](MPlug & self, bool forceEval = true) -> bool {
        return self.isDefaultValue(forceEval);
    }, py::arg("forceEval") = true,
       _doc_Plug_isDefaultValue)

    .def("isDestination", [](MPlug & self) -> bool {
        return self.isDestination();
    }, _doc_Plug_isDestination)

    .def("isDynamic", [](MPlug & self) -> bool {
        return self.isDynamic();
    }, _doc_Plug_isDynamic)

    .def("isElement", [](MPlug & self) -> bool {
        return self.isElement();
    }, _doc_Plug_isElement)

    .def("isFreeToChange", [](MPlug & self, bool checkParents = true, bool checkChildren = true) -> MPlug::FreeToChangeState {
        return self.isFreeToChange(checkParents, checkChildren);
    }, py::arg("checkParents") = true,
       py::arg("checkChildren") = true,
       _doc_Plug_isFreeToChange)

    .def("isFromReferencedFile", [](MPlug & self) -> bool {
        return self.isFromReferencedFile();
    }, _doc_Plug_isFromReferencedFile)

    .def("isIgnoredWhenRendering", [](MPlug & self) -> bool {
        return self.isIgnoredWhenRendering();
    }, _doc_Plug_isIgnoredWhenRendering)

    .def("isKeyable", [](MPlug & self) -> bool {
        return self.isKeyable();
    }, _doc_Plug_isKeyable)

    .def("isLocked", [](MPlug & self) -> bool {
        return self.isLocked();
    }, _doc_Plug_isLocked)

    .def("isNetworked", [](MPlug & self) -> bool {
        return self.isNetworked();    
    }, _doc_Plug_isNetworked)

    .def("isNull", [](MPlug & self) -> bool {
        return self.isNull();
    }, _doc_Plug_isNull)

    .def("isProcedural", [](MPlug & self) -> bool {
        return self.isProcedural();
    }, _doc_Plug_isProcedural)

    .def("isSource", [](MPlug & self) -> bool {
        return self.isSource();
    }, _doc_Plug_isSource)

    .def("logicalIndex", [](MPlug & self) -> unsigned int {
        plug::assert_not_null(self);
        plug::assert_is_element(self);

        MStatus status;
        unsigned int result = self.logicalIndex(&status);

        CHECK_STATUS(status)

        return result; 
    }, _doc_Plug_logicalIndex)

    .def("name", [](MPlug & self) -> std::string {
        MString result = self.name();  // TODO: error handling

        return std::string(result.asChar());
    }, _doc_Plug_name)

    .def("node", [](MPlug & self) -> MObject {
        MStatus status;
        MObject result = self.node(&status);

        CHECK_STATUS(status)

        return result; 
    }, _doc_Plug_node)

    .def("numChildren", [](MPlug & self) -> unsigned int {
        plug::assert_not_null(self);
        plug::assert_is_compound(self);

        MStatus status;
        unsigned int result = self.numChildren(&status);

        CHECK_STATUS(status)

        return result;  
    }, _doc_Plug_numChildren)

    .def("numConnectedChildren", [](MPlug & self) -> int {
        throw std::logic_error{"Function not yet implemented."};
    }, _doc_Plug_numConnectedChildren)

    .def("numConnectedElements", [](MPlug & self) -> int {
        throw std::logic_error{"Function not yet implemented."};
    }, _doc_Plug_numConnectedElements)

    .def("numElements", [](MPlug & self) -> unsigned int {
        plug::assert_not_null(self);
        plug::assert_is_array(self);

        MStatus status;
        unsigned int result = self.numElements(&status);

        CHECK_STATUS(status)

        return result; 
    }, _doc_Plug_numElements)

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
    }, _doc_Plug_parent)

    .def("partialName", [](MPlug & self, bool includeNodeName = false, bool includeNonMandatoryIndices = false, bool includeInstancedIndices = false, bool useAlias = false, bool useFullAttributePath = false, bool useLongNames = false) -> MString {
        throw std::logic_error{"Function not yet implemented."};
    }, py::arg("includeNodeName") = false,
       py::arg("includeNonMandatoryIndices") = false,
       py::arg("includeInstancedIndices") = false,
       py::arg("useAlias") = false,
       py::arg("useFullAttributePath") = false,
       py::arg("useLongNames") = false,
       _doc_Plug_partialName)

    .def("selectAncestorLogicalIndex", [](MPlug & self, unsigned int index, MObject attribute = MObject::kNullObj) {
        throw std::logic_error{"Function not yet implemented."};
    }, py::arg("index"),
       py::arg_v("attribute", MObject::kNullObj, "Object.kNullObj"),
       _doc_Plug_selectAncestorLogicalIndex)

    .def("setAttribute", [](MPlug & self) -> MObject {
        throw std::logic_error{"Function not yet implemented."};
    }, _doc_Plug_setAttribute)

    .def("setBool", [](MPlug & self, bool value) {
        plug::assert_not_null(self);

        self.setBool(value);
    }, py::arg("value"),
       _doc_Plug_setBool)

    .def("setChar", [](MPlug & self, int value) {
        plug::assert_not_null(self);

        self.setChar(char(value));
    }, py::arg("value"),
       _doc_Plug_setChar)

    .def("setDouble", [](MPlug & self, double value) {
        plug::assert_not_null(self);

        self.setDouble(value);
    }, py::arg("value"),
       _doc_Plug_setDouble)

    .def("setFloat", [](MPlug & self, float value) {
        plug::assert_not_null(self);

        self.setFloat(value);
    }, py::arg("value"),
       _doc_Plug_setFloat)

    .def("setInt", [](MPlug & self, int value) {
        plug::assert_not_null(self);

        self.setInt(value);
    }, py::arg("value"),
       _doc_Plug_setInt)

    .def("setMAngle", [](MPlug & self, MAngle angle) {
        plug::assert_not_null(self);

        self.setMAngle(angle);
    }, py::arg("angle"),
       _doc_Plug_setMAngle)

    .def("setMDataHandle", [](MPlug & self, MDataHandle dataHandle) {
        plug::assert_not_null(self);

        self.setMDataHandle(dataHandle);
    }, py::arg("dataHandle"), 
       _doc_Plug_setMDataHandle)

    .def("setMDistance", [](MPlug & self, MDistance distance) {
        plug::assert_not_null(self);

        self.setMDistance(distance);
    }, py::arg("distance"), 
       _doc_Plug_setMDistance)

    .def("setMObject", [](MPlug & self, MObject object) {
        plug::assert_not_null(self);

        self.setMObject(object);
    }, py::arg("object"), 
       _doc_Plug_setMObject)

    .def("setMPxData", [](MPlug & self, MPxData *data) {
        plug::assert_not_null(self);

        self.setMPxData(data);
    }, py::arg("data"),
       _doc_Plug_setMPxData)

    .def("setMTime", [](MPlug & self, MTime time) {
        plug::assert_not_null(self);

        self.setMTime(time);
    }, py::arg("time"),
       _doc_Plug_setMTime)

    .def("setNumElements", [](MPlug & self, unsigned int num_elements) {
        throw std::logic_error{"Function not yet implemented."};
    }, py::arg("num_elements"),
       _doc_Plug_setNumElements)

    .def("setShort", [](MPlug & self, short value) {
        plug::assert_not_null(self);

        self.setShort(value);
    }, py::arg("value"),
       _doc_Plug_setShort)

    .def("setString", [](MPlug & self, std::string value) {
        plug::assert_not_null(self);

        MString string(value.c_str());

        self.setString(string);
    }, py::arg("value"),
       _doc_Plug_setString)

    .def("source", [](MPlug & self) -> MPlug {
        plug::assert_not_null(self);

        MStatus status;
        MPlug result = self.source(&status);

        CHECK_STATUS(status)

        return result;      
    }, _doc_Plug_source)

    .def("sourceWithConversion", [](MPlug & self) -> MPlug {
        plug::assert_not_null(self);

        MStatus status;
        MPlug result = self.sourceWithConversion(&status);

        CHECK_STATUS(status)

        return result;       
    }, _doc_Plug_sourceWithConversion);
