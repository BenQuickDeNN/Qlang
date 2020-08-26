#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include "../lexer/lexer.hpp"
#include "../parser/parser.hpp"

// 三地址码
struct TACode
{
    uint64_t op; // 操作符
    uint64_t addr1; // 操作数1
    uint64_t addr2; // 操作数2
    uint64_t addr_res; // 结果
    void operator = (uint64_t arr[4])
    {
        op = arr[0];
        addr1 = arr[1];
        addr2 = arr[2];
        addr_res = arr[3];
    }
};

// 为了和LLVM的IR区分，加一个命名空间
namespace qlang
{
    class IR
    {
    public:
        static std::vector<TACode> toTACodes(const ASTList &astlist)
        {
        }

        static TACode toTACode(const ASTList &astlist, const size_t &idx)
        {
            if (idx >= astlist.data.size())
                return {0, 0, 0, 0};
            const auto &astline = astlist.data[idx];
        }
    
    private:
        std::vector<TACode> tac_list;
    };
}