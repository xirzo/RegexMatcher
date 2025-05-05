#include "ast.h"
#include "parser.h"
#include <iostream>
#include <memory>

#ifndef MATCHER_H

namespace parser {

bool matches(const std::string &regex, const std::string &input) {
  auto ast_exp = parser::parse(regex);

  if (!ast_exp) {
    std::cerr << "Parse error: " << ast_exp.error() << std::endl;
    return false;
  }

  std::shared_ptr<parser::ASTNode> ast = ast_exp.value();
  std::size_t pos = 0;
  bool matched = ast->evaluate(input, pos);

  return matched && pos == input.length();
}

} // namespace parser

#endif // !MATCHER_H
