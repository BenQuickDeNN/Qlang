#ifndef KEY_WORDS_HPP
#define KEY_WORDS_HPP
#include <string>
#include <map>
enum KeyToken
{
    KEY_RETURN,

    KEY_FOR,
    KEY_WHILE,
    KEY_DO,

    KEY_CLASS,
    KEY_STRUCT,
    KEY_ENUM,
    
    KEY_STATIC,
    KEY_CONST,
    KEY_INLINE,

    KEY_IF,
    KEY_ELSE
};
static const std::map<std::string, KeyToken> KEY_WORDS = {
    {"for", KeyToken::KEY_FOR},
    {"while", KeyToken::KEY_WHILE},
    {"do", KeyToken::KEY_DO},
    {"class", KeyToken::KEY_CLASS},
    {"return", KeyToken::KEY_RETURN}

};
#endif