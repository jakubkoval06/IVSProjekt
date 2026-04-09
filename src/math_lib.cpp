#include "math_lib.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

double add(double a, double b)      {
	return a+b;
}

double subtract(double a, double b) {
	return a-b;
}

double multiply(double a, double b) {
	return a*b;
}

double divide(double a, double b)   {
	if(b == 0){
		throw std::invalid_argument("Division by zero");
	}
	return a/b;
}

double factorial(int n)             {
	if(n<0){
		throw std::invalid_argument("Negative number in factorial");
	}
	if(n==0 || n==1){
		return 1;
	} else {
		return factorial(n-1)*n;
	}
}

//double power(double base, int exp)  {
//	if(exp==0) return 1;
//	if(exp==1) return base;
//	return power(base, exp-1)*base;
//}

double power(double base, int exp) {
	return pow(base, exp);
}

double root(double base, int n)     {
	if (base < 0){
		if(n%2==1){
			return pow(-1*base, 1.0/n)*-1;
}
		throw std::invalid_argument("Negative number in root function base");
}
	if (n<=0){
		throw std::invalid_argument("Negative number or zero in root function exponent");
}
	return pow(base, 1.0/n);
}

//Newton method root
//double root(double base, int n) {
//	double x = base / n;
//	double prev;
//	while (x - prev > 1e-9 || prev - x > 1e-9) {
//        	prev = x;
//        	x = ((n - 1) * x + base / power(x, n - 1)) / n;
//    	}
//    	return x;
//}

double sum(double *val, int len)    {
	double temp = 0;
	for(int i = 0; i < len; i++){
		temp += val[i];
	}
	return temp;
}
