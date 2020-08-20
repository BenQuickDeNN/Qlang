#pragma once

#include <cstdint>
#include <map>
#include "ast_node.hpp"

template <typename type = uint64_t>
static const uint64_t getASTKey(const type tok)
{
    return last * tok;
}

template <typename type = uint64_t, typename... types>
static const uint64_t getASTKey(const type tok, const types... toks)
{
    return getASTKey(tok) + last * getASTKey(toks...);
}

// 生成规则表
static const std::map<uint64_t, uint64_t> GrammarMap = {
    // common
    {getASTKey(stmt_list), root},
    {getASTKey(stmt_list, stmt), stmt_list},
    {getASTKey(TT_BRACE_L, stmt_list, TT_BRACE_R), stmt_block},
    {getASTKey(stmt), stmt_list},
    {getASTKey(expr, TT_SEMI), stmt},
    {getASTKey(stmt_block), stmt},
    {getASTKey(forloop), stmt},
    {getASTKey(TT_SEMI), stmt},
    {getASTKey(stmt, TT_SEMI), stmt},
    
    // 基本表达式 1
    {getASTKey(expr, TT_DOT, expr), expr},
    {getASTKey(expr, COLON2, expr), expr},
    {getASTKey(expr, POINT_TO, expr), expr},
    {getASTKey(NAME), expr},
    {getASTKey(expr_const), expr},
    {getASTKey(expr_postfix, expr, TT_BRACKET_R), expr},
    {getASTKey(expr_decl), expr},
    // 常量表达式 1
    {getASTKey(KEY_CONST, expr), expr_const},
    {getASTKey(INTEGER), expr_const},
    {getASTKey(FLOAT_POINT), expr_const},

    // 后缀表达式 2
    {getASTKey(expr, TT_BRACKET_L), expr_postfix},
    {getASTKey(expr, INCREASE), expr},
    {getASTKey(expr, DECREASE), expr},

    // 一元运算表达式 3
    {getASTKey(INCREASE, expr), expr},
    {getASTKey(DECREASE, expr), expr},
    {getASTKey(NOT, expr), expr},
    {getASTKey(BOOL_NOT, expr), expr},

    // 强制类型表达式 4
    {getASTKey(TT_PARENTHESES_L, expr, TT_PARENTHESES_R), expr},

    // 乘除法 5
    {getASTKey(expr, MUL, expr), expr},
    {getASTKey(expr, DIV, expr), expr},
    {getASTKey(expr, MOD, expr), expr},

    // 加减法 6
    {getASTKey(expr, ADD, expr), expr},
    {getASTKey(expr, SUB, expr), expr},

    // 移位表达式 7
    {getASTKey(expr, MOVE_L, expr), expr},
    {getASTKey(expr, MOVE_R, expr), expr},

    // 关系运算表达式 8
    {getASTKey(expr, TT_ANGLE_BRACKET_L, expr), expr},
    {getASTKey(expr, TT_ANGLE_BRACKET_R, expr), expr},
    {getASTKey(expr, LEQ, expr), expr},
    {getASTKey(expr, GEQ, expr), expr},

    // 相等运算 9
    {getASTKey(expr, TT_EQUAL, expr), expr},
    {getASTKey(expr, TT_NOT_EQUAL, expr), expr},

    // 位与运算 10
    {getASTKey(expr, AND, expr), expr},

    // 位异或运算 11
    {getASTKey(expr, XOR, expr), expr},

    // 位或运算 12
    {getASTKey(expr, OR, expr), expr},

    // 逻辑与运算 13
    {getASTKey(expr, BOOL_AND, expr), expr},

    // 逻辑或运算 14
    {getASTKey(expr, BOOL_OR, expr), expr},

    // 三元条件运算 15
    {getASTKey(expr, TT_QUES, expr, COLON, expr), expr},

    // 赋值运算 16
    {getASTKey(expr, TT_ASSIGN, expr), expr},
    {getASTKey(expr, ASSIGN_ADD, expr), expr},
    {getASTKey(expr, ASSIGN_SUB, expr), expr},
    {getASTKey(expr, ASSIGN_MUL, expr), expr},
    {getASTKey(expr, ASSIGN_DIV, expr), expr},

    // 声明语句
    {getASTKey(expr, expr), expr_decl},

    // for循环元信息
    {getASTKey(KEY_FOR, TT_PARENTHESES_L, expr, TT_SEMI, expr, TT_SEMI, expr, TT_PARENTHESES_R), forloop_meta},
    {getASTKey(KEY_FOR, TT_PARENTHESES_L, expr, TT_SEMI, expr, TT_SEMI, TT_PARENTHESES_R), forloop_meta},
    {getASTKey(KEY_FOR, TT_PARENTHESES_L, expr, TT_SEMI, TT_SEMI, expr, TT_PARENTHESES_R), forloop_meta},
    {getASTKey(KEY_FOR, TT_PARENTHESES_L, expr, TT_SEMI, TT_SEMI, TT_PARENTHESES_R), forloop_meta},
    {getASTKey(KEY_FOR, TT_PARENTHESES_L, TT_SEMI, expr, TT_SEMI, expr, TT_PARENTHESES_R, stmt), forloop_meta},
    {getASTKey(KEY_FOR, TT_PARENTHESES_L, TT_SEMI, expr, TT_SEMI, TT_PARENTHESES_R), forloop_meta},
    {getASTKey(KEY_FOR, TT_PARENTHESES_L, TT_SEMI, TT_SEMI, expr, TT_PARENTHESES_R), forloop_meta},
    {getASTKey(KEY_FOR, TT_PARENTHESES_L, TT_SEMI, TT_SEMI, TT_PARENTHESES_R), forloop_meta},

    // for循环
    {getASTKey(forloop_meta, stmt), forloop}
};

// 优先级表
static const std::map<uint64_t, uint64_t> PriorityMap = {
    // common
    {getASTKey(stmt_list), 200},
    {getASTKey(expr, TT_SEMI), 100},
    {getASTKey(stmt_list, stmt), 107},
    {getASTKey(TT_BRACE_L, stmt_list, TT_BRACE_R), 101},
    {getASTKey(stmt), 108},
    {getASTKey(stmt_block), 103},
    {getASTKey(forloop), 103},
    {getASTKey(TT_SEMI), 104},
    {getASTKey(stmt, TT_SEMI), 106},

    // 基本表达式 1
    {getASTKey(expr, TT_DOT, expr), 1},
    {getASTKey(expr, COLON2, expr), 1},
    {getASTKey(expr, POINT_TO, expr), 1},
    {getASTKey(NAME), 1},
    {getASTKey(expr_const), 1},
    {getASTKey(expr_postfix, expr, TT_BRACKET_R), 1},
    {getASTKey(expr_decl), 1},
    // 常量表达式 1
    {getASTKey(KEY_CONST, expr), 1},
    {getASTKey(INTEGER), 1},
    {getASTKey(FLOAT_POINT), 1},

    // 后缀表达式 2
    {getASTKey(expr, TT_BRACKET_L), 2},
    {getASTKey(expr, INCREASE), 2},
    {getASTKey(expr, DECREASE), 2},

    // 一元运算表达式 3
    {getASTKey(INCREASE, expr), 3},
    {getASTKey(DECREASE, expr), 3},
    {getASTKey(NOT, expr), 3},
    {getASTKey(BOOL_NOT, expr), 3},

    // 强制类型表达式 4
    {getASTKey(TT_PARENTHESES_L, expr, TT_PARENTHESES_R), 4},

    // 乘除法 5
    {getASTKey(expr, MUL, expr), 5},
    {getASTKey(expr, DIV, expr), 5},
    {getASTKey(expr, MOD, expr), 5},

    // 加减法 6
    {getASTKey(expr, ADD, expr), 6},
    {getASTKey(expr, SUB, expr), 6},

    // 移位表达式 7
    {getASTKey(expr, MOVE_L, expr), 7},
    {getASTKey(expr, MOVE_R, expr), 7},

    // 关系运算表达式 8
    {getASTKey(expr, TT_ANGLE_BRACKET_L, expr), 8},
    {getASTKey(expr, TT_ANGLE_BRACKET_R, expr), 8},
    {getASTKey(expr, LEQ, expr), 8},
    {getASTKey(expr, GEQ, expr), 8},

    // 相等运算 9
    {getASTKey(expr, TT_EQUAL, expr), 9},
    {getASTKey(expr, TT_NOT_EQUAL, expr), 9},

    // 位与运算 10
    {getASTKey(expr, AND, expr), 10},

    // 位异或运算 11
    {getASTKey(expr, XOR, expr), 11},

    // 位或运算 12
    {getASTKey(expr, OR, expr), 12},

    // 逻辑与运算 13
    {getASTKey(expr, BOOL_AND, expr), 13},

    // 逻辑或运算 14
    {getASTKey(expr, BOOL_OR, expr), 14},

    // 三元条件运算 15
    {getASTKey(expr, TT_QUES, expr, COLON, expr), 15},

    // 赋值运算 16
    {getASTKey(expr, TT_ASSIGN, expr), 16},
    {getASTKey(expr, ASSIGN_ADD, expr), 16},
    {getASTKey(expr, ASSIGN_SUB, expr), 16},
    {getASTKey(expr, ASSIGN_MUL, expr), 16},
    {getASTKey(expr, ASSIGN_DIV, expr), 16},

    // 声明语句 20
    {getASTKey(expr, expr), 20},

    // for循环元信息
    {getASTKey(KEY_FOR, TT_PARENTHESES_L, expr, TT_SEMI, expr, TT_SEMI, expr, TT_PARENTHESES_R), 40},
    {getASTKey(KEY_FOR, TT_PARENTHESES_L, expr, TT_SEMI, expr, TT_SEMI, TT_PARENTHESES_R), 40},
    {getASTKey(KEY_FOR, TT_PARENTHESES_L, expr, TT_SEMI, TT_SEMI, expr, TT_PARENTHESES_R), 40},
    {getASTKey(KEY_FOR, TT_PARENTHESES_L, expr, TT_SEMI, TT_SEMI, TT_PARENTHESES_R), 40},
    {getASTKey(KEY_FOR, TT_PARENTHESES_L, TT_SEMI, expr, TT_SEMI, expr, TT_PARENTHESES_R), 40},
    {getASTKey(KEY_FOR, TT_PARENTHESES_L, TT_SEMI, expr, TT_SEMI, TT_PARENTHESES_R), 40},
    {getASTKey(KEY_FOR, TT_PARENTHESES_L, TT_SEMI, TT_SEMI, expr, TT_PARENTHESES_R), 40},
    {getASTKey(KEY_FOR, TT_PARENTHESES_L, TT_SEMI, TT_SEMI, TT_PARENTHESES_R), 40},

    // for循环
    {getASTKey(forloop_meta, stmt), 41}
};