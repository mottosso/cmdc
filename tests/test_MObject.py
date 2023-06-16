import cmdc

def test_init_null():
    obj = cmdc.Object()
    assert obj.isNull()

    obj = cmdc.Object.kNullObj
    assert obj.isNull()

def test_init_mobject():
    sel = cmdc.SelectionList().add("persp")
    obj = sel.getDependNode(0)
    other = cmdc.Object(obj)
    assert not other.isNull()

def test_hasFn():
    sel = cmdc.SelectionList().add("persp")
    obj = sel.getDependNode(0)
    assert obj.hasFn(cmdc.Fn.kTransform)

    sel = cmdc.SelectionList().add("perspShape")
    obj = sel.getDependNode(0)
    assert obj.hasFn(cmdc.Fn.kCamera)

def test_apiType():
    sel = cmdc.SelectionList().add("persp")
    obj = sel.getDependNode(0)
    assert obj.apiType() == cmdc.Fn.kTransform.value

def test_apiTypeStr():
    sel = cmdc.SelectionList().add("persp")
    obj = sel.getDependNode(0)
    assert obj.apiTypeStr() == cmdc.Fn.kTransform.name

def test_equality():
    sel = cmdc.SelectionList().add("persp")
    obj = sel.getDependNode(0)
    other = cmdc.Object(obj)
    assert obj == other

    assert cmdc.Object() == cmdc.Object.kNullObj

def test_inequality():
    sel = cmdc.SelectionList()
    sel.add("persp")
    sel.add("front")
    persp = sel.getDependNode(0)
    front = sel.getDependNode(1)
    assert persp != front
