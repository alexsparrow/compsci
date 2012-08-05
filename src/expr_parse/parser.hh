#include <string>
#ifndef PARSER_HH
#define PARSER_HH

#include <map>

class ExprParser {
    std::string in_;
    int pos_;

    protected:
    enum TokenType {
        TOK_NUM,
        TOK_OP,
        TOK_OPEN_PAREN,
        TOK_CLOSE_PAREN
    };

    enum AssocType {
        ASSOC_LEFT,
        ASSOC_RIGHT
    };

    std::map<char, std::pair<int, AssocType> > op_info;

    struct Token {
        TokenType type;
        std::string val;

        Token(TokenType t, std::string s = "") : type(t), val(s) {}
    };

    public:
    ExprParser(const std::string s);
    void PrintParseStatus();
    Token* GetToken();
    virtual void Parse() = 0;
};
#endif    
