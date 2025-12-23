# Kalman 1D

- Better to take the inspiration from temporal difference equation or what we call as exponential average equation.

    $avg_{n+1}=\alpha * avg_n + (1-\alpha)*measurement$

- Instead of alpha we are using $K_k$, kalman gain. Which is different for each measurement based on the confidence we have about the measurement.

- The confidence we have about a measurement is taken using the variance.

- Measurement, estimate, uncertainity of measurement, uncertainty of estimate, system errors?

- Five equations

    1. Kalman gain:

        $K_n = \frac{p_{n, n-1}}{p_{n, n-1} + r_n}$
    
    2. State update

        $\hat x_{n, n} = \hat x_{n, n-1} + K_n (z_n - \hat x_{n,n-1})$
    
    3. Covariance update or 
    
        $p_{n,n} = (1-K_n)p_{n,n-1}$

    4. State Extrapolation

    5. Covariance Extrapolation


Most of the time we don't know the true value. We have a prior estimateand $(\hat x_{n, n-1}, p_{n, n-1})$ a measurement $(z_n, r_n)$. Based on that we derrive a better current estimate $(\hat x_{n, n}, p_{n,n})$.
Where $\hat x$ represent the state and $p$ represent variance, similarly $z$ represent the measurement regarading the state and $r$ is the vaariance.

We combining the distributions of prior estimate and measurement in a way to that maximizes the precision of the current estimate. So we are sort of trying to find the constant or weight that minimizes the current estimate variance. That is how we derive the kalman gain.


State Extrapolation and Covariance Extrapolation depends on the model of the system.


[Good place to start..](https://kalmanfilter.net/kalman1d.html)