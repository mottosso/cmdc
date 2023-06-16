import nose.tools
from maya import cmds

import cmdc


def setup():
    global cubeFn
    transform = cmds.polyCube(ch=False, name='cube')
    cube = cmds.listRelatives(transform, children=True, shapes=True)[0]
    sel = cmdc.SelectionList()
    sel.add(cube)

    cubeObj = sel.getDependNode(0)
    cubeFn = cmdc.FnMesh(cubeObj)


def delete_cube():
    global cubeFn
    cubeName = cubeFn.name()
    cmds.delete(cmds.listRelatives(cubeName, parent=True))


def test_init_mesh():
    mesh = cmdc.FnMesh()


def test_num_vertices():
    mesh = cmdc.FnMesh()
    nose.tools.assert_raises(
        RuntimeError, 
        mesh.numVertices
    )

    assert cubeFn.numVertices() == 8


def test_num_edges():
    mesh = cmdc.FnMesh()
    nose.tools.assert_raises(
        RuntimeError, 
        mesh.numEdges
    )

    assert cubeFn.numEdges() == 12


def test_num_polygons():
    mesh = cmdc.FnMesh()
    nose.tools.assert_raises(
        RuntimeError, 
        mesh.numPolygons
    )

    assert cubeFn.numPolygons() == 6


def test_num_face_vertices():
    mesh = cmdc.FnMesh()
    nose.tools.assert_raises(
        RuntimeError, 
        mesh.numFaceVertices
    )

    assert cubeFn.numFaceVertices() == 24


def test_polygon_vertex_count():
    mesh = cmdc.FnMesh()
    nose.tools.assert_raises(
        RuntimeError, 
        mesh.polygonVertexCount,
        0
    )

    cubeFn.polygonVertexCount(0) == 4
