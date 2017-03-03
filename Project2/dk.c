//David Ciupei
//CS330 Project #2

#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

#define MAXN 25 // max degree

int main(void) {
  int n = 0;  // polynomial degree 
  complex double c[MAXN+1];
  double a, b;
  while (scanf("%lf %lf", &a, &b) == 2)
    c[n++] = a + b*I;
  c[n] = 1;  // leading coeff implied

 #ifdef REGURGITATE  // test input
  for (int i = 0; i < n; i++) {
    a = creal(c[i]);
    b = cimag(c[i]);
    printf("%0.10f + %0.10f i\n", a, b);
  }
 #endif

  // calculates the radius
  double max = 0;
  for (int j = 0; j < n; j++){
    double v = cabs(c[j]);
    if (v > max)
      max = v;
  }
  double Radius = 1 + max;
  //printf("R = %d\n", Radius);
  double complex z[MAXN];
  //initial guesses for the n roots
  for (int j = 0; j < n; j++){
    double theta = j*(2*M_PI) / n;       
    z[j] = ((cos(theta)+I*sin(theta))*Radius);  //store the values into z
  }
  double epsilon = .000001;        //epsilon = 10^-6
    double complex deltaz[MAXN];
    int kmax = 50;
    // will go through the iterations with the max being 50
    for(int k = 1; k <= kmax; k++){
      printf("iteration = %d\n",k);     // k is the number of iteration
      double zmax = 0;

      // will print out the roots
      for(int j = 0; j<n; j++){
	printf(" z[%d] = %.10f + %.10f i\n",j,creal(z[j]), cimag(z[j]));
      }

      // computes Q which is used in the update formula to refine the guesses
      for(int j = 0; j < n; j++){
	complex double Q = 1;

	for(int i = 0; i < n; i++){
	   if(i != j)
	     Q *= (z[j] - z[i]);
	}
	
	// this is the function for the nth degree polynomial
	double complex F = c[n-1] + z[j];
	for(int i = n-2; i>=0; i--){
	  F = F*z[j]+c[i];
	}
	
	deltaz[j] = -F/Q;         // update formula 
	if(cabs(deltaz[j]) > zmax)
	  zmax = cabs(deltaz[j]);
      }
      // updates z[j]
      for(int j = 0; j < n; j++){
	z[j] += deltaz[j]; 
      }
      
      //when its clode to the solution it stops
      if(zmax <= epsilon)
	break;
    }
  return 0;
}
