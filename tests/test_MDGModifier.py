import cmdc
import nose

from nose.plugins.skip import SkipTest

from maya import cmds
from maya.api import OpenMaya

from . import as_obj, as_plug, new_scene


def test_addAttribute_pass(): 
    raise SkipTest("Cannot test DGModifier.addAttribute until MFnAttribute classes are implemented.")


def test_addAttribute_fail():
    node = as_obj(cmds.createNode('network'))
    null = cmdc.Object()

    attr = as_plug('persp.message').attribute()

    for exc, doc, node, attr in (
        [ValueError, 'a null object', null, null],
        [ValueError, 'a null attribute', node, null],
        [TypeError, 'a non-node object', attr, null],
        [TypeError, 'a non-attribute object', node, node],
    ):
        test_addAttribute_fail.__doc__ = """Test MDGModifier::addAttribute errors if passed {}.""".format(doc)

        yield _addAttribute_fail, exc, node, attr 


def _addAttribute_fail(exception, node, attr):    
    nose.tools.assert_raises(
        exception,
        cmdc.DGModifier().addAttribute,
        node, attr
    )


@nose.with_setup(teardown=new_scene)
def test_createNode_pass():
    node = cmds.createNode('network')
    node = OpenMaya.MSelectionList().add(node).getDependNode(0)
    type_id = OpenMaya.MFnDependencyNode(node).typeId.id()

    for name, value in (
        ['typeName', 'network'],
        ['typeId',  cmdc.TypeId(type_id)]
    ):
        test_createNode_pass.__doc__ = """Test for MDGModifier::createNode({}) binding with valid arguments.""".format(name)

        yield _createNode_pass, value


@nose.with_setup(teardown=new_scene)
def test_createNode_fail():

    for name, value in (
        ['typeName', 'foobar'],
        ['typeId', cmdc.TypeId(0xdeadbeef)]
    ):
        test_createNode_fail.__doc__ = """Test MDGModifier::createNode({}) binding with invalid arguments.""".format(name)

        yield _createNode_fail, value


def _createNode_fail(arg):
    old_nodes = cmds.ls(long=True)

    nose.tools.assert_raises(
        TypeError, _createNode_pass, arg
    )

    new_nodes = cmds.ls(long=True)

    assert len(old_nodes) == len(new_nodes), "DGModifier.createNode modified the scene graph."


def _createNode_pass(arg):
    old_nodes = cmds.ls(long=True)
    
    mod = cmdc.DGModifier()
    node = mod.createNode(arg)
    mod.doIt()
    
    new_nodes = cmds.ls(long=True)

    add_nodes = set(new_nodes) - set(old_nodes)

    assert not node.isNull(), "Created node is not valid."
    assert len(add_nodes) == 1, "`ls` did not return new node."
