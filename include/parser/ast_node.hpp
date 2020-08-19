#pragma once
#include <vector>
#include <memory>
#include "../lexer/token.hpp"
#include "../utils/utils.hpp"
enum ASTNodeType
{
    root = TokType::LAST + 1,
    stmt_list = root + 1,
    stmt_block = stmt_list + 1,
    stmt = stmt_block + 1,
    expr = stmt + 1,
    expr_postfix = expr + 1,
    expr_const = expr_postfix + 1,
    expr_decl = expr_const + 1,
    forloop_meta = expr_decl + 1,
    forloop = forloop_meta + 1,
    last = forloop + 1
};
/**
 * @brief node of AST
 */
struct ASTNode
{
    Token token;
    Range<size_t> range;
    std::vector<std::shared_ptr<ASTNode>> children;
    ASTNode() {}
    ASTNode(const Token &token, const Range<size_t> &range)
        : token(token), range(range) {}
    /**
     * @brief check is nonterminal symbol
     */
    bool isNonterminal()
    {
        auto toktype = (ASTNodeType)token.getTokType();
        return toktype < ASTNodeType::last && 
            toktype >= ASTNodeType::root;
    }
};