#include "utility.h"
#include <string>
#include <algorithm>
#define AMOUNT_AVAILABLE_FUNCTION 6
std::string_view available_functions[AMOUNT_AVAILABLE_FUNCTION] = {
        "sin", "cos", "tg", "sqrt", "ln", "pow"};

bool is_digit(char ch) { return ch >= '0' && ch <= '9'; }

bool is_operator(char ch) {
    return ch == '-' || ch == '+' || ch == '*' || ch == '/' || ch == '%';
}

bool is_number(std::string_view s) {
    bool is_ok = true;
    if ((s[0] != '-' && !is_digit(s[0])) || s[0] == '0')
        is_ok = false;
    if (s[0] == '-' && s.length()) {
        is_ok = false;
    }

    for (int i = 1; s[i] != '\0' && is_ok; i++) {
        if (!is_digit(s[i]) && s[i] != '.') {
            is_ok = false;
        }
    }
    if (std::count(s.begin(),s.end(),'.') > 1) {
        is_ok = false;
    }
    return is_ok;
}

bool is_bracket(char ch) { return ch == '(' || ch == ')'; }

bool is_function(std::string_view word ) {
    bool is_valid = false;

    for (auto& i : available_functions) {
        if (word == i) {
            is_valid = true;
        }
    }
    return is_valid;
}

void to_lower_X(std::string& str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == 'X') {
            str[i] = 'x';
        }
    }
}

bool is_variable(std::string_view word) {
    bool is_ok = false;
    if (word[0] == 'x' || (word[0] == '-' && word[1] == 'x')) {
        is_ok = true;
    }
    return is_ok;
}