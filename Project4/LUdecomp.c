//David Ciupei
//cs330 Project #4

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "LUdecomp.h"

double **createMatrix(int N) {
  double **M = (double **) malloc(N*sizeof(double*));
  for (int i = 0; i < N; i++)
    M[i] = (double*) malloc(N*sizeof(double));
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      M[i][j] = (i == j) ? 1.0 : 0.0;
  return M;
}

void LUdestroy(LUdecomp* LU) {
  for (int i = 0; i < LU->N; i++)
    free(LU->LU[i]);
  free(LU);  
}

void LUsolve(LUdecomp *decomp, const double *b, double *x){
  
  double y[decomp->N]; //initialize the y vector 
  //foward substitution
  y[0] = b[decomp->mutate[0]];
  for (int i = 1; i < decomp->N; i++){
    double sum = 0.0;
    for (int j = 0; j < i; j++){
      sum += decomp->LU[i][j]*y[j];
    }
    y[i] = b[decomp->mutate[i]] - sum;
  }
  //back substitution
  x[decomp->N-1] = y[decomp->N-1]/(decomp->LU[decomp->N-1][decomp->N-1]);

  for (int i = decomp->N-2; i>=0; i--){
    double sum = 0.0;
    for (int j = i + 1;  j < decomp->N; j++){
      sum += decomp->LU[i][j]*x[j];
    }
    x[i] = (1/decomp->LU[i][i])*(y[i] - sum);
  }
  
}

LUdecomp *LUdecompose(int N, const double **A){
  LUdecomp *LU = (LUdecomp*) malloc(sizeof(LUdecomp));
  LU->N = N;
  LU->LU = createMatrix(N);
  LU->mutate = (short *) malloc(N*sizeof(short));
  LU->d = +1;                      //initialize row swap parity value

  // Clone A into LU
  double **A_ = LU->LU;
  for (int i = 0; i < N; i++)
    for(int j = 0; j<N; j++)
      A_[i][j] = A[i][j];
  for (int i = 0; i < N; i++)
    LU->mutate[i] = (short) i;


  //start of psuedo code partial pivoting
  double p = 0.0;                
  int n = 0;                     
  for (int j = 0; j < N; j++){   
    for (int i = 0; i <= j; i++){
      double result = 0.0;       
      // solves for the result of the summation
      for (int k = 0; k<i; k++){
	result += (A_[i][k] * A_[k][j]);
      }
      A_[i][j] = (A_[i][j] - result);
      p = fabs(A_[j][j]);            // initial pivot value
      n = j;                         // initial pivot row
    }
    for (int i = j + 1; i < N; i++){
      double result = 0.0;
      // solves for the result of the summation
      for( int k = 0; k<j; k++){
      result += (A_[i][k] * A_[k][j]);
      }
      A_[i][j] = (A_[i][j] - result);
      if (fabs(A_[i][j]) > p){       // if better pivot found
        p = fabs(A_[i][j]);          // new pivot 
	n = i;
      }


    }
    if (p == 0.0){             // checks for singular matrix 
	   return NULL;
	}
    if (n != j){               // if best pivot off diagnol
      // swap n and j of A
	short swap = 0;
	double* temp = A_[n];
        A_[n] = A_[j];
        A_[j] = temp;
       
	swap = LU->mutate[n];
	LU->mutate[n] = LU->mutate[j];
	LU->mutate[j] = swap;
	LU->d = -1;
      }
      for (int i = j+1; i < N; i++){
	A_[i][j] = (A_[i][j]/A_[j][j]);    // perform divisions below diagonal

      }
  }
  
  return LU;
}
