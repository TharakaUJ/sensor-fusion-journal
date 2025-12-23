import numpy as np
import matplotlib.pyplot as plt
import kalman_module  # This is your compiled C++ code!

# 1. Generate Noisy Data
dt, velocity, steps = 0.1, 1.5, 100
t = np.linspace(0, steps*dt, steps)
true_pos = velocity * t
measurements = true_pos + np.random.normal(0, 0.8, steps)

# 2. Configure the C++ Kalman Filter
# We pass Python lambdas directly into the C++ std::function arguments
cpp_filter = kalman_module.Kalman1D(
    0.64,                         # measurement_uncertainty
    0.005,                        # process_uncertainty
    0.0,                          # initial_estimate
    lambda pos: pos + (velocity*dt), # predict lambda
    lambda unc: unc               # predict_uncertainty lambda
)

# 3. Run Filter
estimates = [cpp_filter.update(z) for z in measurements]

# 4. Plot Results
plt.figure(figsize=(10, 5))
plt.scatter(t, measurements, color='red', alpha=0.3, label='Noisy Measurements')
plt.plot(t, true_pos, 'g--', label='Ground Truth')
plt.plot(t, estimates, 'b-', linewidth=2, label='C++ Kalman Estimate')
plt.legend()
plt.title("Testing C++ Kalman Filter in Python (2025)")
plt.xlabel("Time (s)")
plt.ylabel("Position")
plt.grid(True, alpha=0.3)
plt.savefig('kalman_filter_results.png', dpi=300, bbox_inches='tight')
print("Graph saved as 'kalman_filter_results.png'")
plt.show()
