// my_stack.cc --- Implement your stack here!  Look for TODO markers.

// This file is Copyright (C) 2014 by the University of British
// Columbia, Some Rights Reserved.  [If you'd like, you may change
// this and the CC statement below.  Up to you!  Certainly, you can
// put your name in!]
//
// This work is licensed under the Creative Commons Attribution 4.0
// International License. To view a copy of this license, visit
// http://creativecommons.org/licenses/by/4.0/.

#include "./my_stack.h"

#include <cassert>
#include <algorithm>

namespace tokenizer {
MyStack::~MyStack() {
  // For this function IN PARTICULAR and for all your function in
  // general, we recommend checking out builtin_stack.cc.  Yours won't
  // be the same.  (For example, you need to also deallocate array_
  // here, since your class allocated it in my_stack.h) However, in
  // some cases, the structure of that class may help!

  // TODO(you): don't forget to delete anything allocated with new ...[...]
  // using delete [] ...

  delete [] array_;
}

bool MyStack::empty() const {
  // TODO(you): fix this
  return top_ == 0;
}

void MyStack::pop() {
  assert(!empty());
  --top_;
}

void MyStack::push(Token const value) {
  if (top_ >= capacity_)
    double_capacity();

  // TODO(you): finish this
  array_[top_] = &value;
  ++top_;
}

Token const MyStack::top() const {
  assert(!empty());

  // TODO(you): fix this

  // Just something to return so the compile doesn't complain of a
  // function with a non-void return type having no return statement.
  return *array_[top_-1];
}

void MyStack::double_capacity() {
  assert(capacity_ > 0);  // else, doubling is not so useful!

  // This will be deleted by the destructor or the next call to
  // double_capacity.  To set that up, THIS call must delete the old
  // array.
  //
  // We're leaving this commented out for new; else, you'll get a
  // compiler warning for having an unused variable!
  //
  // Token const **new_array = new Token const*[2*capacity_];

  // TODO(you): copy everything from the array_ to new_array, delete the
  // old array, and then point array_ at new_array's new array. Is
  // there anything else you need to update? Yes! Look though
  // my_stack's member fields and figure out which other one needs to
  // change.
  capacity_ *= 2;
  Token const **new_array = new Token const*[capacity_];
  std::copy(array_, array_ + top_, new_array);
  delete [] array_;
  array_ = new_array;
}
}  // namespace tokenizer
