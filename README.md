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


