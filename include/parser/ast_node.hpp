#ifndef AST_NODE_HPP
#define AST_NODE_HPP
#include <vector>
#include "../lexer/token.hpp"
/**
 * @brief node of AST
 */
class ASTNode
{
public:
    Token value;
    std::vector<ASTNode*> children;
};
#endif