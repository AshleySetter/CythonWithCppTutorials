#include <iostream>

#include "MatrixFunctions.h"

class KalmanFilter{
public:
  KalmanFilter(int Dimensionality, double* AMatrix); // prototype of constructor
  ~KalmanFilter(void); // prototype of destructor
  int Dimensionality;
  double **A;
};

KalmanFilter::KalmanFilter(int DIM, double* AMatrixFlattened)
{
  Dimensionality = DIM;
  std::cout << Dimensionality << "\n";
  A = new double*[Dimensionality]; // dynamic array (size Dimensionality) of pointers to double
  for (int i = 0; i < Dimensionality; ++i) {
    A[i] = new double[Dimensionality];
    // each i-th pointer is now pointing to dynamic array (size Dimensionality) of actual double values
  }
  for (int i = 0; i < Dimensionality; ++i) {
    for (int j = 0; j < Dimensionality; ++j) {
      A[i][j] = AMatrixFlattened[3*i+j];
      //std::cout << i << " " << j << " " << AMatrixFlattened[3*i+j] << "\n";
    }
  }
  printMatrix(A, Dimensionality);
};

KalmanFilter::~KalmanFilter(void){
  std::cout << "Being Destroyed" << "\n";
  for (int i = 0; i < Dimensionality; ++i) {
    delete [] A[i];
  }
  delete [] A;
};

double SumArray(double* Array, int length){
  double Sum = 0.0;

  for(int i=0; i<length; i++){
    Sum+= Array[i];
  }
  return Sum;
}

