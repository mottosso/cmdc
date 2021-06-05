import cmdc
import nose

from nose.plugins.skip import SkipTest

from maya import cmds
from maya.api import OpenMaya

from . import assert_equals, as_obj, as_plug, new_scene


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
def test_addExtensionAttribute_pass(): 
    """Test MDGModifier::addExtensionAttribute binding."""

    raise SkipTest("Cannot test DGModifier.addExtensionAttribute until MFnAttribute classes are implemented.")


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



def test_deleteNode_pass():
    """Test MDGModifier::createNode if called with a valid node."""

    node = cmds.createNode('network')
    obj = as_obj(node)
    
    mod = cmdc.DGModifier()
    mod.deleteNode(obj)

    mod.doIt()
    assert not cmds.objExists(node), 'DGModifier.deleteNode doIt failed'

    mod.undoIt()
    assert cmds.objExists(node), 'DGModifier.deleteNode undoIt failed'


def test_deleteNode_fail():
    for exc, name, value in (
        [ValueError, 'null object', cmdc.Object()],
        [TypeError, 'non-node object', as_plug('persp.message').attribute()],
        [TypeError, 'DAG object', as_obj(cmds.createNode('transform'))],
    ):
        test_deleteNode_fail.__doc__ = """Test MDGModifier::deleteNode raises error if called with a(n) {}.""".format(name)

        yield _deleteNode_fail, exc, value


@nose.with_setup(teardown=new_scene)
def _deleteNode_fail(exception, arg):
    old_nodes = cmds.ls(long=True)

    nose.tools.assert_raises(
        exception, 
        cmdc.DGModifier().deleteNode, 
        arg
    )

    new_nodes = cmds.ls(long=True)

    assert len(old_nodes) == len(new_nodes), "DGModifier.deleteNode modified the scene graph."



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
        test_disconnect_fail.__doc__ = """Test MDGModifier::disconnect raises error if called with {}.""".format(doc)

        yield _disconnect_fail, exc, args

def _disconnect_fail(exception, args):    
    nose.tools.assert_raises(
        exception,
        cmdc.DGModifier().disconnect,
        *args
    )


def test_newPlugValue():
    """Test MDGModifier::newPlugValue*."""

    identity = lambda x: x 

    for value, method_name, add_attr_kwargs in (
        [True, 'newPlugValueBool', {'at': 'bool'}],
        [ord('A'), 'newPlugValueChar', {'at': 'char'}],
        [42.0, 'newPlugValueDouble', {'at': 'double'}],
        [42.0, 'newPlugValueFloat', {'at': 'float'}],
        [42, 'newPlugValueInt', {'at': 'long'}],
        # TODO: Enable when bindings are available
        # [None, 'newPlugValueMAngle', {'at': 'doubleAngle'}, {}],
        # [None, 'newPlugValueMDistance', {'at': 'doubleLinear'}, {}],
        # [None, 'newPlugValueMTime', {'at': 'time'}, {}],
        [2, 'newPlugValueShort', {'at': 'enum', 'enumName': 'a:b:c:d'}],
        ["Hello, World!", 'newPlugValueString', {'dt': 'string'}],
    ):
        test_newPlugValue.__doc__ = """Test MDGModifier::{}.""".format(method_name)

        yield _newPlugValue, value, method_name, add_attr_kwargs


def _newPlugValue(new_value, method_name, add_attr_kwargs):
    node = cmds.createNode('network')
    cmds.addAttr(node, longName='test', **add_attr_kwargs)
    attr = node + '.test'
    
    old_value = new_value.__class__(cmds.getAttr(attr))

    plug = as_plug(attr)

    mod = cmdc.DGModifier()
    mod_fn = getattr(mod, method_name)
    mod_fn(plug, new_value)
    mod.doIt()

    # My kingdom for fStrings
    doit_value = new_value.__class__(cmds.getAttr(attr))
    assert_equals(
        new_value, doit_value, 
        'DGModifier.{} doIt failed to set the value - expected: {}, actual: {}'.format(
            method_name, new_value, doit_value
        )
    )

    mod.undoIt()

    undo_value = new_value.__class__(cmds.getAttr(attr))
    assert_equals(
        old_value, undo_value, 
        'DGModifier.{} undo failed to set the value - expected: {}, actual: {}'.format(
            method_name, old_value, undo_value
        )
    )


@nose.with_setup(teardown=new_scene)
def test_removeAttribute_pass():
    """Test MDGModifier::removeAttribute if called with a valid attribute."""

    node = cmds.createNode('network')
    attr = node + '.test'

    cmds.addAttr(node, ln='test')

    plug = as_plug(attr)

    mod = cmdc.DGModifier()
    mod.removeAttribute(plug.node(), plug.attribute())

    mod.doIt()
    assert not cmds.objExists(attr), 'DGModifier.removeAttribute doIt failed'
    
    mod.undoIt()
    assert cmds.objExists(attr), 'DGModifier.removeAttribute undoIt failed'


def test_removeAttribute_fail():
    node = cmds.createNode('network')
    cmds.addAttr(node, ln='test')

    plug = as_plug(node + '.test')
    null = cmdc.Object()

    for exc, doc, (node, attr) in (
        [ValueError, "a null node", (null, null)],
        [ValueError, "a null attribute", (plug.node(), null)],
        [TypeError, "a non-node object", (plug.attribute(), null)],
        [TypeError, "a non-attribute object", (plug.node(), plug.node())],
    ):
        test_removeAttribute_fail.__doc__ = """Test MDGModifier::removeAttribute raises an error if with {}.""".format(doc)

        yield _removeAttribute_fail, exc, node, attr


def _removeAttribute_fail(exception, node, attr):    
    nose.tools.assert_raises(
        exception,
        cmdc.DGModifier().removeAttribute,
        node, attr
    )


@nose.with_setup(teardown=new_scene)
def test_removeExtensionAttribute_pass(): 
    """Test MDGModfifier::removeExtensionAttribute binding."""

    raise SkipTest("Cannot test DGModifier.removeExtensionAttribute until MFnAttribute classes are implemented.")


def test_setNodeLockState():
    """Test MDGModifier::setNodeLockState."""
    
    node = cmds.createNode('network')
    node_obj = as_obj(node)
    null_obj = cmdc.Object()
    
    mod = cmdc.DGModifier()
    mod.setNodeLockState(node_obj, True)
    
    mod.doIt()
    assert cmds.lockNode(node, query=True, lock=True)[0], 'DGModifier.setNodeLockState doIt failed'
    
    mod.undoIt()
    assert not cmds.lockNode(node, query=True, lock=True)[0], 'DGModifier.setNodeLockState undo failed'

    nose.tools.assert_raises(
        TypeError,
        cmdc.DGModifier().setNodeLockState,
        null_obj
    )
