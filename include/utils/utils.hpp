#pragma once
#include <vector>
#include <string>

template <typename type>
struct Range
{
    type _start;
    type _end;
    void setRange(const type &_start, const type &_end)
    {
        this->_start = _start;
        this->_end = _end;
    }
    void operator = (const type _range[2])
    {
        _start = _range[0];
        _end = _range[1];
    }
};

template <typename type>
static bool operator == (const Range<type> &range1, const Range<type> &range2)
{
    return range1._start == range2._start && range1._end == range2._end;
}

template <typename type>
static bool operator != (const Range<type> &range1, const Range<type> &range2)
{
    return !(range1 == range2);
}


template <typename type>
static std::vector<type> getSubVector(const std::vector<type> &vec, const size_t &_pos, const size_t &_size)
{
    std::vector<type> ret(_size);
    for (size_t i = _pos, j = 0; i < vec.size() && j < _size; i++, j++)
        ret[j] = vec[i];
    return ret;
}