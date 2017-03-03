//
//  main.c
//  main
//
//  Created by David Ciupei on 1/17/15.
//  Copyright (c) 2015 David Ciupei. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double stddev(double array[], int k);
double average(double array[],int k);

int main() {
    
    int i, k, j;                           //initializes the intervals, numbers to generate and i for the for loop
    printf("Number of intervals to be used?\n");
    scanf("%i", &j);                       //stores user input into j of how many intervals
    printf("How many numbers to generate?\n");
    scanf("%i", &k);                       //stores how many numbers to generate into k
    
    
    double array[k];
    
    for (i = 0; i < k; i++){               //this for loop gives the requested random numbers
      //  array[i] = rand()/(RAND_MAX / j);  //generates the random numbers and stores them in the array
        array[i] = rand() % j;
        printf("%f\n", array[i]);          //prints the numbers in the array
}
    printf("average = %f\n", average(array,k)); //prints the result from the average method
    printf("Standard Deviation = %f\n", stddev(array,k)); //prints the result from the stddev method
    return 0;
}

double average(double array[], int k){
    double average;
    int i;
    for(i=0; i<k;++i){                     //this loops through the array adding each number and storing it in average
        average+=array[i];
    }
    return average=average/k;              //the average is then divided by the number of elements and returned
}

double stddev(double array[], int k){
    double average, sum;
    int i;                 //
    for(i=0; i<k;++i){     //
        average+=array[i]; // computes the average again
    }                      //
    average=average/k;     //
    for(i=0; i<k;++i)
        sum+=(array[i]-average)*(array[i]-average); //subtracts the average from each element and sqaures it then adds it all together
    return sqrt(sum/k);                    //divide that result with the number of elemnts and square root it and return
}
