
#include "parser.hh"

class PrecedenceClimbingParser : public ExprParser {
    public:
    PrecedenceClimbingParser(const std::string expr) : ExprParser(expr), tok_(0) {}

    void Parse();
    private:
    ExprParser::Token * tok_;
    void NextToken();
    double Atom();
    double Expression(int min_prec);
};

