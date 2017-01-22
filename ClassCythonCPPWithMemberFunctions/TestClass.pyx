import cython
import numpy as np
cimport numpy as np

cdef extern from "TestClassC.cpp":
    cdef cppclass TestClass:
        TestClass(int Dimensionality, double* InputArray)
        double SumListOfNumbers()
        int Dimensionality
        double* ListOfNumbers

cdef class CTestClass:
    cdef TestClass* thisptr # hold a C++ instance
    def __cinit__(self, int Dimensionality, np.ndarray[double, ndim=1, mode="c"] InputArray not None):
        cdef double[::1] InputArrayC = InputArray
        self.thisptr = new TestClass(Dimensionality, &InputArrayC[0])
    def __dealloc__(self):
        del self.thisptr
    def CSumListOfNumbers(self):
        return self.thisptr.SumListOfNumbers()
