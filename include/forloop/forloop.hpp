#pragma once
#include <vector>
#include <memory>
#include <string>
#include <stack>
#include <iostream>
#include "../utils/utils.hpp"
#include "../parser/parser.hpp"
/**
 * @brief 描述For循环的类型
 */
class ForLoop
{
public:
    ForLoop() {}

    ForLoop(const ASTList &astlist)
    {
        initFromASTList(astlist);
    }

    ForLoop(const ASTList &astlist, const size_t &maxIdx)
    {
        initFromASTList(astlist, maxIdx);
    }

    std::string toString() noexcept
    {
        std::string ret = "forloop: ";
        ret += "iterator = \"" + iterName + "\"; ";
        ret += "range = [" + range._start + ", " + range._end;
        if (relation == LEQ || relation == GEQ)
            ret += ']';
        else if (relation == TT_ANGLE_BRACKET_L || TT_ANGLE_BRACKET_R)
            ret += ')';
        else
            return "";
        ret += "; ";
        ret += "stride = " + stride + '\n';
        for (const auto &innerloop : innerLoops)
            ret += '\t' + innerloop->toString();
        return ret;
    }

    void initFromASTList(const ASTList &astlist) noexcept
    {
        initFromASTList(astlist, astlist.data.size() - 1);
    }

    void initFromASTList(const ASTList &astlist, const size_t &maxIdx) noexcept
    {
        if (maxIdx >= astlist.data.size())
            return;
        bool flag_findLoop = false;
        for (size_t i = maxIdx; i >= 0; --i)
        {
            if (astlist.data[i].key.token.getTokType() == (TokType)forloop)
            {
                forloopIdx = i;
                flag_findLoop = true;
                break;
            }
        }
        if (!flag_findLoop)
            return;
        auto &forloopLine = astlist.data[forloopIdx];
        if (forloopLine.expansion.empty())
            return;
        p_astlist = std::make_shared<ASTList>(astlist);
        const size_t forloopmetaIdx = forloopLine.expansion.front();
        auto &forloopmetaLine = astlist.data[forloopmetaIdx];
        getForloopmeta(astlist, forloopmetaLine);
        findInnerLoop(astlist, forloopLine.expansion.back());
    }

private:

    void findInnerLoop(const ASTList &astlist, const size_t &idx) noexcept
    {
        if (idx >= astlist.data.size())
            return;
        const auto &line = astlist.data[idx];
        if (line.key.token.getTokType() == (TokType)forloop)
        {
            innerLoops.push_back(std::make_shared<ForLoop>());
            innerLoops.back()->initFromASTList(astlist, idx);
            findInnerLoop(astlist, line.expansion.back());
        }
        else
            for (const size_t &i : line.expansion)
                findInnerLoop(astlist, i);
    }
    
    void getForloopmeta(const ASTList &astlist, const ASTLine &forloopmetaLine) noexcept
    {
        if (forloopmetaLine.key.token.getTokType() != (TokType)forloop_meta)
        {
            std::cerr << "getForloopmeta error: forloopmetaLine.key.token.getTokType() != (TokType)forloop_meta" << std::endl;
            return;
        }
        if (forloopmetaLine.expansion.size() != 8)
        {
            std::cerr << "getForloopmeta error: forloopmetaLine.expansion.size() != 8" << std::endl;
            return;
        }
        const size_t block1_idx = forloopmetaLine.expansion[2];
        const size_t block2_idx = forloopmetaLine.expansion[4];
        const size_t block3_idx = forloopmetaLine.expansion[6];

        // check block1
        const auto &block1 = astlist.data[block1_idx];
        std::shared_ptr<ASTLine> p_line = std::make_shared<ASTLine>(block1);
        while (!p_line->expansion.empty())
        {
            if (p_line->expansion.size() == 3)
                break;
            p_line = std::make_shared<ASTLine>(astlist.data[p_line->expansion.back()]);
        }
        if (p_line->expansion.size() != 3)
        {
            std::cerr << "getForloopmeta error: p_line->expansion.size() != 3" << std::endl;
            return;
        }

        // check assign
        if (astlist.data[p_line->expansion[1]].key.token.getTokType() != TT_ASSIGN)
        {
            std::cerr << "getForloopmeta error: astlist.data[p_line->expansion[1]].key.token.getTokType() != TT_ASSIGN" << std::endl;
            return;
        }

        // find itername
        std::shared_ptr<ASTLine> p_iterName = std::make_shared<ASTLine>(astlist.data[p_line->expansion.front()]);
        while (!p_iterName->expansion.empty())
            p_iterName = std::make_shared<ASTLine>(astlist.data[p_iterName->expansion.front()]);
        iterName = p_iterName->key.token.getTokStr();

        // find range start
        std::shared_ptr<ASTLine> p_range1 = std::make_shared<ASTLine>(astlist.data[p_line->expansion.back()]);
        // range暂时只支持立即数和单变量，不支持表达式
        if (p_range1->expansion.size() != 1)
        {
            std::cerr << "getForloopmeta error: unrecognized range start" << std::endl;
            return;
        }
        while (!p_range1->expansion.empty())
            p_range1 = std::make_shared<ASTLine>(astlist.data[p_range1->expansion.back()]);
        range._start = p_range1->key.token.getTokStr();

        // check block2
        const auto &block2 = astlist.data[block2_idx];
        if (block2.expansion.size() != 3)
        {
            std::cerr << "getForloopmeta error: block2.expansion.size() != 3" << std::endl;
            return;
        }
        
        p_line = std::make_shared<ASTLine>(block2);

        // check itername
        p_iterName = std::make_shared<ASTLine>(astlist.data[p_line->expansion.front()]);
        while (!p_iterName->expansion.empty())
            p_iterName = std::make_shared<ASTLine>(astlist.data[p_iterName->expansion.front()]);
        if (iterName != p_iterName->key.token.getTokStr())
        {
            std::cerr << "getForloopmeta error: iterName != p_iterName->key.token.getTokStr()" << std::endl;
            return;
        }

        // check relation
        std::shared_ptr<ASTLine> p_relation = std::make_shared<ASTLine>(astlist.data[p_line->expansion[1]]);
        if (!p_relation->expansion.empty())
        {
            std::cerr << "getForloopmeta error: !p_relation->expansion.empty()" << std::endl;
            return;
        }

        relation = p_relation->key.token.getTokType();
        if (relation != TT_ANGLE_BRACKET_L && relation != TT_ANGLE_BRACKET_R &&
            relation != LEQ && relation != GEQ)
        {
            std::cerr << "getForloopmeta error: unrecognized relation" << std::endl;
            return;
        }

        // find range end
        std::shared_ptr<ASTLine> p_range2 = std::make_shared<ASTLine>(astlist.data[p_line->expansion.back()]);
        if (p_range2->expansion.size() != 1)
        {
            std::cerr << "getForloopmeta error: unrecognized range end" << std::endl;
            return;
        }
        while (!p_range2->expansion.empty())
            p_range2 = std::make_shared<ASTLine>(astlist.data[p_range2->expansion.back()]);
        range._end = p_range2->key.token.getTokStr();

        // check block3
        const auto &block3 = astlist.data[block3_idx];
        if (block3.expansion.size() == 2)
        {
            if (astlist.data[block3.expansion.front()].key.token.getTokType() == INCREASE)
            {
                p_iterName = std::make_shared<ASTLine>(astlist.data[block3.expansion.back()]);
                while (!p_iterName->expansion.empty())
                    p_iterName = std::make_shared<ASTLine>(astlist.data[p_iterName->expansion.back()]);
                if (p_iterName->key.token.getTokStr() != iterName)
                {
                    std::cerr << "getForloopmeta error: p_iterName->key.token.getTokStr() != iterName" << std::endl;
                    return;
                }
                stride = "1";
                return;
            }
            else if (astlist.data[block3.expansion.back()].key.token.getTokType() == INCREASE)
            {
                p_iterName = std::make_shared<ASTLine>(astlist.data[block3.expansion.front()]);
                while (!p_iterName->expansion.empty())
                    p_iterName = std::make_shared<ASTLine>(astlist.data[p_iterName->expansion.front()]);
                if (p_iterName->key.token.getTokStr() != iterName)
                {
                    std::cerr << "getForloopmeta error: p_iterName->key.token.getTokStr() != iterName" << std::endl;
                    return;
                }
                stride = "1";
                return;
            }
            std::cerr << "unrecognized stride adder" << std::endl;
            return;
        }
        else if (block3.expansion.size() == 3)
        {
            p_iterName = std::make_shared<ASTLine>(astlist.data[block3.expansion.front()]);
            while (!p_iterName->expansion.empty())
                p_iterName = std::make_shared<ASTLine>(astlist.data[p_iterName->expansion.front()]);
            if (p_iterName->key.token.getTokStr() != iterName)
            {
                std::cerr << "getForloopmeta error: p_iterName->key.token.getTokStr() != iterName" << std::endl;
                return;
            }
            std::shared_ptr<ASTLine> p_adder = std::make_shared<ASTLine>(astlist.data[block3.expansion[1]]);
            if (p_adder->key.token.getTokType() != ASSIGN_ADD)
            {
                std::cerr << "getForloopmeta error: unrecognized adder" << std::endl;
                return;
            }
            std::shared_ptr<ASTLine> p_stride = std::make_shared<ASTLine>(astlist.data[block3.expansion.back()]);
            if (p_stride->expansion.size() != 1)
            {
                std::cerr << "getFroloopmeta error: unrecognized stride" << std::endl;
                return;
            }
            while (!p_stride->expansion.empty())
                p_stride = std::make_shared<ASTLine>(astlist.data[p_stride->expansion.back()]);
            stride = p_stride->key.token.getTokStr();
        }
        else
        {
            std::cerr << "getForloopmeta error: illegal stride expression" << std::endl;
            return;
        }
    }

    std::string iterName; // 迭代变量名 
    Range<std::string> range; // 迭代范围
    TokType relation = LEQ; // 迭代变量比较关系
    Range<size_t> range_num; // 整数格式的迭代范围
    std::string stride; // 迭代步长
    size_t stride_num; // 整数格式的迭代步长
    size_t forloopIdx; // 循环在ASTList中的起始点
    std::shared_ptr<ASTList> p_astlist; // 对应的ASTList
    std::vector<std::shared_ptr<ForLoop>> innerLoops; // 嵌套循环
};