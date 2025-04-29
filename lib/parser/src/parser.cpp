#include "parser.h"

namespace parser {

std::expected<void, std::string> applyOperator(
    std::stack<Token>& operators, std::stack<std::shared_ptr<ASTNode>>& nodes,
    const std::string& input) {
    if (operators.empty()) {
        return std::unexpected("No operator to apply");
    }

    Token op = operators.top();
    operators.pop();

    if (op == Token::KLEENE) {
        if (nodes.empty()) {
            return std::unexpected("Not enough operands for Kleene operator");
        }

        std::shared_ptr<ASTNode> operand = nodes.top();

        nodes.pop();
        nodes.push(std::make_shared<KleeneNode>(operand));
    } else if (op == Token::CONCAT) {
        if (nodes.size() < 2) {
            return std::unexpected("Not enough operands for concatenation");
        }
        auto right = nodes.top();
        nodes.pop();
        auto left = nodes.top();
        nodes.pop();
        nodes.push(std::make_shared<ConcatNode>(left, right));
    } else if (op == Token::OR) {
        if (nodes.size() < 2) {
            return std::unexpected("Not enough operands for alternation");
        }
        auto right = nodes.top();
        nodes.pop();
        auto left = nodes.top();
        nodes.pop();
        nodes.push(std::make_shared<OrNode>(left, right));
    }

    return {};
}

std::expected<std::shared_ptr<ASTNode>, std::string> parse(const std::string& regex) {
    size_t pos = 0;
    auto result = internal::parseAlternation(regex, pos);

    if (!result) {
        return std::unexpected(result.error());
    }

    if (pos != regex.length()) {
        return std::unexpected("Unexpected characters at end of regex");
    }

    return result;
}

namespace internal {

std::expected<std::shared_ptr<ASTNode>, std::string> parseAlternation(
    const std::string& regex, size_t& pos) {
    auto left = parseConcatenation(regex, pos);
    if (!left) {
        return left;
    }

    while (pos < regex.length() && regex[pos] == '|') {
        pos++;

        auto right = parseConcatenation(regex, pos);
        if (!right) {
            return right;
        }

        left = std::expected<std::shared_ptr<ASTNode>, std::string>(
            std::make_shared<OrNode>(left.value(), right.value()));
    }

    return left;
}

std::expected<std::shared_ptr<ASTNode>, std::string> parseConcatenation(
    const std::string& regex, size_t& pos) {
    auto left = parseRepetition(regex, pos);
    if (!left) {
        return left;
    }

    while (pos < regex.length() && regex[pos] != ')' && regex[pos] != '|') {
        auto right = parseRepetition(regex, pos);
        if (!right) {
            return right;
        }

        left = std::expected<std::shared_ptr<ASTNode>, std::string>(
            std::make_shared<ConcatNode>(left.value(), right.value()));
    }

    return left;
}

std::expected<std::shared_ptr<ASTNode>, std::string> parseRepetition(
    const std::string& regex, size_t& pos) {
    auto base = parseAtom(regex, pos);
    if (!base) {
        return base;
    }

    if (pos < regex.length()) {
        if (regex[pos] == '*') {
            pos++;
            base = std::expected<std::shared_ptr<ASTNode>, std::string>(
                std::make_shared<KleeneNode>(base.value()));
        }
    }

    return base;
}

std::expected<std::shared_ptr<ASTNode>, std::string> parseAtom(const std::string& regex,
                                                               size_t& pos) {
    if (pos >= regex.length()) {
        return std::unexpected("Unexpected end of regex");
    }

    char c = regex[pos];

    if (c == '(') {
        pos++;

        auto expr = parseAlternation(regex, pos);
        if (!expr) {
            return expr;
        }

        if (pos >= regex.length() || regex[pos] != ')') {
            return std::unexpected("Missing closing parenthesis");
        }

        pos++;
        return expr;
    } else if (c == '\\' && pos + 1 < regex.length()) {
        pos++;
        char escaped = regex[pos++];
        return std::expected<std::shared_ptr<ASTNode>, std::string>(
            std::make_shared<SymbolNode>(escaped));
    } else if (c == '*' || c == '+' || c == '?' || c == '|' || c == ')') {
        return std::unexpected(std::string("Unexpected metacharacter: ") + c);
    } else {
        pos++;
        return std::expected<std::shared_ptr<ASTNode>, std::string>(
            std::make_shared<SymbolNode>(c));
    }
}

}  // namespace internal
}  // namespace parser
