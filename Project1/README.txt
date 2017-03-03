David Ciupei

SID: 11383576

David.ciupei@wsu.edu 

Ciupei_david@yahoo.com

Files being submitted:

- Relerror.c
- Exp.c
- README

Desciption:

   In the first program I had to compute the relative error equation to find out the smallest n that is below 1.19209x10^-7. This was done by using the equation (sqrt(2)/(n+1)!)*(ln2/2)^(n+1) and plugging in the numbers 1-15 for n to see when the numbers are below the value given. The n value that I found the best to be used is n=7. After finding out the smallest n I then moved on to the second program exp.c where I wrote the myexp() function that computes e^x and the n determined how far to go in the Taylor series. I used Horner’s Rule on the Taylor series to simplify it and used the function fmaf() to compute all the values of the series. After e^x was found for 30 values between -20 and 20 the answer was then compared to the built in function exp() in the c library to get the relative error between the values. I am not sure why the relative errors may exceed the limit. My guess is since the taylor series is a close approximation on the e^x line but it may not be exact therefore the relative error can be higher.
