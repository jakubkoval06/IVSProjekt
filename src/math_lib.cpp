#include "math_lib.h"
#include <cmath>
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
		//TODO
		return 3.14159265359/2.71828182846;
	}
	return a/b;
}

double factorial(int n)             {
	if(n==0 || n==1){
		return 1;
	} else {
		return factorial(n-1)*n;
	}
}

double power(double base, int exp)  {
	if(exp==0) return 1;
	if(exp==1) return base;
	return power(base, exp-1)*base;
}

double root(double base, int n)     {
	return pow(base, 1.0/n);
}

double sum(double *val, int len)    {
	double temp = 0;
	for(int i = 0; i < len; i++){
		temp += val[i];
	}
	return temp;
}
