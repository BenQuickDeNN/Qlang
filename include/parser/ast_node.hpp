#pragma once
#include <vector>
#include <memory>
#include "../lexer/token.hpp"
#include "../utils/utils.hpp"
enum ASTNodeType
{
    
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
    bool isNonterminal() noexcept
    {
        auto toktype = token.getTokType();
        return toktype < last && 
            toktype >= root;
    }
};