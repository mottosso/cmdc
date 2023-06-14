import nose
from maya import cmds

import cmdc

from . import new_scene, as_obj

def test_isvalid():
    handle = cmdc.ObjectHandle()
    assert not handle.isValid()

    node = cmds.createNode('network')
    handle = cmdc.ObjectHandle(as_obj(node))
    assert handle.isValid()

    cmds.delete(node)
    assert not handle.isValid()

def test_isalive():
    handle = cmdc.ObjectHandle()
    assert not handle.isAlive()

    node = cmds.createNode('network')
    handle = cmdc.ObjectHandle(as_obj(node))
    assert handle.isAlive()

    cmds.delete(node)
    assert handle.isAlive()

    cmds.flushUndo()
    assert not handle.isAlive()

@nose.with_setup(teardown=new_scene)
def test_object():
    handle = cmdc.ObjectHandle()
    assert handle.object().isNull()

    node = as_obj(cmds.createNode('network'))
    handle = cmdc.ObjectHandle(node)
    assert handle.object() == node

@nose.with_setup(teardown=new_scene)
def test_hashcode():
    handle = cmdc.ObjectHandle()
    assert handle.hashCode() == 0

    handle = cmdc.ObjectHandle(as_obj(cmds.createNode('network')))
    assert handle.hashCode() != 0