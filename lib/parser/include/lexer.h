#ifndef LEXER_H
#define LEXER_H

#include <expected>
#include <string>
#include <vector>

namespace parser {

enum class Token
{
    UNKNOWN,
    LPARENTH,
    RPARENTH,
    SYMBOL,
    KLEENE,
    CONCAT,
    OR
};

Token lex(const char& symbol);

std::expected<std::vector<Token>, std::string> lex(const std::string& text);

bool isOperator(const Token& token);

int getPrecedence(const Token& token);

};  // namespace parser

#endif  // LEXER_H
