#include "precedence_climb.hh"
#include <iostream>
#include <cstdlib>

/* Advance to next token */
void PrecedenceClimbingParser::NextToken(){
    if(tok_)
        delete tok_;
    tok_ = GetToken();
}

/* Compute an atom input. Either a numeric constant or a bracketed subexpression */
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

/* Evaluate an expression for terms with precedence >= min_prec */
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

double PrecedenceClimbingParser::Evaluate(){
    NextToken();
    return Expression(1);
}

int main(int argc, char** argv){
    std::string inp;
    std::cout << "Give me an expression : ";
    getline(std::cin, inp);
    PrecedenceClimbingParser parser(inp);
    std::cout << "Answer = " << parser.Evaluate() << "\n";

}
