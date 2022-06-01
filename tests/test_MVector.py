import nose.tools

import cmdc


def test_new_vector():
    default = cmdc.Vector()
    assert default.x == 0.0 and default.y == 0.0 and default.z == 0.0

    default.x = 1
    default.y = 2
    default.z = 3
    assert default.x == 1.0 and default.y == 2.0 and default.z == 3.0

    a = cmdc.Vector(1, 2, 3)
    assert a.x == 1.0 and a.y == 2.0 and a.z == 3.0

    a = cmdc.Vector(1, 2)
    assert a.x == 1.0 and a.y == 2.0 and a.z == 0.0

    b = cmdc.Vector([4, 5, 6])
    assert b.x == 4.0 and b.y == 5.0 and b.z == 6.0

    c = cmdc.Vector([7, 8])
    assert c.x == 7.0 and c.y == 8.0 and c.z == 0.0

    d = cmdc.Vector((1, 2, 3))
    assert d.x == 1.0 and d.y == 2.0 and d.z == 3.0

    nose.tools.assert_raises(
        TypeError,
        cmdc.Vector,
        [9]
    )

    nose.tools.assert_raises(
        TypeError,
        cmdc.Vector,
        [9, 10, 11, 12]
    )

    copy = cmdc.Vector(a)
    assert a is not copy

    copy = cmdc.Vector(cmdc.Point(1,2,3))
    assert copy.x == 1.0 and copy.y == 2.0 and copy.z == 3.0

    one = cmdc.Vector.oneVector
    assert one.x == 1.0 and one.y == 1.0 and one.z == 1.0

    zero = cmdc.Vector.zeroVector
    assert zero.x == 0.0 and zero.y == 0.0 and zero.z == 0.0

    xAxis = cmdc.Vector.xAxisVector
    assert xAxis.x == 1.0 and xAxis.y == 0.0 and xAxis.z == 0.0

    xNegAxis = cmdc.Vector.xNegAxisVector
    assert xNegAxis.x == -1.0 and xNegAxis.y == 0.0 and xNegAxis.z == 0.0

    yAxis = cmdc.Vector.yAxisVector
    assert yAxis.x == 0.0 and yAxis.y == 1.0 and yAxis.z == 0.0

    yNegAxis = cmdc.Vector.yNegAxisVector
    assert yNegAxis.x == 0.0 and yNegAxis.y == -1.0 and yNegAxis.z == 0.0

    zAxis = cmdc.Vector.zAxisVector
    assert zAxis.x == 0.0 and zAxis.y == 0.0 and zAxis.z == 1.0

    zNegAxis = cmdc.Vector.zNegAxisVector
    assert zNegAxis.x == 0.0 and zNegAxis.y == 0.0 and zNegAxis.z == -1.0

    assert len(cmdc.Vector.zeroVector) == 3

def test_add():
    xy = cmdc.Vector.xAxisVector + cmdc.Vector.yAxisVector
    assert xy.x == 1.0 and xy.y == 1.0 and xy.z == 0

    xy += cmdc.Vector.zAxisVector
    assert xy.x == 1.0 and xy.y == 1.0 and xy.z == 1.0

def test_multiply():
    result = cmdc.Vector.oneVector * 2.0
    assert result.x == 2.0 and result.y == 2.0 and result.z == 2.0

    result *= 3.0
    assert result.x == 6.0 and result.y == 6.0 and result.z == 6.0

    result = cmdc.Vector.xAxisVector * cmdc.Matrix()
    assert result == cmdc.Vector.xAxisVector

def test_subtract():
    xy = cmdc.Vector.xAxisVector - cmdc.Vector.yAxisVector
    assert xy.x == 1.0 and xy.y == -1.0 and xy.z == 0

    xy -= cmdc.Vector.zAxisVector
    assert xy.x == 1.0 and xy.y == -1.0 and xy.z == -1.0

    invVector = -xy
    assert invVector.x == -1.0 and invVector.y == 1.0 and invVector.z == 1.0

def test_divide():
    result = cmdc.Vector.oneVector / 2.0
    assert result.x == 0.5 and result.y == 0.5 and result.z == 0.5

    result /= 0.5
    assert result.x == 1.0 and result.y == 1.0 and result.z == 1.0

def test_dot():
    assert cmdc.Vector.xAxisVector * cmdc.Vector.xAxisVector == 1.0
    assert cmdc.Vector.xAxisVector * cmdc.Vector.yAxisVector == 0.0

def test_cross():
    xAxis = cmdc.Vector.yAxisVector ^ cmdc.Vector.zAxisVector
    assert xAxis.x == 1.0 and xAxis.y == 0.0 and xAxis.z == 0.0

def test_normal():
    vector = cmdc.Vector.yAxisVector * 2
    assert vector.length() == 2.0

    normalized = vector.normal()
    assert normalized.length() == 1.0
    assert vector.length() == 2.0

    vector.normalize()
    assert vector.length() == 1.0

def test_extra():
    angle = cmdc.Vector.xAxisVector.angle(cmdc.Vector.yAxisVector)
    assert (angle - 1.570) < 0.001

    assert cmdc.Vector.xAxisVector.isParallel(cmdc.Vector.xAxisVector, 0.001)
    assert not cmdc.Vector.xAxisVector.isParallel(cmdc.Vector.yAxisVector, 0.001)

    assert cmdc.Vector.zAxisVector.isEquivalent(cmdc.Vector.zAxisVector, 0.001)
    assert not cmdc.Vector.zAxisVector.isEquivalent(cmdc.Vector.zeroVector, 0.001)

    assert cmdc.Vector.oneVector == cmdc.Vector.oneVector
    assert cmdc.Vector.oneVector != cmdc.Vector.zeroVector