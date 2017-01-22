#include <iostream>

class TestClass{
public:
  TestClass(int Dimensionality); // prototype of constructor
  ~TestClass(void); // prototype of destructor
  int Dimensionality;
};

TestClass::TestClass(int DIM)
{
  Dimensionality = DIM;
  std::cout << Dimensionality << "\n";
};

TestClass::~TestClass(void){
  std::cout << "Being Destroyed" << "\n";
};


