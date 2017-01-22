#from libc.stdlib cimport malloc, free
import cython
import numpy as np
cimport numpy as np

cdef extern from "KalmanFilterC.cpp":
    double SumArray(double* Array, int length)
    cdef cppclass KalmanFilter:
        KalmanFilter(int Dimensionality, double* AMatrixFlattened, double* PMatrixFlattened, double* QMatrixFlattened, double* HVector, double* X_InitVector, double RValue)
        void FilterData(double* Data, int Length, double* FilteredData)

cdef class CKalmanFilter:
    cdef KalmanFilter* thisptr # hold a C++ instance
    def __cinit__(self, int Dimensionality, np.ndarray[double, ndim=2, mode="c"] AMatrix not None, np.ndarray[double, ndim=2, mode="c"] PMatrix not None, np.ndarray[double, ndim=2, mode="c"] QMatrix not None, np.ndarray[double, ndim=1, mode="c"] HVector not None, np.ndarray[double, ndim=1, mode="c"] X_InitVector not None, double RValue):
        cdef double[::1] AMatrixCFlattened = AMatrix.flatten()
        cdef double[::1] PMatrixCFlattened = PMatrix.flatten()
        cdef double[::1] QMatrixCFlattened = QMatrix.flatten()
        cdef double[::1] HVectorC = HVector
        cdef double[::1] X_InitVectorC = X_InitVector 
        self.thisptr = new KalmanFilter(Dimensionality, &AMatrixCFlattened[0], &PMatrixCFlattened[0], &QMatrixCFlattened[0], &HVectorC[0], &X_InitVectorC[0], RValue)
    def __dealloc__(self):
        del self.thisptr
    def FilterData(self, np.ndarray[double, ndim=1, mode="c"] Data not None, int Length):
        cdef double[::1] DataC = Data
        cdef double[::1] FilteredDataResult = np.zeros(Length)
        self.thisptr.FilterData(&DataC[0], Length, &FilteredDataResult[0])
        return np.asarray(FilteredDataResult)
        


