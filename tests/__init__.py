import atexit

import maya.standalone 
from maya import cmds

import cmdc


def setup():
    maya.standalone.initialize()


def new_scene():
    cmds.file(new=True, force=True)


def teardown():
    maya.standalone.uninitialize()


def as_obj(arg):
    """Return the Maya Object for the given node."""

    return cmdc.SelectionList().add(arg).getDependNode(0)


def as_plug(arg):
    """Return the Maya Plug for the given plug."""

    return cmdc.SelectionList().add(arg).getPlug(0)
