//  ==============================
//  project:    IVS Calculator (Profiling)
//  author:     xkadlep01 Patrik Kadlecek
//  date:       2026
//  ==============================

/**
 * @file stddev.cpp
 * @brief Profiling program for the IVS calculator. Reads numbers from stdin and computes the sample standard deviation. 
 * @author Patrik Kadleček / xkadlep01
 * @date 2026
 */

#include "math_lib.h"
#include <iostream>
#include <vector>

/**
 * @brief Reads numbers from stdin and calculates sqrt((SUM(x^2) - n * mean^2) / (n-1)).
 * @return 0 on success, 1 if fewer than 2 values were provided
 */
int main() {

    double x;

    // Read all numbers from stdin
    std::vector<double> numbers;
    while(std::cin >> x) {
        numbers.push_back(x);
    }

    int len = (int)numbers.size();

    if (len < 2) {
        std::cerr << "Error: at least 2 values required\n";
        return 1;
    }

    // Compute sum of all values and sum of squares
    double total = sum(numbers.data(), len);
    double sumOfSquares = 0.0;
    for(double v : numbers) {
        sumOfSquares = add(sumOfSquares, power(v, 2));
    }

    // Standard deviation formula: sqrt((Σx² - n·x̄²) / (n-1))
    double mean = divide(total, len);
    double variance = divide(subtract(sumOfSquares, multiply(power(mean, 2), len)), subtract(len, 1));
    double stdDev = root(variance, 2);

    std::cout << stdDev;
}