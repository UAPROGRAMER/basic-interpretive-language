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

    virtual void print() const = 0;
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

    void print() const
    {
        std::cout << "(type: " << type << ", name: " << name << ", value: ";
        value->print();
        std::cout << ")";
    }
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

    void print() const
    {
        std::cout << "(type: " << type << ", name: " << name << ", value: ";
        value->print();
        std::cout << ")";
    }
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

    void print() const
    {
        std::cout << "(type: " << type << ", name: " << name << ")";
    }
};

class AstInt : public AstNode
{
    public:

    AstType type;

    long value;

    AstInt(long _value):
        value(_value)
    {}

    void print() const 
    {
        std::cout << "(type: " << type << ", value: " << value << ")";
    }
};

class AstReturn : public AstNode
{
    public:

    AstType type;

    unique_ptr<AstNode> value;

    AstReturn(unique_ptr<AstNode> _value):
        type(AST_RETURN),
        value(move(_value))
    {}

    void print() const
    {
        std::cout << "(type: " << type << ", value: ";
        value->print();
        std::cout << ")";
    }
};

unique_ptr<AstNode> make_unique_ast(AstNode* astnode);

void print_ast_tree(vector<unique_ptr<AstNode>>& astTree);

#endif