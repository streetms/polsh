#ifndef LEXEM
#define LEXEM
#include <string>

class Lexeme
{
public:
    enum class Type {function, number, bracket, operator_, variable, undefined};
    Type type;
    int priority;
    std::string buffer;
    Lexeme (std::string_view word);
};
#endif  