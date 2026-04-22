/**
 * @file parser.cpp
 * @brief Recursive-descent parser for evaluating mathematical expressions.
 *
 * Parses and evaluates a string containing a mathematical expression,
 * supporting the four basic arithmetic operators, exponentiation, parentheses,
 * and the built-in functions @c sqrt, @c root, and @c fact.
 *
 * Grammar (informally):
 * @code
 * expr    = term   { ('+' | '-') term }
 * term    = power  { ('*' | '/') power }
 * power   = primary [ ('^' | 'ˆ') power ]
 * primary = '-' primary
 *         | '(' expr ')'
 *         | 'sqrt' '(' expr ')'
 *         | 'root' '(' expr ',' number ')'
 *         | 'fact' '(' expr ')'
 *         | number
 * @endcode
 */

#include "math_lib.h"
#include "parser.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <cctype>
#include <algorithm>

/** @brief The expression string currently being parsed. */
std::string input;

/** @brief Current position (index) within @ref input. */
int pos = 0;

/* Forward declarations */
double parseExpr();
double parseTerm();
double parsePower();
double parsePrimary();

/**
 * @brief Advances @ref pos past any space characters.
 */
void skipSpaces() {
    while (pos < (int)input.size() && input[pos] == ' ')
        pos++;
}

/**
 * @brief Returns the current character without consuming it.
 *
 * Skips leading spaces before peeking.
 *
 * @return The current character, or @c '\\0' if the end of input has been reached.
 */
char peek() {
    skipSpaces();
    if (pos >= (int)input.size()) return '\0';
    return input[pos];
}

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
std::string peekStr() {
    skipSpaces();
    if (pos >= (int)input.size()) return "end of input";
    if ((unsigned char)input[pos] == 0xCB && (unsigned char)input[pos + 1] == 0x86) return "ˆ";
    return std::string(1, input[pos]);
}

/**
 * @brief Consumes and returns the current character.
 *
 * Skips leading spaces before consuming.
 *
 * @return The consumed character.
 */
char consume() {
    skipSpaces();
    return input[pos++];
}

/**
 * @brief Consumes the current character and verifies it matches an expected value.
 *
 * @param c The character that must appear at the current position.
 * @throws std::runtime_error if the consumed character does not equal @p c.
 */
void expect(char c) {
    if (consume() != c)
        throw std::runtime_error(std::string("Expected '") + c + "'");
}

/**
 * @brief Parses and returns a numeric literal from the current position.
 *
 * Accepts an optional leading minus sign followed by digits and an optional
 * decimal point.
 *
 * @return The parsed number as a @c double.
 * @throws std::runtime_error if no valid number is found at the current position.
 */
double parseNumber() {
    skipSpaces();
    int start = pos;

    if (pos < (int)input.size() && input[pos] == '-')
        pos++;

    while (pos < (int)input.size() && (isdigit(input[pos]) || input[pos] == '.'))
        pos++;

    if (pos == start)
        throw std::runtime_error("Expected a number");

    return std::stod(input.substr(start, pos - start));
}

/**
 * @brief Parses and returns an alphabetic identifier from the current position.
 *
 * Consumes characters as long as they satisfy @c isalpha. Used to read
 * function names such as @c sqrt, @c root, and @c fact.
 *
 * @return The parsed identifier as a @c std::string (may be empty if the
 *         current character is not alphabetic).
 */
std::string parseName() {
    skipSpaces();
    int start = pos;
    while (pos < (int)input.size() && isalpha(input[pos]))
        pos++;
    return input.substr(start, pos - start);
}

/**
 * @brief Parses an additive expression.
 *
 * Handles the @c + and @c - binary operators with left-to-right associativity
 * by repeatedly parsing @ref parseTerm sub-expressions.
 *
 * @return The evaluated result of the expression.
 */
double parseExpr() {
    double left = parseTerm();

    while (peek() == '+' || peek() == '-') {
        char op = consume();
        double right = parseTerm();
        if (op == '+') left = add(left, right);
        else           left = subtract(left, right);
    }

    return left;
}

/**
 * @brief Parses a multiplicative expression.
 *
 * Handles the @c * and @c / binary operators with left-to-right associativity
 * by repeatedly parsing @ref parsePower sub-expressions.
 *
 * @return The evaluated result of the term.
 * @throws std::invalid_argument (from math_lib) if a division by zero is attempted.
 */
double parseTerm() {
    double left = parsePower();

    while (peek() == '*' || peek() == '/') {
        char op = consume();
        double right = parsePower();
        if (op == '*') left = multiply(left, right);
        else           left = divide(left, right);
    }

    return left;
}

/**
 * @brief Parses an exponentiation expression.
 *
 * Handles both the ASCII caret @c ^ and the UTF-8 modifier-letter circumflex
 * @c ˆ (U+02C6) as the power operator. Associativity is right-to-left due to
 * the recursive call.
 *
 * @return The evaluated result, i.e. base raised to the parsed exponent.
 */
double parsePower() {
    double base = parsePrimary();

    if (peekStr() == "^" || peekStr() == "ˆ") {
        pos += (peekStr() == "ˆ") ? 2 : 1;
        double exp = parsePower();
        return power(base, (int)exp);
    }

    return base;
}

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
double parsePrimary() {
    skipSpaces();

    if (peek() == '-') {
        consume();
        return -parsePrimary();
    }

    if (peek() == '(') {
        consume();
        double val = parseExpr();
        expect(')');
        return val;
    }

    if (isalpha(peek())) {
        std::string name = parseName();

        if (name == "sqrt") {
            expect('(');
            double val = parseExpr();
            expect(')');
            return root(val, 2);
        }

        if (name == "root") {
            expect('(');
            double val = parseExpr();
            expect(',');
            int n = (int)parseNumber();
            expect(')');
            return root(val, n);
        }

        if (name == "fact") {
            expect('(');
            int val = (int)parseExpr();
            expect(')');
            return factorial(val);
        }

        throw std::runtime_error("Unknown function: " + name);
    }

    return parseNumber();
}

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
double evaluate(const std::string &expr) {
    input = expr;
    pos   = 0;
    return parseExpr();
}