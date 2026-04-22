/**
 * @file math_lib.cpp
 * @brief Implementation of the math library for the IVS Calculator project.
 *
 * Provides basic arithmetic operations, as well as more advanced functions
 * such as factorial, power, nth root, and summation.
 */

#include "math_lib.h"
#include <cmath>
#include <iostream>
#include <stdexcept>


/**
 * @brief Adds two numbers together.
 * @param a First operand.
 * @param b Second operand.
 * @return Sum of @p a and @p b.
 */
double add(double a, double b) {
    return a + b;
}

/**
 * @brief Subtracts one number from another.
 * @param a The minuend.
 * @param b The subtrahend.
 * @return Result of @p a minus @p b.
 */
double subtract(double a, double b) {
    return a - b;
}

/**
 * @brief Multiplies two numbers together.
 * @param a First operand.
 * @param b Second operand.
 * @return Product of @p a and @p b.
 */
double multiply(double a, double b) {
    return a * b;
}

/**
 * @brief Divides one number by another.
 * @param a The dividend.
 * @param b The divisor.
 * @return Result of @p a divided by @p b.
 * @throws std::invalid_argument if @p b is zero.
 */
double divide(double a, double b) {
    if (b == 0) {
        throw std::invalid_argument("Division by zero");
    }
    return a / b;
}

/**
 * @brief Computes the factorial of a non-negative integer.
 *
 * Uses recursion to calculate n! = n * (n-1) * ... * 1.
 * By definition, 0! = 1.
 *
 * @param n A non-negative integer.
 * @return Factorial of @p n.
 * @throws std::invalid_argument if @p n is negative.
 */
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

/**
 * @brief Raises a base to an integer exponent.
 * @param base The base value.
 * @param exp  The integer exponent.
 * @return @p base raised to the power of @p exp.
 */
double power(double base, int exp) {
    return pow(base, exp);
}

/**
 * @brief Computes the nth root of a number.
 *
 * Supports odd roots of negative numbers, returning a negative result.
 * Even roots of negative numbers are not defined and will throw.
 *
 * @param base The radicand (number to take the root of).
 * @param n    The degree of the root. Must be a positive integer.
 * @return The nth root of @p base.
 * @throws std::invalid_argument if @p base is negative and @p n is even.
 * @throws std::invalid_argument if @p n is zero or negative.
 */
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

/**
 * @brief Computes the sum of an array of values.
 * @param val Pointer to the array of doubles to sum.
 * @param len Number of elements in the array.
 * @return Sum of all elements in @p val.
 */
double sum(double *val, int len) {
    double temp = 0;
    for (int i = 0; i < len; i++) {
        temp += val[i];
    }
    return temp;
}