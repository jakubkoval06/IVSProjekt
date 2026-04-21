#include <string>

/**
 * @brief Calculates a mathematical expression string.
 * @param expr Expression to evaluate (3+4*2).
 * @throws std::runtime_error on invalid input or division by zero.
 */
double evaluate(const std::string &expr);
