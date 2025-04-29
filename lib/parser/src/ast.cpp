#include "ast.h"

#include <vector>

namespace parser {

char SymbolNode::getSymbol() const {
    return symbol_;
}

bool SymbolNode::evaluate(const std::string& input, size_t& pos) const {
    if (pos >= input.length()) {
        return false;
    }

    if (input[pos] == symbol_) {
        pos++;
        return true;
    }
    return false;
}

std::shared_ptr<ASTNode> ConcatNode::getLeft() const {
    return left_;
}
std::shared_ptr<ASTNode> ConcatNode::getRight() const {
    return right_;
}

bool ConcatNode::evaluate(const std::string& input, size_t& pos) const {
    size_t original_pos = pos;

    if (left_->evaluate(input, pos) && right_->evaluate(input, pos)) {
        return true;
    }

    pos = original_pos;
    return false;
}

std::shared_ptr<ASTNode> OrNode::getLeft() const {
    return left_;
}

std::shared_ptr<ASTNode> OrNode::getRight() const {
    return right_;
}

bool OrNode::evaluate(const std::string& input, size_t& pos) const {
    size_t original_pos = pos;

    if (left_->evaluate(input, pos)) {
        return true;
    }

    pos = original_pos;

    return right_->evaluate(input, pos);
}

std::shared_ptr<ASTNode> KleeneNode::getNode() const {
    return node_;
}

bool KleeneNode::evaluate(const std::string& input, size_t& pos) const {
    std::vector<size_t> positions;
    positions.push_back(pos);

    size_t match_pos = pos;
    while (match_pos < input.length()) {
        size_t start = match_pos;
        if (!node_->evaluate(input, match_pos)) {
            break;
        }

        if (match_pos == start) {
            break;
        }

        positions.push_back(match_pos);
    }

    for (auto it = positions.rbegin(); it != positions.rend(); ++it) {
        pos = *it;
        return true;
    }

    return true;
}

};  // namespace parser
