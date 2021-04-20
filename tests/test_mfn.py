"""Tests for the MFn bindings."""

import cmdc
import maya.api.OpenMaya


def test_fn_types():
    """Check that the Fn.Type enum is identical to the MFn.Type enum"""

    for k, v in maya.api.OpenMaya.MFn.__dict__.items():
        if not k.startswith('k'):
            continue

        assert hasattr(cmdc.Fn.Type, k), (
            "Missing enum '%s'." % k)

        assert getattr(cmdc.Fn.Type, k).value == v, (
            "Enum has wrong value '%s'." % k)


def test_null_obj_fn():
    """Test that a null Object has the expected Fn"""

    o = cmdc.Object()

    assert not o.hasFn(cmdc.Fn.kInvalid)
    assert o.apiType() == cmdc.Fn.kInvalid.value
    assert o.apiTypeStr() == cmdc.Fn.kInvalid.name
