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
        node = cmds.createNode('network')

        cmds.addAttr(node, ln='test', at='compound', nc=1)
        cmds.addAttr(node, ln='child', parent='test')
        
        parent = cmdc.SelectionList().add(node + '.test').getPlug(0)
        child = cmdc.SelectionList().add(node + '.test.child').getPlug(0).attribute()

        attr = parent.child(child)

        assert attr is not None
        assert attr.name() == node + '.child', attr.name()

    @staticmethod
    def test_fail_attr():
        node = cmds.createNode('network')

        cmds.addAttr(node, ln='parent_a', at='compound', nc=1)
        cmds.addAttr(node, ln='child_a', parent='parent_a')

        cmds.addAttr(node, ln='parent_b', at='compound', nc=1)
        cmds.addAttr(node, ln='child_b', parent='parent_b')

        parent_a = cmdc.SelectionList().add(node + '.parent_a').getPlug(0)
        child_b = cmdc.SelectionList().add(node + '.parent_b.child_b').getPlug(0).attribute()

        nose.tools.assert_raises(ValueError, parent_a.child, child_b)