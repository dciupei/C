//David Ciupei
//CS330 Project #3


#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288 /* pi */
#endif

long double f(long double x) {
  return 4.0L/(1.0L + x*x);
}

long double trapezoid(long double (*f)(long double),//function
		      long double a, long double b, //interval
		      int n){
  assert(a < b);                   //make sure a is less then b
  const long double h = (b - a)/n;  // divides the width of the interval 
  long double sum = 0.0;
  long double x = a + h;
  // evaluates the polynomial for the trapezoid rule
  for (int i = 1; i < n; i++, x += h)
    sum += f(x);
  return h*((f(a) + f(b))/2 + sum);
}



long double simpsons(long double (*f)(long double),long double a, long double b,int n){
  assert(n % 2 == 0);              //checks to see if divisable by 2 
  assert(a < b);                   // checks to see if a is less then b
  const long double h = (b - a)/n; // divides the width of the interval a and b
  // evaluates the polynomial for the simpsons rule
  long double sum1 = 0.0;
  for (int i = 1; i < n; i += 2)
    sum1 += f(a + i*h);
  long double sum2 = 0.0;
  for (int i = 2; i < n; i += 2)
    sum2 += f(a + i*h);
  return h/3*((f(a) + f(b)) + 4*sum1 + 2*sum2);

}

long double simpsons38(long double (*f)(long double),long double a, long double b,int n){
  assert(n % 3 == 0);                //checks to see if divisable by 3
  assert(a < b);                     // checks to see if a is less then b
  const long double h = (b - a)/n;   // divides the width of interval a and b
  // evaluates the polynomial for simpsons 3/8 rule
  long double sum1 = 0.0;
  for (int i = 1; i < n; i += 3)
    sum1 += f(a + i*h);
  long double sum2 = 0.0;
  for (int i = 2; i < n; i += 3)
    sum2 += f(a + i*h);
  long double sum3 = 0.0;
  for (int i = 3; i < n; i += 3)
    sum3 += f(a + i*h);
  return ((3*h)/8)*((f(a) + f(b)) + 3*sum1 + 3*sum2 + 2*sum3);
}

long double booles(long double (*f)(long double),long double a, long double b,int n){
  assert(n % 4 == 0);               //checks to see if divisable by 4
  assert(a < b);                    // checks to see if a is less then b
  const long double h = (b - a)/n;  // divides the width of the interval a and b
  // evaluates the polynomial for booles rule
  long double sum1 = 0.0;
  for(int i = 4; i<n; i +=4){
    sum1 += f(a +i*h);
  }
  long double sum2 = 0.0;
  for (int i = 1; i<n ; i +=2){
    sum2 += f(a +i*h);
  }
  long double sum3 = 0.0;
  for ( int i = 2 ; i < n ; i +=4){
    sum3 += f(a +i*h);
  }
  return ((2.0*h)/45.0)*((7.0*(f(a)+f(b)))+14.0*sum1 + 32.0*sum2 + 12.0*sum3);
}
 
int main(void) {
  const unsigned maxn = 800000;
  for (unsigned n = 12; n <= maxn; n *= 2) {
    const long double I_trap = trapezoid(f, 0, 1, n);
    const long double error_trap = fabsl(M_PI - I_trap);
    const long double I_simp = simpsons(f, 0, 1, n);
    const long double error_simp = fabsl(M_PI - I_simp);
    const long double I_simp38 = simpsons38(f, 0, 1, n);
    const long double error_simp38 = fabsl(M_PI - I_simp38);
    const long double I_booles = booles(f, 0, 1, n);
    const long double error_booles = fabsl(M_PI - I_booles);
    printf("%5d %0.10Le %0.10Le %0.10Le %0.10Le\n", n, 
	   error_trap, error_simp, error_simp38, error_booles);
  }
  return 0;
}
