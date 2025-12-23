# 1D Kalman Filter

## Project Structure

```
Kalman 1D/
├── src/
|   ├── Kalman1D.h          # C++ Kalman filter class header
│   └── README.md           # Explaining theory
├── implementation/
│   ├── kalman_wrapper.cpp  # Pybind11 wrapper for Python binding
│   ├── imp.py              # Python test script with visualization
│   ├── kalman_module.so    # Compiled C++ module
│   └── kalman_filter_results.png  # Output visualization
└── README.md               # This file
```


## C++ Implementation Features

### Kalman 1D theory + equations
[README](./src/README.md)

### Flexible Function Callbacks

The implementation accepts custom prediction functions as `std::function` parameters, allowing:

- **Custom motion models** (constant velocity, acceleration, etc.)
- **Custom uncertainty propagation** (different noise models)
- **Python lambda integration** via Pybind11

### Constructor Signature

```cpp
Kalman1D(
    double measurement_uncertainty,   // Sensor noise (R)
    double process_uncertainty,       // Model noise (Q)
    double initial_estimate,          // Initial position guess
    std::function<double(double)> predict,              // Position prediction function
    std::function<double(double)> predict_uncertainty   // Uncertainty prediction function
)
```

## Python Usage Example

```python
import kalman_module

# Create filter with constant velocity motion model
cpp_filter = kalman_module.Kalman1D(
    0.64,                          # measurement_uncertainty (sensor noise)
    0.005,                         # process_uncertainty (model noise)
    0.0,                           # initial_estimate
    lambda pos: pos + (v*dt),      # predict: position += velocity*dt
    lambda unc: unc                # predict_uncertainty: keep uncertainty
)

# Process measurements
estimates = [cpp_filter.update(measurement) for measurement in measurements]
```

## Test Scenario (imp.py)

The implementation is tested with:

- **True motion**: Constant velocity (1.5 m/s)
- **Time step**: 0.1 seconds
- **Measurement noise**: Gaussian, σ = 0.8 meters
- **100 time steps** total

### Results

![Kalman Filter Results](implementation/kalman_filter_results.png)

The plot shows:
- **Red dots**: Noisy sensor measurements
- **Green dashed line**: Ground truth position
- **Blue solid line**: Kalman filter estimates

The Kalman filter successfully:
✓ Smooths out measurement noise  
✓ Tracks the true position accurately  
✓ Converges quickly from initial uncertainty

## Building from Source

### Requirements

- C++11 or later
- Python 3.x
- Pybind11
- NumPy
- Matplotlib

### Compile C++ Module

```bash
cd "Kalman 1D/implementation"
g++ -O3 -Wall -shared -std=c++11 -fPIC \
    $(python3 -m pybind11 --includes) \
    kalman_wrapper.cpp \
    -o kalman_module$(python3-config --extension-suffix)
```

### Run Test

```bash
python3 imp.py
```

## Key Concepts

### Function Parameters in C++

The implementation demonstrates accepting functions as parameters using `std::function`:

```cpp
std::function<double(double)> predict
```

This allows:
- **Flexibility**: Any callable with matching signature
- **Lambda support**: Works with C++ lambdas and Python lambdas (via Pybind11)
- **Function pointers**: Compatible with traditional C-style callbacks

## Advantages of This Design

1. **Reusable**: Works with any 1D motion model
2. **Testable**: Easy to verify with synthetic data
3. **Fast**: C++ performance with Python convenience
4. **Extensible**: Add new prediction models without modifying core code

**Last Updated**: December 24, 2025
