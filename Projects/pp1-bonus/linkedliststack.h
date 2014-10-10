/*
 * linkedliststack.h
 *
 * Copyright 2014 University of British Columbia
 */

#ifndef _LINKEDLISTSTACK_H_
#define _LINKEDLISTSTACK_H_

#include "./token_stack.h"
#include "./token.h"

namespace tokenizer {

struct Node {
  Token const key;
  Node* next;
  Node(Token const k, Node * n) : key(k), next(n) {}
};

class LinkedListStack : public TokenStack {
 public:
  LinkedListStack();
  virtual ~LinkedListStack();

  // checks if the stack is empty
  virtual bool empty() const;

  // pops an element off the head of the stack
  // precondition: empty() == false.
  virtual void pop();

  // pushes an element onto the head of the stack
  // precondition: empty() == false.
  virtual void push(Token const value);

  // returns the top (head) of the stack
  virtual Token const top() const;
 private:
  Node * head;
};

} /* namespace tokenizer */

#endif /* LINKEDLISTSTACK_H_ */
