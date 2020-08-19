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

// 生成规则表
static const std::map<uint64_t, uint64_t> GrammarMap = {
    {getASTKey(stmt), root},
    {getASTKey(NAME), expr},
    {getASTKey(expr, MUL, expr), expr},
    {getASTKey(expr, DIV, expr), expr},
    {getASTKey(expr, ADD, expr), expr},
    {getASTKey(expr, SUB, expr), expr},
    {getASTKey(expr, TT_ASSIGN, expr), expr},
    {getASTKey(expr, TT_SEMI), stmt}
};

// 优先级表
static const std::map<uint64_t, uint64_t> PriorityMap = {
    {getASTKey(stmt), 0},
    {getASTKey(NAME), 1},
    {getASTKey(expr, MUL, expr), 5},
    {getASTKey(expr, DIV, expr), 5},
    {getASTKey(expr, ADD, expr), 6},
    {getASTKey(expr, SUB, expr), 6},
    {getASTKey(expr, TT_ASSIGN, expr), 16},
    {getASTKey(expr, TT_SEMI), 100}
};

// symbol priority


class ASTBuilder
{
public:
    /**
     * @brief 构造抽象语法树
     */
    static std::shared_ptr<ASTNode> buildAST(const std::vector<Token> &tokens)
    {
        std::vector<ASTNode> nodes;
        for (size_t i = 0; i < tokens.size(); ++i)
            nodes.push_back(ASTNode(tokens[i], {i, i + 1}));
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
                std::cout << '{' << n.range._start << ',' << n.range._end << "}";
                std::cout << ' ';
            }
            std::cout << std::endl;
        }
        p_node = std::make_shared<ASTNode>(tree.back().front());
        buildAST(tree, tree.size() - 1, p_node, true);
        std::cout << "AST is built" << std::endl;
        return p_node;
    }
private:
    struct ASTNodeBuff
    {
        uint64_t key;
        uint64_t priority;
        Range<size_t> range;
        Range<size_t> range_real;
    };

    static void updateBuffs(std::vector<ASTNodeBuff> &buffs, const std::vector<ASTNode> &nodes)
    {
        ASTNodeBuff buff;
        size_t start, end;
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
                        buffs.emplace_back(ASTNodeBuff());
                        buffs.back().key = key;
                        buffs.back().priority = it_pri->second;
                        buffs.back().range = {left, right};
                        buffs.back().range_real = {nodes[left].range._start, nodes[right - 1].range._end};
                    }
                }
            }
        // sort buffs
        std::sort(buffs.begin(), buffs.end(), cmp_astNodeBuff);
    }

    /**
     * @brief comparator for ASTNodeBuff
     */
    static bool cmp_astNodeBuff(const ASTNodeBuff &a, const ASTNodeBuff &b)
    {
        return a.priority < b.priority;
    }

    /**
     * @note this procedure updates tokens
     */
    static std::shared_ptr<ASTNode> genNode(std::vector<ASTNode> &nodes)
    {
        std::vector<ASTNodeBuff> buffs;
        updateBuffs(buffs, nodes);
        if (buffs.empty())
        {
            std::cout << "buffs is empty" << std::endl;
            return nullptr;
        }
        const ASTNodeBuff &buff = buffs.front();
        // generate p_node
        static std::shared_ptr<ASTNode> p_node = std::make_shared<ASTNode>();
        p_node->token.setTokType((TokType)GrammarMap.find(buff.key)->second);
        p_node->range = buff.range_real;
        // update tokens
        nodes.erase(nodes.begin() + buff.range._start + 1, nodes.begin() + buff.range._end);
        nodes[buff.range._start] = *p_node;
        return p_node;
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

    static void buildAST(const std::vector<std::vector<ASTNode>> &tree, 
        const int &level, std::shared_ptr<ASTNode> &p_node, 
        const bool &addChild)
    {
        if (p_node == nullptr)
            return;
        if (addChild)
            p_node->children.clear();
        if (level < 1)
            return;
        if (!p_node->isNonterminal())
            return;
        const int j = level - 1;
        bool flag_addChild = false;
        for (auto &t : tree[j])
        {
            if (t.range._start < p_node->range._start)
                continue;
            if (t.range._end > p_node->range._end)
                break;
            if (t.token.getTokType() != p_node->token.getTokType() ||
                t.range != p_node->range)
            {
                p_node->children.push_back(std::make_shared<ASTNode>(t));
                flag_addChild = true;
            }
        }
        // std::cout << "build " << p_node->token.getTokType();
        // std::cout << '{' << p_node->range._start << ',' << p_node->range._end << "}" << std::endl;
        if (flag_addChild)
        {
            for (size_t i = 0; i < p_node->children.size(); ++i)
            {
                // std::cout << "push back " << tree[j][i].token.getTokType() << ", level = " << level << ", j = " << j << ", i = " << i << std::endl;
                buildAST(tree, j, p_node->children[i], flag_addChild);
            }   
        }
        else
            buildAST(tree, j, p_node, flag_addChild);
    }
};