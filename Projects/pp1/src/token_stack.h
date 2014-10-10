// token_stack.h --- Abstract base class for a stack of tokens.
// (Normally, if we had such a class, we'd make it a templated
// abstract stack base class for any type, but we didn't want to add
// defining a templated class to all the many things you're already
// doing in PP#1!)

// This file is Copyright (C) 2014 by the University of British
// Columbia, Some Rights Reserved.
//
// This work is licensed under the Creative Commons Attribution 4.0
// International License. To view a copy of this license, visit
// http://creativecommons.org/licenses/by/4.0/.

#ifndef RACKET_BRACKET_STACK_TOKEN_STACK_H_
#define RACKET_BRACKET_STACK_TOKEN_STACK_H_

#include "./token.h"

namespace tokenizer {

class TokenStack {
 public:
  TokenStack() { }

  // Abstract classes MUST have virtual destructors or badness occurs.
  virtual ~TokenStack() { }

  virtual bool empty() const = 0;

  // precondition: !empty()
  virtual void pop() = 0;

  virtual void push(Token const value) = 0;

  // precondition: !empty()
  virtual Token const top() const = 0;
};
}  // namespace tokenizer

#endif  // RACKET_BRACKET_STACK_TOKEN_STACK_H_
