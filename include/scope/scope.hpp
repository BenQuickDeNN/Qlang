#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "../lexer/token.hpp"
static bool checkStr(const std::string &line, const std::string &str) noexcept
{
    size_t left = line.find(str);
    if (left == line.npos) 
        return false;
    size_t right = left + str.size();
    if (left > 0)
    {
        --left;
        while (left >= 0)
            if (line[left--] != ' ')
                return false;
    }
    while (right < line.size())
        if (line[right++] != ' ')
            return false;
    return true;
}
/**
 * @brief 获取字符串中 #pragma scope 与 #pragma endscop 之间的 字符串
 */
static std::vector<std::string> getScopes(const std::string &str) noexcept
{
    std::string line = "";
    std::vector<std::string> ret;
    bool isApp = false;
    for (const char &c : str)
    {
        if (getCharType(c) == CharType::ENTER)
        {
            if (checkStr(line, "#pragma scope"))
            {
                if (isApp)
                {
                    std::cerr << "endscope error: no \"#pragma endscope\" statement at scope " << ret.size() << std::endl;
                    if (!ret.empty())
                        ret.pop_back();
                }
                isApp = true;
                ret.push_back("");
            }
            else if (checkStr(line, "#pragma endscope"))
            {
                const size_t idx = ret.size() - 1;
                if (idx >= ret.size())
                {
                    std::cerr << "endscope error" << std::endl;
                    return {};
                }
                ret[idx] = ret[idx].substr(0, ret[idx].size() - 1);
                isApp = false;
            }
            else if (isApp)
                ret[ret.size() - 1] += line + '\n';
            line = "";
        }
        else
            line += c;
    }
    if (isApp)
    {
        std::cerr << "endscope error: no \"#pragma endscope\" statement at scope " << ret.size() << std::endl;
        if (!ret.empty())
            ret.pop_back();
    }
    return ret;
}