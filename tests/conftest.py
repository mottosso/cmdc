import atexit
import pytest 

import maya.standalone 

maya.standalone.initialize()

atexit.register(maya.standalone.uninitialize)

from maya import cmds 

@pytest.fixture(scope='function')
def new_scene():
    """Open a new Maya scene."""

    cmds.file(new=True, force=True)
