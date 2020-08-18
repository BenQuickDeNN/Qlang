#pragma once
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "loop_tuple.hpp"
#include "../lexer/token.hpp"
#include "../utils/utils.hpp"

class LoopBlock
{};

class ForLoopBlock : LoopBlock
{
public:
    ForLoopBlock() {}
    ForLoopBlock(const std::vector<Token> &tokens)
    {
        readTokens(tokens);
    }
    ForLoopBlock(const std::vector<Token> &tokens, const ForLoopBlock &outerLoop)
    {
        this->outerLoop = std::make_shared<ForLoopBlock>(outerLoop);
        readTokens(tokens);
    }
    void clear()
    {
        _iterVar.clear();
        _iterType.clear();
        _range._start.clear();
        _range._end.clear();
        _stride.clear();
        _innerLoops.clear();
        _tuples.clear();
        _tokens.clear();
    }
    void readTokens(const std::vector<Token> &tokens)
    {
        clear();
        if (tokens.empty())
            return;

        // parse for loop info
        // create tuples
        std::string str;
        TokType tt;
        LoopTuple tuple;
        for (size_t i = 0; i < tokens.size(); i++)
        {
            str = tokens[i].getTokStr();
            tt = tokens[i].getTokType();
            _tokens.push_back(tokens[i]);
            // 这里还需要做简单的语法分析
        }
    }
private:
    std::string _iterVar; // 迭代变量
    std::string _iterType; // 迭代变量类型
    Range<std::string> _range; // 迭代范围
    std::string _stride; // 迭代步长
    std::shared_ptr<ForLoopBlock> outerLoop = nullptr; // 外层循环
    std::vector<std::shared_ptr<ForLoopBlock>> _innerLoops; // 嵌套循环
    std::vector<LoopTuple> _tuples;
    std::vector<Token> _tokens;
};