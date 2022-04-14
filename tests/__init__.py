from maya import standalone
standalone.initialize()

from maya import cmds
import cmdc


def new_scene():
    cmds.file(new=True, force=True)


def teardown():
  standalone.uninitialize()


def assert_equals(expected, actual, error_message):
    if isinstance(expected, float):
        assert abs(expected - actual) <= 1e-5, error_message
    else:
        assert expected == actual, error_message


def as_obj(arg):
    """Return the Maya Object for the given node."""

    return cmdc.SelectionList().add(arg).getDependNode(0)


def as_plug(arg):
    """Return the Maya Plug for the given plug."""

    return cmdc.SelectionList().add(arg).getPlug(0)
