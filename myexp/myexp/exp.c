//
//  exp.c
//  myexp
//
//  Created by David Ciupei on 9/2/15.
//  Copyright (c) 2015 David Ciupei. All rights reserved.
//

#include <stdio.h>
#include <math.h>

float myexp(float x) {
    float z, m, w, u,twom, result;
    z = x * M_LOG2E;
    m = round(z);
    w = z - m;
    u = w * M_LN2;
    
    twom = ldexpf(1,m);
    
    float eU = 1.0/5040;
    eU = fmaf(eU, u, 1.0/720);
    eU = fmaf(eU, u, 1.0/120);
    eU = fmaf(eU, u, 1.0/24);
    eU = fmaf(eU, u, 1.0/6);
    eU = fmaf(eU, u, 0.5);
    eU = fmaf(eU, u, 1);
    eU = fmaf(eU, u, 1);
    
    result = twom * eU;
    
    return result;
}

int main(int argc, const char * argv[]) {

    double y1 = -20;
    long double y2 = 20;
    double n = 30;
    long double rerr, x;
    long double dx = (y2 - y1)/(n-1);
    x = y1;
    for (int i = -20.0; i < 20.0; i++, x += dx) {
        y1 = myexp(x);
        y2 = expl(x);
        rerr = fabsl((y1-y2) / y2);
        printf("x = %+0.9Le , myexp = %0.9e , expl = %0.9Le , relative error = %0.15Le\n", x, y1, y2, rerr);
    }
    
    return 0;
}