#include "lib/ast.hpp"

unique_ptr<AstNode> make_unique_ast(AstNode* astnode)
{
    return unique_ptr<AstNode>(astnode);
}