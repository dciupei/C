//David Ciupei
//CS330 Project #1

#include <stdio.h>
#include <math.h>

double relerror(double n){
  double factorial, k, first, ln, second, final;
  factorial = n + 1;
  // this for loop will calculate the factorial for (n+1)!
  for (k = 1; k <= n; k++){
    factorial = factorial * k;
  }
  first = 2 / factorial;    // this becomes the equation 2/(n+1)!
  ln = log(2) / 2;          // (ln2/2)
  second = pow(ln, n+1);    // this raises the ln/2 to the n+1 power 
  final = first * second;   // It multiplies the first and second 
                            // equation to get the rel. error answer    
    
  return final;
    
}

int main() {
  double result;
  int n = 0;
  // gets the rel. error for the first 15 numbers 
  for (double i = 1; i <= 15; i++) {
    result = relerror(i);
    n += 1;
    printf("n = %d, error = %0.21f\n",n , result);
  }
    
  return 0;
}
