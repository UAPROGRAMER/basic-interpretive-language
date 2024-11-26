#include "lib/main.hpp"

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "[ERROR|MAIN]: not enought arguments.\n";
        return 1;
    }

    string sourcecode;

    try
    {sourcecode = readfile(argv[1]);}
    catch (...)
    {return 1;}

    vector<unique_ptr<Token>> tokens;

    try
    {tokens = tokenize(sourcecode);}
    catch (...)
    {return 1;}

    vector<unique_ptr<AstNode>> astTree;

    try
    {astTree = parse(tokens);}
    catch (...)
    {return 1;}

    print_tokens(tokens);
    print_ast_tree(astTree);
    
    return 0;
}

string readfile(char* filepath)
{
    fstream filestream (filepath);

    if (!filestream)
    {
        std::cerr << "[ERROR|MAIN]: unable to access file (" << filepath << ").\n";
        throw std::exception();
    }

    stringstream sourcecode;

    sourcecode << filestream.rdbuf();

    return sourcecode.str();
}