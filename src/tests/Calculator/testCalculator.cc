#include "../tests.h"

TEST(Calculator, CalculatorEmptyConstructor) { s21::Calculator calculator; }

TEST(Calculator, CalculatorCalculate) {
  s21::Calculator calculator;
  ASSERT_DOUBLE_EQ(calculator.calculate("2.000000 3.000000 + "), 5);
  ASSERT_DOUBLE_EQ(calculator.calculate("2.000000 3.000000 ~ + "), -1);
  ASSERT_DOUBLE_EQ(calculator.calculate("2.000000 3.000000 - "), -1);
  ASSERT_DOUBLE_EQ(calculator.calculate("2.000000 3.000000 * "), 6);
  ASSERT_DOUBLE_EQ(calculator.calculate("6.000000 3.000000 / "), 2);
  ASSERT_DOUBLE_EQ(calculator.calculate("6.000000 2.000000 % "), fmod(6, 2));
  ASSERT_DOUBLE_EQ(calculator.calculate("6.000000 5.000000 % "), fmod(6, 5));
  ASSERT_DOUBLE_EQ(calculator.calculate("2.000000 3.000000 ^ "), pow(2, 3));
  ASSERT_DOUBLE_EQ(calculator.calculate("2.000000 2.000000 / 3.000000 + "), 4);
  ASSERT_DOUBLE_EQ(calculator.calculate("1.000000 c"), cos(1));
  ASSERT_DOUBLE_EQ(calculator.calculate("1.000000 s"), sin(1));
  ASSERT_DOUBLE_EQ(calculator.calculate("1.000000 t"), tan(1));
  ASSERT_DOUBLE_EQ(calculator.calculate("1.000000 C"), acos(1));
  ASSERT_DOUBLE_EQ(calculator.calculate("1.000000 S"), asin(1));
  ASSERT_DOUBLE_EQ(calculator.calculate("1.000000 T"), atan(1));
  ASSERT_DOUBLE_EQ(calculator.calculate("16.000000 l"), log(16));
  ASSERT_DOUBLE_EQ(calculator.calculate("100.000000 L"), log10(100));
}
