//  ==============================
//  project:    IVS Calculator (parser)
//  author:     xkovalj00 Jakub Koval
//  date:       2026
//  ==============================
/**
 * @file parser.cpp
 * @brief Implementation file for the IVS calculator expression parser. Implements the
 *        recursive-descent parser used to tokenise and evaluate mathematical
 *        expressions entered by the user.
 * @author Jakub Koval / xkovalj00
 * @date 2026
 */

#include "math_lib.h"
#include "parser.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <cctype>
#include <algorithm>

std::string input;
int pos = 0;

double parseExpr();
double parseTerm();
double parsePower();
double parsePrimary();

void skipSpaces() {
    while (pos < (int)input.size() && input[pos] == ' ')
        pos++;
}

char peek() {
    skipSpaces();
    if (pos >= (int)input.size()) return '\0';
    return input[pos];
}

std::string peekStr() {
    skipSpaces();
    if (pos >= (int)input.size()) return "end of input";
    if ((unsigned char)input[pos] == 0xCB && (unsigned char)input[pos + 1] == 0x86) return "ˆ";
    return std::string(1, input[pos]);
}

char consume() {
    skipSpaces();
    return input[pos++];
}

void expect(char c) {
    if (consume() != c)
        throw std::runtime_error(std::string("Expected '") + c + "'");
}

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

std::string parseName() {
    skipSpaces();
    int start = pos;
    while (pos < (int)input.size() && isalpha(input[pos]))
        pos++;
    return input.substr(start, pos - start);
}

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

double parsePower() {
    double base = parsePrimary();

    if (peekStr() == "^" || peekStr() == "ˆ") {
        pos += (peekStr() == "ˆ") ? 2 : 1;
        double exp = parsePower();
        return power(base, (int)exp);
    }

    return base;
}

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
        
        if (name == "log") {
            expect('(');
            double val = parseExpr();
            expect(',');
            double base = parseExpr();
            expect(')');
            return logarithm(val, base);
        }
        
        throw std::runtime_error("Unknown function: " + name);
    }

    return parseNumber();
}

double evaluate(const std::string &expr) {
    input = expr;
    pos   = 0;
    return parseExpr();
}
