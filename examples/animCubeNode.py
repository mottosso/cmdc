"""
Produces the dependency graph node "spAnimCube".

This plug-in demonstrates how to take time as an input, and create polygonal
geometry for output. The compute method of the node constructs a polygonal
cube whose size depends on the current frame number. The resulting mesh is
passed to an internal Maya node that displays it and allows
it to be positioned.

To use this node, execute the python script animCubeNode.py that contains
the following commands:

  import maya.cmds as cmds
  cmds.createNode("transform", name="animCube1")
  cmds.createNode("mesh", name="animCubeShape1", parent="animCube1")
  cmds.sets("animCubeShape1", add="initialShadingGroup")
  cmds.createNode("spAnimCube", name="animCubeNode1")
  cmds.connectAttr("time1.outTime", "animCubeNode1.time")
  cmds.connectAttr("animCubeNode1.outputMesh", "animCubeShape1.inMesh")

This creates a mesh node under a transform node which is hooked into
the world for display. It then creates an spAnimCube node, and connects
its input to the time node, and its output to the mesh node.

A cube will now appear on the screen. If the play button on the time
slider is pressed, the displayed cube will grow and shrink as the frame
number changes.

import maya.cmds as cmds
cmds.createNode("transform", name="animCube1")
cmds.createNode("mesh", name="animCubeShape1", parent="animCube1")
cmds.sets("animCubeShape1", add="initialShadingGroup")
cmds.createNode("spAnimCube", name="animCubeNode1")
cmds.connectAttr("time1.outTime", "animCubeNode1.time")
cmds.connectAttr("animCubeNode1.outputMesh", "animCubeShape1.inMesh")

"""

import cmdc

kPluginNodeName = "spAnimCube"
kPluginNodeId = cmdc.MTypeId(0x8700B)


class animCube(cmdc.MPxNode):
    time = cmdc.MObject()
    outputMesh = cmdc.MObject()

    @classmethod
    def nodeCreator(cls):
        return cmdc.asMPxPtr(cls())

    @classmethod
    def nodeInitializer(cls):
        unitAttr = cmdc.MFnUnitAttribute()
        typedAttr = cmdc.MFnTypedAttribute()

        cls.time = unitAttr.create("time", "tm",
                                   cmdc.MFnUnitAttribute.kTime, 0.0)
        cls.outputMesh = typedAttr.create("outputMesh", "out",
                                          cmdc.MFnData.kMesh)

        cls.addAttribute(cls.time)
        cls.addAttribute(cls.outputMesh)

        cls.attributeAffects(cls.time, cls.outputMesh)

    def createMesh(self, tempTime, outData):
        frame = max(0, int(tempTime.asUnits(cmdc.MTime.kFilm)))
        cubeSize = 0.5 * float(frame % 10)

        points = [
            cmdc.FloatPoint(-cubeSize, -cubeSize, -cubeSize),
            cmdc.FloatPoint(cubeSize, -cubeSize, -cubeSize),
            cmdc.FloatPoint(cubeSize, -cubeSize, cubeSize),
            cmdc.FloatPoint(-cubeSize, -cubeSize, cubeSize),
            cmdc.FloatPoint(-cubeSize, cubeSize, -cubeSize),
            cmdc.FloatPoint(-cubeSize, cubeSize, cubeSize),
            cmdc.FloatPoint(cubeSize, cubeSize, cubeSize),
            cmdc.FloatPoint(cubeSize, cubeSize, -cubeSize),
        ]

        faceConnects = [
            0, 1, 2, 3, 4, 5, 6, 7, 3, 2, 6, 5,
            0, 3, 5, 4, 0, 4, 7, 1, 1, 7, 6
        ]

        faceCounts = [4, 4, 4, 4, 4, 4]

        meshFS = cmdc.MFnMesh()
        newMesh = meshFS.create(len(points),
                                len(faceCounts),
                                points,
                                faceCounts,
                                faceConnects,
                                outData)

        return newMesh

    def compute(self, plug, data):
        if plug == self.outputMesh:
            timeData = data.inputValue(self.time)
            tempTime = timeData.asTime()

            outputHandle = data.outputValue(self.outputMesh)

            dataCreator = cmdc.MFnMeshData()
            newOutputData = dataCreator.create()

            self.createMesh(tempTime, newOutputData)

            outputHandle.setMObject(newOutputData)
            data.setClean(plug)

            return cmdc.kSuccess

        return cmdc.kUnknownParameter


def initializePlugin(mobject):
    mplugin = cmdc.MFnPlugin(mobject)
    mplugin.registerNode(kPluginNodeName,
                         kPluginNodeId,
                         animCube.nodeCreator,
                         animCube.nodeInitializer)


def uninitializePlugin(mobject):
    mplugin = cmdc.MFnPlugin(mobject)
    mplugin.deregisterNode(kPluginNodeId)
