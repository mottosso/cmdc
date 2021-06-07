import cmdc
import nose

from nose.plugins.skip import SkipTest

from maya import cmds
from maya.api import OpenMaya

from . import assert_equals, as_obj, as_plug, new_scene

def test_createNode():
    node = cmds.createNode('transform', name='root')
    node_obj = as_obj(node)
    null_obj = cmdc.Object()
    type_id = cmdc.FnDependencyNode(node_obj).typeId()

    for doc, (value, parent) in (
        ['a valid type name', ('transform', null_obj)],
        ['a valid type name and parent', ('transform', node_obj)],
        ['a valid typeId', (cmdc.TypeId(type_id), null_obj)],
        ['a valid typeId and parent', (cmdc.TypeId(type_id), node_obj)],
    ):
        test_createNode.__doc__ = """Test MDagModifier::createNode if called with {}.""".format(doc)

        yield _createNode_pass, value, parent

    not_a_dag = as_obj('time1')
    not_a_node = as_plug('persp.message').attribute()
    type_id = cmdc.FnDependencyNode(as_obj('time1')).typeId()

    for doc, (value, parent) in (
        ['an invalid type name', ('foobar', null_obj)],
        ['a non-DAG type name', ('network', null_obj)],
        ['an invalid typeId', (cmdc.TypeId(0xdeadbeef), null_obj)],
        ['an non-DAG typeId', (cmdc.TypeId(type_id), null_obj)],
        ['an invalid parent (not a DAG node)', ('transform', not_a_dag)],
        ['an invalid parent (not a node)', ('transform', not_a_node)],
    ):
        test_createNode.__doc__ = """Test MDagGModifier::createNode raises error if called with {}.""".format(doc)

        yield _createNode_fail, value, parent


@nose.with_setup(teardown=new_scene)
def _createNode_fail(value, parent):
    old_nodes = cmds.ls(long=True)

    nose.tools.assert_raises(
        TypeError, _createNode_pass, value, parent
    )

    new_nodes = cmds.ls(long=True)

    assert len(old_nodes) == len(new_nodes), "DagModifier.createNode modified the scene graph."


@nose.with_setup(teardown=new_scene)
def _createNode_pass(value, parent):
    old_nodes = cmds.ls(long=True)
    
    mod = cmdc.DagModifier()
    node = mod.createNode(value, parent)
    mod.doIt()
    
    new_nodes = cmds.ls(long=True)

    add_nodes = set(new_nodes) - set(old_nodes)

    assert not node.isNull(), "Created node is not valid."
    assert len(add_nodes) == 1, "`ls` did not return new node."
