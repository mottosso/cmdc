import nose.tools

import cmdc 


def test_init_transform():
    transform = cmdc.FnTransform()


def test_create_transform():
    transform = cmdc.FnTransform()

    transformObj = transform.create()
    assert not transformObj.isNull()


def test_limits():
    transform = cmdc.FnTransform()
    transform.create()

    assert not transform.isLimited(cmdc.FnTransform.kScaleMinX)

    transform.enableLimit(cmdc.FnTransform.kScaleMinX, True)
    assert transform.isLimited(cmdc.FnTransform.kScaleMinX)