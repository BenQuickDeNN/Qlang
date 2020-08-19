#pragma once
// #include "ast.hpp"
#include "ast_bt.hpp"
#include "ast_node.hpp"

/**
 * @brief display tree structure in DFS order
 */
void dispDFS(const std::shared_ptr<ASTNode> p_node, const size_t &depth)
{
    if (depth == 0)
        std::cout << "view tree:" << std::endl;
    if (p_node == nullptr)
        return;
    // std::cout << "check " <<p_node->token.getTokType() << std::endl;
    for (size_t i = 0; i < depth; ++i)
        std::cout << "--";
    if (depth > 0)
        std::cout << "> ";
    std::cout << p_node->token.getTokType() << " \"" << p_node->token.getTokStr() << "\"" << std::endl;
    // std::cout << p_node->children.size() << std::endl;
    for (const auto &child : p_node->children)
        dispDFS(child, depth + 1);
}