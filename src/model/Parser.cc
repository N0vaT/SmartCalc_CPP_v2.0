#include "Parser.h"

namespace s21 {

Parser::Parser() noexcept : postfix_str_("") {}
Parser::Parser(const Parser& other) noexcept
    : postfix_str_(other.postfix_str_), stackSign(other.stackSign) {}
Parser::Parser(Parser&& other) noexcept : Parser() {
  std::swap(postfix_str_, other.postfix_str_);
  std::swap(stackSign, other.stackSign);
}
Parser& Parser::operator=(const Parser& other) {
  if (this != &other) {
    postfix_str_ = other.postfix_str_;
    stackSign = other.stackSign;
  }
  return *this;
}
Parser& Parser::operator=(Parser&& other) {
  if (this != &other) {
    postfix_str_ = std::move(other.postfix_str_);
    stackSign = std::move(other.stackSign);
  }
  return *this;
}

std::string Parser::parsing(const std::string& input_string) {
  if (input_string.length() == 0) {
    throw std::runtime_error("String is empty");
  }
  postfix_str_ = "";
  const char* tmp = input_string.c_str();
  while (*tmp) {
    if (*tmp >= '0' && *tmp <= '9') {
      int n = 0;
      double num = 0;
      sscanf(tmp, "%lf%n", &num, &n);
      postfix_str_ += std::to_string(num) + ' ';
      tmp = tmp + n - 1;
    } else if (*tmp == 'x') {
      postfix_str_ += "x ";
    } else {
      parse_sign(*tmp);
    }
    tmp++;
  }
  while (!stackSign.empty()) {
    if (stackSign.top() == '(' || check_pririty(stackSign.top()) < 0) {
      throw std::runtime_error("Input Error");
    }
    postfix_str_ += stackSign.top();
    postfix_str_ += ' ';
    stackSign.pop();
  }
  return postfix_str_;
}

void Parser::parse_sign(char sign) {
  int priority = check_pririty(sign);
  if (stackSign.empty()) {
    stackSign.push(sign);
  } else if (priority == 0) {
    stackSign.push(sign);
  } else if (priority == 5) {
    while (!stackSign.empty() && check_pririty(stackSign.top()) != 0) {
      postfix_str_ += stackSign.top();
      postfix_str_ += ' ';
      stackSign.pop();
    }
    if (!stackSign.empty() && stackSign.top() == '(') stackSign.pop();
    if (!stackSign.empty() && check_pririty(stackSign.top()) == 0 &&
        stackSign.top() != '(') {
      postfix_str_ += stackSign.top();
      postfix_str_ += ' ';
      stackSign.pop();
    }
  } else {
    while (!stackSign.empty() && check_pririty(stackSign.top()) >= priority) {
      postfix_str_ += stackSign.top();
      postfix_str_ += ' ';
      stackSign.pop();
    }
    stackSign.push(sign);
  }
}

int Parser::check_pririty(char ch) {
  int priority = 0;
  switch (ch) {
    case 'c':
    case 's':
    case 't':
    case 'C':
    case 'S':
    case 'T':
    case 'l':
    case 'L':
    case 'q':
    case '(':
      priority = 0;
      break;
    case '+':
    case '-':
      priority = 1;
      break;
    case '*':
    case '/':
    case '%':
      priority = 2;
      break;
    case '^':
      priority = 3;
      break;
    case '~':
      priority = 4;
      break;
    case ')':
      priority = 5;
      break;
    case ' ':
      break;
    default:
      priority = -1;
      break;
  }
  return priority;
}

std::string Parser::getPostfixStr() { return postfix_str_; }

}  // namespace s21