#pragma once
// #include "ast.hpp"
#include "ast_bt.hpp"
#include "ast_node.hpp"
#include "../lexer/tok_str.hpp"

/**
 * @brief display tree structure in DFS order
 */
void dispDFS(const std::shared_ptr<ASTNode> p_node, const size_t &depth)
{
    if (depth == 0)
        std::cout << "view tree:" << std::endl;
    if (p_node == nullptr)
        return;
    for (size_t i = 0; i < depth; ++i)
        std::cout << "--";
    if (depth > 0)
        std::cout << "> ";
    auto it = TokStrMap.find(p_node->token.getTokType());
    if (it != TokStrMap.end())
        std::cout << it->second;
    else
        std::cout << p_node->token.getTokType();
    if (p_node->token.getTokStr().size() > 0)
        std::cout << " \"" << p_node->token.getTokStr() << "\"";
    std::cout << std::endl;
    for (const auto &child : p_node->children)
        dispDFS(child, depth + 1);
}