#include <pybind11/pybind11.h>
#include <pybind11/functional.h> // Required to support std::function
#include "../src/Kalman1D.h"

namespace py = pybind11;

PYBIND11_MODULE(kalman_module, m) {
    py::class_<Kalman1D>(m, "Kalman1D")
        .def(py::init<double, double, double, 
                      std::function<double(double)>, 
                      std::function<double(double)>>())
        .def("update", &Kalman1D::update);
}
