/*
 * linkedliststack_test.cpp
 *
 * Copyright (C) 2014 by the University of British Columbia
 */

#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

#include "./token.h"
#include "./token_stack.h"
#include "./linkedliststack.h"

namespace tokenizer {
class LinkedListStackTest : public Test {
 protected:
  LinkedListStackTest() {
    stack = new LinkedListStack;
  }

  virtual ~LinkedListStackTest() {
    delete stack;
  }

  // We're including the tests inside the StackTest class so that we
  // can easily iterate over all stacks to be tested.  We set things
  // up this way so as to avoid test failures before you implement
  // your stack but to make it easy to test your stack once you're
  // ready to start implementing.  TURN THESE TESTS ON BEFORE you
  // write your first implementation code, not after you're done :)

  void test_empty_only() {
      EXPECT_THAT(stack->empty(), Eq(true));
  }

  void test_single_push_top_pop_with_empty() {
      EXPECT_THAT(stack->empty(), Eq(true));

      stack->push(token1_);

      EXPECT_THAT(stack->empty(), Eq(false));

      EXPECT_THAT(stack->top(), Eq(token1_));

      stack->pop();

      EXPECT_THAT(stack->empty(), Eq(true));
  }

  void test_many_push_many_pop() {
      EXPECT_THAT(stack->empty(), Eq(true));

      for (int j = 0; j < 10; ++j) {
        stack->push(token2_);
        EXPECT_THAT(stack->empty(), Eq(false));

        EXPECT_THAT(stack->top(), Eq(token2_));
      }

      stack->push(token1_);
      EXPECT_THAT(stack->empty(), Eq(false));

      EXPECT_THAT(stack->top(), Eq(token1_));

      stack->pop();
      EXPECT_THAT(stack->empty(), Eq(false));
      EXPECT_THAT(stack->top(), Eq(token2_));

      for (int j = 0; j < 9; ++j) {
        stack->pop();
        EXPECT_THAT(stack->empty(), Eq(false));

        EXPECT_THAT(stack->top(), Eq(token2_));
      }

      stack->pop();
      EXPECT_THAT(stack->empty(), Eq(true));
  }

  void test_up_down_up_down() {
      EXPECT_THAT(stack->empty(), Eq(true));

      stack->push(token2_);

      for (int j = 1; j < 5; ++j) {
        // Push j times.
        for (int k = 0; k < j; ++k) {
          stack->push(token1_);
          EXPECT_THAT(stack->empty(), Eq(false));

          EXPECT_THAT(stack->top(), Eq(token1_));
        }

        // Pop j-1 times.
        for (int k = 0; k < j-1; ++k) {
          EXPECT_THAT(stack->empty(), Eq(false));

          EXPECT_THAT(stack->top(), Eq(token1_));

          stack->pop();
        }

        EXPECT_THAT(stack->empty(), Eq(false));
      }

      for (int j = 1; j < 5; ++j) {
        EXPECT_THAT(stack->empty(), Eq(false));

        EXPECT_THAT(stack->top(), Eq(token1_));

        stack->pop();
      }

      EXPECT_THAT(stack->empty(), Eq(false));

      EXPECT_THAT(stack->top(), Eq(token2_));

      stack->pop();
      EXPECT_THAT(stack->empty(), Eq(true));
  }

  TokenStack * stack;

  Token token1_{1, "foo", 1, 1, 1, 1},
    token2_{2, "bar", 1, 1, 1, 1},
    token3_{3, "baz", 1, 1, 1, 1};
};
TEST_F(LinkedListStackTest, Empty) {
  test_empty_only();
}
TEST_F(LinkedListStackTest, PushTopPop) {
  test_single_push_top_pop_with_empty();
}
TEST_F(LinkedListStackTest, ManyPushManyPop) {
  test_many_push_many_pop();
}
TEST_F(LinkedListStackTest, ComplexUpDownUpDown) {
  test_up_down_up_down();
}
}  // namespace tokenizer
