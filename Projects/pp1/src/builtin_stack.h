// builtin_stack.h --- An implementation of our TokenStack abstract
// base class using C++'s built in stack type.

// This file is Copyright (C) 2014 by the University of British
// Columbia, Some Rights Reserved.
//
// This work is licensed under the Creative Commons Attribution 4.0
// International License. To view a copy of this license, visit
// http://creativecommons.org/licenses/by/4.0/.

#ifndef RACKET_BRACKET_STACK_BUILTIN_STACK_H_
#define RACKET_BRACKET_STACK_BUILTIN_STACK_H_

#include <stack>

#include "./token_stack.h"
#include "./token.h"

namespace tokenizer {
class BuiltinStack : public TokenStack {
 public:
  BuiltinStack() { }
  virtual ~BuiltinStack() {
    // Calling pop will automatically delete each allocated Token.
    while (!empty())
      pop();
  }

  virtual bool empty() const {
    return stack_.empty();
  }

  virtual void pop() {
    delete stack_.top();
    stack_.pop();
  }

  virtual void push(Token const value) {
    stack_.push(new Token(value));
  }

  virtual Token const top() const {
    return *(stack_.top());
  }

 private:
  // Note that this is NOT a pointer.  It will be allocated when the
  // object is constructed and deallocated when the object is
  // deallocated automatically.  Thus, we need not do anything to it
  // in the destructor.
  //
  // It is, however, a stack CONTAINING pointers, and the contained
  // pointers require deleting if we allocated them (which we did!).
  std::stack<Token const*> stack_;
};
}  // namespace tokenizer

#endif  // RACKET_BRACKET_STACK_BUILTIN_STACK_H_
