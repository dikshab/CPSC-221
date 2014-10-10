// stack_test.cc --- Test code for the TokenStack class and its
// subclasses.

// This file is Copyright (C) 2014 by CPSC 221 at the University of
// British Columbia, Some Rights Reserved.
//
// This work is licensed under the Creative Commons Attribution 4.0
// International License. To view a copy of this license, visit
// http://creativecommons.org/licenses/by/4.0/.

// Basing testing on:
// http://johnlamp.net/cmake-tutorial-4-libraries-and-subdirectories.html
// along with MANY other references.

#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

#include "./token.h"
#include "./token_stack.h"
#include "./my_stack.h"
#include "./builtin_stack.h"

namespace tokenizer {
class StackTest : public Test {
 protected:
  StackTest() {
    stacks[0] = new BuiltinStack;
    stacks[1] = new MyStack;
  }

  virtual ~StackTest() {
    delete stacks[0];
    stacks[0] = nullptr;

    delete stacks[1];
    stacks[1] = nullptr;
  }

  // We're including the tests inside the StackTest class so that we
  // can easily iterate over all stacks to be tested.  We set things
  // up this way so as to avoid test failures before you implement
  // your stack but to make it easy to test your stack once you're
  // ready to start implementing.  TURN THESE TESTS ON BEFORE you
  // write your first implementation code, not after you're done :)

  void test_empty_only() {
    for (int i = 0; i < num_token_stacks; ++i) {
      EXPECT_THAT(stacks[i]->empty(), Eq(true));
    }
  }

  void test_single_push_top_pop_with_empty() {
    for (int i = 0; i < num_token_stacks; ++i) {
      EXPECT_THAT(stacks[i]->empty(), Eq(true));

      stacks[i]->push(token1_);

      EXPECT_THAT(stacks[i]->empty(), Eq(false));

      EXPECT_THAT(stacks[i]->top(), Eq(token1_));

      stacks[i]->pop();

      EXPECT_THAT(stacks[i]->empty(), Eq(true));
    }
  }

  void test_many_push_many_pop() {
    for (int i = 0; i < num_token_stacks; ++i) {
      EXPECT_THAT(stacks[i]->empty(), Eq(true));

      for (int j = 0; j < 10; ++j) {
        stacks[i]->push(token2_);
        EXPECT_THAT(stacks[i]->empty(), Eq(false));

        EXPECT_THAT(stacks[i]->top(), Eq(token2_));
      }

      stacks[i]->push(token1_);
      EXPECT_THAT(stacks[i]->empty(), Eq(false));

      EXPECT_THAT(stacks[i]->top(), Eq(token1_));

      stacks[i]->pop();
      EXPECT_THAT(stacks[i]->empty(), Eq(false));
      EXPECT_THAT(stacks[i]->top(), Eq(token2_));

      for (int j = 0; j < 9; ++j) {
        stacks[i]->pop();
        EXPECT_THAT(stacks[i]->empty(), Eq(false));

        EXPECT_THAT(stacks[i]->top(), Eq(token2_));
      }

      stacks[i]->pop();
      EXPECT_THAT(stacks[i]->empty(), Eq(true));
    }
  }

  void test_up_down_up_down() {
    for (int i = 0; i < num_token_stacks; ++i) {
      EXPECT_THAT(stacks[i]->empty(), Eq(true));

      stacks[i]->push(token2_);

      for (int j = 1; j < 5; ++j) {
        // Push j times.
        for (int k = 0; k < j; ++k) {
          stacks[i]->push(token1_);
          EXPECT_THAT(stacks[i]->empty(), Eq(false));

          EXPECT_THAT(stacks[i]->top(), Eq(token1_));
        }

        // Pop j-1 times.
        for (int k = 0; k < j-1; ++k) {
          EXPECT_THAT(stacks[i]->empty(), Eq(false));

          EXPECT_THAT(stacks[i]->top(), Eq(token1_));

          stacks[i]->pop();
        }

        EXPECT_THAT(stacks[i]->empty(), Eq(false));
      }

      for (int j = 1; j < 5; ++j) {
        EXPECT_THAT(stacks[i]->empty(), Eq(false));

        EXPECT_THAT(stacks[i]->top(), Eq(token1_));

        stacks[i]->pop();
      }

      EXPECT_THAT(stacks[i]->empty(), Eq(false));

      EXPECT_THAT(stacks[i]->top(), Eq(token2_));

      stacks[i]->pop();
      EXPECT_THAT(stacks[i]->empty(), Eq(true));
    }
  }

  TokenStack *stacks[2];

  // TODO(you): To test YOUR stack, change this to 2.
  int num_token_stacks = 2;

  Token token1_{1, "foo", 1, 1, 1, 1},
    token2_{2, "bar", 1, 1, 1, 1},
    token3_{3, "baz", 1, 1, 1, 1};
};
TEST_F(StackTest, Empty) {
  test_empty_only();
}
TEST_F(StackTest, PushTopPop) {
  test_single_push_top_pop_with_empty();
}
TEST_F(StackTest, ManyPushManyPop) {
  test_many_push_many_pop();
}
TEST_F(StackTest, ComplexUpDownUpDown) {
  test_up_down_up_down();
}
}  // namespace tokenizer
