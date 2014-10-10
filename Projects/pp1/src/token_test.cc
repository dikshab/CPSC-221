// token_test.cc --- Test code for the Token class

// token_test.cc is Copyright (C) 2014 by CPSC 221 at the
// University of British Columbia, Some Rights Reserved.
//
// This work is licensed under the Creative Commons Attribution 4.0
// International License. To view a copy of this license, visit
// http://creativecommons.org/licenses/by/4.0/.

// Basing testing on:
// http://johnlamp.net/cmake-tutorial-4-libraries-and-subdirectories.html
// along with MANY other references.

#include <gmock/gmock.h>
using ::testing::Eq;
using ::testing::Ne;
#include <gtest/gtest.h>
using ::testing::Test;

#include <sstream>

#include "./token.h"

namespace tokenizer {
class TokenTest : public Test {
 protected:
  TokenTest() { }

  virtual ~TokenTest() { }
};
TEST_F(TokenTest, IsEof) {
  Token eof1(Token::kEofToken, "", 1, 1, 1, 1),
      eof2(Token::kEofToken, "hello", 2, 3, 4, 5),
      not_eof1(85, "", 1, 1, 1, 1),
      not_eof2(85, "hello", 2, 3, 4, 5);
  EXPECT_THAT(eof1.is_eof(), Eq(true));
  EXPECT_THAT(eof2.is_eof(), Eq(true));
  EXPECT_THAT(not_eof1.is_eof(), Eq(false));
  EXPECT_THAT(not_eof2.is_eof(), Eq(false));
}
TEST_F(TokenTest, ConstructorTests) {
  Token t1(85, "hello", 2, 7, 3, 8);
  EXPECT_THAT(t1.type(), Eq(85));
  EXPECT_THAT(t1.data(), Eq("hello"));
  EXPECT_THAT(t1.source_tokenizer(), Eq(nullptr));
  EXPECT_THAT(t1.filename(), Eq(""));
  EXPECT_THAT(t1.start_line(), Eq(2));
  EXPECT_THAT(t1.end_line(), Eq(7));
  EXPECT_THAT(t1.start_column(), Eq(3));
  EXPECT_THAT(t1.end_column(), Eq(8));

  Token t2(85, "hello", reinterpret_cast<Tokenizer*>(64), 5, 9, 6, 10);
  EXPECT_THAT(t2.type(), Eq(85));
  EXPECT_THAT(t2.data(), Eq("hello"));
  EXPECT_THAT(t2.source_tokenizer(), Eq(reinterpret_cast<Tokenizer*>(64)));
  EXPECT_THAT(t2.filename(), Eq(""));
  EXPECT_THAT(t2.start_line(), Eq(5));
  EXPECT_THAT(t2.end_line(), Eq(9));
  EXPECT_THAT(t2.start_column(), Eq(6));
  EXPECT_THAT(t2.end_column(), Eq(10));

  Token t3(22, "hello", "somefile.txt", 2, 2, 3, 3);
  EXPECT_THAT(t3.type(), Eq(22));
  EXPECT_THAT(t3.data(), Eq("hello"));
  EXPECT_THAT(t3.source_tokenizer(), Eq(nullptr));
  EXPECT_THAT(t3.filename(), Eq("somefile.txt"));
  EXPECT_THAT(t3.start_line(), Eq(2));
  EXPECT_THAT(t3.end_line(), Eq(2));
  EXPECT_THAT(t3.start_column(), Eq(3));
  EXPECT_THAT(t3.end_column(), Eq(3));

  Token t4(85, "goodbye", reinterpret_cast<Tokenizer*>(128), "otherfile.cc",
           2, 7, 3, 8);
  EXPECT_THAT(t4.type(), Eq(85));
  EXPECT_THAT(t4.data(), Eq("goodbye"));
  EXPECT_THAT(t4.source_tokenizer(), Eq(reinterpret_cast<Tokenizer*>(128)));
  EXPECT_THAT(t4.filename(), Eq("otherfile.cc"));
  EXPECT_THAT(t4.start_line(), Eq(2));
  EXPECT_THAT(t4.end_line(), Eq(7));
  EXPECT_THAT(t4.start_column(), Eq(3));
  EXPECT_THAT(t4.end_column(), Eq(8));
}
TEST_F(TokenTest, Equality) {
  Token
      eof_blank_differs_by_location1(0, "", nullptr, "test.txt", 1, 1, 1, 1),
      eof_blank_differs_by_location2(0, "", nullptr, "test.txt", 1, 1, 1, 1),
      eof_blank_differs_by_location3(0, "", nullptr, "test2.txt", 1, 1, 1, 1),
      eof_blank_differs_by_location4(0, "", nullptr, "test.txt", 2, 1, 1, 1),
      eof_blank_differs_by_location5(0, "", nullptr, "test.txt", 1, 2, 1, 1),
      eof_blank_differs_by_location6(0, "", nullptr, "test.txt", 1, 1, 2, 1),
      eof_blank_differs_by_location7(0, "", nullptr, "test.txt", 1, 1, 1, 2);
  Token
      token_1a8(1, "a", reinterpret_cast<Tokenizer*>(8), "foo", 1, 1, 1, 1),
      token_2a8(2, "a", reinterpret_cast<Tokenizer*>(8), "bar", 2, 2, 2, 2),
      token_1b8(1, "b", reinterpret_cast<Tokenizer*>(8), "baz", 3, 3, 3, 3),
      token_1a4(1, "a", reinterpret_cast<Tokenizer*>(4), "qux", 4, 4, 4, 4),
      token_1a8_copy(1, "a", reinterpret_cast<Tokenizer*>(8), "bom",
                     5, 5, 5, 5);

  EXPECT_THAT(eof_blank_differs_by_location1,
              Eq(eof_blank_differs_by_location1));
  EXPECT_THAT(eof_blank_differs_by_location1,
              Eq(eof_blank_differs_by_location2));
  EXPECT_THAT(eof_blank_differs_by_location1,
              Eq(eof_blank_differs_by_location3));
  EXPECT_THAT(eof_blank_differs_by_location1,
              Eq(eof_blank_differs_by_location4));
  EXPECT_THAT(eof_blank_differs_by_location1,
              Eq(eof_blank_differs_by_location5));
  EXPECT_THAT(eof_blank_differs_by_location1,
              Eq(eof_blank_differs_by_location6));
  EXPECT_THAT(eof_blank_differs_by_location1,
              Eq(eof_blank_differs_by_location7));

  EXPECT_THAT(token_1a8, Ne(token_2a8));
  EXPECT_THAT(token_1a8, Ne(token_1b8));
  EXPECT_THAT(token_1a8, Ne(token_1a4));
  EXPECT_THAT(token_1a8, Eq(token_1a8_copy));  // only differs by file/loc'n.
}
// If we later decide to have the constructor do any error-testing,
// this first template of a test may be handy, but for now, we do not.
// // TEST(TokenTest, BadConstructorCalls) {
// //   EXPECT_THROW(Token(0, "", 5, -2, 17, 3), std::invalid_argument);
// // }
}  // namespace tokenizer
