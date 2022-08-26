#include "Lexeme.h"
#include "utility.h"
#include <string>
Lexeme::Lexeme(std::string_view word) {
    buffer = word;
    if (is_number(word)) {
        type = Lexeme::Type::number;
        priority = 500;
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
    } else if (is_variable(word)) {
        type = Lexeme::Type::variable;
    } else {
        type = Lexeme::Type::undefined;
    }
}