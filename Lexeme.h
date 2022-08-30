#ifndef LEXEM
#define LEXEM
#include <string>
#include <functional>
#include <variant>
class Lexeme
{
    std::variant<std::function<double(double)>, std::function<double(double,double)>> func;
public:
    double f(double x);
    double f(double x1,double x2);
    enum class Type {function, number, bracket, operator_, variable, undefined};
    Type type;
    int priority;
    std::string buffer;
    Lexeme (std::string_view word);
    Lexeme (double number);
    Lexeme();
};
#endif  