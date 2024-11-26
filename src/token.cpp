#include "lib/token.hpp"

string Token::gettypestr() const
{
    if (type == TOKEN_ID)
        return "id";
    else if (type == TOKEN_KEYWORD)
        return "keyword";
    else if (type == TOKEN_INT)
        return "int";
    else if (type == TOKEN_EQUAL)
        return "equal";
    else if (type == TOKEN_SEMI)
        return "semi";
    else if (type == TOKEN_NOOP)
        return "noop";
    return "<error-type>";
}

void Token::print() const
{
    std::cout << '(' << gettypestr() << ", " << (value!="" ? value : string("null")) << ", " << column << ':' << line << ")\n";
}

unique_ptr<Token> make_unique_token(TokenType type, size_t column, size_t line, string value)
{
    return unique_ptr<Token>(new Token(type, column, line, value));
}

void print_tokens(vector<unique_ptr<Token>>& tokens)
{
    size_t size = tokens.size();
    for (size_t i = 0; i < size; i++)
        tokens.at(i)->print();
}