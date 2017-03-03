//David Ciupei
//cs330 Project #1

#include <stdio.h>
#include <math.h>

float myexp(float x) {
  float z, m, w, u,twom, result;
  // all equations were taken from the project assignment
  z = x * M_LOG2E;        // Z = x / ln2
  m = round(z);           
  w = z - m;
  u = w * M_LN2;          // u = w*ln2
    
  twom = ldexpf(1,m);     // 2^m
  

  // Taylor series for e^u computed to the 7th value
  float eU = 1.0/5040;
  eU = fmaf(eU, u, 1.0/720);
  eU = fmaf(eU, u, 1.0/120);
  eU = fmaf(eU, u, 1.0/24);
  eU = fmaf(eU, u, 1.0/6);
  eU = fmaf(eU, u, 0.5);
  eU = fmaf(eU, u, 1);
  eU = fmaf(eU, u, 1);
    
  result = twom * eU;    // multiplies 2^m * e^u to get the result
    
  return result;
}

int main(int argc, const char * argv[]) {

  double y1 = -20;       // e^x will be computed starting at -20
  long double y2 = 20;   // and end at 20
  double n = 30;         // it will have 30 intervals between -20 and 20
  long double rerr, x;
  long double dx = (y2 - y1)/(n-1);    // this will divide -20 and 20 by 30 to 
                                       // get 30 values between the interval
  x = y1;                // sets y1 to x
  for (int i = -20.0; i < 20.0; i++, x += dx) {
    y1 = myexp(x);                     // y1 is set to myexp
    y2 = expl(x);                      // y2 is set to the library expl
    rerr = fabsl((y1-y2) / y2);        // calculates the rel. error
    printf("%+0.9Le , %0.9e , %0.9Le , %0.15Le\n", x, y1, y2, rerr);
  }
    
  return 0;
}
