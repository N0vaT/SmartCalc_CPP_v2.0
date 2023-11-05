#ifndef CREDITCALCULATOR_H
#define CREDITCALCULATOR_H

#include <cmath>
#include <tuple>
#include <vector>

namespace s21 {
class CreditCalculator {
 public:
  CreditCalculator() noexcept;
  CreditCalculator(double creditSum, double creditTerm,
                   double percent) noexcept;
  CreditCalculator(const CreditCalculator& other);
  CreditCalculator(CreditCalculator&& other) noexcept;
  CreditCalculator& operator=(const CreditCalculator& other);
  CreditCalculator& operator=(CreditCalculator&& other);
  ~CreditCalculator() = default;

  std::tuple<double, double, double> calculateAnn(double creditSum,
                                                  double creditTerm,
                                                  double percent);
  std::tuple<double, double, std::vector<double>> calculateDif(
      double creditSum, double creditTerm, double percent);

 private:
  double creditSum, creditTerm, percent;
};

}  // namespace s21

#endif  // CREDITCALCULATOR_H