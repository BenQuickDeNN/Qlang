#pragma once

#include <cstdint>
#include <map>
#include "ast_node.hpp"

template <typename type = uint64_t>
static const uint64_t getASTKey(const type tok) noexcept
{
    return last * tok;
}

template <typename type = uint64_t, typename... types>
static const uint64_t getASTKey(const type tok, const types... toks) noexcept
{
    return getASTKey(tok) + last * getASTKey(toks...);
}

// 生成规则表
// map<key, pair<target, priority>>
static const std::map<uint64_t, std::pair<uint64_t, uint64_t>> GrammarMap = {
    // common
    {getASTKey(stmt_list), {root, 200}},
    {getASTKey(stmt_list, stmt), {stmt_list, 107}},
    {getASTKey(TT_BRACE_L, stmt_list, TT_BRACE_R), {stmt_block, 101}},
    {getASTKey(stmt), {stmt_list, 108}},
    {getASTKey(expr, TT_SEMI), {stmt, 100}},
    {getASTKey(stmt_block), {stmt, 103}},
    {getASTKey(forloop), {stmt, 103}},
    {getASTKey(TT_SEMI), {stmt, 104}},
    {getASTKey(stmt, TT_SEMI), {stmt, 106}},
    
    // 基本表达式 1
    {getASTKey(expr, TT_DOT, expr), {expr, 1}},
    {getASTKey(expr, COLON2, expr), {expr, 1}},
    {getASTKey(expr, POINT_TO, expr), {expr, 1}},
    {getASTKey(NAME), {expr, 1}},
    {getASTKey(expr_const), {expr, 1}},
    {getASTKey(expr_postfix, expr, TT_BRACKET_R), {expr, 1}},
    {getASTKey(expr_decl), {expr, 1}},
    // 常量表达式 1
    {getASTKey(KEY_CONST, expr), {expr_const, 1}},
    {getASTKey(INTEGER), {expr_const, 1}},
    {getASTKey(FLOAT_POINT), {expr_const, 1}},

    // 后缀表达式 2
    {getASTKey(expr, TT_BRACKET_L), {expr_postfix, 2}},
    {getASTKey(expr, INCREASE), {expr, 2}},
    {getASTKey(expr, DECREASE), {expr, 2}},

    // 一元运算表达式 3
    {getASTKey(INCREASE, expr), {expr, 3}},
    {getASTKey(DECREASE, expr), {expr, 3}},
    {getASTKey(NOT, expr), {expr, 3}},
    {getASTKey(BOOL_NOT, expr), {expr, 3}},

    // 强制类型表达式 4
    {getASTKey(TT_PARENTHESES_L, expr, TT_PARENTHESES_R), {expr, 4}},

    // 乘除法 5
    {getASTKey(expr, MUL, expr), {expr, 5}},
    {getASTKey(expr, DIV, expr), {expr, 5}},
    {getASTKey(expr, MOD, expr), {expr, 5}},

    // 加减法 6
    {getASTKey(expr, ADD, expr), {expr, 6}},
    {getASTKey(expr, SUB, expr), {expr, 6}},

    // 移位表达式 7
    {getASTKey(expr, MOVE_L, expr), {expr, 7}},
    {getASTKey(expr, MOVE_R, expr), {expr, 7}},

    // 关系运算表达式 8
    {getASTKey(expr, TT_ANGLE_BRACKET_L, expr), {expr, 8}},
    {getASTKey(expr, TT_ANGLE_BRACKET_R, expr), {expr, 8}},
    {getASTKey(expr, LEQ, expr), {expr, 8}},
    {getASTKey(expr, GEQ, expr), {expr, 8}},

    // 相等运算 9
    {getASTKey(expr, TT_EQUAL, expr), {expr, 9}},
    {getASTKey(expr, TT_NOT_EQUAL, expr), {expr, 9}},

    // 位与运算 10
    {getASTKey(expr, AND, expr), {expr, 10}},

    // 位异或运算 11
    {getASTKey(expr, XOR, expr), {expr, 11}},

    // 位或运算 12
    {getASTKey(expr, OR, expr), {expr, 12}},

    // 逻辑与运算 13
    {getASTKey(expr, BOOL_AND, expr), {expr, 13}},

    // 逻辑或运算 14
    {getASTKey(expr, BOOL_OR, expr), {expr, 14}},

    // 三元条件运算 15
    {getASTKey(expr, TT_QUES, expr, COLON, expr), {expr, 15}},

    // 赋值运算 16
    {getASTKey(expr, TT_ASSIGN, expr), {expr, 16}},
    {getASTKey(expr, ASSIGN_ADD, expr), {expr, 16}},
    {getASTKey(expr, ASSIGN_SUB, expr), {expr, 16}},
    {getASTKey(expr, ASSIGN_MUL, expr), {expr, 16}},
    {getASTKey(expr, ASSIGN_DIV, expr), {expr, 16}},

    // 声明语句 20
    {getASTKey(expr, expr), {expr_decl, 20}},

    // for循环元信息 40
    {getASTKey(KEY_FOR, TT_PARENTHESES_L, expr, TT_SEMI, expr, TT_SEMI, expr, TT_PARENTHESES_R), {forloop_meta, 40}},
    {getASTKey(KEY_FOR, TT_PARENTHESES_L, expr, TT_SEMI, expr, TT_SEMI, TT_PARENTHESES_R), {forloop_meta, 40}},
    {getASTKey(KEY_FOR, TT_PARENTHESES_L, expr, TT_SEMI, TT_SEMI, expr, TT_PARENTHESES_R), {forloop_meta, 40}},
    {getASTKey(KEY_FOR, TT_PARENTHESES_L, expr, TT_SEMI, TT_SEMI, TT_PARENTHESES_R), {forloop_meta, 40}},
    {getASTKey(KEY_FOR, TT_PARENTHESES_L, TT_SEMI, expr, TT_SEMI, expr, TT_PARENTHESES_R, stmt), {forloop_meta, 40}},
    {getASTKey(KEY_FOR, TT_PARENTHESES_L, TT_SEMI, expr, TT_SEMI, TT_PARENTHESES_R), {forloop_meta, 40}},
    {getASTKey(KEY_FOR, TT_PARENTHESES_L, TT_SEMI, TT_SEMI, expr, TT_PARENTHESES_R), {forloop_meta, 40}},
    {getASTKey(KEY_FOR, TT_PARENTHESES_L, TT_SEMI, TT_SEMI, TT_PARENTHESES_R), {forloop_meta, 40}},

    // for循环 41
    {getASTKey(forloop_meta, stmt), {forloop, 41}}
};