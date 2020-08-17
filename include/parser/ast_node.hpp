#ifndef AST_NODE_HPP
#define AST_NODE_HPP
#include <vector>
#include <memory>
#include "../lexer/token.hpp"
#include "../utils/utils.hpp"
enum ASTNodeType
{
    root = TokType::LAST + 1,
    stmt = root + 1,
    expr = stmt + 1,
    expr_postfix = expr + 1,
    expr_const = expr_postfix + 1,
    type_name = expr_const + 1,
    last = expr_const + 1
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
#endif