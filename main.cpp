#include <list>
#include <iostream>
#include "polsh.h"
#include "Lexeme.h"

int main() {
    std::list<Lexeme> lexemes =  read ("(3-(6*6-8*1-4)-9)+1");

    for (Lexeme& lex : lexemes) {
        std::cout << lex.buffer << " ";

    }

    return 0;
}

//3 6 6 * 8 1 * - 4 - - 9 - 1 +