from maya import standalone, cmds


def setup():
    standalone.initialize()


def new_scene():
    cmds.file(new=True, force=True)


def teardown():
    standalone.uninitialize()
