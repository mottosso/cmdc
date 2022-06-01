import nose.tools

import cmdc 

def test_new_transformation_matrix():
    origMatrix = cmdc.TransformationMatrix()
    copyMatrix = cmdc.TransformationMatrix(origMatrix)
    assert copyMatrix is not origMatrix

    otherCopy = cmdc.TransformationMatrix(cmdc.Matrix())

def test_as_matrix():
    mat = cmdc.TransformationMatrix()

    invMatrix = mat.asMatrixInverse()
    rotMatrix = mat.asRotateMatrix()
    scaleMatrix = mat.asScaleMatrix()

def test_translation():
    mat = cmdc.TransformationMatrix()

    translation = cmdc.Vector(1.0, 2.0, 3.0)
    mat.setTranslation(translation, cmdc.Space.kTransform)
    assert mat.translation(cmdc.Space.kTransform) == translation

    mat.translateBy(translation, cmdc.Space.kTransform)
    assert mat.translation(cmdc.Space.kTransform) == cmdc.Vector(2.0, 4.0, 6.0)

def test_rotation():
    mat = cmdc.TransformationMatrix()

    mat.reorderRotation(cmdc.TransformationMatrix.kZYX)
    assert mat.rotationOrder == cmdc.TransformationMatrix.kZYX

    mat.rotateBy(cmdc.Quaternion(), cmdc.Space.kTransform)
    mat.rotateBy(cmdc.EulerRotation(), cmdc.Space.kTransform)

    rotation = cmdc.Quaternion()
    mat.setRotation(rotation)
    assert rotation == mat.quaternionRotation

    rotation = cmdc.EulerRotation()
    mat.setRotation(rotation)
    assert rotation == mat.eulerRotation

def test_scale():
    mat = cmdc.TransformationMatrix()

    scale = [2.0, 3.0, 4.0]
    mat.setScale(scale, cmdc.Space.kTransform)
    assert mat.scale(cmdc.Space.kTransform) == scale

    mat.scaleBy(scale, cmdc.Space.kTransform)
    assert mat.scale(cmdc.Space.kTransform) == [4.0, 9.0, 16.0]
