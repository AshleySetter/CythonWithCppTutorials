cdef extern from "helloworldC.cpp":
    void Helloworld()

def C_Helloworld():
    Helloworld()

#c_helloworld()
