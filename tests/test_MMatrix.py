import nose.tools

import cmdc


def test_new_matrix():
    default = cmdc.Matrix()

    seq16 = [1,0,0,0,
             0,1,0,0,
             0,0,1,0,
             0,0,0,1]
    seq16Matrix = cmdc.Matrix(seq16)

    seq4 = [[1,0,0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1]]
    seq4Matrix = cmdc.Matrix(seq4)

    nose.tools.assert_raises(
        TypeError,
        cmdc.Matrix,
        [1,0,0]
    )

    nose.tools.assert_raises(
        TypeError,
        cmdc.Matrix,
        [[1,0,0], []]
    )    


def test_properties():
    matrix = cmdc.Matrix()
    assert not matrix.isSingular

    assert len(matrix) == 16