#ifndef __LEXER_HPP__
#define __LEXER_HPP__

#include "includes.hpp"
#include "token.hpp"

class Lexer
{
    private:

    const string sourcecode;
    char current;
    size_t index;
    size_t size;

    size_t column;
    size_t line;
    size_t token_column;
    size_t token_line;

    public:

    Lexer(string _sourcecode):
        sourcecode(_sourcecode),
        current('\0'),
        index((size_t)-1),
        size(_sourcecode.size()),
        column(0),
        line(1),
        token_column(column),
        token_line(line)
    {
        advance();
    }

    void advance();

    unique_ptr<Token> new_token(TokenType type, string value = "") const;

    vector<unique_ptr<Token>> tokenize();

    unique_ptr<Token> next_token();

    unique_ptr<Token> tokenize_id();

    unique_ptr<Token> tokenize_int();
};

#endif