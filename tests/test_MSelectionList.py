"""Test suite for MSelectionList bindings."""

import pytest

import cmdc 

def test_get_object_from_empty_list():
    sel = cmdc.SelectionList()

    assert len(sel) == 0

    with pytest.raises(IndexError):
        obj = sel.getDependNode(0)


def test_add_object_that_exists():
    sel = cmdc.SelectionList()

    sel.add('time1')

    assert len(sel) == 1

    obj = sel.getDependNode(0)

    assert obj.hasFn(cmdc.Fn.kTime)