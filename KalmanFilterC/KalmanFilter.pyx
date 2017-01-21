#from libc.stdlib cimport malloc, free
import cython
import numpy as np
cimport numpy as np

cdef extern from "KalmanFilterC.cpp":
    double SumArray(double* Array, int length)
    cdef cppclass KalmanFilter:
        KalmanFilter(int Dimensionality, double* AMatrixFlattened)
        int Dimensionality
        double** A

cdef class CKalmanFilter:
    cdef KalmanFilter* thisptr # hold a C++ instance
    def __cinit__(self, int Dimensionality, np.ndarray[double, ndim=2, mode="c"] AMatrix not None):
        cdef double[::1] AMatrixCFlattened = AMatrix.flatten()
        self.thisptr = new KalmanFilter(Dimensionality, &AMatrixCFlattened[0])
    def __dealloc__(self):
        del self.thisptr
        

@cython.boundscheck(False)
@cython.wraparound(False)
def C_SumArray(np.ndarray[double, mode="c"] InputArray not None, int length):
    return SumArray(&InputArray[0], length)

