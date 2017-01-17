# CythonWithCppTutorials
A few quick tutorials on using C++ function in Python code with Cython

The directories contain minimal examples of calling C++ functions in Python.

Helloworld for example contains the C++ code for helloworld (contained in helloworldC.cpp) the cython code creating a python wrapper for the C++ function (helloworld.pyx) and the setup script which sets up the module and compiler flags so that the C++ code is compiled and linked properly and compiled into a cython library. I have included a makefile which will run setup.py to build the cython module and a minimal python script which imports and runs the helloworld function in python.


In SumNumpyArray I have implemented a function to sum an array of double precision floats in C++ (one version using pure serial C++, one version using OpenMP parallelisation). I have then compared them with each other and the python builtin and numpy sum functions, the timings found on my computer are found below. If you want to try this on your machine just clone this repo and run make inside of SumNumpyArray/SumArray and SumNumpyArray/SumArrayParallel and then run TimeComparison.py. This generates an array of 10<sup>8</sup> random numbers and runs each version of the sum function of this array. It prints out the time taken for each function to sum the array (recorded by a function wrapper) and the value calculated by each function.

|   Implementation      | elapsed time (s) |
|-----------------------|------------------|
| Python sum()          | 7.326408         |
| numpy np.sum()        | 0.038284         |
| C++ sum               | 0.108173         |
| C++ sum with OpenMP   | 0.042143         |