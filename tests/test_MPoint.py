import nose.tools

import cmdc


def test_new_point():
    point = cmdc.Point()
    assert point.x == 0 and point.y == 0 and point.z == 0 and point.w == 1

    point.x = 4
    point.y = 3
    point.z = 2
    point.w = 0
    assert point.x == 4 and point.y == 3 and point.z == 2 and point.w == 0

    point = cmdc.Point(1,2,3,4)
    assert point.x == 1 and point.y == 2 and point.z == 3 and point.w == 4

    point = cmdc.Point(1,2,3)
    assert point.x == 1 and point.y == 2 and point.z == 3 and point.w == 1

    point = cmdc.Point(1,2)
    assert point.x == 1 and point.y == 2 and point.z == 0 and point.w == 1

    point = cmdc.Point([5,6,7,8])
    assert point.x == 5 and point.y == 6 and point.z == 7 and point.w == 8

    point = cmdc.Point([5,6,7])
    assert point.x == 5 and point.y == 6 and point.z == 7 and point.w == 1

    point = cmdc.Point([5,6])
    assert point.x == 5 and point.y == 6 and point.z == 0 and point.w == 1

    origin = cmdc.Point.origin
    assert origin.x == 0 and origin.y == 0 and origin.z == 0 and origin.w == 1

    copy =  cmdc.Point(point)
    assert copy is not point
    assert copy.x == 5 and copy.y == 6 and copy.z == 0 and copy.w == 1 

    copy = cmdc.Point(cmdc.Vector(1,2,3))
    assert copy.x == 1 and copy.y == 2 and copy.z == 3 and copy.w == 1 

    assert len(cmdc.Point.origin) == 4

def test_multiply():
    point = cmdc.Point(1,2,3)
    scaled = point * 2
    assert scaled.x == 2 and scaled.y == 4 and scaled.z == 6 and scaled.w == 1

    scaled *= 3
    assert scaled.x == 6 and scaled.y == 12 and scaled.z == 18 and scaled.w == 1

    matrix = cmdc.Matrix([1,0,0,0,
                          0,1,0,0,
                          0,0,1,0,
                          4,2,3,1])
    translated = point * matrix
    assert translated.x == 5 and translated.y == 4 and translated.z == 6 and translated.w == 1

    point *= matrix
    assert point.x == 5 and point.y == 4 and point.z == 6 and point.w == 1

def test_divide():
    point = cmdc.Point(4,8,16)
    scaled = point / 2
    assert scaled.x == 2 and scaled.y == 4 and scaled.z == 8 and scaled.w == 1

def test_add():
    point = cmdc.Point(2,3,4)
    result = point + cmdc.Vector.oneVector
    assert result.x == 3 and result.y == 4 and result.z == 5

    point += cmdc.Vector(6,7,8)
    assert point.x == 8 and point.y == 10 and point.z == 12

def test_subtract():
    point = cmdc.Point(2,3,4)
    result = point - cmdc.Vector.oneVector
    assert result.x == 1 and result.y == 2 and result.z == 3

    point -= cmdc.Vector.oneVector
    assert point.x == 1 and point.y == 2 and point.z == 3

def test_extra():
    pointA = cmdc.Point(1,0,0)
    pointB = cmdc.Point(-1,0,0)

    assert pointA.distanceTo(pointB) == 2

    assert not pointA.isEquivalent(pointB)
    assert pointA.isEquivalent(pointA)
