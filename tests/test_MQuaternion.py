import nose.tools
import math
import cmdc


def test_new_quaternion():
    quat = cmdc.Quaternion()
    assert quat.x == 0 and quat.y == 0 and quat.z == 0 and quat.w == 1

    quat = cmdc.Quaternion([.5,.6,.7,1])
    assert quat.x == 0.5 and quat.y == 0.6 and quat.z == 0.7 and quat.w == 1

    copy = cmdc.Quaternion(quat)
    assert copy is not quat
    assert copy.x == 0.5 and copy.y == 0.6 and copy.z == 0.7 and copy.w == 1

    quat = cmdc.Quaternion(math.pi, cmdc.Vector.xAxisVector)
    assert quat.x == 1.0 and quat.y == 0.0 and quat.z == 0.0 and quat.w <= 0.1e-4

    quat = cmdc.Quaternion(cmdc.Vector.xAxisVector, cmdc.Vector.yAxisVector, 0.0)
    assert quat.x == 0.0 and quat.y == 0.0 and quat.z == 0.0 and quat.w == 1.0

    assert len(quat) == 4

def test_multiply():
    quat = cmdc.Quaternion()
    other = quat * cmdc.Quaternion()
    assert other == quat

    quat *= other
    assert other == quat

    quat = 2.0 * other
    assert quat.w == 2.0


def test_set_value():
    quat = cmdc.Quaternion()

    quat.setValue(cmdc.Quaternion())

    quat.setValue(cmdc.EulerRotation())

    quat.setValue(cmdc.Matrix())

    quat.setValue(cmdc.Vector.zAxisVector, 0.0)


def test_extra():
    quat = cmdc.Quaternion()

    axisAngle = quat.asAxisAngle()
    assert isinstance(axisAngle, tuple)
    assert len(axisAngle) == 2
    assert isinstance(axisAngle[0], cmdc.Vector)
    assert isinstance(axisAngle[1], float)