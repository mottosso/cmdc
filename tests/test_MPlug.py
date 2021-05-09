"""Test suite for MPlug bindings."""

import copy
import nose.tools
import six
import unittest

from maya import cmds 
from maya.api import OpenMaya 

import cmdc

def p(base, *args):
    """Construct a plug string from the given attributes."""

    parts = [base]

    for arg in args:
        if isinstance(arg, (int, float)):
            parts[-1] = '{}[{}]'.format(parts[-1], arg)
        elif isinstance(arg, six.string_types):
            if len(arg) == 1:
                parts[-1] = '{}{}'.format(parts[-1], arg)
            else:
                parts.append(arg)

    return '.'.join(parts)

@unittest.skip('')
class TestCommonMethods(unittest.TestCase):
    """Tests for common MPlug methods bindings."""

    node = None 

    @classmethod 
    def setUpClass(cls):
        cmds.file(new=True, force=True)

        node = cmds.createNode('network')

        cmds.addAttr(node, ln='root', at='compound', nc=1)
        cmds.addAttr(node, ln='branch', at='compound', nc=1, parent='root', multi=True)
        cmds.addAttr(node, ln='leaf', parent='branch')
        
        cmds.setAttr(p(node, 'root', 'branch', 0, 'leaf'), 0.0)

        cls.node = node 

    def test_info(self):
        """Test for MPlug::info binding."""

        attr = p(self.node, 'root', 'branch', 0, 'leaf')
        plug = cmdc.SelectionList().add(attr).getPlug(0)

        # You would think it would return the full plug path, but it doesn't...
        assert plug.info() == p(self.node, 'branch', 0, 'leaf')

@unittest.skip('')
class TestArrayMethods(unittest.TestCase):
    """Tests for MPlug methods bindings for array/element plugs."""

    node = None 

    @classmethod 
    def setUpClass(cls):
        cmds.file(new=True, force=True)

        node = cmds.createNode('network')

        cmds.addAttr(node, ln='array', multi=True)
        cmds.addAttr(node, ln='single')
        
        cmds.setAttr(p(node, 'array', 0), 0.0)
        cmds.setAttr(p(node, 'array', 1), 0.0)
        cmds.setAttr(p(node, 'array', 3), 0.0)

        cls.node = node 

    def test_array(self):
        """Test for MPlug::array binding."""
        
        array_element = cmdc.SelectionList().add(p(self.node, 'array', 0)).getPlug(0)
        array_root = array_element.array()

        assert array_root is not None
        assert array_root.name() == p(self.node, 'array')

        non_array_element = cmdc.SelectionList().add(p(self.node, 'single')).getPlug(0)

        nose.tools.assert_raises(TypeError, non_array_element.array)
        nose.tools.assert_raises(ValueError, cmdc.Plug().array)

    def test_elementByLogicalIndex(self):
        """Test for MPlug::elementByLogicalIndex binding."""

        array_root = cmdc.SelectionList().add(p(self.node, 'array')).getPlug(0)
        
        selection = cmdc.SelectionList().add(p(self.node, 'array[*]'))

        plug_0 = selection.getPlug(0)
        plug_1 = selection.getPlug(1)
        plug_3 = selection.getPlug(2)

        assert array_root.elementByLogicalIndex(0) == plug_0
        assert array_root.elementByLogicalIndex(1) == plug_1
        assert array_root.elementByLogicalIndex(3) == plug_3

        # A plug will be created at the requested index if it does not exist.
        assert not array_root.elementByLogicalIndex(5).isNull()

        non_array_root = cmdc.SelectionList().add(p(self.node, 'single')).getPlug(0)

        nose.tools.assert_raises(TypeError, non_array_root.elementByLogicalIndex, 0)
        nose.tools.assert_raises(ValueError, cmdc.Plug().elementByLogicalIndex, 0)

    def test_elementByPhysicalIndex(self):
        """Test for MPlug::elementByPhysicalIndex binding."""

        array_root = cmdc.SelectionList().add(p(self.node, 'array')).getPlug(0)
        
        selection = cmdc.SelectionList().add(p(self.node, 'array[*]'))

        plug_0 = selection.getPlug(0)
        plug_1 = selection.getPlug(1)
        plug_3 = selection.getPlug(2)

        assert array_root.elementByPhysicalIndex(0) == plug_0
        assert array_root.elementByPhysicalIndex(1) == plug_1
        assert array_root.elementByPhysicalIndex(2) == plug_3

        nose.tools.assert_raises(IndexError, array_root.elementByPhysicalIndex, 9001)

        non_array_root = cmdc.SelectionList().add(p(self.node, 'single')).getPlug(0)

        nose.tools.assert_raises(TypeError, non_array_root.elementByPhysicalIndex, 0)
        nose.tools.assert_raises(ValueError, cmdc.Plug().elementByPhysicalIndex, 0)
    
    def test_evaluateNumElements(self):
        """Test for MPlug::evaluateNumElements binding."""

        array_root = cmdc.SelectionList().add(p(self.node, 'array')).getPlug(0)
        
        assert array_root.evaluateNumElements() == 3

        non_array_root = cmdc.SelectionList().add(p(self.node, 'single')).getPlug(0)

        nose.tools.assert_raises(TypeError, non_array_root.evaluateNumElements)
        nose.tools.assert_raises(ValueError, cmdc.Plug().evaluateNumElements)

    def test_getExistingArrayAttributeIndices(self):
        """Test for MPlug::getExistingArrayAttributeIndices binding."""

        array_root = cmdc.SelectionList().add(p(self.node, 'array')).getPlug(0)
        
        indices = array_root.getExistingArrayAttributeIndices()

        assert indices == [0, 1, 3]

        non_array_root = cmdc.SelectionList().add(p(self.node, 'single')).getPlug(0)

        nose.tools.assert_raises(TypeError, non_array_root.getExistingArrayAttributeIndices)
        nose.tools.assert_raises(ValueError, cmdc.Plug().getExistingArrayAttributeIndices)

    def test_logicalIndex(self):
        """Test for MPlug::logicalIndex binding."""

        selection = cmdc.SelectionList().add(p(self.node, 'array[*]'))

        plug_0 = selection.getPlug(0)
        plug_1 = selection.getPlug(1)
        plug_3 = selection.getPlug(2)

        assert plug_0.logicalIndex() == 0
        assert plug_1.logicalIndex() == 1
        assert plug_3.logicalIndex() == 3

        non_element = cmdc.SelectionList().add(p(self.node, 'single')).getPlug(0)

        nose.tools.assert_raises(TypeError, non_element.logicalIndex)
        nose.tools.assert_raises(ValueError, cmdc.Plug().logicalIndex)

    def test_numElements(self):
        """Test for MPlug::numElements binding."""

        array_root = cmdc.SelectionList().add(p(self.node, 'array')).getPlug(0)
        
        assert array_root.numElements() == 3

        non_array_root = cmdc.SelectionList().add(p(self.node, 'single')).getPlug(0)

        nose.tools.assert_raises(TypeError, non_array_root.numElements)
        nose.tools.assert_raises(ValueError, cmdc.Plug().numElements)

@unittest.skip('')
class TestCompoundPlugMethods(unittest.TestCase):
    """Tests for MPlug methods bindings for compound plugs."""

    node = None

    @classmethod 
    def setUpClass(cls):
        cmds.file(new=True, force=True)

        node = cmds.createNode('network')

        cmds.addAttr(node, ln='parent_a', at='compound', nc=1)
        cmds.addAttr(node, ln='child_a', parent='parent_a')

        cmds.addAttr(node, ln='parent_b', at='compound', nc=1)
        cmds.addAttr(node, ln='child_b', parent='parent_b')

        cmds.addAttr(node, ln='single')

        cls.node = node 

    def test_child(self):
        """Test for MPlug::child binding."""

        parent = cmdc.SelectionList().add(p(self.node, 'parent_a')).getPlug(0)
        child = cmdc.SelectionList().add(p(self.node, 'parent_a', 'child_a')).getPlug(0).attribute()

        attr = parent.child(child)

        assert attr is not None
        assert attr.name() == p(self.node, 'child_a'), attr.name()

        attr = parent.child(0)
        
        assert attr is not None
        assert attr.name() == p(self.node, 'child_a'), attr.name()

        parent = cmdc.SelectionList().add(p(self.node, 'parent_a')).getPlug(0)
        child = cmdc.SelectionList().add(p(self.node, 'parent_b', 'child_b')).getPlug(0).attribute()

        nose.tools.assert_raises(ValueError, parent.child, child)
        nose.tools.assert_raises(IndexError, parent.child, 1)
        nose.tools.assert_raises(ValueError, cmdc.Plug().child, 0)

    def test_parent(self):
        """Test for MPlug::parent binding."""

        parent = cmdc.SelectionList().add(p(self.node, 'parent_a')).getPlug(0)
        child = cmdc.SelectionList().add(p(self.node, 'parent_a', 'child_a')).getPlug(0)

        result = child.parent()

        assert result is not None
        assert result.name() == parent.name()

        nose.tools.assert_raises(TypeError, parent.parent)
        nose.tools.assert_raises(ValueError, cmdc.Plug().parent)

    def test_numChildren(self):
        """Test for MPlug::numChildren binding."""

        parent = cmdc.SelectionList().add(p(self.node, 'parent_a')).getPlug(0)

        assert parent.numChildren() == 1
        
        non_parent = cmdc.SelectionList().add(p(self.node, 'single')).getPlug(0)

        nose.tools.assert_raises(TypeError, non_parent.numChildren)
        nose.tools.assert_raises(ValueError, cmdc.Plug().numChildren)

@unittest.skip('')
class TestConnectionMethods(unittest.TestCase):
    """Tests for MPlug methods bindings for connections."""

    src_node = None 
    tgt_node = None 
    alt_node = None

    @classmethod 
    def setUpClass(cls):
        src_node = cmds.createNode('network', name='source')
        tgt_node = cmds.createNode('network', name='target')
        alt_node = cmds.createNode('network')

        cmds.addAttr(src_node, ln='attr', at='double')
        cmds.addAttr(tgt_node, ln='attr', at='doubleAngle')
        cmds.addAttr(alt_node, ln='attr', at='doubleAngle')

        cmds.connectAttr(p(src_node, 'attr'), p(tgt_node, 'attr'))
        cmds.connectAttr(p(src_node, 'attr'), p(alt_node, 'attr'))

        cls.src_node = src_node
        cls.tgt_node = tgt_node
        cls.alt_node = alt_node

    def test_connectedTo(self):
        """Test for MPlug::connectedTo binding."""

        src_node = cmds.createNode('network')
        the_node = cmds.createNode('network')
        dst_node_a = cmds.createNode('network')
        dst_node_b = cmds.createNode('network')

        cmds.addAttr(src_node, ln='attr', at='double')
        cmds.addAttr(the_node, ln='attr', at='double')
        cmds.addAttr(dst_node_a, ln='attr', at='double')
        cmds.addAttr(dst_node_b, ln='attr', at='double')

        cmds.connectAttr(p(src_node, 'attr'), p(the_node, 'attr'))
        cmds.connectAttr(p(the_node, 'attr'), p(dst_node_a, 'attr'))
        cmds.connectAttr(p(the_node, 'attr'), p(dst_node_b, 'attr'))

        the_plug = cmdc.SelectionList().add(p(the_node, 'attr')).getPlug(0)

        src_connections = the_plug.connectedTo(True, True)
        src_input = the_plug.connectedTo(True, False)
        src_outputs = the_plug.connectedTo(False, True)

        assert len(src_connections) == 3
        assert len(src_input) == 1
        assert len(src_outputs) == 2

    def test_destinations(self):
        """Test for MPlug::destinations binding."""

        src_plug = cmdc.SelectionList().add(p(self.src_node, 'attr')).getPlug(0)
        tgt_plug = cmdc.SelectionList().add(p(self.tgt_node, 'attr')).getPlug(0)
        alt_plug = cmdc.SelectionList().add(p(self.alt_node, 'attr')).getPlug(0)

        assert tgt_plug.destinations() == [], 'Plug.destinations should return an empty list for unconnected plugs'
        
        destinations = src_plug.destinations()
        
        assert destinations is not None, 'Plug.destinations returned a null'

        assert len(destinations) == 2, 'Plug.destinations returned %s values; expected 2' % len(destinations)

        assert tgt_plug in destinations, 'Plug.destinations returned incorrect results'
        assert alt_plug in destinations, 'Plug.destinations returned incorrect results'
        
        nose.tools.assert_raises(ValueError, cmdc.Plug().destinations)

    def test_destinationsWithConversion(self):
        """Test for MPlug::destinationsWithConversions binding."""

        src_plug = cmdc.SelectionList().add(p(self.src_node, 'attr')).getPlug(0)
        tgt_plug = cmdc.SelectionList().add(p(self.tgt_node, 'attr')).getPlug(0)
        alt_plug = cmdc.SelectionList().add(p(self.alt_node, 'attr')).getPlug(0)

        assert tgt_plug.destinations() == [], 'Plug.destinationsWithConversions should return an empty list for unconnected plugs'
        
        destinations = src_plug.destinationsWithConversions()
        
        assert destinations is not None, 'Plug.destinationsWithConversions returned a null'

        assert len(destinations) == 2, 'Plug.destinationsWithConversions returned %s values; expected 2' % len(destinations)

        assert destinations[0].node().hasFn(cmdc.Fn.kUnitConversion), 'Plug.destinationsWithConversions skipped over conversion node'
        assert destinations[1].node().hasFn(cmdc.Fn.kUnitConversion), 'Plug.destinationsWithConversions skipped over conversion node'

        assert tgt_plug not in destinations, 'Plug.destinationsWithConversions returned incorrect results'
        assert alt_plug not in destinations, 'Plug.destinationsWithConversions returned incorrect results'
        
        nose.tools.assert_raises(ValueError, cmdc.Plug().destinationsWithConversions)

    def test_source(self):
        """Test for MPlug::source binding."""

        src_plug = cmdc.SelectionList().add(p(self.src_node, 'attr')).getPlug(0)
        tgt_plug = cmdc.SelectionList().add(p(self.tgt_node, 'attr')).getPlug(0)

        assert src_plug.source().isNull(), 'Plug.source should return a null plug when not a destination'
        assert tgt_plug.source() == src_plug, 'Plug.source did not return the source plug.'

        nose.tools.assert_raises(ValueError, cmdc.Plug().source)

    def test_sourceWithConversion(self):
        """Test for MPlug::sourceWithConversion binding."""

        src_plug = cmdc.SelectionList().add(p(self.src_node, 'attr')).getPlug(0)
        tgt_plug = cmdc.SelectionList().add(p(self.tgt_node, 'attr')).getPlug(0)

        assert src_plug.sourceWithConversion().isNull(), 'Plug.sourceWithConversion should return a null plug when not a destination'
        assert tgt_plug.sourceWithConversion() != src_plug, 'Plug.sourceWithConversion skipped over the conversion node'
        assert tgt_plug.sourceWithConversion().node().hasFn(cmdc.Fn.kUnitConversion), 'Plug.sourceWithConversion skipped over conversion node'

        nose.tools.assert_raises(ValueError, cmdc.Plug().sourceWithConversion)


def test_asType():
    """Test for MPlug::as* bindings."""

    for (method_name, value, add_attr_kwargs, set_attr_kwargs) in [
        ('asBool', True, {'at': 'bool'}, {}),
        ('asChar', (65, 'A'), {'at': 'char'}, {}),
        ('asDouble', 1.0, {'at': 'double'}, {}),
        ('asFloat', 1.0, {'at': 'float'}, {}),
        ('asInt', 5, {'at': 'long'}, {}),
        # asMAngle - not yet implemented
        # asMDataHandle - not yet implemented
        # asMDistance - not yet implemented
        # asMObject - custom test (see below)
        # asMTime - not yet implemented
        ('asShort', 3, {'at': 'enum', 'enumName': 'a:b:c:d'}, {}),
        ('asString', 'hello', {'dt': 'string'}, {'type': 'string'}),
    ]:
        # Somehow, this works
        test_asType.__doc__ = """Test for MPlug::{} bindings.""".format(method_name)

        yield check_asType, method_name, value, add_attr_kwargs, set_attr_kwargs


def check_asType(method_name, value, add_attr_kwargs, set_attr_kwargs):
    """Test for MPlug::as* bindings."""

    # 'asChar' expects an int but returns a char in Python
    if isinstance(value, tuple):
        in_value, out_value = value 
    else:
        in_value = value
        out_value = value 
 
    node = cmds.createNode('network')

    attr = p(node, 'attr')

    cmds.addAttr(node, ln='attr', **add_attr_kwargs)
    cmds.setAttr(attr, in_value, **set_attr_kwargs)

    plug = cmdc.SelectionList().add(attr).getPlug(0)
    
    method = getattr(plug, method_name)

    expected = out_value
    actual = method()

    error_message = (
        'Plug method {} returned the wrong value - expected: {}, actual: {}'
        .format(
            method_name, expected, actual
        )
    )

    if isinstance(expected, float):
        assert abs(expected - actual) <= 1e-5, error_message
    else:
        assert expected == actual, error_message


def test_asMObject():
    """Test for MPlug::asMObject bindings."""

    cube, = cmds.polyCube(constructionHistory=False)
    mesh, = cmds.listRelatives(cube, children=True, type='mesh')

    plug = cmdc.SelectionList().add(p(mesh, 'worldMesh')).getPlug(0)
    
    value = plug.asMObject()

    assert value is not None, 'Plug.asMObject returned a null'
    assert not value.isNull(), 'Plug.asMObject returned a null MObject'
    assert value.hasFn(cmdc.Fn.kMesh), \
        'Plug.asMObject returned an object of type {} instead of kMesh'.format(value.apiTypeStr())