#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>

#include "core/image_buffer.hpp"

namespace nb = nanobind;
using imgengine::ImageBuffer;

NB_MODULE(_imgengine, m) {
  m.doc() = "Static image composition engine — native core";
  m.attr("__version__") = "0.0.1";

  nb::class_<ImageBuffer>(m, "ImageBuffer")
      .def(nb::init<int, int>(), nb::arg("width"), nb::arg("height"))
      .def("fill", &ImageBuffer::fill, nb::arg("r"), nb::arg("g"), nb::arg("b"),
           nb::arg("a") = 255)
      .def("save_png", &ImageBuffer::save_png, nb::arg("path"))
      .def_prop_ro("width", &ImageBuffer::width)
      .def_prop_ro("height", &ImageBuffer::height);
}
