#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
 * 4th order Runge-Kutta for system of N first-order differential equations.
 *   X' = F(t,X)
 *   X(a) = S
 * input:
 *   F : function that computes F(t,X).
 *   N : number of differential equations in system.
 *   S : initial value of X at t = a.
 *   a : initial t-value.
 *   b : final t-value.
 *   n : number of iterations to use.
 *   fp : file to dump t, X[] values suitable for gnuplot (NULL ==> no dump)
 * output:
 *   R : result X at t = b.
 */
void RK4(void (*F)(double t, const double X[], double R[]),
         int N, const double S[], double a, double b, unsigned n,
         FILE *fp, double R[]) {
  const double h = (b - a)/n;
  double X[N];
  memcpy(X, S, N*sizeof(double));
  double t = a;
  for (unsigned k = 1; k <= n; k++, t += h) {
    double Y[N], K1[N], K2[N], K3[N], K4[N];

    if (fp != NULL) {
      fprintf(fp, "%0.10g ", t);
      for (unsigned i = 0; i < N; i++)
        fprintf(fp, "%0.10g ", X[i]);
      fprintf(fp, "\n");
    }

    F(t, X, K1);
    for (unsigned i = 0; i < N; i++)
      Y[i] = X[i] + h/2*K1[i];
    F(t+h/2, Y, K2);
    for (unsigned i = 0; i < N; i++)
      Y[i] = X[i] + h/2*K2[i];
    F(t+h/2, Y, K3);
    for (unsigned i = 0; i < N; i++)
      Y[i] = X[i] + h*K3[i];
    F(t+h, Y, K4);
    for (unsigned i = 0; i < N; i++)
      X[i] = X[i] + h/6*(K1[i] + 2*K2[i] + 2*K3[i] + K4[i]);
  }
  for (unsigned i = 0; i < N; i++)
    R[i] = X[i];
}


void F_arrow(double t, const double X[], double R[]) {
  R[0] = X[1];
  R[1] = -32;
}

void F_arrowAirResist(double t, const double X[], double R[]) {
  R[0] = X[1];
  R[1] = -X[1]/25 - 32;
}

void F_baseball(double t, const double X[], double R[]) {
  const double k = 0.25;
  const double g = 32.174;
  R[0] = X[1];        // x-position
  R[1] = -k*X[1];     // x-velocity
  R[2] = X[3];        // y-position
  R[3] = -k*X[3] - g; // y-velocity
}

int main() {
  //
  // ./rk4 > arrow.plot
  // plot "arrow.plot" using 1:2 with lines, -16*x**2 + 300*x
  //
#ifdef XXXXX
  double S[2] = {0, 300};
  double R[2];
  RK4(F_arrow, 2, S, 0, 20.0, 20 /* 100 */, stdout, R);

  double S[2] = {0, 300};
  double R[2];
  RK4(F_arrowAirResist, 2, S, 0, 20.0, 100, stdout, R);
#endif

  //
  // ./rk4 > baseball.plot
  // plot "basebal.plot" using 2:4 with lines
  //
  double S[4] = {0, 207*cos(40*M_PI/180), 3, 207*sin(40*M_PI/180)};
  double R[4];
  RK4(F_baseball, 4, S, 0, 7.0, 100, stdout, R);

  return 0;
}
