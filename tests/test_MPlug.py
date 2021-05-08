"""Test suite for MPlug bindings."""

import nose.tools

from maya import cmds 

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
    def test_fails_on_non_array_plug():
        node = cmds.createNode('network')

        cmds.addAttr(node, ln='test')

        attr_name = '{}.test'.format(node)

        array_element = cmdc.SelectionList().add(attr_name).getPlug(0)

        nose.tools.assert_raises(
            TypeError,
            array_element.array
        )

    @staticmethod
    def test_fails_on_null_plug():
        plug = cmdc.Plug()
        
        nose.tools.assert_raises(
            ValueError,
            plug.array
        )