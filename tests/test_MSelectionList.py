"""Test suite for MSelectionList bindings."""

import pytest

import cmdc 

def test_get_object_from_empty_list():
    sel = cmdc.SelectionList()

    assert sel.isEmpty()
    assert len(sel) == 0

    with pytest.raises(IndexError):
        obj = sel.getDependNode(0)


def test_add_object_that_exists():
    sel = cmdc.SelectionList().add('time1')

    assert len(sel) == 1

    obj = sel.getDependNode(0)

    assert obj.hasFn(cmdc.Fn.kTime)


def test_add_object_that_does_not_exist():
    sel = cmdc.SelectionList()

    with pytest.raises(ValueError):
        sel.add('free_lunch')

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

    with pytest.raises(TypeError):
        sel.getDagPath(0)

    with pytest.raises(TypeError):
        sel.getDagPath(1)


def test_get_plug():
    sel = cmdc.SelectionList().add('time1.outTime')

    plug = sel.getPlug(0)

    assert plug.node().hasFn(cmdc.Fn.kTime)


def test_get_plug_error():
    sel = cmdc.SelectionList()
    sel.add('time1')
    sel.add('persp')

    with pytest.raises(TypeError):
        plug = sel.getPlug(0)

    with pytest.raises(TypeError):
        sel.getPlug(1)


def test_selection_strings():
    sel = cmdc.SelectionList()
    sel.add('time1')
    sel.add('persp')
    sel.add('front')

    sel_str = sel.getSelectionStrings()

    assert sel_str == ['time1', 'persp', 'front']

    sel_str = sel.getSelectionStrings(0)

    assert sel_str == ['time1']

    with pytest.raises(IndexError):
        obj = sel.getDependNode(5)