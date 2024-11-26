#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include "includes.hpp"
#include "token.hpp"
#include "lexer.hpp"
#include "ast.hpp"

class Parser
{
    private:

    vector<unique_ptr<Token>>& tokens;
    size_t index;
    Token* current;

    public:

    Parser(vector<unique_ptr<Token>>& _tokens):
        tokens(_tokens),
        index((size_t)-1),
        current(nullptr)
    {
        advance();
    }

    void advance();

    void check(TokenType type) const;

    void expect(TokenType type);

    vector<unique_ptr<AstNode>> parse();

    unique_ptr<AstNode> parse_statements();

    unique_ptr<AstNode> parse_int();

    unique_ptr<AstNode> parse_varcal();

    unique_ptr<AstNode> parse_expresion();

    unique_ptr<AstNode> parse_vardef();

    unique_ptr<AstNode> parse_varset();

    unique_ptr<AstNode> parse_return();
};

#endif