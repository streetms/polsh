#ifndef UTILITY_H
#define UTILITY_H
#include <string>
bool is_digit (char ch);
bool is_operator(char ch);
bool is_number(std::string_view str);
bool is_bracket(char ch);
bool is_function(std::string_view str);
void to_lower_X(std::string& str);
bool is_variable(std::string_view word);
#endif