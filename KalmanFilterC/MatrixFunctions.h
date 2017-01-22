#include <stdio.h>

void printMatrix(std::vector< std::vector<double> > matrix){
  int i, j;
  int N = matrix.size();
  for(i=0; i<N; i++){
    for(j=0; j<N; j++){
      printf("%.5e , ", matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

void printVector(std::vector<double> vector){
  int i;
  int N = vector.size();
  for(i=0; i<N; i++){
    printf("%.5e , ", vector[i]);
  }
  printf("\n");
  printf("\n");
}

void MatrixTimesColVector(std::vector< std::vector<double> >& Matrix, std::vector<double>& Vector, std::vector<double>* Result){
  int i, j;
  int N = (*Result).size();
  for(j=0; j<N; j++){
    (*Result)[j] = 0;
  }


  for (j=0; j<N; j++){
    for (i=0; i<N; i++){
      (*Result)[j] += Matrix[j][i]*Vector[i];
    }
  }
}

void MatrixTimesMatrix(std::vector< std::vector<double> >& Matrix1, std::vector< std::vector<double> >& Matrix2, std::vector< std::vector<double> >* Result){
  int i, j, k;
  int N = (*Result).size();
  for(i=0; i<N; i++){
    for(j=0; j<N; j++){
      (*Result)[i][j] = 0;
    };
  };

  for(i=0; i<N; i++){
    for(j=0; j<N; j++){
      for(k=0; k<N; k++){
	(*Result)[i][j] += Matrix1[i][k]*Matrix2[k][j];
      };
    };
  };
}

void TransposeMatrix(std::vector< std::vector<double> >& Matrix, std::vector< std::vector<double> >* Result){
  int i, j;
  int N = (*Result).size();
  for(i=0; i<N; i++){
    for(j=0; j<N; j++){
      (*Result)[i][j] = Matrix[j][i];
    };
  };

}

void MatrixPlusMatrix(std::vector< std::vector<double> >& Matrix1, std::vector< std::vector<double> >& Matrix2, std::vector< std::vector<double> >* Result){
  int i, j;
  int N = (*Result).size();
  for(i=0; i<N; i++){
    for(j=0; j<N; j++){
      (*Result)[i][j] = Matrix1[i][j] + Matrix2[i][j];
    };
  };
}

void MatrixMinusMatrix(std::vector< std::vector<double> >& Matrix1, std::vector< std::vector<double> >& Matrix2, std::vector< std::vector<double> >* Result){
  int i, j;
  int N = (*Result).size();
  for(i=0; i<N; i++){
    for(j=0; j<N; j++){
      (*Result)[i][j] = Matrix1[i][j] - Matrix2[i][j];
    };
  };
}

/*void RowVectorTimesColumnVector(double RowVector[N], double ColVector[N], double Result[N]){
  int i;

  for(i=0; i<N; i++){
  (*Result)[i] = RowVector[i]*ColVector[i];
  }
  }*/

void RowVectorTimesMatrix(std::vector<double>& RowVector, std::vector< std::vector<double> >& Matrix, std::vector<double>* Result){
  int i, k;
  int N = (*Result).size();
  for(i=0; i<N; i++){
    (*Result)[i] = 0;
  };


  for(i=0; i<N; i++){
    for(k=0; k<N; k++){
      (*Result)[i] += RowVector[k]*Matrix[k][i];
    };
  };
}

double RowVectorTimesColumnVector(std::vector<double>& RowVector, std::vector<double>& ColVector){
  int i;
  double Result = 0;
  int N = RowVector.size();
  for(i=0; i<N; i++){
    Result += RowVector[i]*ColVector[i];
  }
  
  return Result;
}

void VectorDivideByNumber(std::vector<double>& Vector, double Number, std::vector<double>* Result){
  int i;
  int N = (*Result).size();
  for(i=0; i<N; i++){
    (*Result)[i] = Vector[i]/Number;
  }
}

void VectorTimesByNumber(std::vector<double>& Vector, double Number, std::vector<double>* Result){
  int i;
  int N = (*Result).size();
  for(i=0; i<N; i++){
    (*Result)[i] = Vector[i]*Number;
  }
}

void VectorPlusVector(std::vector<double>& Vector1, std::vector<double>& Vector2, std::vector<double>* Result){
  int i;
  int N = (*Result).size();
  for(i=0; i<N; i++){
    (*Result)[i] = Vector1[i] + Vector2[i];
  }
}

void ColumnVectorTimesRowVector(std::vector<double>& ColVector, std::vector<double>& RowVector, std::vector< std::vector<double> >* Result){
  int i, j;
  int N = (*Result).size();
  for(i=0; i<N; i++){
    for(j=0; j<N; j++){
      (*Result)[i][j] = ColVector[i]*RowVector[j];
    };
  };    
}
