#include "lib/main.hpp"

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "[ERROR|MAIN]: not enought arguments.\n";
        return 1;
    }

    string sourcecode = readfile(argv[1]);

    if (sourcecode == "")
        return 1;
    
    Lexer lexer (sourcecode);

    vector<unique_ptr<Token>> tokens = lexer.tokenize();

    if (tokens.size() == 0)
        return 1;

    print_tokens(tokens); 
    
    return 0;
}

string readfile(char* filepath)
{
    fstream filestream (filepath);

    if (!filestream)
    {
        std::cerr << "[ERROR|MAIN]: unable to access file (" << filepath << ").\n";
        return "";
    }

    stringstream sourcecode;

    sourcecode << filestream.rdbuf();

    return sourcecode.str();
}