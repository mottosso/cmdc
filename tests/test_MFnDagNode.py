import cmdc
from nose.tools import (
    assert_equals,
)


def test_addChild():
    fn = cmdc.FnDagNode()
    child = fn.createNode("transform", name="child")

    fn.createNode("transform", name="parent")
    assert_equals(fn.childCount(), 0)
    fn.addChild(child)
    assert_equals(fn.childCount(), 1)
