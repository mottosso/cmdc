"""Test suite for MSelectionList bindings."""

import nose.tools

import cmdc 

def test_get_object_from_empty_list():
    sel = cmdc.SelectionList()

    assert sel.isEmpty()
    assert len(sel) == 0

    nose.tools.assert_raises(
        IndexError,
        sel.getDependNode, 0
    )


def test_add_object_that_exists():
    sel = cmdc.SelectionList().add('time1')

    assert len(sel) == 1

    obj = sel.getDependNode(0)

    assert obj.hasFn(cmdc.Fn.kTime)


def test_add_object_that_does_not_exist():
    sel = cmdc.SelectionList()

    nose.tools.assert_raises(
        ValueError,
        sel.add, 'free_lunch'
    )

    assert len(sel) == 0


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
