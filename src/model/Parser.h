#ifndef PARSER_H
#define PARSER_H

#include <stack>
#include <stdexcept>
#include <string>

namespace s21 {
class Parser {
 public:
  Parser() noexcept;
  Parser(const Parser& other) noexcept;
  Parser(Parser&& other) noexcept;
  Parser& operator=(const Parser& other);
  Parser& operator=(Parser&& other);
  ~Parser() = default;

  std::string parsing(const std::string& input_string);
  int check_pririty(char ch);
  std::string getPostfixStr();

 private:
  void parse_sign(char sign);

  std::string postfix_str_;
  std::stack<char> stackSign;
};

}  // namespace s21

#endif  // PARSER_H