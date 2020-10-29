#pragma once

#include <string>
#include <vector>

namespace jacobi
{
    template <size_t dim, typename type>
    struct Tuple
    {
    public:
        Tuple & operator[](const size_t &_rank)
        {
            return data[_rank];
        }
    private:
        std::vector<type> data;
    };
    
    /**
     * @brief Jacobi Stencl 基本操作
     */
    template <size_t dim>
    struct Operation
    {
        std::string var_w; // 写变量名
        std::string var_r; // 读变量名
        Tuple<dim, std::string> offset_w; // 写地址
        std::vector<std::string> offsets_r; // 读地址序列
    };
    
}
