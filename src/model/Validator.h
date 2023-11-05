#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <cstring>
#include <stdexcept>
#include <string>

namespace s21 {
class Validator {
 public:
  Validator() noexcept;
  Validator(const Validator& other) noexcept;
  Validator(Validator&& other) noexcept;
  Validator& operator=(const Validator& other);
  Validator& operator=(Validator&& other);
  ~Validator() = default;

  std::string validate(const std::string& str_in);
  std::string getValidStr();

 private:
  void check_c(const char** tmp, int* cnt);
  void check_s(const char** tmp, int* cnt);
  void check_t(const char** tmp, int* cnt);
  void check_a(const char** tmp, int* cnt);
  void check_l(const char** tmp, int* cnt);

  std::string str_in_;
  std::string str_out_;
};
}  // namespace s21

#endif  // VALIDATOR_H