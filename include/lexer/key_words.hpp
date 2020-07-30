#ifndef KEY_WORDS_HPP
#define KEY_WORDS_HPP
#include <string>
#include <map>
static const size_t NUM_KEY_WORDS = 1;
static const std::map<std::string, int> KEY_WORDS = {
    {"int", 0},
    {"for", 1},
    {"class", 2},
    {"void", 3},
    {"return", 4}

};
#endif