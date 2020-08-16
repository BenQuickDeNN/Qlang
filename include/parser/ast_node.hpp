#ifndef AST_NODE_HPP
#define AST_NODE_HPP
#include <vector>
#include <memory>
#include "../lexer/token.hpp"
#include "../utils/utils.hpp"
enum ASTNodeType
{
    expr = TokType::LAST + 1,
    stmt = expr + 1
};
/**
 * @brief node of AST
 */
struct ASTNode
{
    ASTNodeType nodeType;
    bool canLookForward = false;
    Range<size_t> range;
    std::shared_ptr<std::vector<Token>> p_tok;
    std::vector<ASTNode*> children;
};
#endif