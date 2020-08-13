#ifndef LOOP_TUPLE_HPP
#define LOOP_TUPLE_HPP
#include <string>
#include <vector>
/**
 * @brief memory address
 */
struct Address
{
    std::string name;
    std::vector<std::string> offsets; // offsets[i] denotes the ist-dimention offset
};
struct LoopTuple
{
    Address addrW; // address for write
    std::vector<Address> addrRs; // addresses for read
};

#endif