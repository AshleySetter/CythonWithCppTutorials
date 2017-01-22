#include <iostream>

class TestClass{
public:
  TestClass(int Dimensionality, double* InputArray); // prototype of constructor
  ~TestClass(void); // prototype of destructor
  double SumListOfNumbers(void);
  int Dimensionality;
  double* ListOfNumbers;
};

TestClass::TestClass(int DIM, double* InputArray)
{
  Dimensionality = DIM;
  std::cout << Dimensionality << "\n";
  ListOfNumbers = new double[Dimensionality];
  for (int i = 0; i < Dimensionality; ++i) {
    ListOfNumbers[i] = InputArray[i];
    std::cout << ListOfNumbers[i] << ", ";
  }
  std::cout << "\n";
};

TestClass::~TestClass(void){
  std::cout << "Being Destroyed" << "\n";
};

double TestClass::SumListOfNumbers(void){
  double Sum = 0;
  for (int i = 0; i < Dimensionality; ++i) {
    Sum += ListOfNumbers[i];
  }
  return Sum;
}
