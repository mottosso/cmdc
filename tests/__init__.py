# temp fix for nose erroring for Python 3.10
# see nose issue #1122 in github
import sys
if sys.version_info.major == 3 and sys.version_info.minor == 10:
    import collections.abc
    for member in ['Callable', 'Iterable', 'Sequence']:
        if not hasattr(collections, member):
            setattr(collections, member, getattr(collections.abc, member))

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
