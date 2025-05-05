#ifndef PARSER_H
#define PARSER_H

#include <expected>
#include <memory>
#include <stack>
#include <string>

#include "ast.h"
#include "lexer.h"

namespace parser {

std::expected<void, std::string>
applyOperator(std::stack<Token> &operators,
              std::stack<std::shared_ptr<ASTNode>> &nodes,
              const std::string &input);

std::expected<std::shared_ptr<ASTNode>, std::string>
parse(const std::string &regex);

namespace internal {
std::expected<std::shared_ptr<ASTNode>, std::string>
parseAlternation(const std::string &regex, size_t &pos);

std::expected<std::shared_ptr<ASTNode>, std::string>
parseConcatenation(const std::string &regex, size_t &pos);

std::expected<std::shared_ptr<ASTNode>, std::string>
parseRepetition(const std::string &regex, size_t &pos);

std::expected<std::shared_ptr<ASTNode>, std::string>
parseAtom(const std::string &regex, size_t &pos);
}; // namespace internal

}; // namespace parser

#endif // PARSER_H
