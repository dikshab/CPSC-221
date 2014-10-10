// balance_checker.h --- header file for the BalanceChecker.
// Responsible for logic that ensures that brackets of various types
// match against each other (using the Tokenizer to determine what is
// an opening/closing bracket).  Part of the RackaBrackaStack project.

// This file is Copyright (C) 2014 by the University of British
// Columbia, Some Rights Reserved.
//
// This work is licensed under the Creative Commons Attribution 4.0
// International License. To view a copy of this license, visit
// http://creativecommons.org/licenses/by/4.0/.

#ifndef RACKET_BRACKET_STACK_BALANCE_CHECKER_H_
#define RACKET_BRACKET_STACK_BALANCE_CHECKER_H_

#include <gtest/gtest_prod.h>

#include <string>

#include "./token.h"
#include "./tokenizer.h"
#include "./builtin_stack.h"


namespace tokenizer {
class BalanceChecker {
 public:
  enum StackAction {
    kReportUnbalancedToken,
    kPushNewToken,
    kPopOldToken,
    kNoAction
  };

  // Constructs a BalanceChecker object with the given istream
  explicit BalanceChecker(Tokenizer *tokenizer)
    : tokenizer_(tokenizer) { }

  // Checks to see whether whether stream is balanced
  // and updates stack as going through stream
  Token check_balance();

 private:
  Tokenizer *tokenizer_;
  BuiltinStack token_stack_;

  StackAction determine_action(TokenStack const &token_stack,
                               Token const &new_token) const;

  // The tests "reach inside" to test the private function
  // determine_action; so, the Google-provided macro below makes the
  // test classes "friends" with this class.  As Steve Wolfman's
  // university instructor taught him: "In C++ (if not necessarily in
  // life), friends are classes that can touch your private parts."
  //
  // There.. now you won't ever forget it, either. :P
  FRIEND_TEST(BalanceCheckerTest, TokenCausesImbalance);
  FRIEND_TEST(BalanceCheckerTest, MatchingClosingToken);
  FRIEND_TEST(BalanceCheckerTest, NonDelimeterToken);
  FRIEND_TEST(BalanceCheckerTest, OpeningToken);
  FRIEND_TEST(BalanceCheckerTest, EOFToken);
};
}  // namespace tokenizer


#endif  // RACKET_BRACKET_STACK_BALANCE_CHECKER_H_
