#include <list>
#include <iostream>
#include "polsh.h"
#include "Lexeme.h"

int main() {
    std::string s  = "(3-(6*6-8*1-4)-9)+1";
    std::list<Lexeme> lexemes = ToPostfix(read (s));
    //std::list<Lexeme> lexemes = (read(s));
    for (auto& lexeme : lexemes) {
        std::cout << lexeme.buffer << " ";
    }
    return 0;
}

//3 6 6 * 8 1 * - 4 - - 9 - 1 +