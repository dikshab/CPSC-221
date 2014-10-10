// balance_checker_test.cc --- tests the BalanceChecker.
// Part of the RackaBrackaStack project.

// This file is Copyright (C) 2014 by the University of British
// Columbia, Some Rights Reserved.
//
// This work is licensed under the Creative Commons Attribution 4.0
// International License. To view a copy of this license, visit
// http://creativecommons.org/licenses/by/4.0/.


#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::Test;

#include <sstream>
#include <stack>

#include "./racket_tokenizer.h"
#include "./balance_checker.h"
#include "./builtin_stack.h"

namespace tokenizer {
class BalanceCheckerTest : public Test {
 protected:
  BalanceCheckerTest() { }

  virtual ~BalanceCheckerTest() { }

  // Using these tokens in many tests
  Token token_open_paren_{RacketTokenizer::kOpenParen, "(", 1, 1, 3, 3},
    token_open_bracket_{RacketTokenizer::kOpenBracket, "[", 2, 2, 1, 1},
    token_open_brace_{RacketTokenizer::kOpenBrace, "{", 3, 3, 6, 6},
    token_close_brace_{RacketTokenizer::kCloseBrace, "}", 5, 5, 1, 1},
    token_close_bracket_{RacketTokenizer::kCloseBracket, "]", 5, 5, 1, 1},
    token_close_paren_{RacketTokenizer::kCloseParen, ")", 5, 5, 1, 1},
    token_quotation_{RacketTokenizer::kQuotationMark, "\"", 5, 5, 1, 1},
    token_EOF_{RacketTokenizer::kEof, "", 15, 15, 20, 20};

  std::stringstream stream_empty_{""};
  RacketTokenizer toknizer_{stream_empty_};
  BalanceChecker bal_check_empty_stream_{&toknizer_};
  // Using this tokenizer in many tests; specifically:
  //
  // - EmptyStreamTest
  // - TokenCausesImbalance
  // - MatchingClosingToken
  // - NonDelimeterToken
  // - OpeningToken
  // - EOFToken
};

TEST_F(BalanceCheckerTest, TokenCausesImbalance) {
  // stack1, stack2 initially empty.
  BuiltinStack stack1, stack2;

  // Attempting to create a stack with (from bottom to top):
  // (  (  [ ( [
  stack1.push(token_open_paren_);     // (
  stack1.push(token_open_paren_);     // (
  stack1.push(token_open_bracket_);   // [
  stack1.push(token_open_paren_);     // (
  stack1.push(token_open_bracket_);   // [

  EXPECT_EQ(BalanceChecker::kReportUnbalancedToken,
            bal_check_empty_stream_.determine_action(stack1,
                                                     token_close_brace_));

  EXPECT_EQ(BalanceChecker::kReportUnbalancedToken,
            bal_check_empty_stream_.determine_action(stack2,
                                                     token_close_paren_));
}

TEST_F(BalanceCheckerTest, MatchingClosingToken) {
  // stack initially empty
  BuiltinStack stack;

  stack.push(token_open_paren_);    // (
  stack.push(token_open_paren_);    // (
  stack.push(token_open_bracket_);  // [
  stack.push(token_open_paren_);    // (
  stack.push(token_open_brace_);    // {
  stack.push(token_quotation_);     // "

  // Stack looks like (from bottom to top):
  // ( ( [ ( { "

  EXPECT_EQ(BalanceChecker::kPopOldToken,
            bal_check_empty_stream_.determine_action(stack, token_quotation_));

  stack.pop();
  EXPECT_EQ(BalanceChecker::kPopOldToken,
            bal_check_empty_stream_.determine_action(stack,
                                                     token_close_brace_));

  stack.pop();
  EXPECT_EQ(BalanceChecker::kPopOldToken,
            bal_check_empty_stream_.determine_action(stack,
                                                     token_close_paren_));

  stack.pop();
  EXPECT_EQ(BalanceChecker::kPopOldToken,
            bal_check_empty_stream_.determine_action(stack,
                                                     token_close_bracket_));

  stack.pop();
  EXPECT_EQ(BalanceChecker::kPopOldToken,
            bal_check_empty_stream_.determine_action(stack,
                                                     token_close_paren_));

  stack.pop();
  EXPECT_EQ(BalanceChecker::kPopOldToken,
            bal_check_empty_stream_.determine_action(stack,
                                                     token_close_paren_));
}

TEST_F(BalanceCheckerTest, NonDelimeterToken) {
  // stack initially empty
  BuiltinStack stack;

  Token
      token_token(RacketTokenizer::kToken, "hello", 5, 5, 6, 10),
      token_comment(RacketTokenizer::kComment, "; hello", 2, 2, 6, 13),
      token_string(RacketTokenizer::kStringData, "hello", 5, 5, 6, 10),
      token_whitespace(RacketTokenizer::kWhitespace, "\n", 5, 6, 100, 1);

  stack.push(token_open_paren_);
  stack.push(token_open_paren_);
  stack.push(token_open_bracket_);
  stack.push(token_open_paren_);
  stack.push(token_open_brace_);

  // stack looks like (from bottom to top):
  // ( ( [ ( {

  EXPECT_EQ(BalanceChecker::kNoAction,
            bal_check_empty_stream_.determine_action(stack, token_token));
  EXPECT_EQ(BalanceChecker::kNoAction,
            bal_check_empty_stream_.determine_action(stack, token_comment));
  EXPECT_EQ(BalanceChecker::kNoAction,
            bal_check_empty_stream_.determine_action(stack, token_string));
  EXPECT_EQ(BalanceChecker::kNoAction,
            bal_check_empty_stream_.determine_action(stack, token_whitespace));
}

TEST_F(BalanceCheckerTest, OpeningToken) {
  // stack initially empty
  BuiltinStack stack;

  stack.push(token_open_paren_);     // (
  stack.push(token_open_paren_);     // (
  stack.push(token_open_bracket_);   // [
  stack.push(token_open_paren_);     // (
  stack.push(token_open_brace_);     // {
  stack.push(token_quotation_);      // "

  // Stack looks like (from bottom to top):
  // ( ( [ ( { "

  Token
      tokenOpenBrace(RacketTokenizer::kOpenBrace, "{", 3, 3, 6, 6),
      tokenOpenBracket(RacketTokenizer::kOpenBracket, "[", 12, 12, 58, 58),
      tokenQuotation(RacketTokenizer::kQuotationMark, "\"", 8, 8, 9, 9),
      tokenOpenParen(RacketTokenizer::kOpenParen, "(", 6, 6, 9, 9);

  // Quotations can be opening or closing, so just because it doesn't match top
  // of stack, doesn't mean it causes an imbalance.
  EXPECT_EQ(BalanceChecker::kPopOldToken,
            bal_check_empty_stream_.determine_action(stack, tokenQuotation));
  stack.pop();
  EXPECT_EQ(BalanceChecker::kPushNewToken,
            bal_check_empty_stream_.determine_action(stack, tokenQuotation));

  EXPECT_EQ(BalanceChecker::kPushNewToken,
            bal_check_empty_stream_.determine_action(stack, tokenOpenBrace));

  EXPECT_EQ(BalanceChecker::kPushNewToken,
            bal_check_empty_stream_.determine_action(stack, tokenOpenBracket));

  EXPECT_EQ(BalanceChecker::kPushNewToken,
            bal_check_empty_stream_.determine_action(stack, tokenOpenParen));
}

TEST_F(BalanceCheckerTest, EOFToken) {
  // stack1, stack2 intially empty
  BuiltinStack stack1, stack2;

  stack1.push(token_open_paren_);
  stack1.push(token_open_paren_);
  // stack1 looks like (from bottom to top):
  // ( (
  //
  // stack2 is empty

  Token tokenEOF(RacketTokenizer::kEof, "", 15, 15, 20, 20);

  EXPECT_EQ(BalanceChecker::kNoAction,
            bal_check_empty_stream_.determine_action(stack2, tokenEOF));
  EXPECT_EQ(BalanceChecker::kReportUnbalancedToken,
            bal_check_empty_stream_.determine_action(stack1, tokenEOF));
}

TEST_F(BalanceCheckerTest, EmptyStreamTest) {
  EXPECT_EQ(token_EOF_, bal_check_empty_stream_.check_balance());
}

TEST_F(BalanceCheckerTest, NoDelimiterTests) {
  std::stringstream stream_no_delimiters{"afadf"};

  RacketTokenizer tokenizer(stream_no_delimiters);
  BalanceChecker bchecker(&tokenizer);
  EXPECT_EQ(token_EOF_,
            bchecker.check_balance());
}

TEST_F(BalanceCheckerTest, SimpleUnbalancedTooManyOpeningDelimiters) {
  std::stringstream
      // imbalance caused by first opening brace
      stream_extra_opening_brace("{"),
      // imbalance caused by first opening bracket
      stream_extra_opening_bracket("["),
      // imbalance caused by first opening paren
      stream_extra_opening_paren("("),
      // imbalance caused by first "
      stream_extra_quotation("\"");

  RacketTokenizer tokenizer1(stream_extra_opening_brace),
      tokenizer2(stream_extra_opening_bracket),
      tokenizer3(stream_extra_opening_paren),
      tokenizer4(stream_extra_quotation);
  BalanceChecker bal_check_extra_open_brace(&tokenizer1),
      bal_check_extra_open_bracket(&tokenizer2),
      bal_check_extra_open_paren(&tokenizer3),
      bal_check_extra_quotation(&tokenizer4);

  EXPECT_EQ(token_open_brace_, bal_check_extra_open_brace.check_balance());
  EXPECT_EQ(token_open_bracket_, bal_check_extra_open_bracket.check_balance());
  EXPECT_EQ(token_open_paren_, bal_check_extra_open_paren.check_balance());
  EXPECT_EQ(token_quotation_, bal_check_extra_quotation.check_balance());
}

TEST_F(BalanceCheckerTest, UnbalancedTooManyOpeningDelimiters) {
  std::stringstream
      // imbalance caused by first opening brace
      stream_extra_opening_brace("{(a[s \"hello\"])"),
      // imbalance caused by first opening bracket
      stream_extra_opening_bracket("[ *[+(3 5) 9 ]"),
      // imbalance caused by first opening paren
      stream_extra_opening_paren("(/(+ (3 5)) 6 "),
      // imbalance caused by third "
      stream_extra_quotation("(stringeq(\"foo\", \"bar)");

  RacketTokenizer tokenizer1(stream_extra_opening_brace),
      tokenizer2(stream_extra_opening_bracket),
      tokenizer3(stream_extra_opening_paren),
      tokenizer4(stream_extra_quotation);
  BalanceChecker bal_check_extra_open_brace(&tokenizer1),
      bal_check_extra_open_bracket(&tokenizer2),
      bal_check_extra_open_paren(&tokenizer3),
      bal_check_extra_quotation(&tokenizer4);

  EXPECT_EQ(token_open_brace_, bal_check_extra_open_brace.check_balance());
  EXPECT_EQ(token_open_bracket_, bal_check_extra_open_bracket.check_balance());
  EXPECT_EQ(token_open_paren_, bal_check_extra_open_paren.check_balance());
  EXPECT_EQ(token_quotation_, bal_check_extra_quotation.check_balance());
}

TEST_F(BalanceCheckerTest, SimpleUnbalancedTooManyClosingBrackets) {
  std::stringstream
      // imbalance caused by closing brace
      stream_extra_closing_brace("}"),
      // imnbalance caused by closing bracket
      stream_extra_closing_bracket("]"),
      // imbalance caused by closing paren
      stream_extra_closing_paren(")"),
      // imbalance caused by \"
      stream_extra_quotation("\"");

  RacketTokenizer tokenizer1(stream_extra_closing_brace),
      tokenizer2(stream_extra_closing_bracket),
      tokenizer3(stream_extra_closing_paren),
      tokenizer4(stream_extra_quotation);

  BalanceChecker bal_check_extra_close_brace(&tokenizer1);
  BalanceChecker bal_check_extra_close_bracket(&tokenizer2);
  BalanceChecker bal_check_extra_close_paren(&tokenizer3);
  BalanceChecker bal_check_extra_quotation(&tokenizer4);

  EXPECT_EQ(token_close_brace_,
            bal_check_extra_close_brace.check_balance());
  EXPECT_EQ(token_close_bracket_,
            bal_check_extra_close_bracket.check_balance());
  EXPECT_EQ(token_close_paren_,
            bal_check_extra_close_paren.check_balance());
  EXPECT_EQ(token_quotation_,
            bal_check_extra_quotation.check_balance());
}

TEST_F(BalanceCheckerTest, UnbalancedTooManyClosingBrackets) {
  std::stringstream
      // imbalance caused by final closing brace
      stream_extra_closing_brace("(a[s \"hello\"]{})}"),
      // imnbalance caused by final closing bracket
      stream_extra_closing_bracket("{ *[+(3 5) 9] ]"),
      // imbalance caused by final closing paren
      stream_extra_closing_paren("(/(+ (3 5)) 6)) "),
      // imbalance caused by final \"
      stream_extra_quotation("(stringeq(\"foo\", \"bar\")\"");

  RacketTokenizer tokenizer1(stream_extra_closing_brace),
      tokenizer2(stream_extra_closing_bracket),
      tokenizer3(stream_extra_closing_paren),
      tokenizer4(stream_extra_quotation);

  BalanceChecker bal_check_extra_close_brace(&tokenizer1);
  BalanceChecker bal_check_extra_close_bracket(&tokenizer2);
  BalanceChecker bal_check_extra_close_paren(&tokenizer3);
  BalanceChecker bal_check_extra_quotation(&tokenizer4);

  EXPECT_EQ(token_close_brace_,
            bal_check_extra_close_brace.check_balance());
  EXPECT_EQ(token_close_bracket_,
            bal_check_extra_close_bracket.check_balance());
  EXPECT_EQ(token_close_paren_,
            bal_check_extra_close_paren.check_balance());
  EXPECT_EQ(token_quotation_,
            bal_check_extra_quotation.check_balance());
}

TEST_F(BalanceCheckerTest, Balanced) {
  std::stringstream stream_balanced1("(* ({+[8 7]} 9))"),
      stream_balanced2("\"cool(({\" {(12345)}"),
      stream_balanced3(";blue({))}\n(+[3 5])");

  RacketTokenizer tokenizer1(stream_balanced1),
      tokenizer2(stream_balanced2),
      tokenizer3(stream_balanced3);

  BalanceChecker bal_check_balanced1(&tokenizer1);
  BalanceChecker bal_check_balanced2(&tokenizer2);
  BalanceChecker bal_check_balanced3(&tokenizer3);


  EXPECT_EQ(token_EOF_, bal_check_balanced1.check_balance());
  EXPECT_EQ(token_EOF_, bal_check_balanced2.check_balance());
  EXPECT_EQ(token_EOF_, bal_check_balanced3.check_balance());
}
}  // namespace tokenizer
