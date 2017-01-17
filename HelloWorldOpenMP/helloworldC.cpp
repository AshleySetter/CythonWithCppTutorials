#include <iostream>
#include <omp.h>

void Helloworld(){
#pragma omp parallel
  {
    int Thread_Num = omp_get_thread_num();
#pragma omp critical
    std::cout << "Hello world! from Thread " << Thread_Num << "\n";
  }
}
