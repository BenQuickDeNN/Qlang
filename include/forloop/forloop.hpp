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
    std::string toString()
    {

    }
    // 迭代变量名
    std::string iterName;
    // 迭代范围
    Range<size_t> range;
    // 迭代步长
    size_t iterStride = 1;
    // 嵌套循环
    std::vector<std::shared_ptr<ForLoop>> innerLoops;
};