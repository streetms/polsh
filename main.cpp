#include <list>
#include <iostream>
#include "polsh.h"
#include "Lexeme.h"
int main() {
    std::list<Lexeme> lexemes = read("1  +  2+3*sin ()");

    for (Lexeme& lex : lexemes) {
        std::cout << lex.buffer << " ";

    }

    return 0;
}
