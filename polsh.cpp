#include "polsh.h"
#include "utility.h"
#include <string>
#include <list>
#include <stack>
#include "Lexeme.h"
#include <iostream>
#include <ciso646>
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
            if (cur->type == Lexeme::Type::function && next->buffer  != "(")  {
                is_ok = false;
            }
            if (cur->buffer == "(" && next->buffer == ")") {
                is_ok = false;
            }
            if (cur->buffer == "(" && next->type == Lexeme::Type::operator_ && next->buffer != "-"){
                is_ok = false;
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
    for ( auto lex = lexeme.begin(); lex != lexeme.end(); lex++) {
        //lex->buffer - symbol
        if (lex->type == Lexeme::Type::number) {
            str.push_back(*lex);
        } else if (lex->buffer == "(") {
            stack.push(*lex);
        } else if (lex->buffer == ")") {
            while ( stack.top().buffer != "(" ) {
                str.push_back(stack.top());
                stack.pop();
            }
            stack.pop();
        } else {
            if (stack.empty() || stack.top().type == Lexeme::Type::bracket) {
                stack.push(*lex);
            } else if (stack.top().priority < lex->priority) {
                stack.push(*lex);
            } else {
                while (stack.top().type == Lexeme::Type::operator_ && stack.top().priority >= lex->priority) {
                    str.push_back(stack.top());
                    stack.pop();
                } stack.push(*lex);
            }

        }
    }

    while (!stack.empty()){
        str.push_back(stack.top());
        stack.pop();
    }

    return str;
}


//list_node *ToPostfix(List head) {
//    Lexem x;
//    List postfix_str = NULL;
//    stack_node *head_s = NULL;
//    int i = -1;
//
//    if (head == NULL) {
//        puts("sd");
//    }
//
//    for (list_node *cur = head; cur != NULL; cur = cur->next) {
//
//
//        printf("%s\n", cur->data.buffer);
//        //  cur->data - LEXEM
//        i++;
//        Lexem c = cur->data; // символ
//
//        if (cur->data.type == number)  {
//            add_back_list(&postfix_str, c);
//
//        } else if (c.buffer[0] == '(') {
//
//            head_s = push(head_s, cur->data);
//
//        } else if (c.buffer[0] == ')') {
//
//            while ( head_s != NULL  && ((x = pop(&head_s)).buffer[0] != '(')) {
//                add_back_list(&postfix_str, x);
//                // printf("%s\n", x.buffer);
//            }
//        } else {
//            Lexem pred = cur->prev->data;
//            if (i > 0) {
//
//                if (pred.type == bracket || head_s == NULL) {
//                    head_s = push(head_s, cur->data);
//
//                } else {
//                    Lexem pred_s = pop(&head_s);
//                    head_s = push(head_s, pred_s);
//                    //printf ("%s---%s\n",pred_s.buffer, c.buffer);
//                    while (head_s != NULL && pred_s.priotity <= c.priotity && pred_s.type != bracket) {
//                        printf ("%s---%s\n",pred_s.buffer, c.buffer);
//                        pred_s = pop(&head_s);
//
//                        if (head_s != NULL) {
//                            pred_s = pop(&head_s);
//                            head_s = push(head_s, pred_s);
//                        }
//
//                        // printf("x = %d", x.buffer[0]);
//                        add_back_list(&postfix_str, pred_s);
//                    }
//                    head_s = push(head_s, cur->data);
//                }
//            }
//        }
//        if (cur->next == NULL) {
//            while (head_s != NULL) {
//                x = pop(&head_s);
//                add_back_list(&postfix_str, x);
//                // printf("ost ");
//            }
//        }
//    }
//    destroy_list(head);
//    return postfix_str;
//}

// sin(x)
// cos(x)
// tan(x)
// ctg(x)
// sqrt(x)
// ln(x)

// void Count(List *postfix_str) {
//     Lexem stack;
//     Lexem x;
//     stack_node *head = init_stack(stack);
//     for (list_node* cur = head; cur != NULL; cur = cur->next){
//         int i;
//         for (i = 0; cur->data.buffer[i] != '\n'; i++){
//             Lexem c = cur->data;
//             if (cur->data.type == number){
//                 add(postfix_str, c);
//                 //printf("num ");
//             } else {
//                     switch (c.buffer[0])
//                 {
//                 case '+':
//                     printf("tt");
//                     break;

//                 case '-':
//                     printf("tt");
//                     break;

//                 case '*':
//                     printf("tt");
//                     break;

//                  case '^':
//                     printf("tt");
//                     break;
//                 case 'cosx':
//                     printf("tt");
//                     break;

//                 case 'costyu':
//                     printf("tt");
//                     break;

//                 default:
//                     break;
//                 }
//             }

//         }
//     }
// }