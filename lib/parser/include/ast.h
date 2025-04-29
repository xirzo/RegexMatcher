#ifndef AST_H
#define AST_H

#include <memory>
#include <string>

namespace parser {

enum class ASTNodeType
{
    SYMBOL,
    KLEENE,
    CONCAT,
    OR
};

class ASTNode
{
public:
    virtual ~ASTNode() = default;
    virtual ASTNodeType getType() const = 0;
    virtual bool evaluate(const std::string& input, std::size_t& pos) const = 0;
};

class SymbolNode : public ASTNode
{
private:
    char symbol_;

public:
    explicit SymbolNode(char symbol) : symbol_(symbol) {}

    ASTNodeType getType() const override {
        return ASTNodeType::SYMBOL;
    }

    char getSymbol() const;

    bool evaluate(const std::string& input, size_t& pos) const override;
};

class KleeneNode : public ASTNode
{
private:
    std::shared_ptr<ASTNode> node_;

public:
    KleeneNode(std::shared_ptr<ASTNode> node) : node_(node) {}

    ASTNodeType getType() const override {
        return ASTNodeType::KLEENE;
    }

    std::shared_ptr<ASTNode> getNode() const;

    bool evaluate(const std::string& input, size_t& pos) const override;
};

class OrNode : public ASTNode
{
private:
    std::shared_ptr<ASTNode> left_;
    std::shared_ptr<ASTNode> right_;

public:
    OrNode(std::shared_ptr<ASTNode> left, std::shared_ptr<ASTNode> right)
        : left_(left), right_(right) {};

    ASTNodeType getType() const override {
        return ASTNodeType::KLEENE;
    }

    std::shared_ptr<ASTNode> getLeft() const;
    std::shared_ptr<ASTNode> getRight() const;

    bool evaluate(const std::string& input, size_t& pos) const override;
};

class ConcatNode : public ASTNode
{
private:
    std::shared_ptr<ASTNode> left_;
    std::shared_ptr<ASTNode> right_;

public:
    ConcatNode(std::shared_ptr<ASTNode> left, std::shared_ptr<ASTNode> right)
        : left_(left), right_(right) {};

    ASTNodeType getType() const override {
        return ASTNodeType::CONCAT;
    }

    std::shared_ptr<ASTNode> getLeft() const;
    std::shared_ptr<ASTNode> getRight() const;

    bool evaluate(const std::string& input, size_t& pos) const override;
};

};  // namespace parser

#endif  // AST_H
