#include "../tests.h"

TEST(Parser, ParserEmptyConstructor) {
  s21::Parser parser;
  ASSERT_EQ(parser.getPostfixStr(), "");
}

TEST(Parser, ParserValidateError) {
  s21::Parser parser;
  // EXPECT_ANY_THROW(parser.parsing(""));
  // EXPECT_ANY_THROW(parser.parsing("h(3)"));
  // EXPECT_ANY_THROW
  // EXPECT_ANY_THROW(parser.parsing("s3)"));
}

TEST(Parser, ParserParsing) {
  s21::Parser parser;
  ASSERT_EQ(parser.parsing("2+2"), "2.000000 2.000000 + ");
  ASSERT_EQ(parser.parsing("2-2"), "2.000000 2.000000 - ");
  ASSERT_EQ(parser.parsing("2*2"), "2.000000 2.000000 * ");
  ASSERT_EQ(parser.parsing("2/2"), "2.000000 2.000000 / ");
  ASSERT_EQ(parser.parsing("2%2"), "2.000000 2.000000 % ");
  ASSERT_EQ(parser.parsing("2^2"), "2.000000 2.000000 ^ ");
  ASSERT_EQ(parser.parsing("(2/2)"), "2.000000 2.000000 / ");
  ASSERT_EQ(parser.parsing("((2/2)+3)"), "2.000000 2.000000 / 3.000000 + ");
  ASSERT_EQ(parser.parsing("(((2/2)+3))"), "2.000000 2.000000 / 3.000000 + ");
  ASSERT_EQ(parser.parsing("(((2/2)+3+x))"),
            "2.000000 2.000000 / 3.000000 + x + ");
  ASSERT_EQ(parser.parsing("s(x)"), "x s ");
  ASSERT_EQ(parser.parsing("c(x)"), "x c ");
  ASSERT_EQ(parser.parsing("t(x)"), "x t ");
  ASSERT_EQ(parser.parsing("S(x)"), "x S ");
  ASSERT_EQ(parser.parsing("C(x)"), "x C ");
  ASSERT_EQ(parser.parsing("T(x)"), "x T ");
  ASSERT_EQ(parser.parsing("l(x)"), "x l ");
  ASSERT_EQ(parser.parsing("L(x)"), "x L ");
  ASSERT_EQ(parser.parsing("L(~x)"), "x ~ L ");
  ASSERT_EQ(parser.parsing("2+~3"), "2.000000 3.000000 ~ + ");
  ASSERT_EQ(
      parser.parsing("15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
                     "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))"),
      "15.000000 7.000000 1.000000 1.000000 + - / 3.000000 * 2.000000 1.000000 "
      "1.000000 + + 15.000000 * 7.000000 200.000000 1.000000 + - / 3.000000 * "
      "- 2.000000 1.000000 1.000000 + + 15.000000 7.000000 1.000000 1.000000 + "
      "- / 3.000000 * 2.000000 1.000000 1.000000 + + - 15.000000 7.000000 "
      "1.000000 1.000000 + - / 3.000000 * + 2.000000 1.000000 1.000000 + + - * "
      "- ");
}

TEST(Parser, ParserGetPostfixStr) {
  s21::Parser parser;
  parser.parsing("2+2");
  ASSERT_EQ(parser.getPostfixStr(), "2.000000 2.000000 + ");
  parser.parsing("2-2");
  ASSERT_EQ(parser.getPostfixStr(), "2.000000 2.000000 - ");
}
