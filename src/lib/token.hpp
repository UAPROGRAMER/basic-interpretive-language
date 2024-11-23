#ifndef __TOKEN_HPP__
#define __TOKEN_HPP__

#include "includes.hpp"

typedef enum
{
    TOKEN_ID,
    TOKEN_KEYWORD,
    TOKEN_INT,
    TOKEN_EQUAL,
    TOKEN_SEMI,
    TOKEN_NOOP,
    TOKEN_ERROR
} TokenType;

static const vector<string> TokenKeywords = {"var", "return", "print"};

class Token
{
    public:

    TokenType type;
    string value;

    size_t column;
    size_t line;

    Token(TokenType _type, size_t _column, size_t _line, string _value = ""):
        type(_type),
        value(_value),
        column(_column),
        line(_line) 
    {}
    
    string gettypestr() const;

    void print() const;
};

unique_ptr<Token> make_unique_token(TokenType type, size_t column, size_t line, string value = "");

void print_tokens(vector<unique_ptr<Token>>& tokens);

#endif