import cython

import numpy as np
cimport numpy as np

@cython.boundscheck(False)
@cython.wraparound(False)
def C_SumArray(np.ndarray[double, mode="c"] InputArray not None):
    return np.sum(InputArray)
