#pragma once
#include <map>
#include <string>
#include "token.hpp"
#include "../parser/ast_node.hpp"

static const std::map<unsigned int, std::string> TokStrMap = 
{
    {TT_DEFAULT, "TOK_DEFAULT"},

    {NAME, "NAME"},
    {INTEGER, "INTEGER"},
    {FLOAT_POINT, "FLOAT_POINT"},

    {TT_SEMI, ";"},
    {TT_ASSIGN, "="},
    {TT_PARENTHESES_L, "("},
    {TT_PARENTHESES_R, ")"},
    {TT_BRACKET_L, "["},
    {TT_BRACKET_R, "]"},
    {TT_BRACE_L, "{"},
    {TT_BRACE_R, "}"},
    {ADD, "+"},
    {SUB, "-"},
    {MUL, "*"},
    {DIV, "/"},
    {INCREASE, "++"},
    {DECREASE, "--"},
    {KEY_FOR, "for"},
    {TT_ANGLE_BRACKET_L, "<"},
    {TT_ANGLE_BRACKET_R, ">"},
    {LEQ, "<="},
    {GEQ, ">="},

    {expr, "expr"},
    {expr_const, "expr_const"},
    {expr_postfix, "expr_postfix"},
    {expr_decl, "expr_decl"},
    {stmt_list, "stmt_list"},
    {stmt_block, "stmt_block"},
    {stmt, "stmt"},
    {root, "scope"},
    {forloop_meta, "forloop_meta"},
    {forloop, "forloop"}
};