from cythonSumPackage.SumArrayCython import C_SumArray
import numpy as np

def do_a_thing(n):
    test_array = np.array(list(range(n)))
    sumval = C_SumArray(test_array)
    return sumval
