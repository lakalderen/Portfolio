# Portfolio
Scientific computing projects in Python and C++


##C++ Heat Equation
The goal is to model the temperature across a square or cube over time using the heat equation. This is done by applying finite difference discretization to create a mesh of the square/cube and discretizing time into steps. The temperature at each time is approximated by the central finite difference method and the temperature change is approximated susing the backward Euler method. 

This is implemented in C++ by using a class template. A vector is constructed and initialed with a  given length
