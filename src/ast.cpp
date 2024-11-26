#include "lib/ast.hpp"

unique_ptr<AstNode> make_unique_ast(AstNode* astnode)
{
    return unique_ptr<AstNode>(astnode);
}

void print_ast_tree(vector<unique_ptr<AstNode>>& astTree)
{
    size_t size = astTree.size();
    for (size_t i = 0; i < size; i++)
    {
        astTree.at(i)->print();
        std::cout << "\n";
    }
}