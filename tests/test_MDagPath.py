import nose
import cmdc

def test_equality():
    sel = cmdc.SelectionList().add("persp")

    a = sel.getDagPath(0)
    b = sel.getDagPath(0)
    assert a == b


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

def test_fullPathName():
    sel = cmdc.SelectionList().add("persp").add("perspShape")

    persp = sel.getDagPath(0)
    persp_path_name =persp.fullPathName() 
    assert persp_path_name == "|persp"
    assert isinstance(persp_path_name, str)

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


def test_isValid():
    sel = cmdc.SelectionList().add("persp")
    persp = sel.getDagPath(0)
    assert persp.isValid()

    invalid_dag = cmdc.DagPath()
    assert not invalid_dag.isValid()

