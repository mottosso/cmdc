import cmdc


def test_example():
    cmdc.TypeId(16)

    mat4 = cmdc.Matrix()
    mat4 *= cmdc.Matrix().inverse()

    vec3 = cmdc.Vector()
    vec3.x = 6

    quat = cmdc.Quaternion(angle=0.5, axis=cmdc.Vector(1, 0, 0))
    mat4 *= quat

    # Modify the Maya scene graph
    from maya import standalone
    standalone.initialize()
    fn = cmdc.FnDependencyNode()
    fn.create("reverse", name="myReverse")
    assert fn.name() == "myReverse"

    # This next line really shouldn't work, should require MFnDagNode
    fn.create("transform", name="myTransform")
    assert fn.name() == "myTransform"
