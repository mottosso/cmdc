"""Test suite for MSelectionList bindings."""

import cmdc 

def test_add_object_that_exists():
    sel = cmdc.SelectionList()

    sel.add('time1')

    assert len(sel) == 1

    obj = sel.getDependNode(0)

    assert obj.hasFn(cmdc.Fn.kTime)