import atexit

import maya.standalone 
from maya import cmds

def setup():
    maya.standalone.initialize()

def new_scene():
    cmds.file(new=True, force=True)

def teardown():
    maya.standalone.uninitialize()
