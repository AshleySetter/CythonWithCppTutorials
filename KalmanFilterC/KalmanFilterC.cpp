#include <iostream>
#include <vector>

#include "MatrixFunctions.h"

class KalmanFilter{
public:
  KalmanFilter(int Dimensionality, double* AMatrixFlattened, double* PMatrixFlattened, double* QMatrixFlattened, double* HVector, double* X_InitVector, double RValue); // prototype of constructor
  ~KalmanFilter(void); // prototype of destructor
  void FilterData(double* Data, int Length, double* FilteredData);
  std::vector< std::vector<double> > A; // initialise empty 2D (0x0) vector
  std::vector< std::vector<double> > P; // initialise empty 2D (0x0) vector
  std::vector< std::vector<double> > Q; // initialise empty 2D (0x0) vector
  std::vector<double> H; // initialise empty 1D (0 length) vector
  std::vector<double> X_Init; // initialise empty 1D (0 length) vector
  double R;
private:
  int Dimensionality;
};

KalmanFilter::KalmanFilter(int DIM, double* AMatrixFlattened, double* PMatrixFlattened, double* QMatrixFlattened, double* HVector, double* X_InitVector, double RValue)
{
  Dimensionality = DIM;

  A.resize(Dimensionality, std::vector<double>(Dimensionality)); // resize 2D vector to be (Dim x Dim)
  for (int i = 0; i < Dimensionality; ++i) {
    for (int j = 0; j < Dimensionality; ++j) {
      A[i][j] = AMatrixFlattened[3*i+j];
    }
  }
  P.resize(Dimensionality, std::vector<double>(Dimensionality)); // resize 2D vector to be (Dim x Dim)
  for (int i = 0; i < Dimensionality; ++i) {
    for (int j = 0; j < Dimensionality; ++j) {
      P[i][j] = PMatrixFlattened[3*i+j];
    }
  }
  Q.resize(Dimensionality, std::vector<double>(Dimensionality)); // resize 2D vector to be (Dim x Dim)
  for (int i = 0; i < Dimensionality; ++i) {
    for (int j = 0; j < Dimensionality; ++j) {
      Q[i][j] = QMatrixFlattened[3*i+j];
    }
  }
  H.resize(Dimensionality);
  for (int i = 0; i < Dimensionality; ++i) {
    H[i] = HVector[i];
  }
  X_Init.resize(Dimensionality);
  for (int i = 0; i < Dimensionality; ++i) {
    X_Init[i] = X_InitVector[i];
  }

  R = RValue;
};

KalmanFilter::~KalmanFilter(void){
  std::cout << "Being Destroyed!" << "\n";
};

void KalmanFilter::FilterData(double* Data, int Length, double* FilteredData){
  std::vector<double> CurrentStateVector;
  CurrentStateVector.resize(Dimensionality);
  std::vector<double> PredictedStateVector;
  PredictedStateVector.resize(Dimensionality);
  std::vector< std::vector<double> > CurrentProcessCovarianceMatrix;
  CurrentProcessCovarianceMatrix.resize(Dimensionality, std::vector<double>(Dimensionality));
  std::vector< std::vector<double> > PredictedProcessCovarianceMatrix_temp1;
  PredictedProcessCovarianceMatrix_temp1.resize(Dimensionality, std::vector<double>(Dimensionality));
  std::vector< std::vector<double> > PredictedProcessCovarianceMatrix;
  PredictedProcessCovarianceMatrix.resize(Dimensionality, std::vector<double>(Dimensionality));
  std::vector< std::vector<double> > ATimesP;
  ATimesP.resize(Dimensionality, std::vector<double>(Dimensionality));
  std::vector< std::vector<double> > A_Transpose;
  A_Transpose.resize(Dimensionality, std::vector<double>(Dimensionality));
  double MeasurementPredicionResidual, HtimesXpk, KalmanGain_Denominator;
  std::vector<double> KalmanGain_Denominator_temp1;
  KalmanGain_Denominator_temp1.resize(Dimensionality);
  std::vector<double> H_T;
  H_T.resize(Dimensionality);
  std::vector<double> KalmanGain_Numerator;
  KalmanGain_Numerator.resize(Dimensionality);
  std::vector<double> KalmanGain;
  KalmanGain.resize(Dimensionality);
  std::vector<double> CurrentStateVector_temp1;
  CurrentStateVector_temp1.resize(Dimensionality);
  std::vector< std::vector<double> > KalmanGainTimesH;
  KalmanGainTimesH.resize(Dimensionality, std::vector<double>(Dimensionality));
  std::vector< std::vector<double> > CurrentProcessCovarianceMatrix_temp1;
  CurrentProcessCovarianceMatrix_temp1.resize(Dimensionality, std::vector<double>(Dimensionality));
  std::vector< std::vector<double> > identityMatrix;
  identityMatrix.resize(Dimensionality, std::vector<double>(Dimensionality, 0.0)); // init to all zeros

  for (int i=0; i<Dimensionality; i++){
    identityMatrix[i][i] = 1.0;
  }
  
  CurrentStateVector = X_Init;
  CurrentProcessCovarianceMatrix = P;

  TransposeMatrix(A, &A_Transpose); // calculate transpose of A matrix
  H_T = H;
  
  for (int i=0; i<Length; i++){
    //--------- PREDICTION STEP --------------
    // calculating PredictedStateVector
    MatrixTimesColVector(A, CurrentStateVector, &PredictedStateVector);
    // calculating PredictedProcessCovarianceMatrix
    MatrixTimesMatrix(A, CurrentProcessCovarianceMatrix, &ATimesP);
    MatrixTimesMatrix(ATimesP, A_Transpose, &PredictedProcessCovarianceMatrix_temp1);
    MatrixPlusMatrix(PredictedProcessCovarianceMatrix_temp1, Q, &PredictedProcessCovarianceMatrix);

    //--------- MEASUREMENT STEP -------------
    // calculating MeasurementPredicionResidual
    HtimesXpk = RowVectorTimesColumnVector(H, PredictedStateVector);
    MeasurementPredicionResidual = Data[i] - HtimesXpk;
    // calculating KalmanGain_Denominator
    RowVectorTimesMatrix(H, PredictedProcessCovarianceMatrix, &KalmanGain_Denominator_temp1);
    KalmanGain_Denominator = RowVectorTimesColumnVector(KalmanGain_Denominator_temp1, H) + R;
    // Calculating KalmanGain
    MatrixTimesColVector(PredictedProcessCovarianceMatrix, H_T, &KalmanGain_Numerator);
    VectorDivideByNumber(KalmanGain_Numerator, KalmanGain_Denominator, &KalmanGain);

    //--------- UPDATE STEP ------------------
    // Calculating CurrentStateVector
    VectorTimesByNumber(KalmanGain, MeasurementPredicionResidual, &CurrentStateVector_temp1);
    VectorPlusVector(PredictedStateVector, CurrentStateVector_temp1, &CurrentStateVector);
    FilteredData[i] = RowVectorTimesColumnVector(H, CurrentStateVector);
    // Calculating CurrentProcessCovarianceMatrix
    ColumnVectorTimesRowVector(KalmanGain, H, &KalmanGainTimesH);
    MatrixMinusMatrix(identityMatrix, KalmanGainTimesH, &CurrentProcessCovarianceMatrix_temp1);
    MatrixTimesMatrix(CurrentProcessCovarianceMatrix_temp1, PredictedProcessCovarianceMatrix, &CurrentProcessCovarianceMatrix);
    
  }
};
