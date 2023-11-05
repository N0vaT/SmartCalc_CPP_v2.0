#ifndef CALCCONTROLLER_H
#define CALCCONTROLLER_H

#include "../model/Calculator.h"
#include "../model/CreditCalculator.h"
#include "../model/Parser.h"
#include "../model/Validator.h"

namespace s21 {

class CalcController {
 public:
  CalcController() noexcept;
  explicit CalcController(s21::Validator validator, s21::Parser parser,
                          s21::Calculator calculator,
                          s21::CreditCalculator credit) noexcept;
  CalcController(const CalcController& other) noexcept;
  CalcController(CalcController&& other) noexcept;
  CalcController& operator=(const CalcController& other);
  CalcController& operator=(CalcController&& other);
  ~CalcController() = default;

  std::string validate(const std::string& input_string);
  std::string parsing(const std::string& input_string);
  double calculate(const std::string& input_string);
  double calculateX(double x);
  std::tuple<double, double, double> calculateCreditAnn(double creditSum,
                                                        double creditTerm,
                                                        double percent);
  std::tuple<double, double, std::vector<double>> calculateCreditDif(
      double creditSum, double creditTerm, double percent);

 private:
  s21::Validator validator;
  s21::Parser parser;
  s21::Calculator calculator;
  s21::CreditCalculator credit;
};

}  // namespace s21

#endif  // CALCCONTROLLER_H
