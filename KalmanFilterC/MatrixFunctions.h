#include <stdio.h>

#define N 3 // Number of Rows and Columns of the Kalman filter system


void printMatrix(double** matrix, int M){
  int i, j;
  
  for(i=0; i<M; i++){
    for(j=0; j<M; j++){
      printf("%.5e , ", matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

void printVector(double matrix[N]){
  int i, j;
  
  for(i=0; i<N; i++){
    printf("%.5e , ", matrix[i]);
  }
  printf("\n");
  printf("\n");
}

void MatrixTimesColVector(double Matrix[N][N], double Vector[N], double Result[N]){
  int i, j;

  for(j=0; j<N; j++){
    Result[j] = 0;
  }


  for (j=0; j<N; j++){
    for (i=0; i<N; i++){
      Result[j] += Matrix[j][i]*Vector[i];
    }
  }
}

void MatrixTimesMatrix(double Matrix1[N][N], double Matrix2[N][N], double Result[N][N]){
  int i, j, k;

  for(i=0; i<N; i++){
    for(j=0; j<N; j++){
      Result[i][j] = 0;
    };
  };

  for(i=0; i<N; i++){
    for(j=0; j<N; j++){
      for(k=0; k<N; k++){
	Result[i][j] += Matrix1[i][k]*Matrix2[k][j];
      };
    };
  };
}

void TransposeMatrix(double Matrix[N][N], double Result[N][N]){
  int i, j;
  
  for(i=0; i<N; i++){
    for(j=0; j<N; j++){
      Result[i][j] = Matrix[j][i];
    };
  };

}

void MatrixPlusMatrix(double Matrix1[N][N], double Matrix2[N][N], double Result[N][N]){
  int i, j;

  for(i=0; i<N; i++){
    for(j=0; j<N; j++){
      Result[i][j] = Matrix1[i][j] + Matrix2[i][j];
    };
  };
}

void MatrixMinusMatrix(double Matrix1[N][N], double Matrix2[N][N], double Result[N][N]){
  int i, j;

  for(i=0; i<N; i++){
    for(j=0; j<N; j++){
      Result[i][j] = Matrix1[i][j] - Matrix2[i][j];
    };
  };
}

/*void RowVectorTimesColumnVector(double RowVector[N], double ColVector[N], double Result[N]){
  int i;

  for(i=0; i<N; i++){
    Result[i] = RowVector[i]*ColVector[i];
  }
  }*/

void RowVectorTimesMatrix(double RowVector[N], double Matrix[N][N], double Result[N]){
  int i, k;

  for(i=0; i<N; i++){
    Result[i] = 0;
  };


  for(i=0; i<N; i++){
    for(k=0; k<N; k++){
      Result[i] += RowVector[k]*Matrix[k][i];
    };
  };
}

double RowVectorTimesColumnVector(double RowVector[N], double ColVector[N]){
  int i;
  double Result = 0;

  for(i=0; i<N; i++){
    Result += RowVector[i]*ColVector[i];
  }
  
  return Result;
}

void VectorDivideByNumber(double Vector[N], double Number, double Result[N]){
  int i;

  for(i=0; i<N; i++){
    Result[i] = Vector[i]/Number;
  }
}

void VectorTimesByNumber(double Vector[N], double Number, double Result[N]){
  int i;

  for(i=0; i<N; i++){
    Result[i] = Vector[i]*Number;
  }
}

void VectorPlusVector(double Vector1[N], double Vector2[N], double Result[N]){
  int i;

  for(i=0; i<N; i++){
    Result[i] = Vector1[i] + Vector2[i];
  }
}

double identityMatrix[N][N] = {
  {1, 0, 0},
  {0, 1, 0},
  {0, 0, 1}
};


void ColumnVectorTimesRowVector(double ColVector[N], double RowVector[N], double Result[N][N]){
  int i, j;

  for(i=0; i<N; i++){
    for(j=0; j<N; j++){
      Result[i][j] = ColVector[i]*RowVector[j];
    };
  };  

  
  
}
