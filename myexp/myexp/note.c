//
//  note.c
//  myexp
//
//  Created by David Ciupei on 9/3/15.
//  Copyright (c) 2015 David Ciupei. All rights reserved.
//

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

//simple recursive factorial function we learn in CS121...
double factorial(double n){
    if (n<1)
        n = fabs(n);
    if (n == 0.0)
        return 1.0;
    return (n*factorial(n-1));
}

int relerror(){
    
    double errorArray[16];
    const double z = 0.5*M_LN2;
    const double machError = 0.000000119209;
    int smallest_n = 16;
    
    //We loop downward through the possible n's, getting 1 smaller each time
    //when we get 1 that is bigger than the machine error, the n+1 integer
    //is then the smallest n that stays under the machine error of 0.000000119209
    //NOTE: n's that give us 0.0000000 in output are obviously smaller than mach
    //error and thus we don't really care about them and keep looping downward anyways
    for (int n=15; n>0; n--){
        errorArray[n] = ((2.0/(factorial((double) n+1))) * pow(z, (double) n+1));
        if (errorArray[n] < machError) {smallest_n = n;}
        printf("n : %d, error : %.10lf\n", n, errorArray[n]);
    }
    
    printf("smallest n is: %d, relerror: %.10lf\n", smallest_n, errorArray[smallest_n]);
    return smallest_n;
}

//int main(){
    
//    int test = relerror();
    
//    return 0;
//}
