#include <iostream>

double SumArray(double* Array, int length){
  double Sum = 0.0;

  for(int i=0; i<length; i++){
    Sum+= Array[i];
  }
  return Sum;
}
