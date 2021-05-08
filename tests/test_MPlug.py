"""Test suite for MPlug bindings."""

import nose.tools

from maya import cmds 
from maya.api import OpenMaya 

import cmdc

class test_array(object):
    @staticmethod
    def test_pass():
        node = cmds.createNode('network')

        cmds.addAttr(node, ln='test', multi=True)

        attr_name = '{}.test'.format(node)
        elem_name = '{}[0]'.format(attr_name)

        cmds.setAttr(elem_name, 0.0)

        array_element = cmdc.SelectionList().add(elem_name).getPlug(0)
        array_root = array_element.array()

        assert array_root is not None
        assert array_root.name() == attr_name

    @staticmethod
    def test_fail():
        node = cmds.createNode('network')

        cmds.addAttr(node, ln='test')

        attr_name = '{}.test'.format(node)

        array_element = cmdc.SelectionList().add(attr_name).getPlug(0)

        nose.tools.assert_raises(
            TypeError,
            array_element.array
        )

    @staticmethod
    def test_null():
        plug = cmdc.Plug()

        nose.tools.assert_raises(
            ValueError,
            plug.array
        )


class test_child(object):
    @staticmethod
    def test_pass_attr():
        node = test_child._setup_scene()

        parent = cmdc.SelectionList().add(node + '.parent_a').getPlug(0)
        child = cmdc.SelectionList().add(node + '.parent_a.child_a').getPlug(0).attribute()

        attr = parent.child(child)

        assert attr is not None
        assert attr.name() == node + '.child_a', attr.name()

    @staticmethod
    def test_fail_attr():
        node = test_child._setup_scene()

        parent = cmdc.SelectionList().add(node + '.parent_a').getPlug(0)
        child = cmdc.SelectionList().add(node + '.parent_b.child_b').getPlug(0).attribute()

        nose.tools.assert_raises(ValueError, parent.child, child)

    @staticmethod
    def test_pass_index():
        node = test_child._setup_scene()
        
        parent = cmdc.SelectionList().add(node + '.parent_a').getPlug(0)

        attr = parent.child(0)

        assert attr is not None
        assert attr.name() == node + '.child_a', attr.name()

    @staticmethod
    def test_fail_index():
        node = test_child._setup_scene()

        parent = cmdc.SelectionList().add(node + '.parent_a').getPlug(0)

        nose.tools.assert_raises(IndexError, parent.child, 1)

    @staticmethod
    def _setup_scene():
        node = cmds.createNode('network')

        cmds.addAttr(node, ln='parent_a', at='compound', nc=1)
        cmds.addAttr(node, ln='child_a', parent='parent_a')

        cmds.addAttr(node, ln='parent_b', at='compound', nc=1)
        cmds.addAttr(node, ln='child_b', parent='parent_b')

        return node


class test_source(object):
    @staticmethod
    def test_pass():
        src_node = cmds.createNode('network', name='source')
        tgt_node = cmds.createNode('network', name='target')

        cmds.addAttr(src_node, ln='attr', at='double')
        cmds.addAttr(tgt_node, ln='attr', at='doubleAngle')

        cmds.connectAttr(src_node + '.attr', tgt_node + '.attr')

        src_plug = cmdc.SelectionList().add(src_node + '.attr').getPlug(0)
        tgt_plug = cmdc.SelectionList().add(tgt_node + '.attr').getPlug(0)

        assert src_plug.source().isNull(), 'Plug.source should return a null plug when not a destination'
        assert tgt_plug.source() == src_plug, 'Plug.source did not return the source plug.'

    @staticmethod
    def test_pass_with_conversion():
        src_node = cmds.createNode('network', name='source')
        tgt_node = cmds.createNode('network', name='target')

        cmds.addAttr(src_node, ln='attr', at='double')
        cmds.addAttr(tgt_node, ln='attr', at='doubleAngle')

        cmds.connectAttr(src_node + '.attr', tgt_node + '.attr')

        src_plug = cmdc.SelectionList().add(src_node + '.attr').getPlug(0)
        tgt_plug = cmdc.SelectionList().add(tgt_node + '.attr').getPlug(0)

        assert src_plug.sourceWithConversion().isNull(), 'Plug.sourceWithConversion should return a null plug when not a destination'
        assert tgt_plug.sourceWithConversion() != src_plug, 'Plug.sourceWithConversion skipped over the conversion node'
        assert tgt_plug.sourceWithConversion().node().hasFn(cmdc.Fn.kUnitConversion), 'Plug.sourceWithConversion skipped over conversion node'
