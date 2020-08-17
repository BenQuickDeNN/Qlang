#ifndef TOKEN_HPP
#define TOKEN_HPP
#include <string>
#include <cstdlib>
#include <iostream>
/**
 * @brief type of token
 */
enum TokType
{
    // common

    TT_DEFAULT,

    KEY_WORD,
    NAME,
    INTEGER,
    FLOAT_POINT,

    TT_COMMA,
    TT_DOT,
    TT_DOT3,
    TT_SEMI,
    TT_ASSIGN,
    TT_EQUAL,
    TT_NOT_EQUAL,
    TT_PARENTHESES_L,
    TT_PARENTHESES_R,
    TT_BRACKET_L,
    TT_BRACKET_R,
    TT_BRACE_L,
    TT_BRACE_R,
    TT_ANGLE_BRACKET_L,
    TT_ANGLE_BRACKET_R,
    COLON,
    COLON2,
    TT_QUES,

    MOVE_L,
    MOVE_R,
    ADD,
    SUB,
    MUL,
    DIV,
    AND,
    OR,
    NOT,
    MOD,
    XOR,
    INCREASE,
    DECREASE,
    BOOL_AND,
    BOOL_OR,
    BOOL_NOT,
    ASSIGN_ADD,
    ASSIGN_SUB,
    ASSIGN_MUL,
    ASSIGN_DIV,
    ASSIGN_AND,
    ASSIGN_OR,
    ASSIGN_NOT,
    ASSIGN_MOD,
    ASSIGN_XOR,

    LEQ,
    GEQ,

    POINT_TO,

    // key words

    KEY_RETURN,
    KEY_USING,
    KEY_NAMESPACE,
    KEY_TYPEDEF,

    KEY_FOR,
    KEY_WHILE,
    KEY_DO,
    KEY_BREAK,
    KEY_CONTINUE,

    KEY_CLASS,
    KEY_STRUCT,
    KEY_ENUM,
    KEY_TEMPLATE,
    
    KEY_STATIC,
    KEY_CONST,
    KEY_INLINE,

    KEY_IF,
    KEY_ELSE,
    KEY_SWITCH,
    KEY_CASE,
    KEY_DEFAULT,

    KEY_SIZEOF,

    // #
    POUND_INCLUDE,
    POUND_DEFINE,
    POUND_PRAGMA,
    POUND_IF,
    POUND_ELSE,
    POUND_ELSIF,
    POUND_ENDIF,
    POUND_IFDEF,
    POUND_IFNDEF,

    OP_LEVEL_6,

    // last
    LAST
};

/**
 * @brief type of character
 */
enum CharType
{
    CT_DEFAULT,

    ALPHA,
    UNDERLINE,
    DIGIT,

    SPACE,
    ENTER,
    CT_EOF,
    CT_ESCAPE_CHAR,

    CT_COMMA,
    CT_DOT,
    CT_SEMI,
    CT_ASSIGN,

    CT_PARENTHESES_L,
    CT_PARENTHESES_R,
    CT_BRACKET_L,
    CT_BRACKET_R,
    CT_BRACE_L,
    CT_BRACE_R,
    CT_ANGLE_BRACKET_L,
    CT_ANGLE_BRACKET_R,
    CT_COLON,
    CT_QUES,

    CT_ADD,
    CT_SUB,
    CT_MUL,
    CT_DIV,
    CT_AND,
    CT_OR,
    CT_NOT,
    CT_MOD,
    CT_XOR,
    CT_BOOL_NOT,

    CT_POUND
};

static CharType getCharType(const char &c)
{

    if (std::isalpha(c))
        return CharType::ALPHA;
    else if (std::isdigit(c))
        return CharType::DIGIT;
    else
        switch (c)
        {
        case ' ':
            return CharType::SPACE;
            break;
        case '\t':
            return CharType::SPACE;
            break;
        case '\r':
            return CharType::ENTER;
            break;
        case '\n':
            return CharType::ENTER;
            break;
        case '\\':
            return CharType::CT_ESCAPE_CHAR;
            break;

        case ',':
            return CharType::CT_COMMA;
            break;
        case '.':
            return CharType::CT_DOT;
            break;
        case ';':
            return CharType::CT_SEMI;
            break;

        case '=':
            return CharType::CT_ASSIGN;
            break;

        case '(':
            return CharType::CT_PARENTHESES_L;
            break;
        case ')':
            return CharType::CT_PARENTHESES_R;
            break;
        case '[':
            return CharType::CT_BRACKET_L;
            break;
        case ']':
            return CharType::CT_BRACKET_R;
            break;
        case '{':
            return CharType::CT_BRACE_L;
            break;
        case '}':
            return CharType::CT_BRACE_R;
            break;
        case '<':
            return CharType::CT_ANGLE_BRACKET_L;
            break;
        case '>':
            return CharType::CT_ANGLE_BRACKET_R;
            break;
        case ':':
            return CharType::CT_COLON;
            break;
        case '?':
            return CharType::CT_QUES;
            break;

        case '_':
            return CharType::UNDERLINE;
            break;

        case '+':
            return CharType::CT_ADD;
            break;
        case '-':
            return CharType::CT_SUB;
            break;
        case '*':
            return CharType::CT_MUL;
            break;
        case '/':
            return CharType::CT_DIV;
            break;
        case '&':
            return CharType::CT_AND;
            break;
        case '|':
            return CharType::CT_OR;
            break;
        case '~':
            return CharType::CT_NOT;
            break;
        case '^':
            return CharType::CT_XOR;
            break;
        case '!':
            return CharType::CT_BOOL_NOT;
            break;
        case '%':
            return CharType::CT_MOD;
            break;

        case '#':
            return CharType::CT_POUND;
            break;

        case EOF:
            return CharType::CT_EOF;
            break;

        default:
            return CharType::CT_DEFAULT;
            break;
        }
}

class Token
{

public:
    Token() {}
    Token(const TokType &tok_type) : tok_type(tok_type) {}
    Token(const std::string &tok_str, const TokType &tok_type) : tok_str(tok_str), tok_type(tok_type) {}
    std::string getTokStr() const {
        return tok_str;
    }
    void setTokStr(const std::string &tok_str) {
        this->tok_str = tok_str;
    }
    TokType getTokType() const {
        return tok_type;
    }
    void setTokType(const TokType &tok_type) {
        this->tok_type = tok_type;
    }
    static bool isToken(const unsigned int &tok)
    {
        return tok >= TokType::TT_DEFAULT && tok < TokType::LAST;
    }

private:
    std::string tok_str;
    TokType tok_type = TokType::TT_DEFAULT;
};
#endif