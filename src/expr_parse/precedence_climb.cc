#include "precedence_climb.hh"
#include <iostream>
#include <cstdlib>

void PrecedenceClimbingParser::NextToken(){
    if(tok_)
        delete tok_;
    tok_ = GetToken();
}

double PrecedenceClimbingParser::Atom(){
    std::cout << "Atom: " << tok_->val << "\n";
    PrintParseStatus();
    double val;
    if(tok_ == 0){
        std::cout << "Source ended unexpectedly\n";
        return 0;
    }
    switch(tok_->type){
        case ExprParser::TOK_OPEN_PAREN:
            NextToken();
            val = Expression(1);
            if(tok_->type != ExprParser::TOK_CLOSE_PAREN){
                std::cout << "Unmatched (\n";
                return 0;
            }
            NextToken();
            return val;
        case ExprParser::TOK_OP:
            std::cout << "Expected an atom not operator\n";
            return 0;
        default:
            val = atof(tok_->val.c_str());
            NextToken();
            return val; 
    }
}

double PrecedenceClimbingParser::Expression(int min_prec){
    std::cout << "Expr: " << tok_->val << " " << min_prec << std::endl;
    PrintParseStatus();
    double lhs = Atom();
    for(;;){
        if(!tok_ || tok_->type != TOK_OP || op_info[tok_->val[0]].first < min_prec)
            break;
        char op = tok_->val[0];
        NextToken();
        double rhs = Expression(op_info[op].second == ASSOC_LEFT ? op_info[op].first + 1 : op_info[op].first);

        switch(op){
            case '+': lhs = lhs + rhs;
                      break;
            case '-': lhs = lhs - rhs;
                      break;
            case '*': lhs = lhs * rhs;
                      break;
            case '/': lhs = lhs / rhs;
                      break;
        }
    }
    return lhs;
}

void PrecedenceClimbingParser::Parse(){
    NextToken();
    std::cout << "Answer is: " << Expression(1) << "\n";
}

int main(int argc, char** argv){
    std::string inp;
    getline(std::cin, inp);
    PrecedenceClimbingParser parser(inp);
    parser.Parse();

}
