#include "matcher.h"

constexpr char regex[] = "(a|.|-)(a|.|-)*@((a*.*a)|a)((a*.*a)|a)*";

int main(void) {
  std::vector<std::pair<std::string, std::string>> tests = {
      {regex, "aaaa@aaaaaaa"},  {regex, "aaaa@aaa...aaa"},
      {regex, "aaaa@a.a.a.a"},  {regex, "aaaa@.a.a.a"},
      {regex, "aaaa@.....a"},   {regex, "aaaa@....."},
      {regex, "aaaa@aaaa...."},
  };

  for (const auto &[regex, input] : tests) {
    std::cout << std::endl
              << "Regex: '" << regex << "' with input '" << input << "'\n";

    bool result = parser::matches(regex, input);

    std::cout << (result ? "Match" : "No match") << std::endl;
  }

  return 0;
}
