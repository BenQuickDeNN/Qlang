#ifndef LEXER_HPP
#define LEXER_HPP

#include <vector>
#include <iostream>
#include "key_words.hpp"
#include "token.hpp"
#include "jump_table.hpp"

/**
 * @brief 词法分析器
 */
class Lexer
{
public:
    Lexer() {}
    static std::vector<Token> lexStr(const std::string &str)
    {
        std::vector<Token> ret;
        size_t idx = 0;
        size_t row = 1;
        size_t charCount = 0;
        char c;
        CharType ct;
        JumpState state = JumpState::START;
        JumpState last_state;
        std::string tmp_str = "";
        while (idx < str.size())
        {
            c = str[idx];
            // std::cout << "get '" << c << "', ascii=" << (int)c << std::endl;
            ct = getCharType(c);
            last_state = state;
            if (JUMP_TABLE.find({state, ct}) != JUMP_TABLE.end())
                state = JUMP_TABLE[{state, ct}]; // jump state
            else
            {
                std::cerr << "lex error in idx=" << idx << ", c='" << c << "': unknown state or chartype" << std::endl;
                std::cerr << "state=" << state << ", last_state=" << last_state << ", ct=" << ct << std::endl;
                logError(row, idx + 1 - charCount, c);
                return std::vector<Token>(0);
            }

            // jump
            switch (state)
            {
            case JumpState::START:
                // 从注释段恢复
                if (ct == CharType::CT_DIV && last_state == JumpState::STATE12)
                    ++idx;
                else if (ct == CharType::ENTER && last_state == JumpState::STATE13)
                {
                    ++row;
                    ++idx;
                }
                break;

            // NAME
            case JumpState::CHECK_KEYWORD:
                if (isKeyWord(tmp_str))
                    ret.emplace_back(Token(tmp_str, TokType::KEY_WORD));
                else
                    ret.emplace_back(Token(tmp_str, TokType::NAME));
                tmp_str = "";
                state = JumpState::START;
                if (checkBackward(ct, CharType::CT_COMMA, CharType::CT_DOT, CharType::CT_SEMI,
                                  CharType::CT_ASSIGN, CharType::CT_PARENTHESES_L, CharType::CT_PARENTHESES_R, CharType::CT_BRACKET_L,
                                  CharType::CT_BRACKET_R, CharType::CT_BRACE_L, CharType::CT_ANGLE_BRACKET_L, CharType::CT_ANGLE_BRACKET_R,
                                  CharType::SPACE, CharType::ENTER, CharType::CT_EOF,
                                  CharType::CT_ADD, CharType::CT_SUB, CharType::CT_MUL, CharType::CT_DIV,
                                  CharType::CT_AND, CharType::CT_OR))
                    --idx;
                break;

            // number
            case JumpState::TOK_INTEGER:
                ret.emplace_back(Token(tmp_str, TokType::INTEGER));
                tmp_str = "";
                state = JumpState::START;
                if (checkBackward(ct, CharType::CT_COMMA, CharType::CT_DOT, CharType::CT_SEMI,
                                  CharType::CT_PARENTHESES_R, CharType::CT_BRACE_R, CharType::CT_ANGLE_BRACKET_R,
                                  CharType::SPACE, CharType::ENTER, CharType::CT_EOF,
                                  CharType::CT_ADD, CharType::CT_SUB, CharType::CT_MUL, CharType::CT_DIV,
                                  CharType::CT_AND, CharType::CT_OR))
                    --idx;
                break;
            case JumpState::TOK_FLOAT_POINT:
                ret.emplace_back(Token(tmp_str, TokType::FLOAT_POINT));
                tmp_str = "";
                state = JumpState::START;
                if (checkBackward(ct, CharType::CT_COMMA, CharType::CT_DOT,
                                  CharType::CT_SEMI, CharType::CT_PARENTHESES_R, CharType::CT_BRACKET_R,
                                  CharType::SPACE, CharType::ENTER, CharType::CT_EOF,
                                  CharType::CT_ADD, CharType::CT_SUB, CharType::CT_MUL, CharType::CT_DIV,
                                  CharType::CT_AND, CharType::CT_OR))
                    --idx;
                break;

            // end symbols
            case JumpState::TOK_COMMA:
                tmp_str = c;
                ret.emplace_back(Token(tmp_str, TokType::TT_COMMA));
                tmp_str = "";
                state = JumpState::START;
                break;
            case JumpState::TOK_DOT:
                tmp_str = c;
                ret.emplace_back(Token(tmp_str, TokType::TT_DOT));
                tmp_str = "";
                state = JumpState::START;
                break;
            case JumpState::TOK_SEMI:
                tmp_str = c;
                ret.emplace_back(Token(tmp_str, TokType::TT_SEMI));
                tmp_str = "";
                state = JumpState::START;
                break;

            // symbols
            case JumpState::TOK_EQUAL:
                tmp_str += c;
                ret.emplace_back(Token(tmp_str, TokType::TT_EQUAL));
                tmp_str = "";
                state = JumpState::START;
                break;
            case JumpState::TOK_ASSIGN:
                ret.emplace_back(Token(tmp_str, TokType::TT_ASSIGN));
                tmp_str = "";
                state = JumpState::START;
                if (checkBackward(ct, CharType::CT_PARENTHESES_L, CharType::ALPHA,
                                  CharType::DIGIT, CharType::CT_BRACKET_L, CharType::SPACE, CharType::ENTER,
                                  CharType::CT_NOT))
                    --idx;
                break;

            // 括号
            case JumpState::TOK_PARENTHESES_L:
                tmp_str = c;
                ret.emplace_back(Token(tmp_str, TokType::TT_PARENTHESES_L));
                tmp_str = "";
                state = JumpState::START;
                break;
            case JumpState::TOK_PARENTHESES_R:
                tmp_str = c;
                ret.emplace_back(Token(tmp_str, TokType::TT_PARENTHESES_R));
                tmp_str = "";
                state = JumpState::START;
                break;
            case JumpState::TOK_BRACKET_L:
                tmp_str = c;
                ret.emplace_back(Token(tmp_str, TokType::TT_BRACKET_L));
                tmp_str = "";
                state = JumpState::START;
                break;
            case JumpState::TOK_BRACKET_R:
                tmp_str = c;
                ret.emplace_back(Token(tmp_str, TokType::TT_BRACKET_R));
                tmp_str = "";
                state = JumpState::START;
                break;
            case JumpState::TOK_BRACE_L:
                tmp_str = c;
                ret.emplace_back(Token(tmp_str, TokType::TT_BRACE_L));
                tmp_str = "";
                state = JumpState::START;
                break;
            case JumpState::TOK_BRACE_R:
                tmp_str = c;
                ret.emplace_back(Token(tmp_str, TokType::TT_BRACE_R));
                tmp_str = "";
                state = JumpState::START;
                break;
            case JumpState::TOK_ANGLE_BRACKET_L:
                ret.emplace_back(Token(tmp_str, TokType::TT_ANGLE_BRACKET_L));
                tmp_str = "";
                state = JumpState::START;
                if (checkBackward(ct, CharType::SPACE, CharType::ENTER, CharType::ALPHA, CharType::UNDERLINE, CharType::DIGIT, CharType::CT_PARENTHESES_L))
                    --idx;
                break;
            case JumpState::TOK_ANGLE_BRACKET_R:
                ret.emplace_back(Token(tmp_str, TokType::TT_ANGLE_BRACKET_R));
                tmp_str = "";
                state = JumpState::START;
                if (checkBackward(ct, CharType::SPACE, CharType::ENTER, CharType::ALPHA, CharType::UNDERLINE, CharType::CT_PARENTHESES_L, CharType::CT_COMMA))
                    --idx;
                break;

            // arithmetic
            case JumpState::TOK_MOVE_L:
                tmp_str += c;
                ret.emplace_back(Token(tmp_str, TokType::MOVE_L));
                tmp_str = "";
                state = JumpState::START;
                break;
            case JumpState::TOK_MOVE_R:
                tmp_str += c;
                ret.emplace_back(Token(tmp_str, TokType::MOVE_R));
                tmp_str = "";
                state = JumpState::START;
                break;

            case JumpState::TOK_ADD:
                ret.emplace_back(Token(tmp_str, TokType::ADD));
                tmp_str = "";
                state = JumpState::START;
                if (checkBackward(ct, CharType::SPACE, CharType::ENTER, CharType::ALPHA, CharType::DIGIT, CharType::UNDERLINE, CharType::CT_PARENTHESES_L,
                            CharType::CT_NOT))
                    --idx;
                break;
            case JumpState::TOK_SUB:
                ret.emplace_back(Token(tmp_str, TokType::SUB));
                tmp_str = "";
                state = JumpState::START;
                if (checkBackward(ct, CharType::SPACE, CharType::ENTER, CharType::ALPHA, CharType::DIGIT, CharType::UNDERLINE, CharType::CT_PARENTHESES_L,
                            CharType::CT_NOT))
                    --idx;
                break;
            case JumpState::TOK_MUL:
                ret.emplace_back(Token(tmp_str, TokType::MUL));
                tmp_str = "";
                state = JumpState::START;
                if (checkBackward(ct, CharType::SPACE, CharType::ENTER, CharType::ALPHA, CharType::DIGIT, CharType::UNDERLINE, CharType::CT_PARENTHESES_L,
                            CharType::CT_NOT))
                    --idx;
                break;
            case JumpState::TOK_DIV:
                ret.emplace_back(Token(tmp_str, TokType::DIV));
                tmp_str = "";
                state = JumpState::START;
                if (checkBackward(ct, CharType::SPACE, CharType::ENTER, CharType::ALPHA, CharType::DIGIT, CharType::UNDERLINE, CharType::CT_PARENTHESES_L,
                            CharType::CT_NOT))
                    --idx;
                break;
            case JumpState::TOK_AND:
                ret.emplace_back(Token(tmp_str, TokType::AND));
                tmp_str = "";
                state = JumpState::START;
                if (checkBackward(ct, CharType::SPACE, CharType::ENTER, CharType::ALPHA, CharType::DIGIT, CharType::UNDERLINE, CharType::CT_PARENTHESES_L,
                            CharType::CT_NOT))
                    --idx;
                break;
            case JumpState::TOK_OR:
                ret.emplace_back(Token(tmp_str, TokType::OR));
                tmp_str = "";
                state = JumpState::START;
                if (checkBackward(ct, CharType::SPACE, CharType::ENTER, CharType::ALPHA, CharType::DIGIT, CharType::UNDERLINE, CharType::CT_PARENTHESES_L,
                            CharType::CT_NOT))
                    --idx;
                break;
            case JumpState::TOK_NOT:
                ret.emplace_back(Token(tmp_str, TokType::NOT));
                tmp_str = "";
                state = JumpState::START;
                if (checkBackward(ct, CharType::SPACE, CharType::ENTER, CharType::ALPHA, CharType::DIGIT, CharType::UNDERLINE, CharType::CT_PARENTHESES_L,
                            CharType::CT_NOT))
                    --idx;
                break;

            case JumpState::TOK_INCREASE:
                tmp_str += c;
                ret.emplace_back(Token(tmp_str, TokType::INCREASE));
                tmp_str = "";
                state = JumpState::START;
                break;
            case JumpState::TOK_DECREASE:
                tmp_str += c;
                ret.emplace_back(Token(tmp_str, TokType::DECREASE));
                tmp_str = "";
                state = JumpState::START;
                break;
            case JumpState::TOK_BOOL_AND:
                tmp_str += c;
                ret.emplace_back(Token(tmp_str, TokType::BOOL_AND));
                tmp_str = "";
                state = JumpState::START;
                break;
            case JumpState::TOK_BOOL_OR:
                tmp_str += c;
                ret.emplace_back(Token(tmp_str, TokType::BOOL_OR));
                tmp_str = "";
                state = JumpState::START;
                break;

            case JumpState::TOK_ASSIGN_ADD:
                tmp_str += c;
                ret.emplace_back(Token(tmp_str, TokType::ASSIGN_ADD));
                tmp_str = "";
                state = JumpState::START;
                break;
            case JumpState::TOK_ASSIGN_SUB:
                tmp_str += c;
                ret.emplace_back(Token(tmp_str, TokType::ASSIGN_SUB));
                tmp_str = "";
                state = JumpState::START;
                break;
            case JumpState::TOK_ASSIGN_MUL:
                tmp_str += c;
                ret.emplace_back(Token(tmp_str, TokType::ASSIGN_MUL));
                tmp_str = "";
                state = JumpState::START;
                break;
            case JumpState::TOK_ASSIGN_DIV:
                tmp_str += c;
                ret.emplace_back(Token(tmp_str, TokType::ASSIGN_DIV));
                tmp_str = "";
                state = JumpState::START;
                break;
            case JumpState::TOK_ASSIGN_AND:
                tmp_str += c;
                ret.emplace_back(Token(tmp_str, TokType::ASSIGN_AND));
                tmp_str = "";
                state = JumpState::START;
                break;
            case JumpState::TOK_ASSIGN_OR:
                tmp_str += c;
                ret.emplace_back(Token(tmp_str, TokType::ASSIGN_OR));
                tmp_str = "";
                state = JumpState::START;
                break;
            case JumpState::TOK_ASSIGN_NOT:
                tmp_str += c;
                ret.emplace_back(Token(tmp_str, TokType::ASSIGN_NOT));
                tmp_str = "";
                state = JumpState::START;
                break;

            case JumpState::TOK_LEQ:
                tmp_str += c;
                ret.emplace_back(Token(tmp_str, TokType::LEQ));
                tmp_str = "";
                state = JumpState::START;
                break;
            case JumpState::TOK_GEQ:
                tmp_str += c;
                ret.emplace_back(Token(tmp_str, TokType::GEQ));
                tmp_str = "";
                state = JumpState::START;
                break;

            // middle states
            case JumpState::STATE1:
                tmp_str += c;
                if (idx == str.size() - 1)
                    if (isKeyWord(tmp_str))
                        ret.emplace_back(Token(tmp_str, TokType::KEY_WORD));
                    else
                        ret.emplace_back(Token(tmp_str, TokType::NAME));
                break;
            case JumpState::STATE2:
                tmp_str += c;
                if (idx == str.size() - 1)
                    ret.emplace_back(Token(tmp_str, TokType::INTEGER));
                break;
            case JumpState::STATE3:
                tmp_str += c;
                if (idx == str.size() - 1)
                    ret.emplace_back(Token(tmp_str, TokType::FLOAT_POINT));
                break;
            case JumpState::STATE4:
                tmp_str += c;
                break;
            case JumpState::STATE5:
                tmp_str += c;
                break;
            case JumpState::STATE6:
                tmp_str += c;
                break;
            case JumpState::STATE7:
                tmp_str += c;
                break;
            case JumpState::STATE8:
                tmp_str += c;
                break;
            case JumpState::STATE9:
                tmp_str += c;
                break;
            case JumpState::STATE10:
                tmp_str += c;
                break;
            case JumpState::STATE11:
                // do nothing
                break;
            case JumpState::STATE12:
                // do nothing
                break;
            case JumpState::STATE13:
                // do nothing
                break;
            case JumpState::STATE14:
                // do nothing
                break;
            case JumpState::STATE15:
                tmp_str += c;
                break;
            case JumpState::STATE16:
                tmp_str += c;
                break;
            case JumpState::STATE17:
                tmp_str += c;
                break;

            // no token
            case JumpState::NO_TOKEN:
                tmp_str = "";
                state = JumpState::START;
                break;

            // error occur
            default:
                std::cerr << "lex error in idx=" << idx << ", c='" << c << "': unknown state or chartype" << std::endl;
                return std::vector<Token>(0);
                break;
            }
            if (getCharType(str[idx]) == CharType::ENTER)
            {
                ++row;
                charCount = idx + 1;
            }
            ++idx;
        }
        return ret;
    }

    /**
     * @brief 检查某个字符串是否是关键字
     */
    static bool isKeyWord(const std::string &str)
    {
        return KEY_WORDS.find(str) != KEY_WORDS.end();
    }

    /**
     * @brief 判断索引是否要减一
     */
    template <typename type, typename... types>
    static bool checkBackward(const type &ct, const type &ctype, types... args)
    {
        return checkBackward(ct, ctype) || checkBackward(ct, args...);
    }

private:
    static bool checkBackward(const CharType &ct, const CharType &ctype)
    {
        return ct == ctype;
    }
    static void logError(const size_t &row, const size_t &col, const char &c)
    {
        std::cerr << "lex error in line " << row
                  << ", column " << col
                  << ", bad character '" << c << "'." << std::endl;
    }
};

#endif