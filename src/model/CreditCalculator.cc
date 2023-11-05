#include "CreditCalculator.h"

namespace s21 {
CreditCalculator::CreditCalculator() noexcept
    : creditSum(0), creditTerm(0), percent(0) {}
CreditCalculator::CreditCalculator(const CreditCalculator& other)
    : creditSum(other.creditSum),
      creditTerm(other.creditTerm),
      percent(other.percent) {}
CreditCalculator::CreditCalculator(CreditCalculator&& other) noexcept
    : CreditCalculator() {
  std::swap(creditSum, other.creditSum);
  std::swap(creditTerm, other.creditTerm);
  std::swap(percent, other.percent);
}

CreditCalculator& CreditCalculator::operator=(const CreditCalculator& other) {
  if (this != &other) {
    creditSum = other.creditSum;
    creditTerm = other.creditTerm;
    percent = other.percent;
  }
  return *this;
}

CreditCalculator& CreditCalculator::operator=(CreditCalculator&& other) {
  if (this != &other) {
    creditSum = std::move(other.creditSum);
    creditTerm = std::move(other.creditTerm);
    percent = std::move(other.percent);
  }
  return *this;
}

std::tuple<double, double, double> CreditCalculator::calculateAnn(
    double creditSum, double creditTerm, double percent) {
  double m = percent / 12. / 100.;
  double kef = m * pow(1 + m, creditTerm) / (pow(1 + m, creditTerm) - 1);
  return std::make_tuple(kef * creditSum,
                         kef * creditSum * creditTerm - creditSum,
                         kef * creditSum * creditTerm);
}

std::tuple<double, double, std::vector<double>> CreditCalculator::calculateDif(
    double creditSum, double creditTerm, double percent) {
  std::vector<double> paymentByMonth;
  double s_m = creditSum / creditTerm;
  double s_c, ost = creditSum, res = 0;
  for (int i = 1; i <= creditTerm; i++) {
    s_c = s_m + (ost * percent * 1.0 / 12);
    ost -= s_m;
    paymentByMonth.push_back(s_c);
    res += s_c;
  }
  return std::make_tuple(res - creditSum, res, paymentByMonth);
}

}  // namespace s21