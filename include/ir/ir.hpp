#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include "../lexer/lexer.hpp"
#include "../parser/parser.hpp"

// 操作数
union Operand {
    std::string str; // 值
    size_t idx; // 值所在的索引
};


// 三元式
struct Ternary
{
    uint64_t op; // 运算符
    Operand opr1; // 操作数1
    Operand opr2; // 操作数2
};

// 三元式表
class TernaryList
{
public:
    size_t getTernary(const std::shared_ptr<ASTNode> node)
    {
        if (node == nullptr)
            return;
        // 深度优先后序遍历
        for (const auto &child : node->children)
            getTernary(child);
        uint64_t tt = node->token.getTokType();
        return data.size() - 1;
    }
    std::vector<Ternary> data;
};