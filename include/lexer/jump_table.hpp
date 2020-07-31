#ifndef JUMP_TABLE_HPP
#define JUMP_TABLE_HPP
#include <map>
#include <utility>
#include "token.hpp"
enum JumpState
{
    START,
    STATE1,
    STATE2,
    STATE3,
    STATE4,
    STATE5,
    STATE6,
    STATE7,
    STATE8,
    STATE9,
    STATE10,
    STATE11, // 注释状态
    STATE12, // 注释状态
    STATE13, // 注释状态
    STATE14, //注释状态
    NO_TOKEN,
    CHECK_KEYWORD,
    TOK_INTEGER,
    TOK_FLOAT_POINT,
    TOK_COMMA,
    TOK_DOT,
    TOK_SEMI,
    TOK_EQUAL,
    TOK_ASSIGN,
    TOK_PARENTHESES_L,
    TOK_PARENTHESES_R,
    TOK_BRACKET_L,
    TOK_BRACKET_R,
    TOK_BRACE_L,
    TOK_BRACE_R,
    TOK_ANGLE_BRACKET_L,
    TOK_ANGLE_BRACKET_R,
    TOK_MOVE_L,
    TOK_MOVE_R,
    TOK_ADD,
    TOK_SUB,
    TOK_MUL,
    TOK_DIV,
    TOK_INCREASE,
    TOK_DECREASE,
    TOK_ASSIGN_ADD,
    TOK_ASSIGN_SUB,
    TOK_ASSIGN_MUL,
    TOK_ASSIGN_DIV
};

/**
 * @brief 状态跳转表
 */
static std::map<std::pair<JumpState, CharType>, JumpState> JUMP_TABLE = {
    {{JumpState::START, CharType::ALPHA}, JumpState::STATE1},
    {{JumpState::START, CharType::UNDERLINE}, JumpState::STATE1},
    {{JumpState::START, CharType::DIGIT}, JumpState::STATE2},
    {{JumpState::START, CharType::SPACE}, JumpState::NO_TOKEN},
    {{JumpState::START, CharType::CT_EOF}, JumpState::NO_TOKEN},
    {{JumpState::START, CharType::ENTER}, JumpState::NO_TOKEN},
    {{JumpState::START, CharType::CT_COMMA}, JumpState::TOK_COMMA},
    {{JumpState::START, CharType::CT_DOT}, JumpState::TOK_DOT},
    {{JumpState::START, CharType::CT_SEMI}, JumpState::TOK_SEMI},
    {{JumpState::START, CharType::CT_ASSIGN}, JumpState::STATE4},
    {{JumpState::START, CharType::CT_PARENTHESES_L}, JumpState::TOK_PARENTHESES_L},
    {{JumpState::START, CharType::CT_PARENTHESES_R}, JumpState::TOK_PARENTHESES_R},
    {{JumpState::START, CharType::CT_BRACKET_L}, JumpState::TOK_BRACKET_L},
    {{JumpState::START, CharType::CT_BRACKET_R}, JumpState::TOK_BRACKET_R},
    {{JumpState::START, CharType::CT_BRACE_L}, JumpState::TOK_BRACE_L},
    {{JumpState::START, CharType::CT_BRACE_R}, JumpState::TOK_BRACE_R},
    {{JumpState::START, CharType::CT_ANGLE_BRACKET_L}, JumpState::STATE5},
    {{JumpState::START, CharType::CT_ANGLE_BRACKET_R}, JumpState::STATE6},
    {{JumpState::START, CharType::CT_ADD}, JumpState::STATE7},
    {{JumpState::START, CharType::CT_SUB}, JumpState::STATE8},
    {{JumpState::START, CharType::CT_MUL}, JumpState::STATE9},
    {{JumpState::START, CharType::CT_DIV}, JumpState::STATE10},

    {{JumpState::STATE1, CharType::ALPHA}, JumpState::STATE1},
    {{JumpState::STATE1, CharType::UNDERLINE}, JumpState::STATE1},
    {{JumpState::STATE1, CharType::DIGIT}, JumpState::STATE1},
    {{JumpState::STATE1, CharType::SPACE}, JumpState::CHECK_KEYWORD},
    {{JumpState::STATE1, CharType::ENTER}, JumpState::CHECK_KEYWORD},
    {{JumpState::STATE1, CharType::CT_EOF}, JumpState::CHECK_KEYWORD},
    {{JumpState::STATE1, CharType::CT_COMMA}, JumpState::CHECK_KEYWORD},
    {{JumpState::STATE1, CharType::CT_DOT}, JumpState::CHECK_KEYWORD},
    {{JumpState::STATE1, CharType::CT_SEMI}, JumpState::CHECK_KEYWORD},
    {{JumpState::STATE1, CharType::CT_ASSIGN}, JumpState::CHECK_KEYWORD},
    {{JumpState::STATE1, CharType::CT_PARENTHESES_L}, JumpState::CHECK_KEYWORD},
    {{JumpState::STATE1, CharType::CT_PARENTHESES_R}, JumpState::CHECK_KEYWORD},
    {{JumpState::STATE1, CharType::CT_BRACKET_L}, JumpState::CHECK_KEYWORD},
    {{JumpState::STATE1, CharType::CT_BRACKET_R}, JumpState::CHECK_KEYWORD},
    {{JumpState::STATE1, CharType::CT_BRACE_L}, JumpState::CHECK_KEYWORD},
    {{JumpState::STATE1, CharType::CT_ANGLE_BRACKET_L}, JumpState::CHECK_KEYWORD},
    {{JumpState::STATE1, CharType::CT_ANGLE_BRACKET_R}, JumpState::CHECK_KEYWORD},
    {{JumpState::STATE1, CharType::CT_ADD}, JumpState::CHECK_KEYWORD},
    {{JumpState::STATE1, CharType::CT_SUB}, JumpState::CHECK_KEYWORD},
    {{JumpState::STATE1, CharType::CT_MUL}, JumpState::CHECK_KEYWORD},
    {{JumpState::STATE1, CharType::CT_DIV}, JumpState::CHECK_KEYWORD},

    {{JumpState::STATE2, CharType::DIGIT}, JumpState::STATE2},
    {{JumpState::STATE2, CharType::SPACE}, JumpState::TOK_INTEGER},
    {{JumpState::STATE2, CharType::ENTER}, JumpState::TOK_INTEGER},
    {{JumpState::STATE2, CharType::CT_EOF}, JumpState::TOK_INTEGER},
    {{JumpState::STATE2, CharType::CT_COMMA}, JumpState::TOK_INTEGER},
    {{JumpState::STATE2, CharType::CT_SEMI}, JumpState::TOK_INTEGER},
    {{JumpState::STATE2, CharType::CT_PARENTHESES_R}, JumpState::TOK_INTEGER},
    {{JumpState::STATE2, CharType::CT_BRACKET_R}, JumpState::TOK_INTEGER},
    {{JumpState::STATE2, CharType::CT_ANGLE_BRACKET_R}, JumpState::TOK_INTEGER},
    {{JumpState::STATE2, CharType::CT_ADD}, JumpState::TOK_INTEGER},
    {{JumpState::STATE2, CharType::CT_SUB}, JumpState::TOK_INTEGER},
    {{JumpState::STATE2, CharType::CT_MUL}, JumpState::TOK_INTEGER},
    {{JumpState::STATE2, CharType::CT_DIV}, JumpState::TOK_INTEGER},
    {{JumpState::STATE2, CharType::CT_DOT}, JumpState::STATE3},

    {{JumpState::STATE3, CharType::DIGIT}, JumpState::STATE3},
    {{JumpState::STATE3, CharType::SPACE}, JumpState::TOK_FLOAT_POINT},
    {{JumpState::STATE3, CharType::ENTER}, JumpState::TOK_FLOAT_POINT},
    {{JumpState::STATE3, CharType::CT_EOF}, JumpState::TOK_FLOAT_POINT},
    {{JumpState::STATE3, CharType::CT_COMMA}, JumpState::TOK_FLOAT_POINT},
    {{JumpState::STATE3, CharType::CT_SEMI}, JumpState::TOK_FLOAT_POINT},
    {{JumpState::STATE3, CharType::CT_PARENTHESES_R}, JumpState::TOK_FLOAT_POINT},
    {{JumpState::STATE3, CharType::CT_ADD}, JumpState::TOK_FLOAT_POINT},
    {{JumpState::STATE3, CharType::CT_SUB}, JumpState::TOK_FLOAT_POINT},
    {{JumpState::STATE3, CharType::CT_MUL}, JumpState::TOK_FLOAT_POINT},
    {{JumpState::STATE3, CharType::CT_DIV}, JumpState::TOK_FLOAT_POINT},

    {{JumpState::STATE4, CharType::CT_ASSIGN}, JumpState::TOK_EQUAL},
    {{JumpState::STATE4, CharType::SPACE}, JumpState::TOK_ASSIGN},
    {{JumpState::STATE4, CharType::ENTER}, JumpState::TOK_ASSIGN},
    {{JumpState::STATE4, CharType::ALPHA}, JumpState::TOK_ASSIGN},
    {{JumpState::STATE4, CharType::UNDERLINE}, JumpState::TOK_ASSIGN},
    {{JumpState::STATE4, CharType::DIGIT}, JumpState::TOK_ASSIGN},
    {{JumpState::STATE4, CharType::CT_PARENTHESES_L}, JumpState::TOK_ASSIGN},
    {{JumpState::STATE4, CharType::CT_BRACKET_L}, JumpState::TOK_ASSIGN},

    {{JumpState::STATE5, CharType::SPACE}, JumpState::TOK_ANGLE_BRACKET_L},
    {{JumpState::STATE5, CharType::ENTER}, JumpState::TOK_ANGLE_BRACKET_L},
    {{JumpState::STATE5, CharType::ALPHA}, JumpState::TOK_ANGLE_BRACKET_L},
    {{JumpState::STATE5, CharType::UNDERLINE}, JumpState::TOK_ANGLE_BRACKET_L},
    {{JumpState::STATE5, CharType::DIGIT}, JumpState::TOK_ANGLE_BRACKET_L},
    {{JumpState::STATE5, CharType::CT_PARENTHESES_L}, JumpState::TOK_ANGLE_BRACKET_L},
    {{JumpState::STATE5, CharType::CT_ANGLE_BRACKET_L}, JumpState::TOK_MOVE_L},

    {{JumpState::STATE6, CharType::SPACE}, JumpState::TOK_ANGLE_BRACKET_R},
    {{JumpState::STATE6, CharType::ENTER}, JumpState::TOK_ANGLE_BRACKET_R},
    {{JumpState::STATE6, CharType::ALPHA}, JumpState::TOK_ANGLE_BRACKET_R},
    {{JumpState::STATE6, CharType::UNDERLINE}, JumpState::TOK_ANGLE_BRACKET_R},
    {{JumpState::STATE6, CharType::CT_PARENTHESES_L}, JumpState::TOK_ANGLE_BRACKET_R},
    {{JumpState::STATE6, CharType::CT_COMMA}, JumpState::TOK_ANGLE_BRACKET_R},
    {{JumpState::STATE6, CharType::CT_ANGLE_BRACKET_R}, JumpState::TOK_MOVE_R},

    {{JumpState::STATE7, CharType::SPACE}, JumpState::TOK_ADD},
    {{JumpState::STATE7, CharType::ENTER}, JumpState::TOK_ADD},
    {{JumpState::STATE7, CharType::ALPHA}, JumpState::TOK_ADD},
    {{JumpState::STATE7, CharType::DIGIT}, JumpState::TOK_ADD},
    {{JumpState::STATE7, CharType::UNDERLINE}, JumpState::TOK_ADD},
    {{JumpState::STATE7, CharType::CT_PARENTHESES_L}, JumpState::TOK_ADD},
    {{JumpState::STATE7, CharType::CT_ADD}, JumpState::TOK_INCREASE},
    {{JumpState::STATE7, CharType::CT_ASSIGN}, JumpState::TOK_ASSIGN_ADD},

    {{JumpState::STATE8, CharType::SPACE}, JumpState::TOK_SUB},
    {{JumpState::STATE8, CharType::ENTER}, JumpState::TOK_SUB},
    {{JumpState::STATE8, CharType::ALPHA}, JumpState::TOK_SUB},
    {{JumpState::STATE8, CharType::DIGIT}, JumpState::TOK_SUB},
    {{JumpState::STATE8, CharType::UNDERLINE}, JumpState::TOK_SUB},
    {{JumpState::STATE8, CharType::CT_PARENTHESES_L}, JumpState::TOK_SUB},
    {{JumpState::STATE8, CharType::CT_SUB}, JumpState::TOK_DECREASE},
    {{JumpState::STATE8, CharType::CT_ASSIGN}, JumpState::TOK_ASSIGN_SUB},

    {{JumpState::STATE9, CharType::SPACE}, JumpState::TOK_MUL},
    {{JumpState::STATE9, CharType::ENTER}, JumpState::TOK_MUL},
    {{JumpState::STATE9, CharType::ALPHA}, JumpState::TOK_MUL},
    {{JumpState::STATE9, CharType::DIGIT}, JumpState::TOK_MUL},
    {{JumpState::STATE9, CharType::UNDERLINE}, JumpState::TOK_MUL},
    {{JumpState::STATE9, CharType::CT_PARENTHESES_L}, JumpState::TOK_MUL},
    {{JumpState::STATE9, CharType::CT_ASSIGN}, JumpState::TOK_ASSIGN_MUL},

    {{JumpState::STATE10, CharType::SPACE}, JumpState::TOK_DIV},
    {{JumpState::STATE10, CharType::ENTER}, JumpState::TOK_DIV},
    {{JumpState::STATE10, CharType::ALPHA}, JumpState::TOK_DIV},
    {{JumpState::STATE10, CharType::DIGIT}, JumpState::TOK_DIV},
    {{JumpState::STATE10, CharType::UNDERLINE}, JumpState::TOK_DIV},
    {{JumpState::STATE10, CharType::CT_PARENTHESES_L}, JumpState::TOK_DIV},
    {{JumpState::STATE10, CharType::CT_ASSIGN}, JumpState::TOK_ASSIGN_DIV},
    {{JumpState::STATE10, CharType::CT_MUL}, JumpState::STATE11},
    {{JumpState::STATE10, CharType::CT_DIV}, JumpState::STATE13},

    {{JumpState::STATE11, CharType::CT_MUL}, JumpState::STATE12},
    {{JumpState::STATE11, CharType::CT_DEFAULT}, JumpState::STATE11},
    {{JumpState::STATE11, CharType::ALPHA}, JumpState::STATE11},
    {{JumpState::STATE11, CharType::UNDERLINE}, JumpState::STATE11},
    {{JumpState::STATE11, CharType::DIGIT}, JumpState::STATE11},
    {{JumpState::STATE11, CharType::SPACE}, JumpState::STATE11},
    {{JumpState::STATE11, CharType::ENTER}, JumpState::STATE11},
    {{JumpState::STATE11, CharType::CT_EOF}, JumpState::STATE11},
    {{JumpState::STATE11, CharType::CT_COMMA}, JumpState::STATE11},
    {{JumpState::STATE11, CharType::CT_DOT}, JumpState::STATE11},
    {{JumpState::STATE11, CharType::CT_SEMI}, JumpState::STATE11},
    {{JumpState::STATE11, CharType::CT_ASSIGN}, JumpState::STATE11},
    {{JumpState::STATE11, CharType::CT_PARENTHESES_L}, JumpState::STATE11},
    {{JumpState::STATE11, CharType::CT_PARENTHESES_R}, JumpState::STATE11},
    {{JumpState::STATE11, CharType::CT_BRACKET_L}, JumpState::STATE11},
    {{JumpState::STATE11, CharType::CT_BRACKET_R}, JumpState::STATE11},
    {{JumpState::STATE11, CharType::CT_BRACE_L}, JumpState::STATE11},
    {{JumpState::STATE11, CharType::CT_BRACE_R}, JumpState::STATE11},
    {{JumpState::STATE11, CharType::CT_ANGLE_BRACKET_L}, JumpState::STATE11},
    {{JumpState::STATE11, CharType::CT_ANGLE_BRACKET_R}, JumpState::STATE11},
    {{JumpState::STATE11, CharType::CT_ADD}, JumpState::STATE11},
    {{JumpState::STATE11, CharType::CT_SUB}, JumpState::STATE11},
    {{JumpState::STATE11, CharType::CT_DIV}, JumpState::STATE11},

    {{JumpState::STATE12, CharType::CT_DIV}, JumpState::START},
    {{JumpState::STATE12, CharType::CT_DEFAULT}, JumpState::STATE11},
    {{JumpState::STATE12, CharType::ALPHA}, JumpState::STATE11},
    {{JumpState::STATE12, CharType::UNDERLINE}, JumpState::STATE11},
    {{JumpState::STATE12, CharType::DIGIT}, JumpState::STATE11},
    {{JumpState::STATE12, CharType::SPACE}, JumpState::STATE11},
    {{JumpState::STATE12, CharType::ENTER}, JumpState::STATE11},
    {{JumpState::STATE12, CharType::CT_EOF}, JumpState::STATE11},
    {{JumpState::STATE12, CharType::CT_COMMA}, JumpState::STATE11},
    {{JumpState::STATE12, CharType::CT_DOT}, JumpState::STATE11},
    {{JumpState::STATE12, CharType::CT_SEMI}, JumpState::STATE11},
    {{JumpState::STATE12, CharType::CT_ASSIGN}, JumpState::STATE11},
    {{JumpState::STATE12, CharType::CT_PARENTHESES_L}, JumpState::STATE11},
    {{JumpState::STATE12, CharType::CT_PARENTHESES_R}, JumpState::STATE11},
    {{JumpState::STATE12, CharType::CT_BRACKET_L}, JumpState::STATE11},
    {{JumpState::STATE12, CharType::CT_BRACKET_R}, JumpState::STATE11},
    {{JumpState::STATE12, CharType::CT_BRACE_L}, JumpState::STATE11},
    {{JumpState::STATE12, CharType::CT_BRACE_R}, JumpState::STATE11},
    {{JumpState::STATE12, CharType::CT_ANGLE_BRACKET_L}, JumpState::STATE11},
    {{JumpState::STATE12, CharType::CT_ANGLE_BRACKET_R}, JumpState::STATE11},
    {{JumpState::STATE12, CharType::CT_ADD}, JumpState::STATE11},
    {{JumpState::STATE12, CharType::CT_SUB}, JumpState::STATE11},
    {{JumpState::STATE12, CharType::CT_MUL}, JumpState::STATE11}

};

#endif