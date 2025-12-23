#pragma once

#include <functional>

class Kalman1D
{
public:
    Kalman1D(
        double measurement_uncertainty,
        double process_uncertainty,
        double initial_estimate,
        std::function<double(double)> predict,
        std::function<double(double)> predict_uncertainty)
        : measurement_uncertainty(measurement_uncertainty),
          process_uncertainty(process_uncertainty),
          predict(predict),
          kalman_gain(0.0),
          prior_estimate(initial_estimate)
    {
    }

    double update(double measurement)
    {
        // Prediction step
        prior_estimate = predict(prior_estimate);
        prior_uncertainty = predict_uncertainty(prior_uncertainty) + process_uncertainty;

        // Update step
        calculate_kalman_gain(prior_uncertainty);
        double current_estimate = calculate_current_estimate(prior_estimate, measurement);
        prior_uncertainty = calculate_current_uncertainty(prior_uncertainty);
        prior_estimate = current_estimate;

        return current_estimate;
    }

private:
    double kalman_gain;
    double measurement_uncertainty;
    double process_uncertainty;
    double prior_estimate;
    std::function<double(double)> predict;
    std::function<double(double)> predict_uncertainty;
    double prior_uncertainty = 1.0;

    void calculate_kalman_gain(double prior_uncertainty)
    {
        kalman_gain = prior_uncertainty / (prior_uncertainty + measurement_uncertainty);
    }

    double calculate_current_estimate(double prior_estimate, double measurement)
    {
        return prior_estimate + kalman_gain * (measurement - prior_estimate);
    }

    double calculate_current_uncertainty(double prior_uncertainty)
    {
        return (1 - kalman_gain) * prior_uncertainty;
    }
};