/*
 * linkedliststack.cpp
 *
 * Copyright 2014 University of British Columbia
 */

#include <cassert>
#include "./linkedliststack.h"

namespace tokenizer {

LinkedListStack::LinkedListStack() : head(nullptr) {}

LinkedListStack::~LinkedListStack() {
  while (head != nullptr) {
    Node * next = head->next;
    delete head;
    head = next;
  }
}

bool LinkedListStack::empty() const {
  return head == nullptr;
}

void LinkedListStack::pop() {
  assert(!empty());
  Node * newHead = head->next;   // sets the new head of the stack to next node
  delete head;
  head = newHead;
}

void LinkedListStack::push(const Token value) {
  Node * front = new Node(value, head);  // creates a new Node pointing to head
  head = front;   // update head of array
}

const Token LinkedListStack::top() const {
  assert(!empty());
  return head->key;
}

} /* namespace tokenizer */
