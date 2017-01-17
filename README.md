# CythonWithCppTutorials
A few quick tutorials on using C++ function in Python code with Cython

The directories contain minimal examples of calling C++ functions in Python.

Helloworld for example contains the C++ code for helloworld (contained in helloworldC.cpp) the cython code creating a python wrapper for the C++ function (helloworld.pyx) and the setup script which sets up the module and compiler flags so that the C++ code is compiled and linked properly and compiled into a cython library. I have included a makefile which will run setup.py to build the cython module and a minimal python script which imports and runs the helloworld function in python.
