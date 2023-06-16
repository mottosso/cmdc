#include <pybind11/pybind11.h>
#include <maya/MObject.h>
#include <maya/MPlug.h>
#include <maya/MFnDependencyNode.h>
#include "../init.h"

namespace py = pybind11;

#define CHECK_STATUS(status) if (!status) { throw std::runtime_error(status.errorString().asChar());}


#define _doc_FnDependencyNode_create \
    "Creates a new dependency node with the given type."
#define _doc_FnDependencyNode_findPlug \
    "Attempt to find a plug for the given attribute."

template <>
void init_class(py::class_<MFnDependencyNode> &FnDependencyNode) {
    FnDependencyNode
        .def(py::init<>())
        .def(py::init<const MObject &>(), py::arg("object"))

        .def("create", [](MFnDependencyNode& self,
                        const std::string type) -> MObject {
            MStatus status;
            MObject obj = self.create(type.c_str(), &status);
            CHECK_STATUS(status);
            return obj;
        }, py::arg("type"),
        _doc_FnDependencyNode_create)

        .def("create", [](MFnDependencyNode& self,
                        const std::string type,
                        const std::string name) -> MObject {
            MStatus status;
            MObject obj = self.create(type.c_str(), name.c_str(), &status);
            CHECK_STATUS(status);
            return obj;
        }, py::arg("type"),
        py::arg("name"),
        _doc_FnDependencyNode_create)

        .def("findPlug", [](MFnDependencyNode& self,
                        const std::string attrName,
                        const bool wantNetworkedPlug) -> MObject {
            MStatus status;
            MPlug obj = self.findPlug(attrName.c_str(), wantNetworkedPlug, &status);
            CHECK_STATUS(status);
            return obj;
        }, py::arg("attrName"),
        py::arg("wantNetworkedPlug") = true,
        _doc_FnDependencyNode_findPlug)

        .def("name", [](MFnDependencyNode& self) -> std::string {
            MStatus status;
            auto name = self.name(&status);
            if (!status) throw std::runtime_error("Could not get name.");
            return name.asChar();
        })

        .def("typeName", [](MFnDependencyNode& self) -> std::string {
            MStatus status;
            auto typeName = self.typeName(&status);
            if (!status) throw std::runtime_error("Could not get typeName.");
            return typeName.asChar();
        })

        .def("pluginName", [](MFnDependencyNode& self) -> std::string {
            MStatus status;
            auto pluginName = self.pluginName(&status);
            if (!status) throw std::runtime_error("Could not get pluginName.");
            return pluginName.asChar();
        })

        .def("absoluteName", [](MFnDependencyNode& self) -> std::string {
            MStatus status;
            auto absoluteName = self.absoluteName(&status);
            if (!status) throw std::runtime_error("Could not get absoluteName.");
            return absoluteName.asChar();
        })

        .def("typeId", [](MFnDependencyNode& self) -> unsigned int {
            MStatus status;
            auto typeId = self.typeId(&status);
            if (!status) throw std::runtime_error("Could not get typeId.");
            return typeId.id();
        })

        .def("__repr__", [](const MObject &a) {
            return "<cmdc.FnDependencyNode()>";
        }
    );
}