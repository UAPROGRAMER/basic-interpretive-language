#ifndef __AST_HPP__
#define __AST_HPP__

#include "includes.hpp"
#include "token.hpp"
#include "lexer.hpp"

typedef enum
{
    AST_VARDEF,
    AST_VARSET,
    AST_VARCAL,
    AST_INT,
    AST_RETURN
} AstType;

class AstNode
{
    public:

    AstType type;

    virtual ~AstNode() = default;
};

class AstVardef : public AstNode
{
    public:

    AstType type;

    string name;
    unique_ptr<AstNode> value;

    AstVardef(string _name, unique_ptr<AstNode> _value):
        type(AST_VARDEF),
        name(_name),
        value(move(_value))
    {}
};

class AstVarset : public AstNode
{
    public:

    AstType type;

    string name;
    unique_ptr<AstNode> value;

    AstVarset(string _name, unique_ptr<AstNode> _value):
        type(AST_VARSET),
        name(_name),
        value(move(_value))
    {}
};

class AstVarcal : public AstNode
{
    public:

    AstType type;

    string name;

    AstVarcal(string _name):
        type(AST_VARCAL),
        name(_name)
    {}
};

class AstInt : public AstNode
{
    public:

    AstType type;

    long value;

    AstInt(long _value):
        value(_value)
    {}
};

class AstReturn : public AstNode
{
    public:

    AstType type;

    unique_ptr<AstNode> value;

    AstReturn(unique_ptr<AstNode> _value):
        value(move(_value))
    {}
};

unique_ptr<AstNode> make_unique_ast(AstNode* astnode);

#endif