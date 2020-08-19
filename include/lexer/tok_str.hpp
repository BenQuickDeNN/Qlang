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
    {ADD, "+"},
    {SUB, "-"},
    {MUL, "*"},
    {DIV, "/"},
    {INCREASE, "++"},
    {expr, "expr"},
    {expr_const, "expr_const"},
    {stmt_list, "stmt_list"},
    {stmt, "stmt"},
    {root, "scope"}
};