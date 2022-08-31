#include "polsh.h"
#include "utility.h"
#include <string>
#include <list>
#include <stack>
#include "Lexeme.h"
bool bracket_check(std::string_view expression) {
    int counter = 0;
    bool is_ok = true;
    for (size_t i = 0; i < expression.length() && is_ok; i++) {
        if (expression[i] == '(') {
            counter++;
        }
        if (expression[i] == ')') {
            counter--;
        }
        if (counter < 0) {
            is_ok = false;
        }
    }
    if (counter != 0) {
        is_ok = false;
    }
    return is_ok;
}

std::list<Lexeme> split(std::string_view str) {
    std::string buffer;
    std::list<Lexeme> tokens;
    for (size_t i = 0; str[i] != '\0'; i++) {
        bool lexem_ready = false;
        if (str[i] == ' ') {
            continue;
        }
        if (is_bracket(str[i])) {
            buffer.push_back(str[i]);
            lexem_ready = true;
        } else if (is_digit(str[i]) || str[i] == '.') {
            buffer.push_back(str[i]);
            if(!is_digit(str[i+1]) && str[i+1] != '.') {
                lexem_ready = true;
            }
        } else if ((is_operator(str[i]) && str[i] != '-') || ((str[i] == '-' && i != 0 && !is_bracket(str[i-1])) || is_bracket(str[i+1]))){
            buffer.push_back(str[i]);
            lexem_ready = true;
        } else if(str[i] == '-') {
            buffer.push_back(str[i]);
            if (str[i-1] == ')') {
                lexem_ready = true;
            }
        } else if (str[i] == 'x' && (str.empty()  || str[i-1] == '-')){
            buffer.push_back(str[i]);
            lexem_ready = true;
        } else {
            buffer.push_back(str[i]);
            if(is_digit(str[i+1]) || is_operator(str[i+1]) || is_bracket(str[i+1]) || str[i+1] == ' '){
                lexem_ready = true;
            }
        }
        if (lexem_ready) {
            if (buffer[0] != ' ') {
                tokens.emplace_back(Lexeme(buffer));
            }
            buffer.clear();
        }
    }
    return tokens;
}

std::list<Lexeme> read(std::string expression) {
    bool is_ok = true;
    is_ok = bracket_check(expression);
    to_lower_X(expression);
    std::list<Lexeme> list_lexems;
    if (is_ok) {
        list_lexems = split(expression);
        if (list_lexems.empty() || (*list_lexems.begin()).type == Lexeme::Type::operator_ ){
            is_ok = false;
        }
        if (list_lexems.back().type == Lexeme::Type::function or list_lexems.back().type == Lexeme::Type::operator_) {
            is_ok = false;
        }
        for(auto cur = list_lexems.begin(); cur != list_lexems.end() && is_ok; cur++) {
            if (cur->type == Lexeme::Type::undefined) {
                is_ok = false;
            }
            auto next = ++cur;
            cur--;
            if (cur->type == Lexeme::Type::function && next->to_string()  != "(")  {
                is_ok = false;
            }
            if (cur->type != Lexeme::Type::number && next->type != Lexeme::Type::number) {
                if (cur->to_string() == "(" && next->to_string() == ")") {
                    is_ok = false;
                }
                if (cur->to_string() == "(" && next->type == Lexeme::Type::operator_ && next->to_string() != "-") {
                    is_ok = false;
                }
            }
            if (cur->type == Lexeme::Type::operator_ && next->type == Lexeme::Type::operator_) {
                is_ok = false;
            }
        }
        if (! is_ok ) {
            list_lexems.clear();
        }
    }
    return list_lexems;
}

std::list<Lexeme> ToPostfix(std::list<Lexeme> lexeme) {
    std::list<Lexeme> str;
    std::stack<Lexeme> stack;
    for (auto lex : lexeme) {
        //lex->buffer - symbol
        if (lex.type == Lexeme::Type::number) {
            str.push_back(lex);
        } else if (lex.to_string() == "(") {
            stack.push(lex);
        } else if (lex.to_string() == ")") {
            while (stack.top().to_string() != "(") {
                str.push_back(stack.top());
                stack.pop();
            }
            stack.pop();
        } else {
            if (stack.empty() || stack.top().type == Lexeme::Type::bracket) {
                stack.push(lex);
            } else if (stack.top().priority < lex.priority) {
                stack.push(lex);
            } else {
                while ( !stack.empty()  &&  (stack.top().type == Lexeme::Type::operator_ || stack.top().type == Lexeme::Type::function && stack.top().priority >= lex.priority)) {
                    str.push_back(stack.top());
                    stack.pop();
                } stack.push(lex);
            }

        }
    }

    while (!stack.empty()){
        str.push_back(stack.top());
        stack.pop();
    }

    return str;
}
 double Сalculator(std::list<Lexeme> str) {
    std::stack<Lexeme> stack;
    double res = 0;
    for ( auto lex : str) {
        if  (lex.type == Lexeme::Type::number) {
            stack.push(lex);
        } else {
            if (!stack.empty()) {
                Lexeme cur_s_2 = stack.top();
                stack.pop();
                if (!stack.empty() && lex.type == Lexeme::Type::operator_) {
                    Lexeme cur_s_1 = stack.top();
                    stack.pop();
                    switch (lex.to_string()[0]) {
                        case '+':
                            res = cur_s_1 + cur_s_2;
                            stack.push(res);
                            break;
                        case '-':
                            res = cur_s_1 - cur_s_2;
                            stack.push(res);
                            break;
                        case '*':
                            res = cur_s_1 * cur_s_2;
                            stack.push(res);
                            break;
                        case '/':
                            res = cur_s_1 / cur_s_2;
                            stack.push(res);
                            break;
                        }
                    }
                    if (lex.type == Lexeme::Type::function) {
                        stack.push( lex.f(cur_s_2));
                    }
                }
            }
        }
    if (!stack.empty()) {
        res = stack.top();
    }
    return res;
}
