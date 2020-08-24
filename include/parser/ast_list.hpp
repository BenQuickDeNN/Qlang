#pragma once
#include <vector>
#include <string>
#include "ast_bt.hpp"
#include "../utils/utils.hpp"
#include "../lexer/tok_str.hpp"
struct ASTLine
{
    ASTNode key;
    std::vector<size_t> expansion;
};

class ASTList
{
public:
    std::vector<ASTLine> data;
    size_t getDataFromAST(const std::shared_ptr<ASTNode> node)
    {
        // 后序遍历构建ASTList
        if (node == nullptr)
            return 0;
        ASTLine astline;
        for (const auto &c : node->children)
            astline.expansion.emplace_back(getDataFromAST(c));
        astline.key = *node;
        data.emplace_back(astline);
        return data.size() - 1;
    }
    std::string toString()
    {
        std::string ret = "ASTList:\n";
        ret += "index\ttoktype\tvalue\texpansions\n";
        for (size_t i = 0; i < data.size(); ++i)
        {
            ret += std::to_string(i) + '\t';
            auto it = TokStrMap.find(data[i].key.token.getTokType());
            if (it != TokStrMap.end())
                ret += it->second + '\t';
            ret += data[i].key.token.getTokStr() + '\t';
            for (const auto &ex : data[i].expansion)
                ret += std::to_string(ex) + ' ';
            ret += '\n';
        }
        return ret;
    }
};