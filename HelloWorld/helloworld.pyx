cdef extern from "helloworldC.cpp":
    void Helloworld() # cpdef instructs cython to automatically wrap the C function with a python function

def C_Helloworld():
    Helloworld()

#c_helloworld()
