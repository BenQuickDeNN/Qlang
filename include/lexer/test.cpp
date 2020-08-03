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
    return 0;
}
void test1()
{
    string testStr =
        "/**\n\
          * @author benquick\n\
          * @brief lexer\n\
        */\n\
    template<typname type> type func(type &param_1, type &param_2)\n\
    {\n\
    \tint ret_val = param_1 << param_2 == param_1 >> param_2;\n\
    \treturn ret_val; // return the value \n\
    }\n\
    int a = 0;\n\
    /* kernel */\n\
    for (int i = 0; i <= _size && i >=0 || i ==20; i++)\n\
    {\n\
    \ta = (int)func<float>(2 + 1.54 * 6.0 - 4.568, 1.25);\n\
    \ta *= 2.4;\n\
    \ta /= 1.0 +2.35 / 20;\n\
    \ta &=100;\n\
    \tif (i >= 5)\n\
    \t\ta += 5.5;\n\
    \ta |= 200;\n\
    \ta = a | 500;\n\
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
        case TokType::AND:
            cout << "AND";
            break;
        case TokType::OR:
            cout << "OR";
            break;
        case TokType::INCREASE:
            cout << "INCREASE";
            break;
        case TokType::DECREASE:
            cout << "DECREASE";
            break;
        case TokType::BOOL_AND:
            cout << "BOOL_AND";
            break;
        case TokType::BOOL_OR:
            cout << "BOOL_OR";
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
        case TokType::ASSIGN_AND:
            cout << "ASSIGN_AND";
            break;
        case TokType::ASSIGN_OR:
            cout << "ASSIGN_OR";
            break;
        case TokType::LEQ:
            cout << "LEQ";
            break;
        case TokType::GEQ:
            cout << "GEQ";
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