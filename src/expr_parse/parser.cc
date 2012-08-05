#include <cctype>
#include <sstream>
#include <iostream>
#include <utility>

#include "parser.hh"

void ExprParser::PrintParseStatus(){
    std::cout << in_ << "\n";
    for(int i = 0 ; i < pos_ ; ++i) std::cout << " ";
    std::cout << "^\n";
}

ExprParser::Token* ExprParser::GetToken(){
    if(pos_ == in_.size()) return 0;

    int c = in_[pos_++];

    while(isspace(c) && pos_ < in_.size()) c = in_[pos_++];
    std::stringstream ss; 
    switch(c){
        case 43:
        case 45:
        case 42:
        case 47:
            ss.put(c);
            return new Token(TOK_OP, ss.str()); 
        case 40:
            return new Token(TOK_OPEN_PAREN);
        case 41:
            return new Token(TOK_CLOSE_PAREN);
        default:
            if(isdigit(c)){
                std::stringstream ss;
                ss.put(c);
                for(;;){ 
                    c = in_[pos_++];
                    if(isdigit(c) || c == 46) ss.put(c);
                    else break;
                }
                pos_--;
                return new Token(TOK_NUM, ss.str()); 
            }
            else std::cout << "Unrecognised character: " << c;
    }
}

ExprParser::ExprParser(const std::string s) : in_(s), pos_(0) {
    op_info['+'] = std::make_pair(1, ASSOC_LEFT);
    op_info['-'] = std::make_pair(1, ASSOC_LEFT);
    op_info['*'] = std::make_pair(2, ASSOC_LEFT);
    op_info['/'] = std::make_pair(2, ASSOC_LEFT);
}


