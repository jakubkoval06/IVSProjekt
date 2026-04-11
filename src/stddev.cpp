//  ==============================
//  project:    IVS Calculator (Profiling)
//  author:     xkadlep01 Patrik Kadlecek
//  date:       2026
//  ==============================

#include "math_lib.h"
#include <iostream>
#include <vector>

int main() {

    double x;

    std::vector<double> values;
    while(std::cin >> x) {
        values.push_back(x);
    }

    int len = values.size();
    double VectorSum = sum(values.data(), len);

    double SumSq = 0.0;
    for(double v : values) {
        SumSq = add(SumSq, power(v,2));
    }

    double mean = divide(VectorSum, len);

    double mean_sq = power(mean,2);
    double n_times_mean_sq = multiply(mean_sq, len);

    double brackets = subtract(SumSq, n_times_mean_sq);
    double divided = divide(brackets, subtract(len,1));

    double std_dev = root(divided, 2);

    std::cout << std_dev;
}