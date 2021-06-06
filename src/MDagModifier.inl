py::class_<MDagModifier>(m, "DagModifier")
    .def(py::init<>())

    .def("createNode", [](MDagModifier & self, MString type, MObject parent = MObject::kNullObj) -> MObject {
        throw std::logic_error{"Function not yet implemented."};
    }, 
R"pbdoc(Adds an operation to the modifier to create a DAG node of the specified type. 
If a parent DAG node is provided the new node will be parented under it. 
If no parent is provided and the new DAG node is a transform type then it will be parented under the world. 
In both of these cases, the method returns the new DAG node.

If no parent is provided and the new DAG node is not a transform type 
then a transform node will be created and the child parented under that. 
The new transform will be parented under the world \
and it is the transform node which will be returned by the method, not the child.

None of the newly created nodes will be added to the DAG until the modifier's doIt() method is called.)pbdoc")

    .def("createNode", [](MDagModifier & self, MTypeId typeId, MObject parent = MObject::kNullObj) -> MObject {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Adds an operation to the modifier to create a DAG node of the specified type. 
    
If a parent DAG node is provided the new node will be parented under it. 
If no parent is provided and the new DAG node is a transform type then it will be parented under the world. 
In both of these cases the method returns the new DAG node.

If no parent is provided and the new DAG node is not a transform type 
then a transform node will be created and the child parented under that. 
The new transform will be parented under the world \ 
and it is the transform node which will be returned by the method, not the child.

None of the newly created nodes will be added to the DAG until the modifier's doIt() method is called.)pbdoc")

    .def("reparentNode", [](MDagModifier & self, MObject node, MObject newParent = MObject::kNullObj) {
        throw std::logic_error{"Function not yet implemented."};
    }, R"pbdoc(Adds an operation to the modifier to reparent a DAG node under a specified parent.

If no parent is provided then the DAG node will be reparented under the world, so long as it is a transform type. 
If it is not a transform type then the doIt() will raise a RuntimeError.)pbdoc");