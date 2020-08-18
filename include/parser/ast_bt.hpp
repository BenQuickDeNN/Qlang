/**
 * @brief build ast from bottom to top
 */
#pragma once
#include <map>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <memory>
#include <iostream>
#include "ast_node.hpp"
#include "lexer/token.hpp"
#include "utils/utils.hpp"

template <typename type = uint64_t>
static const uint64_t getASTKey(const type tok)
{
    return last * tok;
}

template <typename type = uint64_t, typename... types>
static const uint64_t getASTKey(const type tok, const types... toks)
{
    return getASTKey(tok) + last * getASTKey(toks...);
}

static const std::map<uint64_t, uint64_t> GrammarMap = {
    {getASTKey(NAME), expr},
    {getASTKey(expr, TT_ASSIGN, expr), expr},
    {getASTKey(expr, TT_SEMI), stmt},
    {getASTKey(stmt), root}
};

// 优先级表
static const std::map<uint64_t, uint64_t> PriorityMap = {
    {getASTKey(NAME), 1},
    {getASTKey(expr, TT_ASSIGN, expr), 16},
    {getASTKey(expr, TT_SEMI), 100},
    {getASTKey(stmt), 101}
};

// symbol priority


class ASTBuilder
{
public:
    /**
     * @note this procedure updates tokens
     */
    static std::shared_ptr<ASTNode> genNode(std::vector<ASTNode> &nodes)
    {
        size_t right = 0;
        size_t left = right;
        ASTNodeBuff buff;
        std::vector<ASTNodeBuff> buffs;
        while (right <= nodes.size())
        {
            auto key = getASTKeyRange(nodes, {left, right});
            auto it = GrammarMap.find(key);
            if (it != GrammarMap.end())
            {
                auto it_pri = PriorityMap.find(key);
                if (it_pri != PriorityMap.end())
                {
                    buff.key = key;
                    buff.priority = it_pri->second;
                    buff.range = {left, right};
                    buffs.emplace_back(buff);
                    ++left;
                    continue;
                }
            }
            ++right;
        }
        if (buffs.empty())
            return nullptr;
        static std::shared_ptr<ASTNode> p_node = std::make_shared<ASTNode>();
        // sort buffs
        std::sort(buffs.begin(), buffs.end(), cmp_astNodeBuff);
        buff = buffs[0];
        // generate p_node
        p_node->token.setTokType((TokType)GrammarMap.find(buff.key)->second);
        p_node->range = buff.range;
        for (size_t i = buff.range._start; i < buff.range._end; ++i)
            p_node->children.push_back(std::make_shared<ASTNode>(ASTNode(nodes[i].token, nodes[i].range)));
        // update tokens
        //for (size_t i = buff.range._start + 1; i < buff.range._end; ++i)
        nodes.erase(nodes.begin() + buff.range._start + 1, nodes.begin() + buff.range._end);
        nodes[buff.range._start] = *p_node;
        // std::vector<ASTNode> nodes_buff;
        // for (size_t i = 0; i < buff.range._start; ++i)
        //    nodes_buff.emplace_back(nodes[i]);
        // nodes_buff.emplace_back(*p_node);
        // for (size_t i = buff.range._end; i < nodes.size(); ++i)
        //    nodes_buff.emplace_back(nodes[i]);
        // nodes.clear();
        // nodes = nodes_buff;
        return p_node;
    }

    static std::shared_ptr<ASTNode> buildAST(std::vector<ASTNode> &nodes)
    {
        std::shared_ptr<ASTNode> p_node;
        while (nodes.size() > 1)
        {
            p_node = genNode(nodes);
            if (p_node == nullptr)
            {
                std::cerr << "parser error, unknown rules" << std::endl;
                return nullptr;
            }
            std::cout << "gen node " << p_node->token.getTokType() << std::endl;
            for (const auto &n : nodes)
                std::cout << n.token.getTokType() << ' ';
            std::cout << std::endl;
        }
        if (p_node == nullptr)
            return nullptr;
        if (p_node->token.getTokType() != (TokType)root)
            return nullptr;
        return p_node;
    }
private:
    struct ASTNodeBuff
    {
        uint64_t key;
        uint64_t priority;
        Range<size_t> range;
    };

    /**
     * @brief comparator for ASTNodeBuff
     */
    static bool cmp_astNodeBuff(const ASTNodeBuff &a, const ASTNodeBuff &b)
    {
        return a.priority <= b.priority;
    }

    static uint64_t getASTKeyRange(const std::vector<ASTNode> &nodes, Range<size_t> range)
    {
        uint64_t sum = 0;
        for (size_t i = range._start; i < range._end; ++i)
            sum += last * nodes[i].token.getTokType();
        return sum;
    }
};