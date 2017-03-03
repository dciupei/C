//David Ciupei
//CS330 Project #5

#include <stdio.h>
#include <stdlib.h>
#include "LUdecomp.h"


int main(){


  int N = 0;

  scanf("%d", &N);
  //printf("N value = %i\n", N);                                                              
  double xySource[N][2];
  double xyTarget[N][2];

  // gets the points from the .in files
  for(int i = 0; i < N; i++){
    scanf("%lf %lf", &xySource[i][0], &xySource[i][1]);
  }
  for(int i = 0; i < N; i++){
    scanf("%lf %lf", &xyTarget[i][0], &xyTarget[i][1]);
  }

  //creates  matrix A
  double** A = (double**)malloc(2*N*sizeof(double*));;     
  for(int i = 0; i < 2*N; i++){
    A[i] = (double*)malloc(8*sizeof(double));;
    }
  

  int count = 0;
  int count1 = 0;
  int count2 = 0;
  int count3 = 0;
  int count4 = 0;
  int count5 = 0;
  int count6 = 0;
  int count7 = 0;

  // fill in the matrix using equation 7 
 for(int r = 0; r < 2*N; r++){
    if(r % 2 == 0){ // will fill in the matrix for every second row starting at row 1
      A[r][0] = xySource[count++][0];           // column 1
      A[r][1] = xySource[count1++][1];          // column 2
      A[r][2] = 1;                              // column 3
      A[r][3] = 0;                              // column 4 
      A[r][4] = 0;                              // column 5
      A[r][5] = 0;                              // column 6
      A[r][6] = (-1)*(xySource[count2][0])*(xyTarget[count2][0]);   // column 7
      count2++;
      A[r][7] = (-1)*(xySource[count3][1])*(xyTarget[count3][0]);   // column 8
      count3++;

    }else{        // will fill out the rest of the rows in the matrix
      A[r][0] = 0;                              // column 1
      A[r][1] = 0;                              // column 2
      A[r][2] = 0;                              // column 3
      A[r][3] = xySource[count4++][0];          // column 4
      A[r][4] = xySource[count5++][1];          // column 5
      A[r][5] = 1;                              // column 6
      A[r][6] = (-1)*(xySource[count6][0])*(xyTarget[count6][1]);  // column 7
      count6++;
      A[r][7] = (-1)*(xySource[count7][1])*(xyTarget[count7][1]);  // column 8
      count7++;

    }
 }
  

  
  
  // makes the x matrix of the equation Ax = b                                                 
  double* x = (double*)malloc(8*sizeof(double));;
  for(int j = 0; j < 8; j++){
    x[j] = 0.0;
  }

  //makes the b part of the equation Ax = b
  double* b = (double*)malloc(2*N*sizeof(double));;
  count = 0;
  for(int j = 0; j < 2*N; j += 2){
    b[j] = xyTarget[count][0];
    b[j+1] = xyTarget[count++][1];
  }
  
  // this is the A^TA matrix of equation 8
  double** AT = (double**)malloc(8*sizeof(double*));
  for(int i = 0; i < 8; i++){
    AT[i] = (double*)malloc(8*sizeof(double));
  }
  
  // the A^Tb matrix of equation 8
  double* BT = (double*)malloc(8*sizeof(double));

  if(N > 4){
    double result = 0.0;
    for(int i = 0; i < 8; i++){
      for(int j = i; j < 8; j++){
	result = 0.0;
	//gets the result of the summation of equation 9
	for(int k = 0; k < 2*N; k++){
	  result += A[k][i]*A[k][j];
	}
	AT[i][j] = result;       // result of equation 9 (A^TA)ij
      }
    }
    for(int i = 0; i < 8; i++)
      for(int j = 0; j < i; j++)
	AT[i][j] = AT[j][i];    // equationg 10 (A^TA)ij = (A^TA)ji

    result = 0.0;    
    //solves for the summation in equation 11
    for(int i = 0; i < 8; i++){
      result = 0.0;
      for(int j = 0; j < 2*N; j++)
	result += A[j][i] * b[j];
      BT[i] = result;          // (A^Tb)i
    }
  }
  
  if(N == 4){
    LUdecomp* Adecomp = LUdecompose(2*N, (const double**)A);  
    LUsolve(Adecomp, b, x);
  }else{
    LUdecomp* ATrans_decomp = LUdecompose(8, (const double**)AT);
    LUsolve(ATrans_decomp, BT, x);
  }
  

  printf("%.10lf %.10lf %.10lf \n%.10lf %.10lf %.10lf \n%.10lf %.10lf 1.0000000000 \n", x[0], x[1], x[2],x[3],x[4],x[5],x[6],x[7]);
  
  return 0;
}
