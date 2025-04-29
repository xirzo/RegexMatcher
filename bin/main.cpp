#include <cstdlib>
#include <iostream>

#include "parser.h"

bool matches(const std::string& regex, const std::string& input) {
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

constexpr char regex[] = "(a|.|-)(a|.|-)*@((a*.*a)|a)((a*.*a)|a)*";

int main(void) {
    std::vector<std::pair<std::string, std::string>> tests = {
        {regex, "aaaa@aaaaaaa"},  {regex, "aaaa@aaa...aaa"}, {regex, "aaaa@a.a.a.a"},
        {regex, "aaaa@.a.a.a"},   {regex, "aaaa@.....a"},    {regex, "aaaa@....."},
        {regex, "aaaa@aaaa...."},
    };

    for (const auto& [regex, input] : tests) {
        std::cout << std::endl
                  << "Regex: '" << regex << "' with input '" << input << "'\n";

        bool result = matches(regex, input);

        std::cout << (result ? "Match" : "No match") << std::endl;
    }

    return 0;
}
