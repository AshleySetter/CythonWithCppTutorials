import cython

import numpy as np
cimport numpy as np

cdef extern from "SumArrayCOpenMP.cpp":
    double SumArray(double* Array, int length)

@cython.boundscheck(False)
@cython.wraparound(False)
def C_SumArray(np.ndarray[double, mode="c"] InputArray not None, int length):
    return SumArray(&InputArray[0], length)
