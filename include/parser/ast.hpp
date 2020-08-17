#ifndef AST_HPP
#define AST_HPP
#include <memory>
#include <map>
#include <vector>
#include "ast_node.hpp"
#include "../lexer/token.hpp"
using Node = ASTNodeType;
using Tok = TokType;

static ASTNode BuildAST(const std::vector<Token> &tokens);

/**
 * @brief 生成式列表
 */
static const std::map<unsigned int, std::vector<std::vector<unsigned int>>> GrammarList =
{
    {Node::root, {{Node::stmt}}},

    {Node::stmt, {{Node::expr, TokType::TT_SEMI}}},

    // 基本表达式
    {Node::expr, 
        {
            // 基本表达式 优先级=1
            {Tok::TT_PARENTHESES_L, Node::expr, Tok::TT_PARENTHESES_R},
            {Node::expr, Tok::TT_DOT, Node::expr},
            {Node::expr, Tok::COLON2, Node::expr},
            {Node::expr, Tok::POINT_TO, Node::expr},
            {Tok::MUL, Node::expr}, // 指针取值

            // 一元运算表达式 优先级=3
            {Node::expr, Tok::INCREASE},
            {Node::expr, Tok::DECREASE},
            {Tok::INCREASE, Node::expr},
            {Tok::DECREASE, Node::expr},
            {Tok::NOT, Node::expr},
            {Tok::BOOL_NOT, Node::expr},

            // 强制类型表达式 优先级=4
            {Tok::TT_PARENTHESES_L, Node::type_name, Tok::TT_PARENTHESES_R, Node::expr},

            // 加减法 优先级=6
            {Node::expr, Tok::ADD, Node::expr},
            {Node::expr, Tok::SUB, Node::expr},

            // 赋值运算 优先级=16
            {Node::expr, Tok::TT_ASSIGN, Node::expr}
        }
    },

    // 后缀表达式 优先级=2
    {Node::expr_postfix, {{Tok::TT_BRACKET_L, Node::expr, Tok::TT_ANGLE_BRACKET_R}}}
};
// Grammar
static ASTNode BuildAST(const std::vector<Token> &tokens)
{
    int right = tokens.size();
    Token tok_root("root", (Tok)Node::root);
    ASTNode root(tok_root, {0, right});
    std::shared_ptr<ASTNode> p_node = std::make_shared<ASTNode>(root);
    p_node->children.push_back(std::make_shared<ASTNode>(ASTNode(Token("stmt", (Tok)Node::stmt), root.range)));
    // 从左向右遍历，找到第一个非终结符
    for (auto &node : p_node->children)
    {
        if (ASTNode::isNonterminal(*node))
        {

        }
    }
}
#endif