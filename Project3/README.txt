David Ciupei

Email:
-ciupei_david@yahoo.com
-david.ciupei@wsu.edu

Files:
-estPi.c
-README.txt

Description:
	The project is estimating Pi via the numerical integration. This project uses 4 numerical methods to estimate Pi. The four methods are the Trapazoid Rule, Simpson's Rule 1/3, Simpson's Rule 3/8, and Boole's Rule. These methods divide up the integral of integration to get a value for Pi. The program then compares the values to the actual value and prints out the error of each method. 

Compile: 
gcc -g -std=c99 -Wall estPi.c -o estPi -lm

run:
./estPi
