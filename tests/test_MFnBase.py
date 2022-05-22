import cmdc
import maya.api.OpenMaya as om
import nose
from nose.tools import raises


def test_type():
    sel = cmdc.SelectionList().add("persp")
    persp = sel.getDependNode(0)
    fn = cmdc.FnDagNode(persp)
    assert cmdc.FnBase.type(fn) == cmdc.Fn.kDagNode

def test_hasObj():
    # we have to test this on a subclass of FnBase as it can't be instantiated
    sel = cmdc.SelectionList().add("persp")
    persp = sel.getDependNode(0)
    fn = cmdc.FnDagNode(persp)
    assert fn.hasObj(persp)

def test_object():
    # we have to test this on a subclass of FnBase as it can't be instantiated
    sel = cmdc.SelectionList().add("persp")
    persp = sel.getDependNode(0)
    fn = cmdc.FnDagNode(persp)
    assert fn.object() == persp
    
@raises(RuntimeError)
def test_object_invalid():
    fn = cmdc.FnDagNode()
    fn.object()

def test_setObject():
    # we have to test this on a subclass of FnBase as it can't be instantiated
    sel = cmdc.SelectionList().add("persp").add("perspShape")
    persp = sel.getDependNode(0)
    persp_shape = sel.getDependNode(1)

    fn = cmdc.FnDagNode(persp)
    assert fn.object() == persp

    fn.setObject(persp_shape)
    assert fn.object() == persp_shape

def test_className():
    assert cmdc.FnBase.className() == cmdc.FnBase.__name__

def test_typeString():
    if om.MGlobal.apiVersion() < 20200000:
        raise nose.SkipTest(
            "MFnBase::typeString is not defined prior to maya 2020."
        )

    assert cmdc.FnBase.typeString(cmdc.Fn.kDagNode) == "kDagNode"

def test_isValid():
    if om.MGlobal.apiVersion() < 20200000:
        raise nose.SkipTest(
            "MFnBase::isValid is not defined prior to maya 2020."
        )

    assert cmdc.FnBase.isValid(cmdc.Fn.kDagNode) is True
    assert cmdc.FnBase.isValid(cmdc.Fn.kLast) is False
