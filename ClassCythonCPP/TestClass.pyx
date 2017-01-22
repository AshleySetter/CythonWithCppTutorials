import cython

cdef extern from "TestClassC.cpp":
    cdef cppclass TestClass:
        TestClass(int Dimensionality)
        int Dimensionality

cdef class CTestClass:
    cdef TestClass* thisptr # hold a C++ instance
    def __cinit__(self, int Dimensionality):
        self.thisptr = new TestClass(Dimensionality)
    def __dealloc__(self):
        del self.thisptr
        
