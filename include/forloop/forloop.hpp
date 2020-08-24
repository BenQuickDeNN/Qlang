#pragma once
#include <vector>
#include <memory>
#include <string>
#include <stack>
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
        ret += "range = [" + range._start + ',' + range._end + "]; ";
        ret += "stride = " + iterStride + '\n';
        for (const auto &innerloop : innerLoops)
            ret += '\t' + innerloop->toString();
        return ret;
    }
    void initFromASTList(const ASTList &astlist)
    {
        initFromASTList(astlist, astlist.data.size() - 1);
    }
private:
    void initFromASTList(const ASTList &astlist, const size_t &maxIdx)
    {
        if (maxIdx >= astlist.data.size())
            return;
        size_t forloopIdx;
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
        const size_t forloopmetaIdx = forloopLine.expansion.front();
        auto &forloopmetaLine = astlist.data[forloopmetaIdx];
        getForloopmeta(astlist, forloopmetaLine);
    }

    void getForloopmeta(const ASTList &astlist, const ASTLine &forloopmetaLine)
    {
        if (forloopmetaLine.key.token.getTokType() != (TokType)forloop_meta)
            return;
        if (forloopmetaLine.expansion.size() != 8)
            return;
        const size_t block1_idx = forloopmetaLine.expansion[2];
        const size_t block2_idx = forloopmetaLine.expansion[4];
        const size_t block3_idx = forloopmetaLine.expansion[6];

        // check block1
        auto &block1 = astlist.data[block1_idx];
        std::shared_ptr<ASTLine> p_line = std::make_shared<ASTLine>(block1);
        while (!p_line->expansion.empty())
        {
            if (p_line->expansion.size() == 3)
                break;
            p_line = std::make_shared<ASTLine>(astlist.data[p_line->expansion.back()]);
        }
        if (p_line->expansion.size() != 3)
            return;
        // check assign
        if (astlist.data[p_line->expansion[1]].key.token.getTokType() != TT_ASSIGN)
            return;

        // find itername
        std::shared_ptr<ASTLine> p_iterName = std::make_shared<ASTLine>(astlist.data[p_line->expansion.front()]);
        while (!p_iterName->expansion.empty())
            p_iterName = std::make_shared<ASTLine>(astlist.data[p_iterName->expansion.front()]);
        iterName = p_iterName->key.token.getTokStr();

        // range 的获取非常复杂
        // find range start
        std::shared_ptr<ASTLine> p_range1 = std::make_shared<ASTLine>(astlist.data[p_line->expansion.back()]);
        while (!p_range1->expansion.empty())
            p_range1 = std::make_shared<ASTLine>(astlist.data[p_range1->expansion.back()]);
        range._start = p_range1->key.token.getTokStr();

        // check block2
        auto &block2 = astlist.data[block2_idx];
        p_line = std::make_shared<ASTLine>(block2);
        while (!p_line->expansion.empty())
        {
            if (p_line->expansion.size() == 3)
                break;
            p_line = std::make_shared<ASTLine>(astlist.data[p_line->expansion.back()]);
        }
        if (p_line->expansion.size() != 3)
            return;

        // check itername
        std::shared_ptr<ASTLine> p_iterName = std::make_shared<ASTLine>(astlist.data[p_line->expansion.front()]);
        while (!p_iterName->expansion.empty())
            p_iterName = std::make_shared<ASTLine>(astlist.data[p_iterName->expansion.front()]);
        if (iterName != p_iterName->key.token.getTokStr())
            return;


    }
    // 迭代变量名
    std::string iterName;
    // 迭代范围
    Range<std::string> range;
    // Range<std::vector<Token>> range;
    Range<size_t> range_num; // 数字格式的range
    // 迭代步长
    std::string iterStride;
    // 嵌套循环
    std::vector<std::shared_ptr<ForLoop>> innerLoops;
};