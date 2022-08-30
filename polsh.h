#ifndef POLSH_H
#define POLSH_H
#include <list>
#include "Lexeme.h"
std::list<Lexeme> read(std::string expression);
bool bracket_check(std::string_view expression);
std::list<Lexeme> split(std::string_view expression);
std::list<Lexeme> ToPostfix (std::list<Lexeme>);
double Сalculator(std::list<Lexeme> str);

#endif