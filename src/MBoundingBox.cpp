#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <maya/MBoundingBox.h>
#include <maya/MPoint.h>
#include <maya/MMatrix.h>
#include "init.h"

namespace py = pybind11;

#define _doc_BoundingBox_center \
    "Center point"

#define _doc_BoundingBox_clear \
    "Empties the bounding box, setting its corners to (0, 0, 0)."

#define _doc_BoundingBox_contains \
    "Returns True if a point lies within the bounding box."

#define _doc_BoundingBox_depth \
    "Size in Z"

#define _doc_BoundingBox_expand \
    "Expands the bounding box to include a point or other bounding box."

#define _doc_BoundingBox_height \
    "Size in Y"

#define _doc_BoundingBox_intersects \
    "Returns True if any part of a given bounding box lies within this one."

#define _doc_BoundingBox_transformUsing \
    "Multiplies the bounding box's corners by a matrix."

#define _doc_BoundingBox_width \
    "Size in X"

template <>
void init_class(py::class_<MBoundingBox> &BoundingBox) {
    BoundingBox
        .def(py::init<>())

        .def("center", [](MBoundingBox& self) -> MPoint {
            return self.center();
        }, _doc_BoundingBox_center)

        .def("clear", [](MBoundingBox& self) -> void {
            self.clear();
        }, _doc_BoundingBox_clear)

        .def("contains", [](MBoundingBox& self, MPoint point) -> bool {
            return self.contains(point);
        },
        py::arg("point"),
        _doc_BoundingBox_contains)

        .def("depth", [](MBoundingBox& self) -> double {
            return self.depth();
        }, _doc_BoundingBox_depth)

        .def("expand", [](MBoundingBox& self, MBoundingBox box) -> void {
            self.expand(box);
        },
        py::arg("box"), 
        _doc_BoundingBox_expand)

        .def("expand", [](MBoundingBox& self, MPoint point) -> void {
            self.expand(point);
        }, py::arg("point"), 
        _doc_BoundingBox_expand)

        .def("height", [](MBoundingBox& self) -> double {
            return self.height();
        }, _doc_BoundingBox_height)

        .def("intersects", [](MBoundingBox& self, MBoundingBox box, double tol = 0.0) -> bool {
            return self.intersects(box, tol);
        }, py::arg("box"),
        py::arg("tol") = 0.0,
        _doc_BoundingBox_intersects)

        .def("transformUsing", [](MBoundingBox& self, MMatrix matrix) -> void {
            self.transformUsing(matrix);
        }, py::arg("matrix"),
        _doc_BoundingBox_transformUsing)

        .def("width", [](MBoundingBox& self) -> double {
            return self.width();
        }, _doc_BoundingBox_width);
}