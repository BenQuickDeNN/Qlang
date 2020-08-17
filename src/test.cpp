#include <iostream>
#include <string>
#include "file/file.hpp"
#include "scope/scope.hpp"
#include "lexer/lexer.hpp"
#include "parser/parser.hpp"

using namespace std;

void test1();
int main()
{
    test1();
    return 0;
}
void test1()
{
    string text = readStrFromFile("examples/simple-1.cpp");
    auto scopes = getScopes(text);
    for (const auto &scope : scopes)
    {
        cout << "scope {" << endl << scope << endl << "} endscope" << endl;
        auto tokens = Lexer::lexStr(scope);
        cout << "tokens:" << endl;
        for (const Token &tok : tokens)
            std::cout << "toktype = " << tok.getTokType() 
                << ", tokval = " << tok.getTokStr() << endl;
        auto ast = BuildAST(tokens);
    }
}