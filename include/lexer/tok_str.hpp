#pragma once
#include <map>
#include <string>
#include "token.hpp"
#include "../parser/ast_node.hpp"

static const std::map<unsigned int, std::string> TokStrMap = 
{
    {TT_DEFAULT, "TOK_DEFAULT"},
    {NAME, "NAME"},
    {TT_SEMI, "SEMI"},
    {TT_ASSIGN, "="},
    {TT_PARENTHESES_L, "("},
    {TT_PARENTHESES_R, ")"},
    {TT_BRACKET_L, "["},
    {TT_BRACKET_R, "]"},
    {ADD, "+"},
    {SUB, "-"},
    {MUL, "*"},
    {DIV, "/"},
    {INCREASE, "++"},
    {DECREASE, "--"},
    {expr, "expr"},
    {expr_const, "expr_const"},
    {expr_postfix, "expr_postfix"},
    {stmt_list, "stmt_list"},
    {stmt, "stmt"},
    {root, "scope"}
};