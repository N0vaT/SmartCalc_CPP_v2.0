#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <cmath>
#include <stack>
#include <stdexcept>
#include <string>

namespace s21 {
class Calculator {
 public:
  Calculator() noexcept;
  Calculator(const Calculator& other);
  Calculator(Calculator&& other) noexcept;
  Calculator& operator=(const Calculator& other);
  Calculator& operator=(Calculator&& other);
  ~Calculator() = default;

  double calculate(const std::string& input_string);
  void setX(double x);

 private:
  void execute(char ch);
  void execute_cos();
  void execute_sin();
  void execute_tan();
  void execute_acos();
  void execute_asin();
  void execute_atan();
  void execute_log();
  void execute_log10();
  void execute_sqrt();
  void execute_plus();
  void execute_minus();
  void execute_mul();
  void execute_div();
  void execute_mod();
  void execute_pow();

  double first, second, x;
  std::stack<double> stackNumber;
};

}  // namespace s21

#endif  // CALCULATOR_H