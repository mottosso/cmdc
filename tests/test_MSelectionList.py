"""Test suite for MSelectionList bindings."""

import nose.tools
from maya import cmds

import cmdc 

def test_get_object_from_empty_list():
    sel = cmdc.SelectionList()

    assert sel.isEmpty()
    assert len(sel) == 0
    assert not sel

    nose.tools.assert_raises(
        IndexError,
        sel.getDependNode, 0
    )


def test_add_object_that_exists():
    sel = cmdc.SelectionList().add('time1')

    assert len(sel) == 1
    assert sel

    obj = sel.getDependNode(0)

    assert obj.hasFn(cmdc.Fn.kTime)


def test_add_object_that_does_not_exist():
    sel = cmdc.SelectionList()

    nose.tools.assert_raises(
        ValueError,
        sel.add, 'free_lunch'
    )

    assert len(sel) == 0


def test_add_match_string():
    sel = cmdc.SelectionList()
    sel.add('ti*')

    assert len(sel) == 1

    nose.tools.assert_raises(
        ValueError,
        sel.add, 'free_*'
    )


def test_get_dg_node():
    sel = cmdc.SelectionList().add('time1')
    obj = sel.getDependNode(0)

    assert obj.hasFn(cmdc.Fn.kTime)


def test_get_dag_path():
    sel = cmdc.SelectionList().add('persp')

    dag = sel.getDagPath(0)

    assert dag.hasFn(cmdc.Fn.kCamera)


def test_get_dag_path_error():
    sel = cmdc.SelectionList()
    sel.add('time1')
    sel.add('time1.outTime')

    nose.tools.assert_raises(
        TypeError,
        sel.getDagPath, 0
    )

    nose.tools.assert_raises(
        TypeError,
        sel.getDagPath, 1
    )


def test_get_plug():
    sel = cmdc.SelectionList().add('time1.outTime')

    plug = sel.getPlug(0)

    assert plug.node().hasFn(cmdc.Fn.kTime)


def test_get_plug_error():
    sel = cmdc.SelectionList()
    sel.add('time1')
    sel.add('persp')

    nose.tools.assert_raises(
        TypeError,
        sel.getPlug, 0
    )

    nose.tools.assert_raises(
        TypeError,
        sel.getPlug, 1
    )

    nose.tools.assert_raises(
        IndexError,
        sel.getPlug, 5
    )


def test_selection_strings():
    sel = cmdc.SelectionList()
    sel.add('time1')
    sel.add('persp')
    sel.add('front')

    sel_str = sel.getSelectionStrings()

    assert sel_str == ['time1', 'persp', 'front']

    sel_str = sel.getSelectionStrings(0)

    assert sel_str == ['time1']


def test_has_item():
    selA = cmdc.SelectionList().add('time1')
    timeObj = selA.getDependNode(0)

    time2 = cmds.createNode('time')

    selB = cmdc.SelectionList().add(time2)
    time2obj = selB.getDependNode(0)

    assert selA.hasItem(timeObj)
    assert not selA.hasItem(time2obj)
    assert selB.hasItem(time2obj)
    assert not selB.hasItem(timeObj)

    cmds.delete(time2)

    selC = cmdc.SelectionList().add('persp')
    perspDag = selC.getDagPath(0)
    perspObj = selC.getDependNode(0)

    assert selC.hasItem(perspDag)
    assert not selC.hasItem(perspObj)

    selD = cmdc.SelectionList().add('time1.outTime')
    plug = selD.getPlug(0)

    assert selD.hasItem(plug)


def test_clear():
    sel = cmdc.SelectionList()
    sel.add('time1')
    assert len(sel) == 1

    sel.clear()
    assert len(sel) == 0
