import atexit

import maya.standalone 

def setup():
    maya.standalone.initialize()

def teardown():
    maya.standalone.uninitialize()
