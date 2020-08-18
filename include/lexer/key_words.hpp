#pragma once
#include <string>
#include <map>
#include "token.hpp"

static const std::map<std::string, TokType> KEY_WORDS = {

    // common
    {"return", TokType::KEY_RETURN},
    {"using", TokType::KEY_USING},
    {"namespace", TokType::KEY_NAMESPACE},
    {"typedef", TokType::KEY_TYPEDEF},

    // loop
    {"for", TokType::KEY_FOR},
    {"while", TokType::KEY_WHILE},
    {"do", TokType::KEY_DO},
    {"break", TokType::KEY_BREAK},
    {"continue", TokType::KEY_CONTINUE},

    // object
    {"class", TokType::KEY_CLASS},
    {"struct", TokType::KEY_STRUCT},
    {"enum", TokType::KEY_ENUM},
    {"template", TokType::KEY_TEMPLATE}, 

    // decorate
    {"static", TokType::KEY_STATIC},
    {"const", TokType::KEY_CONST},
    {"inline", TokType::KEY_INLINE},

    // condition
    {"if", TokType::KEY_IF},
    {"else", TokType::KEY_ELSE},
    {"switch", TokType::KEY_SWITCH},
    {"case", TokType::KEY_CASE},
    {"default", TokType::KEY_DEFAULT},

    // arithmetic
    {"sizeof", TokType::KEY_SIZEOF},

    // #
    {"#include", TokType::POUND_INCLUDE},
    {"#define", TokType::POUND_DEFINE},
    {"#pragma", TokType::POUND_PRAGMA},
    {"#if", TokType::POUND_IF},
    {"#else", TokType::POUND_ELSE},
    {"#elsif", TokType::POUND_ELSIF},
    {"#endif", TokType::POUND_ENDIF},
    {"#ifdef", TokType::POUND_IFDEF},
    {"#ifndef", TokType::POUND_IFNDEF}

};