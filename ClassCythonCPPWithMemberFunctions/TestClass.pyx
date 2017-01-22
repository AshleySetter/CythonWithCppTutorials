import cython
import numpy as np
cimport numpy as np

cdef extern from "TestClassC.cpp": # defines the source C++ file
    cdef cppclass TestClass: # says that there is a class defined in the above C++ file called TestClass
        TestClass(int Dimensionality, double* InputArray) # the class has public member function TestClass which takes some arguments
        double SumListOfNumbers() # the class has a public member function which returns a double and has no arguments
        int Dimensionality # the class has a public variable that is an integer and is called Dimensionality
        double* ListOfNumbers # the class has another public variable that is a pointer to a double

cdef class CTestClass: # defines a python wrapper to the C++ class
    cdef TestClass* thisptr # thisptr is a pointer that will hold to the instance of the C++ class
    def __cinit__(self, int Dimensionality, np.ndarray[double, ndim=1, mode="c"] InputArray not None): # defines the python wrapper class' init function
        cdef double[::1] InputArrayC = InputArray # defines a memoryview containnig a 1D numpy array - this can be passed as a C-like array by providing a pointer to the 1st element and the length
        self.thisptr = new TestClass(Dimensionality, &InputArrayC[0]) # creates an instance of the C++ class and puts allocates the pointer to this
    def __dealloc__(self): # defines the python wrapper class' deallocation function (python destructor)
        del self.thisptr # destroys the reference to the C++ instance (which calls the C++ class destructor
    def CSumListOfNumbers(self):
        return self.thisptr.SumListOfNumbers()
