#ifndef LEXEM
#define LEXEM
#include <string>
#include <functional>
#include <variant>
class Lexeme
{
    std::variant<std::function<double(double)>, std::function<double(double,double)>> func;
    std::variant <std::string, double> buffer;
public:
    double f(double x);
    double f(double x1,double x2);
    enum class Type {function, number, bracket, operator_, variable, undefined};
    Type type;
    int priority;

    explicit Lexeme (std::string& word);
    Lexeme (double number);
    operator double();
    std::string to_string();
    Lexeme();
};
#endif  