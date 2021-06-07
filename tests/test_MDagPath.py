import cmdc
import nose
from maya import cmds

from . import new_scene


def test_equality():
    sel = cmdc.SelectionList().add("persp")

    a = sel.getDagPath(0)
    b = sel.getDagPath(0)
    assert a == b


def test_inequality():
    sel = cmdc.SelectionList().add("persp").add("perspShape")

    a = sel.getDagPath(0)
    b = sel.getDagPath(1)
    assert a != b


def test_apiType():
    sel = cmdc.SelectionList().add("persp")

    valid_dag = sel.getDagPath(0)
    assert valid_dag.apiType() == cmdc.Fn.kTransform

    invalid_dag = cmdc.DagPath()
    assert invalid_dag.apiType() == cmdc.Fn.kInvalid


def test_child():
    sel = cmdc.SelectionList().add("persp").add("perspShape")

    dag_with_child = sel.getDagPath(0)
    assert isinstance(dag_with_child.child(0), cmdc.Object)

    dag_without_children = sel.getDagPath(1)
    nose.tools.assert_raises(
        IndexError,
        dag_without_children.child,
        0
    )

    invalid_dag = cmdc.DagPath()
    nose.tools.assert_raises(
        RuntimeError,
        invalid_dag.child,
        0
    )


def test_childCount():
    sel = cmdc.SelectionList().add("persp").add("perspShape")

    persp = sel.getDagPath(0)
    assert persp.childCount() == 1

    persp_shape = sel.getDagPath(1)
    assert persp_shape.childCount() == 0

    invalid_dag = cmdc.DagPath()
    nose.tools.assert_raises(
        RuntimeError,
        invalid_dag.childCount,
    )


def test_exclusiveMatrix():
    sel = cmdc.SelectionList().add("persp").add("perspShape")

    persp = sel.getDagPath(0)
    assert isinstance(persp.exclusiveMatrix(), cmdc.Matrix)

    invalid_dag = cmdc.DagPath()
    nose.tools.assert_raises(
        RuntimeError,
        invalid_dag.exclusiveMatrix,
    )


def test_exclusiveMatrixInverse():
    sel = cmdc.SelectionList().add("persp").add("perspShape")

    persp = sel.getDagPath(0)
    assert isinstance(persp.exclusiveMatrixInverse(), cmdc.Matrix)

    invalid_dag = cmdc.DagPath()
    nose.tools.assert_raises(
        RuntimeError,
        invalid_dag.exclusiveMatrixInverse,
    )


def test_extendToShape():
    sel = cmdc.SelectionList().add("persp").add("perspShape")

    persp = sel.getDagPath(0)
    persp_shape = sel.getDagPath(1)
    persp.extendToShape()
    assert persp == persp_shape

    invalid_dag = cmdc.DagPath()
    nose.tools.assert_raises(
        RuntimeError,
        invalid_dag.extendToShape,
    )


@nose.with_setup(teardown=new_scene)
def test_extendToShapeDirectlyBelow():
    transform = cmds.polyCube()[0]
    cmds.duplicate("pCubeShape1")
    shape1 = "pCubeShape1"
    shape2 = "pCubeShape2"
    cmds.parent(shape2, transform, shape=True, relative=True)
    assert len(cmds.listRelatives(transform, shapes=True)) == 2

    sel = cmdc.SelectionList().add(transform).add(shape1).add(shape2)

    transform_dag = sel.getDagPath(0)
    shape1_dag = sel.getDagPath(1)
    transform_dag.extendToShapeDirectlyBelow(0)
    assert transform_dag == shape1_dag

    transform_dag = sel.getDagPath(0)
    shape2_dag = sel.getDagPath(2)
    transform_dag.extendToShapeDirectlyBelow(1)
    assert transform_dag == shape2_dag

    transform_dag = sel.getDagPath(0)
    nose.tools.assert_raises(
        IndexError,
        transform_dag.extendToShapeDirectlyBelow,
        2
    )

    invalid_dag = cmdc.DagPath()
    nose.tools.assert_raises(
        RuntimeError,
        invalid_dag.extendToShapeDirectlyBelow,
        0
    )


def test_fullPathName():
    sel = cmdc.SelectionList().add("persp").add("perspShape")

    persp = sel.getDagPath(0)
    persp_path_name = persp.fullPathName()
    assert persp_path_name == "|persp"

    persp_shape = sel.getDagPath(1)
    assert persp_shape.fullPathName() == "|persp|perspShape"

    invalid_dag = cmdc.DagPath()
    nose.tools.assert_raises(
        RuntimeError,
        invalid_dag.fullPathName,
    )


def test_getAPathTo():
    sel = cmdc.SelectionList().add("persp").add("time1")

    persp_obj = sel.getDependNode(0)
    persp_dag = sel.getDagPath(0)
    result = cmdc.DagPath.getAPathTo(persp_obj)
    assert result == persp_dag

    time_obj = sel.getDependNode(1)
    nose.tools.assert_raises(
        TypeError,
        cmdc.DagPath.getAPathTo,
        time_obj
    )

    invalid_obj = cmdc.Object()
    nose.tools.assert_raises(
        RuntimeError,
        cmdc.DagPath.getAPathTo,
        invalid_obj
    )


def test_hasFn():
    sel = cmdc.SelectionList().add("persp").add("perspShape")

    persp = sel.getDagPath(0)
    assert persp.hasFn(cmdc.Fn.kTransform)

    persp_shape = sel.getDagPath(1)
    assert persp_shape.hasFn(cmdc.Fn.kCamera)

    invalid_dag = cmdc.DagPath()
    nose.tools.assert_raises(
        RuntimeError,
        invalid_dag.hasFn,
        cmdc.Fn.kTransform
    )


def test_inclusiveMatrix():
    sel = cmdc.SelectionList().add("persp").add("perspShape")

    persp = sel.getDagPath(0)
    assert isinstance(persp.inclusiveMatrix(), cmdc.Matrix)

    invalid_dag = cmdc.DagPath()
    nose.tools.assert_raises(
        RuntimeError,
        invalid_dag.inclusiveMatrix,
    )


def test_inclusiveMatrixInverse():
    sel = cmdc.SelectionList().add("persp").add("perspShape")

    persp = sel.getDagPath(0)
    assert isinstance(persp.inclusiveMatrixInverse(), cmdc.Matrix)

    invalid_dag = cmdc.DagPath()
    nose.tools.assert_raises(
        RuntimeError,
        invalid_dag.inclusiveMatrixInverse,
    )


@nose.with_setup(teardown=new_scene)
def test_instancenumber():
    sel = cmdc.SelectionList().add("|persp|perspShape")

    persp_shape = sel.getDagPath(0)
    nose.tools.assert_raises(
        TypeError,
        persp_shape.instanceNumber,
    )

    cmds.instance("perspShape")
    sel.add("|persp1|perspShape")
    persp1_shape = sel.getDagPath(1)
    assert persp_shape.instanceNumber() == 0
    assert persp1_shape.instanceNumber() == 1

    invalid_dag = cmdc.DagPath()
    nose.tools.assert_raises(
        RuntimeError,
        invalid_dag.instanceNumber,
    )


@nose.with_setup(teardown=new_scene)
def test_isInstanced():
    sel = cmdc.SelectionList().add("perspShape")

    persp_shape = sel.getDagPath(0)
    assert not persp_shape.isInstanced()

    cmds.instance("perspShape")
    assert persp_shape.isInstanced()

    invalid_dag = cmdc.DagPath()
    nose.tools.assert_raises(
        RuntimeError,
        invalid_dag.isInstanced,
    )


@nose.with_setup(teardown=new_scene)
def test_isTemplated():
    class DisplayType(object):
        normal = 0
        template = 1

    sel = cmdc.SelectionList().add("persp")
    persp = sel.getDagPath(0)
    assert not persp.isTemplated()

    cmds.setAttr("persp.overrideEnabled", True)
    cmds.setAttr("persp.overrideDisplayType", DisplayType.template)
    assert persp.isTemplated()

    invalid_dag = cmdc.DagPath()
    nose.tools.assert_raises(
        RuntimeError,
        invalid_dag.isTemplated,
    )


def test_isValid():
    sel = cmdc.SelectionList().add("persp")
    persp = sel.getDagPath(0)
    assert persp.isValid()

    invalid_dag = cmdc.DagPath()
    assert not invalid_dag.isValid()


@nose.with_setup(teardown=new_scene)
def test_isVisible():
    sel = cmdc.SelectionList().add("persp")

    persp = sel.getDagPath(0)
    assert not persp.isVisible()

    cmds.showHidden("persp")
    assert persp.isVisible()

    invalid_dag = cmdc.DagPath()
    nose.tools.assert_raises(
        RuntimeError,
        invalid_dag.isVisible,
    )


def test_length():
    sel = cmdc.SelectionList().add("persp").add("perspShape")

    persp = sel.getDagPath(0)
    assert persp.length() == 1

    persp_shape = sel.getDagPath(1)
    assert persp_shape.length() == 2

    invalid_dag = cmdc.DagPath()
    nose.tools.assert_raises(
        RuntimeError,
        invalid_dag.length,
    )


def test_node():
    sel = cmdc.SelectionList().add("persp")

    persp_dag = sel.getDagPath(0)
    persp_obj = sel.getDependNode(0)
    assert persp_dag.node() == persp_obj

    invalid_dag = cmdc.DagPath()
    nose.tools.assert_raises(
        RuntimeError,
        invalid_dag.length,
    )


def test_numberOfShapesDirectlyBelow():
    sel = cmdc.SelectionList().add("persp").add("perspShape")

    persp = sel.getDagPath(0)
    assert persp.numberOfShapesDirectlyBelow() == 1

    persp_shape = sel.getDagPath(1)
    assert persp_shape.numberOfShapesDirectlyBelow() == 0

    invalid_dag = cmdc.DagPath()
    nose.tools.assert_raises(
        RuntimeError,
        invalid_dag.numberOfShapesDirectlyBelow,
    )


def test_partialPathName():
    sel = cmdc.SelectionList().add("persp").add("perspShape")

    persp = sel.getDagPath(0)
    assert persp.partialPathName() == "persp"

    persp_shape = sel.getDagPath(1)
    assert persp_shape.partialPathName() == "perspShape"

    invalid_dag = cmdc.DagPath()
    nose.tools.assert_raises(
        RuntimeError,
        invalid_dag.partialPathName,
    )


def test_pop():
    sel = cmdc.SelectionList().add("persp").add("perspShape")

    persp = sel.getDagPath(0)
    persp_shape = sel.getDagPath(1)
    persp_shape.pop(1)
    assert persp == persp_shape

    invalid_dag = cmdc.DagPath()
    nose.tools.assert_raises(
        RuntimeError,
        invalid_dag.pop,
    )


def test_push():
    sel = cmdc.SelectionList().add("persp").add("perspShape")

    persp_dag = sel.getDagPath(0)
    persp_shape_dag = sel.getDagPath(1)
    persp_shape_obj = sel.getDependNode(1)

    persp_dag.push(persp_shape_obj)
    assert persp_dag == persp_shape_dag

    invalid_dag = cmdc.DagPath()
    nose.tools.assert_raises(
        RuntimeError,
        invalid_dag.push,
        cmdc.Object()
    )


def test_set():
    sel = cmdc.SelectionList().add("persp")

    persp_dag = sel.getDagPath(0)

    dag = cmdc.DagPath()
    dag.set(persp_dag)
    assert dag == persp_dag


def test_transform():
    sel = cmdc.SelectionList().add("persp").add("perspShape")

    persp_obj = sel.getDependNode(0)

    persp_dag = sel.getDagPath(0)
    assert persp_dag.transform() == persp_obj

    persp_shape_dag = sel.getDagPath(1)
    assert persp_shape_dag.transform() == persp_obj

    invalid_dag = cmdc.DagPath()
    nose.tools.assert_raises(
        RuntimeError,
        invalid_dag.transform,
    )
