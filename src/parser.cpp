#include "lib/parser.hpp"

void Parser::advance()
{
    current = &*tokens.at(++index);
}

void Parser::check(TokenType type) const
{
    if (current->type != type)
    {
        std::cerr << "[ERROR|PARSER]: unexpected token ("
            << current->type
            << ", "
            << (current->value != "" ? current->value : "null")
            << ") at "
            << current->column
            << ':'
            << current->line
            << ".\n";
        throw std::exception();
    }
}

void Parser::expect(TokenType type)
{
    advance();
    check(type);
}

vector<unique_ptr<AstNode>> Parser::parse()
{
    vector<unique_ptr<AstNode>> astTree;

    while (current->type != TOKEN_NOOP)
        astTree.push_back(parse_statements());
    
    return astTree;
}

unique_ptr<AstNode> Parser::parse_statements()
{
    switch (current->type)
    {
        case TOKEN_KEYWORD:
            if (current->value == "var")
                return parse_vardef();
            else if (current->value == "return")
                return parse_return();
        case TOKEN_ID:
            return parse_varset();
        default:
            std::cerr << "[ERROR|PARSER]: unexpected token ("
                << current->type
                << ", "
                << (current->value != "" ? current->value : "null")
                << ") at "
                << current->column
                << ':'
                << current->line
                << ".\n";
            throw std::exception();
    }
}

unique_ptr<AstNode> Parser::parse_int()
{
    long value = stol(current->value);
    advance();
    return make_unique_ast(new AstInt(value));
}

unique_ptr<AstNode> Parser::parse_varcal()
{
    string name = current->value;
    advance();
    return make_unique_ast(new AstVarcal(name));
}

unique_ptr<AstNode> Parser::parse_expresion()
{
    switch (current->type)
    {
        case TOKEN_INT:
            return parse_int();
        case TOKEN_ID:
            return parse_varcal();
        default:
            std::cerr << "[ERROR|PARSER]: unexpected token ("
                << current->type
                << ", "
                << (current->value != "" ? current->value : "null")
                << ") at "
                << current->column
                << ':'
                << current->line
                << ".\n";
            throw std::exception();
    }
}

unique_ptr<AstNode> Parser::parse_vardef()
{
    expect(TOKEN_ID);
    string name = current->value;
    expect(TOKEN_EQUAL);
    advance();
    unique_ptr<AstNode> value = parse_expresion();
    check(TOKEN_SEMI);
    advance();
    return make_unique_ast(new AstVardef(name, move(value)));
}

unique_ptr<AstNode> Parser::parse_varset()
{
    string name = current->value;
    expect(TOKEN_EQUAL);
    advance();
    unique_ptr<AstNode> value = parse_expresion();
    check(TOKEN_SEMI);
    advance();
    return make_unique_ast(new AstVarset(name, move(value)));
}

unique_ptr<AstNode> Parser::parse_return()
{
    advance();
    unique_ptr<AstNode> value = parse_expresion();
    check(TOKEN_SEMI);
    advance();
    return make_unique_ast(new AstReturn(move(value)));
}