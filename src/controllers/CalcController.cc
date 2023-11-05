#include "CalcController.h"

namespace s21 {

CalcController::CalcController() noexcept {}
CalcController::CalcController(s21::Validator validator, s21::Parser parser,
                               s21::Calculator calculator,
                               s21::CreditCalculator credit) noexcept {
  this->validator = validator;
  this->parser = parser;
  this->calculator = calculator;
  this->credit = credit;
}
CalcController::CalcController(const CalcController& other) noexcept
    : validator(other.validator),
      parser(other.parser),
      calculator(other.calculator),
      credit(other.credit) {}
CalcController::CalcController(CalcController&& other) noexcept
    : CalcController() {
  std::swap(validator, other.validator);
  std::swap(parser, other.parser);
  std::swap(calculator, other.calculator);
  std::swap(credit, other.credit);
}
CalcController& CalcController::operator=(const CalcController& other) {
  if (this != &other) {
    validator = other.validator;
    parser = other.parser;
    calculator = other.calculator;
    credit = other.credit;
  }
  return *this;
}

CalcController& CalcController::operator=(CalcController&& other) {
  if (this != &other) {
    validator = std::move(other.validator);
    parser = std::move(other.parser);
    calculator = std::move(other.calculator);
    credit = std::move(other.credit);
  }
  return *this;
}

std::string CalcController::validate(const std::string& input_string) {
  validator.validate(input_string);
  return validator.getValidStr();
}

std::string CalcController::parsing(const std::string& input_string) {
  parser.parsing(input_string);
  return parser.getPostfixStr();
}

double CalcController::calculate(const std::string& input_string) {
  return calculator.calculate(input_string);
}

double CalcController::calculateX(double x) {
  calculator.setX(x);
  return calculator.calculate(parser.getPostfixStr());
}

std::tuple<double, double, double> CalcController::calculateCreditAnn(
    double creditSum, double creditTerm, double percent) {
  return credit.calculateAnn(creditSum, creditTerm, percent);
}

std::tuple<double, double, std::vector<double>>
CalcController::calculateCreditDif(double creditSum, double creditTerm,
                                   double percent) {
  return credit.calculateDif(creditSum, creditTerm, percent);
}

}  // namespace s21
