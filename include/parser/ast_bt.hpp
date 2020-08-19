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
extern void dispDFS(const std::shared_ptr<ASTNode> p_node, const size_t &depth);
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
        ASTNodeBuff buff;
        std::vector<ASTNodeBuff> buffs;
        for (size_t left = 0; left < nodes.size(); ++left)
            for (size_t right = left + 1; right <= nodes.size(); ++right)
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
                    }
                }
            }
        if (buffs.empty())
        {
            std::cout << "buffs is empty" << std::endl;
            return nullptr;
        }
        static std::shared_ptr<ASTNode> p_node = std::make_shared<ASTNode>();
        // sort buffs
        std::sort(buffs.begin(), buffs.end(), cmp_astNodeBuff);
        buff = buffs[0];
        // generate p_node
        p_node->token.setTokType((TokType)GrammarMap.find(buff.key)->second);
        p_node->range = buff.range;
        p_node->children.clear();
        for (size_t i = buff.range._start; i < buff.range._end; ++i)
            p_node->children.emplace_back(std::make_shared<ASTNode>(ASTNode(nodes[i].token, nodes[i].range)));
        // update tokens
        nodes.erase(nodes.begin() + buff.range._start + 1, nodes.begin() + buff.range._end);
        nodes[buff.range._start] = *p_node;
        return p_node;
    }

    static std::shared_ptr<ASTNode> buildAST(std::vector<ASTNode> &nodes)
    {
        std::shared_ptr<ASTNode> p_node;
        std::vector<std::vector<ASTNode>> tree;
        tree.clear();
        tree.emplace_back(nodes);
        while (!nodes.empty())
        {
            p_node = genNode(nodes);
            if (p_node == nullptr)
            {
                std::cerr << "parser error, unknown rules" << std::endl;
                return nullptr;
            }
            tree.emplace_back(nodes);
            if (p_node->token.getTokType() == (TokType)root)
                break;
        }
        if (tree.empty())
            return nullptr;
        for (int i = tree.size() - 1; i >= 0; --i)
        {
            if (i < tree.size() - 1)
                std::cout << "=> ";
            for (auto &n : tree[i])
            {
                std::cout << n.token.getTokType();
                std::cout << '{' << n.range._start << ',' << n.range._end << "} ";
            }
            std::cout << std::endl;
        }
        p_node = std::make_shared<ASTNode>(tree.back().front());
        buildAST(tree, (int)tree.size() - 2, p_node);
        std::cout << "AST is built" << std::endl;
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
        return a.priority < b.priority;
    }

    static uint64_t getASTKeyRange(const std::vector<ASTNode> &nodes, Range<size_t> range)
    {
        uint64_t sum = 0;
        uint64_t tmp = last;
        for (size_t i = range._start; i < range._end; ++i)
        {
            sum += tmp * nodes[i].token.getTokType();
            tmp *= last;
        }
        return sum;
    }

    static void buildAST(const std::vector<std::vector<ASTNode>> &tree, const int &level, std::shared_ptr<ASTNode> &p_node)
    {
        if (p_node == nullptr)
            return;
        p_node->children.clear();
        if (level < 0)
            return;
        if (!p_node->isNonterminal())
            return;
        bool flag_addChild = false;
        for (size_t i = p_node->range._start; i < p_node->range._end; ++i)
        {
            if (!(tree[level][i].token.getTokType() == p_node->token.getTokType() &&
                tree[level][i].range == p_node->range))
            {
                p_node->children.push_back(std::make_shared<ASTNode>(tree[level][i]));
                flag_addChild = true;
            }
            if (flag_addChild)
                buildAST(tree, level - 1, p_node->children.back());
            else
                buildAST(tree, level - 1, p_node);
        }
    }
};