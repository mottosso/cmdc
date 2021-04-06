import cmdc

typ = cmdc.TypeId(16)

mat4 = cmdc.Matrix()
mat4 *= cmdc.Matrix().inverse()

vec3 = cmdc.Vector()
vec3.x = 6

quat = cmdc.Quaternion(angle=0.5, axis=cmdc.Vector(1, 0, 0))
mat4 *= quat

# No need for MString
string = str()

# Modify the Maya scene graph
from maya import standalone
standalone.initialize()
fn = cmdc.FnDependencyNode()
r = fn.create("reverse", name="myReverse")
print(fn.name())

# This next line really shouldn't work, should require MFnDagNode
t = fn.create("transform", name="myTransform")
print(fn.name())

print("Success")