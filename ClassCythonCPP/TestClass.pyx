import cython

cdef extern from "TestClassC.cpp": # defines the source C++ file
    cdef cppclass TestClass: # says that there is a class defined in the above C++ file called TestClass
        TestClass(int Dimensionality) # the class has public member function TestClass which takes some arguments
        int Dimensionality # the class has a public variable that is an integer and is called Dimensionality

cdef class CTestClass: # defines a python wrapper to the C++ class
    cdef TestClass* thisptr # thisptr is a pointer that will hold to the instance of the C++ class
    def __cinit__(self, int Dimensionality): # defines the python wrapper class' init function
        self.thisptr = new TestClass(Dimensionality) # creates an instance of the C++ class and puts allocates the pointer to thisB
    def __dealloc__(self): # defines the python wrapper class' deallocation function (python destructor)
        del self.thisptr # destroys the reference to the C++ instance (which calls the C++ class destructor
        
