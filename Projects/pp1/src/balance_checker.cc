// balance_checker.cc --- Defines the BalanceChecker class that
// will determine whether the stream used by given tokenizer is
// balanced.

// balance_checker.cc is Copyright (C) 2014 by the University of
// British Columbia, Some Rights Reserved.
//
// This work is licensed under the Creative Commons Attribution 4.0
// International License. To view a copy of this license, visit
// http://creativecommons.org/licenses/by/4.0/.


#include "./balance_checker.h"
#include <assert.h>


namespace tokenizer {
// Checks balance of opening/closing tokens. Updates stack
// as going through stream
//
// Returns one of three types of things:
//
// A closing token (i.e., a token that is closing but IS NOT
// opening) if a closing token did not match the preceeding opening
// token.
//
// An opening token if the file ended without closing an opening
// token.
//
// Or, on success, the EOF token that terminated input.
Token BalanceChecker::check_balance() {
  do {
    // Using an apparently infinite loop that terminates under three
    // conditions:
    //
    // (1) EOF reached and stack is empty (returns current token).
    // (EOF = End of File.)
    //
    // (2) EOF reached and stack is non-empty (returns top of
    // stack).
    //
    // (3) Any other unbalanced token (returns it).
    //
    // Why not just loop until eof is reached and then handle (1) &
    // (2)? Scope.  With no assignment operator for Token, it's icky
    // to get at it outside this loop's scope. :(
    Token current_token = tokenizer_->next_token();
    StackAction action = determine_action(token_stack_, current_token);

    switch (action) {
      case kNoAction:
        // Do nothing
        break;
      case kPopOldToken:
        token_stack_.pop();
        break;
      case kPushNewToken:
        token_stack_.push(current_token);
        break;
      case kReportUnbalancedToken:
        // **** HANS WAS HERE!!! **** Your code looks a bit unbalanced here!
        if (current_token.is_eof() && !token_stack_.empty()) {
          return token_stack_.top();
        } else {
          return current_token;
        }
        break;
    }

    if (current_token.is_eof()) {
      // Must have an empty stack; else, we'd get
      // kReportUnbalancedToken at EOF.
      assert(token_stack_.empty());    // is_empty() was replaced with empty()
      return current_token;
    }
  } while (true);  // Loop termination discussed @ start of loop.
}   // fixed closing braces


// Returns a stack action based on the passed stack and token.
//
// There are four cases to consider:
//
// A token that is both opening and closing (like a quotation mark
// might be) acts as an opening token against an empty stack or a
// stack whose top doesn't match it and gets pushed on the stack.
// Against a stack whose top DOES match it, it acts as a closing token
// instead and pops the token on the top of the stack.
//
// Otherwise, an opening token is easy: it gets pushed on the stack.
//
// A closing token must match the top of the stack and will then pop
// it.  Otherwise, we have an unbalanced closing token.
//
// Finally, an EOF with something still on the stack means some
// opening token was never closed. With an empty stack, it's fine!
//
// Note that this function is just about determining the action, NOT
// doing it.  That should facilitate testing.  (No need to consider
// the current state of this BalanceChecker's tokenizer or to
// construct a full input stream.  Just make a stack and a token and
// test what should happen with them directly.)
BalanceChecker::StackAction
BalanceChecker::determine_action(TokenStack const &token_stack,
                                 Token const &new_token) const {
  // **** HANS WAS HERE!!!! **** Case #1? We don't need no stinking Case #1.
  if (tokenizer_->is_opening(new_token) && tokenizer_->is_closing(new_token)) {
    // Case #1: Both opener and closer. If token matches top of stack,
    // then interpret as close token. If not, interpret as opening token.
    if (!token_stack.empty()
        && tokenizer_->are_matching(token_stack.top(), new_token)) {
      return kPopOldToken;
    } else {
      return kPushNewToken;
    }
  } else if (tokenizer_->is_opening(new_token)) {
    // Case #2: An opener ONLY. Just push.
    return kPushNewToken;
  } else if (tokenizer_->is_closing(new_token)) {
    // Case #3: A close ONLY. To be matching, there must be a matching
    // opening token on the top of the stack (which must be non-empty).
    if (!token_stack.empty()
        && tokenizer_->are_matching(token_stack.top(), new_token)) {
      return kPopOldToken;
    } else {
      return kReportUnbalancedToken;
    }
  } else if (new_token.is_eof()) {
    // Case #4: Reached EOF
    if (token_stack.empty()) {
      return kNoAction;
    } else {
      return kReportUnbalancedToken;
    }
  } else {
    // Otherwise: a "normal" token (no bracketing effect).
    return BalanceChecker::kNoAction;
  }
}
}  // namespace tokenizer
