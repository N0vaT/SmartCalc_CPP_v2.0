#include "../tests.h"

TEST(Validator, ValidatorEmptyConstructor) {
  s21::Validator validator;
  ASSERT_EQ(validator.getValidStr(), "");
}

TEST(Validator, ValidatorValidateError) {
  s21::Validator validator;
  ASSERT_ANY_THROW(validator.validate(""));
  ASSERT_ANY_THROW(validator.validate(")+sin(3)"));
  ASSERT_ANY_THROW(validator.validate("sin)3("));
  ASSERT_ANY_THROW(validator.validate("sin3)"));
  ASSERT_ANY_THROW(validator.validate("son(3)"));
  ASSERT_ANY_THROW(validator.validate("con(3)"));
  ASSERT_ANY_THROW(validator.validate("ton(3)"));
  ASSERT_ANY_THROW(validator.validate("ason(3)"));
  ASSERT_ANY_THROW(validator.validate("acon(3)"));
  ASSERT_ANY_THROW(validator.validate("atn(3)"));
  ASSERT_ANY_THROW(validator.validate("min(3)"));
  ASSERT_ANY_THROW(validator.validate("li(3)"));
  ASSERT_ANY_THROW(validator.validate("los(3)"));
  ASSERT_ANY_THROW(validator.validate("3.3.3"));
}

TEST(Validator, ValidatorValidate) {
  s21::Validator validator;
  validator.validate("cos(3)");
  ASSERT_EQ(validator.getValidStr(), "c(3.000000)");
  validator.validate("sin(3)");
  ASSERT_EQ(validator.getValidStr(), "s(3.000000)");
  validator.validate("tan(3)");
  ASSERT_EQ(validator.getValidStr(), "t(3.000000)");
  validator.validate("acos(3)");
  ASSERT_EQ(validator.getValidStr(), "C(3.000000)");
  validator.validate("asin(3)");
  ASSERT_EQ(validator.getValidStr(), "S(3.000000)");
  validator.validate("ln(3)");
  ASSERT_EQ(validator.getValidStr(), "l(3.000000)");
  validator.validate("log(3)");
  ASSERT_EQ(validator.getValidStr(), "L(3.000000)");
  validator.validate("-4");
  ASSERT_EQ(validator.getValidStr(), "~4.000000");
  validator.validate("(-4)");
  ASSERT_EQ(validator.getValidStr(), "(~4.000000)");
  validator.validate("2--4");
  ASSERT_EQ(validator.getValidStr(), "2.000000-~4.000000");
  validator.validate("2+-4");
  ASSERT_EQ(validator.getValidStr(), "2.000000+~4.000000");
  validator.validate("2*-4");
  ASSERT_EQ(validator.getValidStr(), "2.000000*~4.000000");
  validator.validate("2/-4");
  ASSERT_EQ(validator.getValidStr(), "2.000000/~4.000000");
  validator.validate("2^-4");
  ASSERT_EQ(validator.getValidStr(), "2.000000^~4.000000");
  validator.validate("2%-4");
  ASSERT_EQ(validator.getValidStr(), "2.000000%~4.000000");
}

TEST(Validator, ValidatorX) {
  s21::Validator validator;
  validator.validate("cos(x)");
  ASSERT_EQ(validator.getValidStr(), "c(x)");
}
