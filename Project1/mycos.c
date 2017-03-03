#include <math.h>
#include <stdio.h>

float mycos( float x ) {
  x = fabsf(x);
  const int n = floorf(x/(2*M_PI));
  x -= 2*M_PI*n;
  if ( x > M_PI)
    x = 2*M_PI - x;
  float sign = +1;
  if (x > M_PI/2){
    x = M_PI - x;
    sign = -1;
  }
  const float x2 = x*x;
  float r = -1.0/3628800;
  r = fmaf(r, x2, 1.0/40320);
  r = fmaf(r, x2, -1.0/720);
  r = fmaf(r, x2, 1.0/24);
  r = fmaf(r, x2, -0.5);
  r = fmaf(r, x2, 1);
  return copysignf(r, sign);

}

int main(){
  const float x0 = -5;
  const float x1 = 5;
  const float n = 20;
  const float dx = (x1 - x0)/(n-1);
  float x = x0;
  for(int i = 0; i < n; i++, x +=dx) { 
    const float c = mycos(x);
    const double t = cos(x);
    const double e = fabs(c - t);
    printf("%0.10f\n", e);
  }

  return 0;
}
