import cmdc
import nose

from nose.plugins.skip import SkipTest

from maya import cmds
from maya.api import OpenMaya

from . import assert_equals, as_obj, as_plug, new_scene

def test_subclassDGModifier():
    assert issubclass(cmdc.DagModifier, cmdc.DGModifier)

def test_createNode():
    return 

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


def test_reparentNode():
    node_a = cmds.createNode('transform')
    node_b = cmds.createNode('transform')
    node_c = cmds.createNode('transform', parent=node_a)
    node_d = cmds.createNode('transform', parent=node_c)

    node_obj_a = as_obj(node_a)
    node_obj_b = as_obj(node_b)
    node_obj_c = as_obj(node_c)
    node_obj_d = as_obj(node_d)
    null_obj = cmdc.Object()

    for doc, (node, new_parent) in (
        ['a null object (parent to world)', (node_obj_c, null_obj)],
        ['a valid object', (node_obj_c, node_obj_b)],
    ):
        test_reparentNode.__doc__ = """Test MDagModifier::reparentNode if called with {}.""".format(doc)

        yield _reparentNode_pass, node, new_parent

    not_a_dag = as_obj('time1')
    not_a_node = as_plug('persp.message').attribute()

    for exc, doc, (node, new_parent) in (
        [TypeError, 'an invalid object (not a DAG node)', (node_obj_c, not_a_dag)],
        [TypeError, 'an invalid object (not a node)', (node_obj_c, not_a_node)],
        [ValueError, 'the same object', (node_obj_c, node_obj_c)],
        [ValueError, 'a parent and one of its children', (node_obj_c, node_obj_d)],
    ):
        test_reparentNode.__doc__ = """Test MDagModifier::reparentNode raises an error if called with {}.""".format(doc)

        yield _reparentNode_fail, exc, node, new_parent


def _reparentNode_pass(node, new_parent):
    fn_node = cmdc.FnDagNode(node)

    old_parent = fn_node.parent(0)

    mod = cmdc.DagModifier()
    mod.reparentNode(node, new_parent)

    mod.doIt()
    parent = fn_node.parent(0)

    if new_parent.isNull():
        assert parent == fn_node.dagRoot(), "DagModifier.reparentNode doIt failed"
    else:
        assert parent == new_parent, "DagModifier.reparentNode doIt failed"
    
    mod.undoIt()
    parent = fn_node.parent(0)
    assert parent == old_parent, "DagModifier.reparentNode undo failed"

    # Parent the node to world before the next test.
    mod = cmdc.DagModifier()
    mod.reparentNode(node, old_parent)
    mod.doIt()


def _reparentNode_fail(exception, node, new_parent):
    nose.tools.assert_raises(
        exception, 
        cmdc.DagModifier().reparentNode, 
        node, new_parent
    )