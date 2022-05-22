import cmdc

def test_inherits_FnBase():
    assert issubclass(cmdc.FnDependencyNode, cmdc.FnBase)