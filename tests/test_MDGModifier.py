import cmdc
import nose

from nose.plugins.skip import SkipTest

from maya import cmds
from maya.api import OpenMaya

from . import as_obj, as_plug, new_scene


@nose.with_setup(teardown=new_scene)
def test_addAttribute_pass(): 
    raise SkipTest("Cannot test DGModifier.addAttribute until MFnAttribute classes are implemented.")


@nose.with_setup(teardown=new_scene)
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
        test_addAttribute_fail.__doc__ = """Test MDGModifier::addAttribute raises error if called with {}.""".format(doc)

        yield _addAttribute_fail, exc, node, attr 


def _addAttribute_fail(exception, node, attr):    
    nose.tools.assert_raises(
        exception,
        cmdc.DGModifier().addAttribute,
        node, attr
    )


@nose.with_setup(teardown=new_scene)
def test_connect_pass(): 
    src_plug = as_plug(cmds.createNode('transform') + '.visibility')
    dst_plug = as_plug(cmds.createNode('transform') + '.visibility')

    for doc, args in (
        ["plugs", (src_plug, dst_plug)],
        ["node/attribute pairs", (src_plug.node(), src_plug.attribute(), dst_plug.node(), dst_plug.attribute())]
    ):
        test_connect_pass.__doc__ = """Test MDGModifier::connect if called with {}.""".format(doc)

        yield _connect_pass, src_plug, dst_plug, args


def _connect_pass(src_plug, dst_plug, args):    
    mod = cmdc.DGModifier()
    mod.connect(*args)

    mod.doIt()
    assert cmds.isConnected(src_plug.name(), dst_plug.name()), "DGModifier.connect doIt failed"
    
    mod.undoIt()
    assert not cmds.isConnected(src_plug.name(), dst_plug.name()), 'DGModifier.connect undoIt failed'


@nose.with_setup(teardown=new_scene)
def test_connect_fail(): 
    src_plug = as_plug(cmds.createNode('transform') + '.visibility')
    src_node = src_plug.node()
    src_attr = src_plug.attribute()

    dst_plug = as_plug(cmds.createNode('transform') + '.visibility')
    dst_node = dst_plug.node()
    dst_attr = dst_plug.attribute()

    null = cmdc.Object()
    nop_plug = cmdc.Plug()

    for exc, doc, args in (
        [ValueError, 'a null source object', (null, null, null, null)],
        [ValueError, 'a null source attribute', (src_node, null, null, null)],
        [ValueError, 'a null destination object', (src_node, src_attr, null, null)],
        [ValueError, 'a null destination attribute', (src_node, src_attr, dst_node, null)],
        [TypeError, 'a non-node source object', (src_attr, src_attr, null, null)],
        [TypeError, 'a non-attribute source attribute',(src_node, src_node, null, null)],
        [TypeError, 'a non-node destination object', (src_node, src_attr, dst_attr, dst_attr)],
        [TypeError, 'a non-attribute destination attribute', (src_node, src_attr, dst_node, dst_node)],
        [ValueError, 'a null source plug', (nop_plug, dst_plug)],
        [ValueError, 'a null destination plug', (src_plug, nop_plug)],
    ):
        test_connect_fail.__doc__ = """Test MDGModifier::connect raises exception if called with {}.""".format(doc)

        yield _connect_fail, exc, args


def _connect_fail(exception, args):    
    nose.tools.assert_raises(
        exception,
        cmdc.DGModifier().connect,
        *args
    )


def test_createNode_pass():
    node = as_obj(cmds.createNode('network'))
    type_id = cmdc.FnDependencyNode(node).typeId()

    for name, value in (
        ['typeName', 'network'],
        ['typeId',  cmdc.TypeId(type_id)]
    ):
        test_createNode_pass.__doc__ = """Test MDGModifier::createNode if called with a valid {}.""".format(name)

        yield _createNode_pass, value


def test_createNode_fail():
    for name, value in (
        ['typeName', 'foobar'],
        ['typeId', cmdc.TypeId(0xdeadbeef)]
    ):
        test_createNode_fail.__doc__ = """Test MDGModifier::createNode raises error if called with an invalid {}.""".format(name)

        yield _createNode_fail, value


@nose.with_setup(teardown=new_scene)
def _createNode_fail(arg):
    old_nodes = cmds.ls(long=True)

    nose.tools.assert_raises(
        TypeError, _createNode_pass, arg
    )

    new_nodes = cmds.ls(long=True)

    assert len(old_nodes) == len(new_nodes), "DGModifier.createNode modified the scene graph."


@nose.with_setup(teardown=new_scene)
def _createNode_pass(arg):
    old_nodes = cmds.ls(long=True)
    
    mod = cmdc.DGModifier()
    node = mod.createNode(arg)
    mod.doIt()
    
    new_nodes = cmds.ls(long=True)

    add_nodes = set(new_nodes) - set(old_nodes)

    assert not node.isNull(), "Created node is not valid."
    assert len(add_nodes) == 1, "`ls` did not return new node."



def test_disconnect_pass(): 
    def _plugs():
        src_plug = as_plug(cmds.createNode('transform') + '.visibility')
        dst_plug = as_plug(cmds.createNode('transform') + '.visibility')

        return (
            src_plug, dst_plug, 
            (src_plug, dst_plug)
        )
    
    def _objects():
        src_plug = as_plug(cmds.createNode('transform') + '.visibility')
        dst_plug = as_plug(cmds.createNode('transform') + '.visibility')

        return (
            src_plug, dst_plug,
            (src_plug.node(), src_plug.attribute(), dst_plug.node(), dst_plug.attribute())
        )

    for doc, setup_fn in (
        ["plugs", _plugs],
        ["node/attribute pairs", _objects]
    ):
        test_disconnect_pass.__doc__ = """Test MDGModifier::disconnect if called with {}.""".format(doc)

        yield _disconnect_pass, setup_fn


@nose.with_setup(teardown=new_scene)
def _disconnect_pass(setup_fn):    
    src_plug, dst_plug, args = setup_fn()
    cmds.connectAttr(src_plug.name(), dst_plug.name())

    mod = cmdc.DGModifier()
    mod.disconnect(*args)

    mod.doIt()
    assert not cmds.isConnected(src_plug.name(), dst_plug.name()), "DGModifier.disconnect doIt failed"
    
    mod.undoIt()
    assert cmds.isConnected(src_plug.name(), dst_plug.name()), 'DGModifier.disconnect undoIt failed'


def test_disconnect_fail(): 
    src_plug = as_plug(cmds.createNode('transform') + '.visibility')
    src_node = src_plug.node()
    src_attr = src_plug.attribute()

    dst_plug = as_plug(cmds.createNode('transform') + '.visibility')
    dst_node = dst_plug.node()
    dst_attr = dst_plug.attribute()

    null = cmdc.Object()
    nop_plug = cmdc.Plug()

    for exc, doc, args in (
        [ValueError, 'a null source object', (null, null, null, null)],
        [ValueError, 'a null source attribute', (src_node, null, null, null)],
        [ValueError, 'a null destination object', (src_node, src_attr, null, null)],
        [ValueError, 'a null destination attribute', (src_node, src_attr, dst_node, null)],
        [TypeError, 'a non-node source object', (src_attr, src_attr, null, null)],
        [TypeError, 'a non-attribute source attribute',(src_node, src_node, null, null)],
        [TypeError, 'a non-node destination object', (src_node, src_attr, dst_attr, dst_attr)],
        [TypeError, 'a non-attribute destination attribute', (src_node, src_attr, dst_node, dst_node)],
        [ValueError, 'a null source plug', (nop_plug, dst_plug)],
        [ValueError, 'a null destination plug', (src_plug, nop_plug)],
    ):
        test_disconnect_fail.__doc__ = """Test MDGModifier::disconnect raises exception if called with {}.""".format(doc)

        yield _disconnect_fail, exc, args

def _disconnect_fail(exception, args):    
    nose.tools.assert_raises(
        exception,
        cmdc.DGModifier().disconnect,
        *args
    )