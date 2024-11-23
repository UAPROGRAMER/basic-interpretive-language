#include "lib/lexer.hpp"

void Lexer::advance()
{
    current = (++index<size) ? sourcecode.at(index) : '\0';
    column++;
    if (current == '\n')
    {
        line++;
        column = 0;
    }
}

unique_ptr<Token> Lexer::new_token(TokenType type, string value) const
{
    return make_unique_token(type, token_column, token_line, value);
}

vector<unique_ptr<Token>> Lexer::tokenize()
{
    vector<unique_ptr<Token>> tokens;
    unique_ptr<Token> token = next_token();

    while (token->type != TOKEN_NOOP)
    {
        tokens.push_back(move(token));
        token = next_token();
        if (token->type == TOKEN_ERROR)
        {
            tokens.clear();
            return tokens;
        }
    }
    
    tokens.push_back(move(token));

    return tokens;
}

unique_ptr<Token> Lexer::next_token()
{
    unique_ptr<Token> token;

    token_column = column;
    token_line = line;

    validation:

    while (current == ' ' || current == '\n' || current == '\t')
        advance();
    
    if (current == '#')
    {
        while (current != '\n' && current != '\0')
            advance();
        goto validation;
    }

    if (current == '\0')
        return new_token(TOKEN_NOOP);
    

    if (isalpha(current) || current == '_')
        return tokenize_id();
    else if (isdigit(current))
        return tokenize_int();


    switch (current)
    {
        case '=':
            token = new_token(TOKEN_EQUAL);
            break;
        case ';':
            token = new_token(TOKEN_SEMI);
            break;
        default:
            std::cerr << "[ERROR|LEXER]: unvalid character at " << column << ':' << line << ".\n";
            token = new_token(TOKEN_ERROR);
            break;
    }

    advance();

    return token;
}

unique_ptr<Token> Lexer::tokenize_id()
{
    stringstream valuebuff;
    string value;

    while (isalnum(current) || current == '_')
    {
        valuebuff << current;
        advance();
    }

    value = valuebuff.str();

    for (string keyword : TokenKeywords)
        if (value == keyword)
            return new_token(TOKEN_KEYWORD, value);

    return new_token(TOKEN_ID, value);
}

unique_ptr<Token> Lexer::tokenize_int()
{
    stringstream valuebuff;

    while (isdigit(current))
    {
        valuebuff << current;
        advance();
    }

    return new_token(TOKEN_INT, valuebuff.str());
}