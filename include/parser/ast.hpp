/**
 * @deprecated
 */
#pragma once
#include <memory>
#include <map>
#include <vector>
#include <iostream>
#include <queue>
#include "ast_node.hpp"
#include "../lexer/token.hpp"

static ASTNode BuildAST(const std::vector<Token> &tokens);
static void BuildAST(const std::vector<Token> &tokens, 
    std::shared_ptr<ASTNode> &p_node);

/**
 * @brief 判断toks串能否和语法匹配上，并输出匹配终结符的位置
 */
static bool isMatch(const std::vector<unsigned int> &toks, 
    const std::vector<unsigned int> &grammar, 
    std::vector<size_t> &tok_idxs,
    const size_t &tok_offset);

/**
 * @brief 生成式列表
 */
static const std::map<unsigned int, std::vector<std::vector<unsigned int>>> GrammarList =
{
    {ASTNodeType::root, {{ASTNodeType::stmt}}},

    {ASTNodeType::stmt, {{ASTNodeType::expr, TokType::TT_SEMI}}},

    // 基本表达式
    {ASTNodeType::expr, 
        {
            // 基本表达式 优先级=1
            {ASTNodeType::expr, TokType::TT_DOT, ASTNodeType::expr},
            {ASTNodeType::expr, TokType::COLON2, ASTNodeType::expr},
            {ASTNodeType::expr, TokType::POINT_TO, ASTNodeType::expr},
            {TokType::MUL, ASTNodeType::expr}, // 指针取值
            {TokType::NAME},
            {TokType::TT_PARENTHESES_L, ASTNodeType::expr, TokType::TT_PARENTHESES_R},

            // 一元运算表达式 优先级=3
            {ASTNodeType::expr, TokType::INCREASE},
            {ASTNodeType::expr, TokType::DECREASE},
            {TokType::INCREASE, ASTNodeType::expr},
            {TokType::DECREASE, ASTNodeType::expr},
            {TokType::NOT, ASTNodeType::expr},
            {TokType::BOOL_NOT, ASTNodeType::expr},

            // 强制类型表达式 优先级=4
            {TokType::TT_PARENTHESES_L, ASTNodeType::type_name, TokType::TT_PARENTHESES_R, ASTNodeType::expr},
            // 乘除法 优先级=5
            // 加减法 优先级=6
            // {ASTNodeType::expr, TokType::ADD, ASTNodeType::expr},
            // {ASTNodeType::expr, TokType::SUB, ASTNodeType::expr},
            {ASTNodeType::expr, TokType::OP_LEVEL_6, ASTNodeType::expr},

            // 赋值运算 优先级=16
            {ASTNodeType::expr, TokType::TT_ASSIGN, ASTNodeType::expr}

        }
    },

    // 后缀表达式 优先级=2
    {ASTNodeType::expr_postfix, {{TokType::TT_BRACKET_L, ASTNodeType::expr, TokType::TT_ANGLE_BRACKET_R}}}
};
// Grammar
static ASTNode BuildAST(const std::vector<Token> &tokens)
{
    // 处理token中运算符的优先级
    std::vector<Token> _tokens(tokens.size());
    for (size_t i = 0; i < tokens.size(); i++)
    {
        auto tt = tokens[i].getTokType();
        _tokens[i] = tokens[i];
        if (tt == TokType::ADD || tt == TokType::SUB)
            _tokens[i].setTokType(TokType::OP_LEVEL_6);
    }
    size_t right = tokens.size();
    Token tok_root((TokType)ASTNodeType::root);
    ASTNode root(tok_root, {0, right});
    std::shared_ptr<ASTNode> p_node = std::make_shared<ASTNode>(root);
    BuildAST(_tokens, p_node);
    return *p_node;
}
static void BuildAST(const std::vector<Token> &tokens, std::shared_ptr<ASTNode> &p_node)
{
    if (p_node == nullptr)
        return;
    std::cout << "ast building " << p_node->token.getTokType() << std::endl;
    // std::cout << "range = {" << p_node->range._start << ", " << p_node->range._end << "}" << std::endl;
    // 遍历token，看看有没有终结符与生成式匹配
    std::vector<unsigned int> toks;
    for (size_t i = p_node->range._start; i < p_node->range._end; ++i)
        toks.emplace_back((unsigned int)tokens[i].getTokType());
    TokType tokType = p_node->token.getTokType();
    auto it = GrammarList.find(tokType);
    if (it == GrammarList.end())
    {
        return;
    }
    // std::cout << "toktype check pass" << std::endl;
    const auto &grammars = it->second;
    // std::cout << "size of gramars = " << grammars.size() << std::endl;
    std::vector<size_t> tok_idxs;
    for (size_t i = grammars.size() - 1; i >= 0; --i)
    {   
        auto grammar = grammars[i];
        // 若匹配，则展开当前节点
        // std::cout << "check matched " << p_node->token.getTokType() << std::endl;
        // std::cout << "toks.size() = " << toks.size() << std::endl;
        if (isMatch(toks, grammar, tok_idxs, p_node->range._start))
        {
            //std::cout << "matched" << std::endl;
            size_t left = p_node->range._start, right;
            // std::cout << "tok_idxs.size() = " << tok_idxs.size() << std::endl;
            size_t j = 0;
            for (const auto &nodeType : grammar)
            {
                if (Token::isToken(nodeType))
                {
                    //std::cout << "left = " << left << ", right = " << right << std::endl;
                    p_node->children.emplace_back(
                        std::make_shared<ASTNode>(
                            ASTNode(
                                Token(tokens[tok_idxs[j]]),
                                {tok_idxs[j], tok_idxs[j] + 1}
                            )));
                    ++j;
                }
                else
                {
                    if (j < tok_idxs.size())
                        right = tok_idxs[j];
                    else
                        right = p_node->range._end;
                    //std::cout << "left = " << left << ", right = " << right << std::endl;
                    p_node->children.emplace_back(
                        std::make_shared<ASTNode>(
                            ASTNode(
                                Token((TokType)nodeType),
                                {left, right}
                            )));
                    if (j < tok_idxs.size())
                        left = tok_idxs[j] + 1;
                }
            }
            
            break;
        }
    }
    
     for (auto &child : p_node->children)
       std::cout << "child = " << child->token.getTokType() << 
        ", range = {" << child->range._start << ", " << 
        child->range._end << "}" << ", value = \"" << 
        child->token.getTokStr() << "\"" << std::endl;
    // 从左向右遍历，找到非终结符并递归
    // 最左推导；如果想改成最右推导，从右向左遍历即可
    for (auto &child : p_node->children)
        if (child->isNonterminal())
            BuildAST(tokens, child);
}
/**
 * @brief 判断toks串能否和语法匹配上，并输出匹配终结符的位置
 */
static bool isMatch(const std::vector<unsigned int> &toks, 
    const std::vector<unsigned int> &grammar, 
    std::vector<size_t> &tok_idxs,
    const size_t &tok_offset)
{
    if (toks.empty())
        return false;
    if (grammar.empty())
        return false;
    // 对比首尾终结符
    // 首
    // auto first1 = toks[0];
    // auto first2 = grammar[0];
    // if (Token::isToken(first2) && first1 != first2)
    //    return false;
    // 尾
    // auto last1 = toks[toks.size() - 1];
    // auto last2 = grammar[grammar.size() - 1];
    // if (Token::isToken(last2) && last1 != last2)
    //    return false;
    // 看看gramar中所有的终结符是不是都能在toks中找到
    int i = toks.size() - 1;
    //std::cout << "isMatched: head and tail are the same" << std::endl;
    for (int j = grammar.size() - 1; j >= 0; --j)
        if (Token::isToken(grammar[j]))
        {
            bool isMatched = false;
            for (; i >= 0; --i)
                if (toks[i] == grammar[j])
                {
                    std::cout << i + tok_offset << std::endl;
                    tok_idxs.emplace_back(i + tok_offset);
                    isMatched = true;
                    break;
                }
            if (!isMatched)
            {
                // std::cout << "isMatched: dismatched" << std::endl;
                return false;
            }
        }
    //std::cout << "isMatched: matched" << std::endl;
    return true;
}

