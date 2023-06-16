#include <algorithm>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <maya/MDagPath.h>
#include <maya/MObject.h>
#include <maya/MPlug.h>
#include <maya/MFnMesh.h>

#include "../init.h"

namespace py = pybind11;


template <>
void init_class(py::class_<MFnMesh, MFnDagNode> &FnMesh) {

    FnMesh
        .def(py::init<>())
        .def(py::init([](MObject& object) {
            MStatus status;
            auto result = std::unique_ptr<MFnMesh>(new MFnMesh(object, &status));

            if (!status) {
                throw std::runtime_error(
                    "Invalid parameter passed for object - "
                    "not a Mesh Node, "
                    "Node does not exist or "
                    "no valid pointer to Node"
                );
            }

            return result;
        }), py::arg("object"))

        .def(py::init([](MDagPath& dagPath) {
            MStatus status;
            auto result = std::unique_ptr<MFnMesh>(new MFnMesh(dagPath, &status));

            if (!status) {
                throw std::runtime_error(
                    "Invalid parameter passed for object - "
                    "not a Mesh Node, "
                    "Node does not exist or "
                    "no valid pointer to Node"
                );
            }

            return result;
        }), py::arg("dagPath"))

        .def("getSmoothMeshDisplayOptions", [](MFnMesh& self) -> MMeshSmoothOptions {
            MMeshSmoothOptions options;
            MStatus status = self.getSmoothMeshDisplayOptions(options);

            if (!status) {
                throw std::logic_error(status.errorString().asChar());
            }

            return options;
        }, "Retrieve the current display smoothing options for the mesh.")

        .def("numVertices", [](MFnMesh& self) -> int {
            MStatus status;
            int count = self.numVertices(&status);

            if (!status) {
                throw std::logic_error(status.errorString().asChar());
            }

            return count;
        })

        .def("numEdges", [](MFnMesh& self) -> int {
            MStatus status;
            int count = self.numEdges(&status);

            if (!status) {
                throw std::logic_error(status.errorString().asChar());
            }

            return count;
        })

        .def("numPolygons", [](MFnMesh& self) -> int {
            MStatus status;
            int count = self.numPolygons(&status);

            if (!status) {
                throw std::logic_error(status.errorString().asChar());
            }

            return count;
        })

        .def("numFaceVertices", [](MFnMesh& self) -> int {
            MStatus status;
            int count = self.numFaceVertices(&status);

            if (!status) {
                throw std::logic_error(status.errorString().asChar());
            }

            return count;
        })

        .def("polygonVertexCount", [](MFnMesh& self, int polygonId) -> int {
            MStatus status;
            int count = self.polygonVertexCount(polygonId, &status);

            if (!status) {
                throw std::logic_error(status.errorString().asChar());
            }

            return count;
        }, py::arg("polygonId"))

        ;

}