#ifndef PARSER_H
#define PARSER_H

#include <string>

/** @brief The expression string currently being parsed. */
extern std::string input;

/** @brief Current position (index) within @ref input. */
extern int pos;

/**
 * @brief Advances @ref pos past any space characters.
 */
void skipSpaces();

/**
 * @brief Returns the current character without consuming it.
 *
 * Skips leading spaces before peeking.
 *
 * @return The current character, or @c '\\0' if the end of input has been reached.
 */
char peek();

/**
 * @brief Returns a string representation of the current token without consuming it.
 *
 * Handles the two-byte UTF-8 sequence for the modifier-letter circumflex @c ˆ
 * (U+02C6) in addition to regular single-byte characters. Skips leading spaces.
 *
 * @return A one-character string for ordinary characters, @c "ˆ" for the
 *         UTF-8 circumflex, or @c "end of input" when the end of the string
 *         has been reached.
 */
std::string peekStr();

/**
 * @brief Consumes and returns the current character.
 *
 * Skips leading spaces before consuming.
 *
 * @return The consumed character.
 */
char consume();

/**
 * @brief Consumes the current character and verifies it matches an expected value.
 *
 * @param c The character that must appear at the current position.
 * @throws std::runtime_error if the consumed character does not equal @p c.
 */
void expect(char c);

/**
 * @brief Parses and returns a numeric literal from the current position.
 *
 * Accepts an optional leading minus sign followed by digits and an optional
 * decimal point.
 *
 * @return The parsed number as a @c double.
 * @throws std::runtime_error if no valid number is found at the current position.
 */
double parseNumber();

/**
 * @brief Parses and returns an alphabetic identifier from the current position.
 *
 * Consumes characters as long as they satisfy @c isalpha. Used to read
 * function names such as @c sqrt, @c root, and @c fact.
 *
 * @return The parsed identifier as a @c std::string (may be empty if the
 *         current character is not alphabetic).
 */
std::string parseName();

/**
 * @brief Parses an additive expression.
 *
 * Handles the @c + and @c - binary operators with left-to-right associativity
 * by repeatedly parsing @ref parseTerm sub-expressions.
 *
 * @return The evaluated result of the expression.
 */
double parseExpr();

/**
 * @brief Parses a multiplicative expression.
 *
 * Handles the @c * and @c / binary operators with left-to-right associativity
 * by repeatedly parsing @ref parsePower sub-expressions.
 *
 * @return The evaluated result of the term.
 * @throws std::invalid_argument (from math_lib) if a division by zero is attempted.
 */
double parseTerm();

/**
 * @brief Parses an exponentiation expression.
 *
 * Handles both the ASCII caret @c ^ and the UTF-8 modifier-letter circumflex
 * @c ˆ (U+02C6) as the power operator. Associativity is right-to-left due to
 * the recursive call.
 *
 * @return The evaluated result, i.e. base raised to the parsed exponent.
 */
double parsePower();

/**
 * @brief Parses a primary expression.
 *
 * A primary expression is one of:
 * - A unary negation: @c -primary
 * - A parenthesised sub-expression: @c (expr)
 * - A function call: @c sqrt(expr), @c root(expr,n), or @c fact(expr)
 * - A numeric literal
 *
 * @return The evaluated value of the primary expression.
 * @throws std::runtime_error if an unknown function name is encountered.
 * @throws std::runtime_error if a closing parenthesis or comma is missing.
 * @throws std::invalid_argument (from math_lib) for domain errors such as
 *         an even root of a negative number or a negative factorial argument.
 */
double parsePrimary();

/**
 * @brief Evaluates a mathematical expression given as a string.
 *
 * Initialises the global parser state (@ref input and @ref pos) and
 * delegates to @ref parseExpr to produce the result.
 *
 * @param expr The expression to evaluate (e.g. @c "3 + sqrt(16) * 2").
 * @return The numeric result of the expression.
 * @throws std::runtime_error for syntax errors such as unknown tokens or
 *         missing parentheses.
 * @throws std::invalid_argument (from math_lib) for mathematical domain errors.
 */
double evaluate(const std::string &expr);

#endif
