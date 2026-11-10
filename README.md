# Portfolio
Scientific computing projects in Python and C++


## C++ Heat Equation
This assignment was completed as part of an introductory course in C++ and object oriented programming. 

The goal was to model how temperature changes over time in a square or cube using the heat equation. This project uses numerical methods to discretize the heat equation. The numerical methods include the central finite difference method, the Backward Euler method and the Conjugate Gradient method. 

The heat equation is: 

$$\frac{\partial u}{\partial t}=\alpha\nabla^2u,$$

where $u$ is the temperature, $\alpha$ is the thermal diffusivity and $\nabla^2$ is the Laplacian operator.

By discretizing time and space, the mesh temperatures $\omega$ at the next time step $l+1$ can be modeled at each point in the mesh using: 
$$M\omega_{l+1} = \omega_l$$

where $M$ is the matrix with coefficients of the discretized heat equation at each point in space. Each element in the matrix M is defined by:
$$M_{ij} = I_{ij} - \alpha \frac{\Delta t}{\Delta x^2} \sum_{k=0}^{n-1} D_{kij}.$$

Here, $I$ is the identity matrix,$\Delta t$ is the time step size,$\Delta x$ is the spatial step size, $\alpha$ the heat coefficient and $D_{kij}$ is the approximated second order derivative for spatial dimension $k$. 

This is implemented in C++ using class templates and consists of the following components:
- A vector class that stores the temperature values and supports addition, subtraction, scalar multiplication and the dot product.
- The matrix class stores the coefficients of the discretized heat equation using a sparse representation. It allows accessing and inserting matrix elements, as well as matrix vector multiplication.
- A function that implements the Conjugate Gradient method to solve the linear system at each time step.
- The Heat class takes the thermal diffusivity, number of mesh points, the time step size. It constructs the matrix and computes the numerical solution at a given time. 


## Python PCA Ising Model
This project was completed as part of the course AI for Physicists.

The goal was to use Principal Component Analysis (PCA) to analyze spin configurations of the Ising model. The data consisted of 2D lattices with 900 spins each, at different temperatures. The code standardizes the data, finds the eigenvalues and eigenvectors of the covariance matrix, and projects the data onto the eigenvectors with the largest corresponding eigenvalues (principal components). The plot shows that higher temperatures correspond to lower absolute magnetization, as the spins become more disordered.

## Python Supervised Learning
### Supervised Learning Asteroid Orbital Parameters

This project was completed as part of the course AI for Physicists. The assignment was to train 4 different models and compare their performances. 

The goal was to use supervised learning to predict the semi major axis of an asteroid's orbit from its orbital and physical parameters. The project uses neural networks implemented in Python with PyTorch.

The dataset was cleaned by removing missing values and outliers. The data was then divided into training and testing sets and standardized before training. The models were evaluated using mean squared error (MSE) and the coefficient of determination (R²).

### Model 1: Individual Input Parameters

The first model uses a neural network with one hidden layer containing 32 neurons and a ReLU activation function.

Eight different input parameters were tested individually to investigate which had the strongest predictive relationship with the semi major axis. These included inclination, eccentricity, perihelion distance, minimum orbit intersection distance with Earth, diameter, albedo, epoch, and time of perihelion passage.

The results were compared using the test loss and R² score. The minimum orbit intersection distance with Earth gave the best results for this model.

### Model 2 – Multiple Input Parameters

The second model uses the same neural network architecture but combines different input parameters rather than testing them individually.

Based on the results from Model 1, perihelion distance, minimum orbit intersection distance with Earth, and asteroid diameter were selected for further investigation. Different combinations of two and three parameters were tested to determine whether using multiple inputs improved the predictions.

The results showed that the three input combination performed slightly better than the best two input combination. However, the difference was small, so the combination of diameter and minimum orbit intersection distance was selected for further investigation.

### Model 3 – Network Architecture

The third model investigates whether increasing the number of hidden layers improves the predictions.

Using the two selected input parameters from Model 2, a neural network with two hidden layers was compared with the previous network containing one hidden layer.

### Model 4 – Convolutional Neural Network

A one dimensional convolutional neural network (CNN) was also tested to compare its performance with the fully connected neural networks.

The CNN performed worse than the other models, suggesting that this architecture was less suitable for the selected input data.

### Discussion

The project investigated how input parameter selection and neural network architecture affect the prediction of asteroid orbital parameters.

The models showed small improvements as different input combinations and architectures were tested. An interesting observation was that eccentricity and perihelion distance did not individually perform as well as expected, despite their relationship with the semi-major axis through the equation:

\[
q = a(1-e)
\]

where \(q\) is the perihelion distance, \(a\) is the semi-major axis, and \(e\) is the eccentricity.

