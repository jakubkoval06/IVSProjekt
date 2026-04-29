//  ==============================
//  project:    IVS Calculator (math_lib)
//  author:     xkovalj00 Jakub Koval
//  date:       2026
//  ==============================
/**
 * @file math_lib.h
 * @brief Header file for the IVS calculator math library. Declares arithmetic,
 *        factorial, power, root, and statistical functions.
 * @author Jakub Koval / xkovalj00
 * @date 2026
 */

#ifndef MATH_LIB_H
#define MATH_LIB_H

/**
 * @brief Adds two numbers together.
 * @param a First operand.
 * @param b Second operand.
 * @return Sum of @p a and @p b.
 */
double add(double a, double b);

/**
 * @brief Subtracts one number from another.
 * @param a The minuend.
 * @param b The subtrahend.
 * @return Result of @p a minus @p b.
 */
double subtract(double a, double b);

/**
 * @brief Multiplies two numbers together.
 * @param a First operand.
 * @param b Second operand.
 * @return Product of @p a and @p b.
 */
double multiply(double a, double b);

/**
 * @brief Divides one number by another.
 * @param a The dividend.
 * @param b The divisor.
 * @return Result of @p a divided by @p b.
 * @throws std::invalid_argument if @p b is zero.
 */
double divide(double a, double b);

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
double factorial(int n);

/**
 * @brief Raises a base to an integer exponent.
 * @param base The base value.
 * @param exp  The integer exponent.
 * @return @p base raised to the power of @p exp.
 */
double power(double base, int exp);

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
double root(double base, int n);

/**
 * @brief Computes the sum of an array of values.
 * @param val Pointer to the array of doubles to sum.
 * @param len Number of elements in the array.
 * @return Sum of all elements in @p val.
 */
double sum(double *val, int len);
/**
 * @brief Computes the logarithm of a value in a given base.
 *
 * Calculates log_base(x) using the change-of-base formula: ln(x) / ln(base).
 *
 * @param x    The argument of the logarithm. Must be a positive number.
 * @param base The base of the logarithm. Must be a positive number other than 1.
 * @return Logarithm of @p x in the given @p base.
 * @throws std::invalid_argument if @p x is zero or negative.
 * @throws std::invalid_argument if @p base is zero, negative, or equal to 1.
 */
double logarithm(double x, double base);
#endif
