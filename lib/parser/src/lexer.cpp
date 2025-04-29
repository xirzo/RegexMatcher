#include "lexer.h"

namespace parser {

Token lex(const char& symbol) {
    switch (symbol) {
        case '(': {
            return Token::LPARENTH;
        }
        case ')': {
            return Token::RPARENTH;
        }
        case '*': {
            return Token::KLEENE;
        }
        case '+': {
            return Token::CONCAT;
        }
        case '|': {
            return Token::OR;
        }
        default: {
            if (isalnum(symbol)) {
                return Token::SYMBOL;
            }

            return Token::UNKNOWN;
        }
    }
}

std::expected<std::vector<Token>, std::string> lex(const std::string& text) {
    if (text.size() == 0) {
        return std::unexpected("Trying to lex an empty string");
    }

    std::vector<Token> tokens;

    for (std::size_t i = 0; i < text.size(); i++) {
        Token token = lex(text[i]);

        if (token == Token::UNKNOWN) {
            return std::unexpected("Got UNKNOWN token, while parsing: " +
                                   std::to_string(text[i]));
        }

        tokens.push_back(token);
    }

    return tokens;
}

bool isOperator(const Token& token) {
    return token == Token::CONCAT || token == Token::KLEENE || token == Token::OR;
}

int getPrecedence(const Token& token) {
    switch (token) {
        case Token::OR:
            return 1;
        case Token::CONCAT:
            return 2;
        case Token::KLEENE:
            return 3;
        default:
            return 0;
    }
}

};  // namespace parser
