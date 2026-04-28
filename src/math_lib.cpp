//  ==============================
//  project:    IVS Calculator (math_lib)
//  author:     xkovalj00 Jakub Koval
//  date:       2026
//  ==============================
/**
 * @file math_lib.cpp
 * @brief Implementation file for the IVS calculator math library. Implements arithmetic,
 *        factorial, power, root, and statistical functions.
 * @author Jakub Koval / xkovalj00
 * @date 2026
 */

#include "math_lib.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    if (b == 0) {
        throw std::invalid_argument("Division by zero");
    }
    return a / b;
}

double factorial(int n) {
    if (n < 0) {
        throw std::invalid_argument("Negative number in factorial");
    }
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return factorial(n - 1) * n;
    }
}

double power(double base, int exp) {
    return pow(base, exp);
}

double root(double base, int n) {
    if (base < 0) {
        if (n % 2 == 1) {
            return pow(-1 * base, 1.0 / n) * -1;
        }
        throw std::invalid_argument("Negative number in root function base");
    }
    if (n <= 0) {
        throw std::invalid_argument("Negative number or zero in root function exponent");
    }
    return pow(base, 1.0 / n);
}

double sum(double *val, int len) {
    double temp = 0;
    for (int i = 0; i < len; i++) {
        temp += val[i];
    }
    return temp;
}
