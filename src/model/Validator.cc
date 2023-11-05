#include "Validator.h"

namespace s21 {
Validator::Validator() noexcept : str_in_(""), str_out_("") {}
Validator::Validator(const Validator& other) noexcept
    : str_in_(other.str_in_), str_out_(other.str_out_) {}
Validator::Validator(Validator&& other) noexcept : Validator() {
  std::swap(str_in_, other.str_in_);
  std::swap(str_out_, other.str_out_);
}
Validator& Validator::operator=(const Validator& other) {
  if (this != &other) {
    str_in_ = other.str_in_;
    str_out_ = other.str_out_;
  }
  return *this;
}

Validator& Validator::operator=(Validator&& other) {
  if (this != &other) {
    str_in_ = std::move(other.str_in_);
    str_out_ = std::move(other.str_out_);
  }
  return *this;
}

std::string Validator::validate(const std::string& input_string) {
  str_in_ = input_string;
  int cnt_1 = 0, cnt_2 = 0, cnt = 1;
  if (str_in_.length() == 0) {
    throw std::runtime_error("String is empty");
  }
  const char* tmp = str_in_.c_str();
  str_out_ = "";
  while (tmp && *tmp != '\0') {
    if (*tmp == ' ') {
    } else if (*tmp == '(') {
      str_out_ += *tmp;
      ++cnt_1;
    } else if (*tmp == ')') {
      str_out_ += *tmp;
      ++cnt_2;
    } else if (*tmp == 'x' || *tmp == 'X') {
      str_out_ += *tmp;
    } else if (*tmp == 'c') {
      check_c(&tmp, &cnt);
    } else if (*tmp == 's') {
      check_s(&tmp, &cnt);
    } else if (*tmp == 't') {
      check_t(&tmp, &cnt);
    } else if (*tmp == 'a') {
      check_a(&tmp, &cnt);
    } else if (*tmp == 'l') {
      check_l(&tmp, &cnt);
    } else if (*tmp == '-' &&
               (cnt == 1 || *(tmp - 1) == '(' || *(tmp - 1) == '+' ||
                *(tmp - 1) == '-' || *(tmp - 1) == '*' || *(tmp - 1) == '/' ||
                *(tmp - 1) == '^' || *(tmp - 1) == '%')) {
      str_out_ += "~";
    } else if (*tmp == '+' &&
               (cnt == 1 || *(tmp - 1) == '(' || *(tmp - 1) == '+' ||
                *(tmp - 1) == '-' || *(tmp - 1) == '*' || *(tmp - 1) == '/' ||
                *(tmp - 1) == '^' || *(tmp - 1) == '%')) {
    } else if (*tmp >= '0' && *tmp <= '9') {
      int n = 0;
      double num = 0;
      sscanf(tmp, "%lf%n", &num, &n);
      str_out_ += std::to_string(num);
      tmp = tmp + n - 1;
      cnt += n - 1;
    } else if (*tmp == '+' || *tmp == '-' || *tmp == '*' || *tmp == '/' ||
               *tmp == '^' || *tmp == '%') {
      str_out_ += *tmp;
    } else {
      throw std::runtime_error("Input Error in position - " +
                               std::to_string(cnt));
    }
    if (cnt_2 > cnt_1) throw std::runtime_error("Parenthesis error");
    tmp++;
    cnt++;
  }
  if (cnt_1 != cnt_2) throw std::runtime_error("Parenthesis error");
  return str_out_;
}

std::string Validator::getValidStr() { return str_out_; }

void Validator::check_c(const char** tmp, int* cnt) {
  if (memcmp(*tmp, "cos", 3) == 0) {
    str_out_ += 'c';
    *tmp += 2;
    *cnt += 2;
  } else {
    throw std::runtime_error("Input Error in position - " +
                             std::to_string(*cnt));
  }
}

void Validator::check_s(const char** tmp, int* cnt) {
  if (memcmp(*tmp, "sin", 3) == 0) {
    str_out_ += 's';
    *tmp += 2;
    *cnt += 2;
  } else if (memcmp(*tmp, "sqrt", 4) == 0) {
    str_out_ += 'q';
    *tmp += 3;
    *cnt += 3;
  } else {
    throw std::runtime_error("Input Error in position - " +
                             std::to_string(*cnt));
  }
}

void Validator::check_t(const char** tmp, int* cnt) {
  if (memcmp(*tmp, "tan", 3) == 0) {
    str_out_ += 't';
    *tmp += 2;
    *cnt += 2;
  } else {
    throw std::runtime_error("Input Error in positions - " +
                             std::to_string(*cnt));
  }
}

void Validator::check_a(const char** tmp, int* cnt) {
  if (memcmp(*tmp, "asin", 4) == 0) {
    str_out_ += 'S';
    *tmp += 3;
  } else if (memcmp(*tmp, "acos", 4) == 0) {
    str_out_ += 'C';
    *tmp += 3;
  } else if (memcmp(*tmp, "atan", 4) == 0) {
    str_out_ += 'T';
    *tmp += 3;
  } else {
    throw std::runtime_error("Input Error in position - " +
                             std::to_string(*cnt));
  }
  *cnt += 3;
}

void Validator::check_l(const char** tmp, int* cnt) {
  if (memcmp(*tmp, "ln", 2) == 0) {
    str_out_ += 'l';
    *tmp += 1;
    *cnt += 1;
  } else if (memcmp(*tmp, "log", 3) == 0) {
    str_out_ += 'L';
    *tmp += 2;
    *cnt += 2;
  } else {
    throw std::runtime_error("Input Error in position - " +
                             std::to_string(*cnt));
  }
}
}  // namespace s21