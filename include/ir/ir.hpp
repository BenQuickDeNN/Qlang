#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <iostream>
#include "../lexer/lexer.hpp"
#include "../parser/parser.hpp"

// 三地址码
struct TACode
{
    uint64_t op; // 操作符
    uint64_t addr1; // 操作数1
    uint64_t addr2; // 操作数2
    uint64_t addr_res; // 结果
    std::string toString()
    {
        return std::to_string(op) + std::to_string(addr1) + 
            std::to_string(addr2) + std::to_string(addr_res);
    }
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
        void buildTACList(const std::shared_ptr<ASTNode> node)
        {
            // 和构建ASTList一样采用后序遍历
            if (node == nullptr)
                return;
            for (const auto &child : node->children)
                buildTACList(child);
            addTACode(node);
        }

        /**
         * @note 这种构建三地址码的方法暂时还区分不了不同作用域的相同变量名
         * @note 这种构建三地址码的方法暂时还区分不了变量和数组名
         */
        void addTACode(const std::shared_ptr<ASTNode> node)
        {
            if (node == nullptr)
                return;
            if (node->children.empty())
                return;
            const auto tok_type = node->token.getTokType();
            if (tok_type == forloop)
            {

            }
            else if (tok_type == expr)
            {
                if (node->children.size() == 3)
                {
                    auto p_op = node->children.at(1);
                    while (!p_op->children.empty())
                        p_op = p_op->children.front();
                    auto p_addr1 = p_op->children.front();
                    uint64_t addr1;
                    if (p_addr1->children.size() == 1)
                    {
                        while (!p_addr1->children.empty())
                            p_addr1 = p_addr1->children.front();
                        const auto& _name = p_addr1->token.getTokStr();
                        const auto& it = addrMap.find(_name);
                        if (it == addrMap.end())
                        {
                            addr1 = getVarCount();
                            nameMap.insert({addr1, p_addr1->token.getTokStr()});
                            addrMap.insert({p_addr1->token.getTokStr(), addr1});
                        }
                        else
                        {

                        }
                    }
                    else
                        addr1 = getVarCount();
                    auto p_addr2 = node->children.back();
                    uint64_t addr2 = getVarCount();
                }
                else if (node->children.size() == 2)
                {

                }
            }
        }
    
    private:
        std::vector<TACode> tac_list;
        uint64_t var_count = 0;
        uint64_t getVarCount() { return ++var_count; }
        std::unordered_map<uint64_t, std::string> nameMap;
        std::unordered_map<std::string, uint64_t> addrMap;
    };
}