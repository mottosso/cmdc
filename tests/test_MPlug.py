"""Test suite for MPlug bindings."""

import nose.tools
import unittest

from maya import cmds 
from maya.api import OpenMaya 

import cmdc

class TestArrayMethods(unittest.TestCase):
    node = None 

    @classmethod 
    def setUpClass(cls):
        cmds.file(new=True, force=True)

        node = cmds.createNode('network')

        cmds.addAttr(node, ln='array', multi=True)
        cmds.addAttr(node, ln='single', multi=True)
        
        cmds.setAttr(node + '.array[0]', 0.0)

        cls.node = node 

    def test_array_pass(self):
        array_element = cmdc.SelectionList().add(self.node + '.array[0]').getPlug(0)
        array_root = array_element.array()

        assert array_root is not None
        assert array_root.name() == self.node + '.array'

    def test_array_fail(self):
        array_element = cmdc.SelectionList().add(self.node + '.single').getPlug(0)

        nose.tools.assert_raises(
            TypeError,
            array_element.array
        )


class TestCompoundPlugMethods(unittest.TestCase):
    node = None

    @classmethod 
    def setUpClass(cls):
        cmds.file(new=True, force=True)

        node = cmds.createNode('network')

        cmds.addAttr(node, ln='parent_a', at='compound', nc=1)
        cmds.addAttr(node, ln='child_a', parent='parent_a')

        cmds.addAttr(node, ln='parent_b', at='compound', nc=1)
        cmds.addAttr(node, ln='child_b', parent='parent_b')

        cls.node = node 

    def test_child_pass(self):
        parent = cmdc.SelectionList().add(self.node + '.parent_a').getPlug(0)
        child = cmdc.SelectionList().add(self.node + '.parent_a.child_a').getPlug(0).attribute()

        attr = parent.child(child)

        assert attr is not None
        assert attr.name() == self.node + '.child_a', attr.name()

        attr = parent.child(0)
        
        assert attr is not None
        assert attr.name() == self.node + '.child_a', attr.name()

    def test_child_fail(self):
        parent = cmdc.SelectionList().add(self.node + '.parent_a').getPlug(0)
        child = cmdc.SelectionList().add(self.node + '.parent_b.child_b').getPlug(0).attribute()

        nose.tools.assert_raises(ValueError, parent.child, child)
        nose.tools.assert_raises(IndexError, parent.child, 1)


class TestConnectionMethods(unittest.TestCase):
    src_node = None 
    tgt_node = None 

    @classmethod 
    def setUpClass(cls):
        src_node = cmds.createNode('network', name='source')
        tgt_node = cmds.createNode('network', name='target')

        cmds.addAttr(src_node, ln='attr', at='double')
        cmds.addAttr(tgt_node, ln='attr', at='doubleAngle')

        cmds.connectAttr(src_node + '.attr', tgt_node + '.attr')

        cls.src_node = src_node
        cls.tgt_node = tgt_node

    def test_source_pass(self):
        src_plug = cmdc.SelectionList().add(self.src_node + '.attr').getPlug(0)
        tgt_plug = cmdc.SelectionList().add(self.tgt_node + '.attr').getPlug(0)

        assert src_plug.source().isNull(), 'Plug.source should return a null plug when not a destination'
        assert tgt_plug.source() == src_plug, 'Plug.source did not return the source plug.'

    def test_sourceWithConversion_pass(self):
        src_plug = cmdc.SelectionList().add(self.src_node + '.attr').getPlug(0)
        tgt_plug = cmdc.SelectionList().add(self.tgt_node + '.attr').getPlug(0)

        assert src_plug.sourceWithConversion().isNull(), 'Plug.sourceWithConversion should return a null plug when not a destination'
        assert tgt_plug.sourceWithConversion() != src_plug, 'Plug.sourceWithConversion skipped over the conversion node'
        assert tgt_plug.sourceWithConversion().node().hasFn(cmdc.Fn.kUnitConversion), 'Plug.sourceWithConversion skipped over conversion node'
