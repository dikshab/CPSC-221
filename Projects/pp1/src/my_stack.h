// my_stack.h --- Eventually: your own implementation of the stack
// abstract base class using an underlying, dynamically allocated
// array.

// This file is Copyright (C) 2014 by the University of British
// Columbia, Some Rights Reserved.  [If you'd like, you may change
// this and the CC statement below.  Up to you!  Certainly, you can
// put your name in!]
//
// This work is licensed under the Creative Commons Attribution 4.0
// International License. To view a copy of this license, visit
// http://creativecommons.org/licenses/by/4.0/.

#ifndef RACKET_BRACKET_STACK_MY_STACK_H_
#define RACKET_BRACKET_STACK_MY_STACK_H_

#include "./token_stack.h"
#include "./token.h"

namespace tokenizer {
// You should NOT change this file.  Your implementation goes in
// my_stack.cc.
class MyStack : public TokenStack {
 public:
  MyStack() { }
  virtual ~MyStack();
  virtual bool empty() const;

  // precondition: empty() == false.
  virtual void pop();

  virtual void push(Token const value);

  // precondition: empty() == false.
  virtual Token const top() const;

 private:
  // Doubles the capacity of the stack.
  void double_capacity();

  // Default initial capacity (do not change!).
  int INITIAL_ARRAY_CAPACITY = 4;

  // The array in which the data is actually stored.

  // Note: this is of the type "pointer to a pointer to a constant
  // Token". It is, in fact, a pointer to the start of an array of
  // tokens.  So, e.g., array_[2] would be a Token const*.
  //
  // Why store pointers? Because once we construct a Token, we cannot
  // change it.  So, to copy and locally manipulate the Tokens passed
  // in, we need to explicitly make copies.
  //
  // That means in the destructor, we need to ensure we delete
  // everything that we've allocated!
  Token const **array_ = new Token const*[INITIAL_ARRAY_CAPACITY];

  // Location where the next element pushed belongs.
  int top_ = 0;

  // Maximum number of elements storable in the array before it
  // resizes.
  int capacity_ = INITIAL_ARRAY_CAPACITY;
};
}  // namespace tokenizer

#endif  // RACKET_BRACKET_STACK_MY_STACK_H_
