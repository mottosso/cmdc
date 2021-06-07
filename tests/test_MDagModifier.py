import cmdc
import nose

from nose.plugins.skip import SkipTest

from maya import cmds
from maya.api import OpenMaya

from . import assert_equals, as_obj, as_plug, new_scene

def test_createNode():
    node = as_obj(cmds.createNode('transform'))
    type_id = cmdc.FnDependencyNode(node).typeId()

    for name, value in (
        ['typeName', 'transform'],
        ['typeId',  cmdc.TypeId(type_id)]
    ):
        test_createNode.__doc__ = """Test MDagModifier::createNode if called with a valid {}.""".format(name)

        yield _createNode_pass, value

    for name, value in (
        ['typeName', 'foobar'],
        ['typeName', 'network'],
        ['typeId', cmdc.TypeId(0xdeadbeef)]
    ):
        test_createNode.__doc__ = """Test MDagGModifier::createNode raises error if called with an invalid {}.""".format(name)

        yield _createNode_fail, value


@nose.with_setup(teardown=new_scene)
def _createNode_fail(arg):
    old_nodes = cmds.ls(long=True)

    nose.tools.assert_raises(
        TypeError, _createNode_pass, arg
    )

    new_nodes = cmds.ls(long=True)

    assert len(old_nodes) == len(new_nodes), "DagModifier.createNode modified the scene graph."


@nose.with_setup(teardown=new_scene)
def _createNode_pass(arg):
    old_nodes = cmds.ls(long=True)
    
    mod = cmdc.DagModifier()
    node = mod.createNode(arg, cmdc.Object())
    mod.doIt()
    
    new_nodes = cmds.ls(long=True)

    add_nodes = set(new_nodes) - set(old_nodes)

    assert not node.isNull(), "Created node is not valid."
    assert len(add_nodes) == 1, "`ls` did not return new node."
