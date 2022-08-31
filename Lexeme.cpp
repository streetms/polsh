#include "Lexeme.h"
#include "utility.h"
#include <cmath>


Lexeme::Lexeme(std::string& word) {
    buffer = word;
    if (is_number(word)) {
        type = Lexeme::Type::number;
        priority = 500;
        buffer = atof(word.c_str());
    } else if (is_bracket(word[0])) {
        type = Lexeme::Type::bracket;
        priority = 0;
    } else if (is_operator(word[0]) && word.length() == 1) {
        if (word == "+" || word == "-") {
            priority = 1;
        }
        if (word == "*" || word == "/" || word == "%") {
            priority = 2;
        }
        type = Lexeme::Type::operator_;
    } else if (is_function(word)) {
        type = Lexeme::Type::function;
        priority = 3;
        if (word == "sin") {
            func = sin;
        } else if (word == "cos") {
            func = cos;
        } else if (word == "tg") {
            func = tan;
        } else if (word == "sqrt") {
            func = sqrt;
        } else if (word == "ln") {
            func = log;
        } else if (word == "pow") {
            func = pow;
        }
    } else if (is_variable(word)) {
        type = Lexeme::Type::variable;
    } else {
        type = Lexeme::Type::undefined;
    }
}

double Lexeme::f(double x) {
    return   std::get<0>(func)(x);
}

double Lexeme::f(double x1, double x2) {
    return std::get<1>(func)(x1,x2);
}

Lexeme::Lexeme(double number) {
    this->buffer = number;
    type = Type::number;
    priority = 500;
}

Lexeme::Lexeme() {
    this->type = Type::undefined;
}

Lexeme::operator double() {
    return std::get<1>(buffer);
}

std::string Lexeme::to_string() {
    return std::get<0>(buffer);;
}
