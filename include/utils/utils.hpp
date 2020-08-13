#ifndef UTILS_HPP
#define UTILS_HPP
#include <vector>

template <typename type>
struct Range
{
    type _start;
    type _end;
};

template <typename type>
static std::vector<type> getSubVector(const std::vector<type> &vec, const size_t &_pos, const size_t &_size)
{
    std::vector<type> ret(_size);
    for (size_t i = _pos, j = 0; i < vec.size() && j < _size; i++, j++)
        ret[j] = vec[i];
    return ret;
}
#endif