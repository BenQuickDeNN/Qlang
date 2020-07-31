#include <string>
#include <iostream>
#include "lexer.hpp"
#include "token.hpp"
using namespace std;
void test1();
void test2();
int main()
{
    test1();
    // test2();
    return 0;
}
void test1()
{
    string testStr =
        "template<typname type> type func(type param_1, type param_2)\n\
    {\n\
    \tint ret_val = param_1 << param_2 == param_1 >> param_2; return ret_val;  \n\
    }\n\
    int a = 0;\n\
    for (int i = 0; i < _size; i++)\n\
    {\n\
    \ta = func<int, float>(2 + 1.54 * 6.0 - 4.568);\n\
    \ta *= 2.4;\n\
    \ta /= 1.0 +2.35 / 20;\n\
    }";
    vector<Token> tokens = Lexer::lexStr(testStr);
    for (const Token &t : tokens)
    {
        cout << t.getTokStr() << '\t';
        switch (t.getTokType())
        {
        case TokType::KEY_WORD:
            cout << "KEY_WORD";
            break;
        case TokType::NAME:
            cout << "NAME";
            break;
        case TokType::INTEGER:
            cout << "INTEGER";
            break;
        case TokType::FLOAT_POINT:
            cout << "FLOAT_POINT";
            break;
        case TokType::TT_COMMA:
            cout << "COMMA";
            break;
        case TokType::TT_DOT:
            cout << "DOT";
            break;
        case TokType::TT_SEMI:
            cout << "SEMI";
            break;
        case TokType::TT_ASSIGN:
            cout << "ASSIGN";
            break;
        case TokType::TT_EQUAL:
            cout << "EQUAL";
            break;
        case TokType::TT_PARENTHESES_L:
            cout << "PARENTHESES_L";
            break;
        case TokType::TT_PARENTHESES_R:
            cout << "PARENTHESES_R";
            break;
        case TokType::TT_BRACKET_L:
            cout << "BRACKET_L";
            break;
        case TokType::TT_BRACKET_R:
            cout << "BRACKET_R";
            break;
        case TokType::TT_BRACE_L:
            cout << "BRACE_L";
            break;
        case TokType::TT_BRACE_R:
            cout << "BRACE_R";
            break;
        case TokType::TT_ANGLE_BRACKET_L:
            cout << "ANGLE_BRACKET_L";
            break;
        case TokType::TT_ANGLE_BRACKET_R:
            cout << "ANGLE_BRACKET_R";
            break;
        case TokType::MOVE_L:
            cout << "MOVE_L";
            break;
        case TokType::MOVE_R:
            cout << "MOVE_R";
            break;
        case TokType::ADD:
            cout << "ADD";
            break;
        case TokType::SUB:
            cout << "SUB";
            break;
        case TokType::MUL:
            cout << "MUL";
            break;
        case TokType::DIV:
            cout << "DIV";
            break;
        case TokType::INCREASE:
            cout << "INCREASE";
            break;
        case TokType::DECREASE:
            cout << "DECREASE";
            break;
        case TokType::ASSIGN_ADD:
            cout << "ASSIGN_ADD";
            break;
        case TokType::ASSIGN_SUB:
            cout << "ASSIGN_SUB";
            break;
        case TokType::ASSIGN_MUL:
            cout << "ASSIGN_MUL";
            break;
        case TokType::ASSIGN_DIV:
            cout << "ASSIGN_DIV";
            break;
        default:
            break;
        }
        cout << endl;
    }
}
void test2()
{
    cout << JUMP_TABLE[{JumpState::START, getCharType('h')}] << endl;
}