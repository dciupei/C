#include <stdio.h>
#include <math.h>
#include <float.h>
#include <assert.h>


float bisection(float (*f)(float), float a, float b) {
  assert (b > a);
  float fa = f(a);
  float fb = f(b);
  assert(fa*fb < 0);
  float c = (a + b)/2;
  while(b - a > (fabsf(a) + fabs(b))*FLT_EPSILON){
    float fc = f(c);
    if (fa*fc < 0){
      b = c;
      fb = fc;
    }else{
      a = c;
      fa = fc;
    }
    c = (a + b)/2;
  }
  return c;
}

float sqrt1(float a){
  int exp;
  const float m = frexpf(a, &exp);
  float x = (float)(1 << (exp >> 1)); // guess at sqrt(a)
  float xnext;
  while(1){
    xnext = (x + a/x)/2;
    float const err = xnext - x;
    if (fabsf(err) <= 1e-7)
      break;
    x = xnext;
  }
  return xnext;
}


float f(float x){
  return x*x - 10;
}

int main(void){
  //float r = bisection(f, 3,4);
  float r = sqrt1(10);
  printf("%.10f\n", r);
  return 0;
}
