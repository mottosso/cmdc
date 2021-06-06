import cmdc

from nose.tools import (
    assert_equals,
)


def test_create():
    fn = cmdc.FnDagNode()
    fn.create("transform", name="child")
    assert_equals(fn.partialPathName(), "child")


def test_create_parent():
    fn = cmdc.FnDagNode()
    parent = fn.create("transform", name="parent")
    fn.create("transform", name="child", parent=parent)
    assert_equals(fn.fullPathName(), "|parent|child")


def test_addChild():
    fn = cmdc.FnDagNode()
    child = fn.create("transform", name="child")

    fn.create("transform", name="parent")
    assert_equals(fn.childCount(), 0)
    fn.addChild(child)
    assert_equals(fn.childCount(), 1)


def test_boundingBox():
    fn = cmdc.FnDagNode()
    fn.create("transform")
    bbox = fn.boundingBox()

    assert_equals(bbox.width(), 0)
    assert_equals(bbox.height(), 0)
    assert_equals(bbox.depth(), 0)
