#pragma once
#include <memory>
#include <vector>
#include "../lexer/lexer.hpp"
class ActivityNode
{
public:
    Token token;
    std::shared_ptr<ActivityNode> parent; // 父节点
    std::vector<std::shared_ptr<ActivityNode>> children; // 子节点
private:
    void addChild(std::shared_ptr<ActivityNode> node)
    {
        node->parent = std::make_shared<ActivityNode>(*this);
        children.push_back(node);
    }
};