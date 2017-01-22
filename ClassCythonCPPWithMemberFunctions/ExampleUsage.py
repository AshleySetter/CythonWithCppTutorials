import TestClass
import numpy as np

ListOfNums = np.array([0, 0.4, 0.7, 0.2, 8.0, 3.14159])
L = len(ListOfNums)

Tc = TestClass.CTestClass(L, ListOfNums)

SumTotal = Tc.CSumListOfNumbers()

print(SumTotal)

del(Tc)

