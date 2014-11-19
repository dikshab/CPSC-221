// word_set_test.cc --- Test code for the WordSet class declared in
// word_set.h

// word_set_test.cc is Copyright (C) 2014 by CPSC 221 at the
// University of British Columbia, Some Rights Reserved.
//
// This work is licensed under the Creative Commons Attribution 4.0
// International License. To view a copy of this license, visit
// http://creativecommons.org/licenses/by/4.0/.

// Basing testing and CMake files on:
// http://johnlamp.net/cmake-tutorial-4-libraries-and-subdirectories.html
// along with MANY other references.

#include <gmock/gmock.h>
using ::testing::Eq;
using ::testing::StrEq;
using ::testing::Ne;
using ::testing::Ge;
using ::testing::ElementsAre;
using ::testing::UnorderedElementsAre;
using ::testing::Contains;
#include <gtest/gtest.h>
using ::testing::Test;

#include <sstream>

#include "./word_set.h"

namespace evil_hangman {
namespace testing {
class WordSetPartitionTest : public Test {
 protected:
  WordSetPartitionTest() :
      ws1_("", {}),
      ws2_("_____", {"hello", "gdbye", "rectl"}),
      ws3_("___e_ae_", {"dbrevaex", "dpretaeb", "dblenaer", "dwwewaew"}) {
  }

  virtual ~WordSetPartitionTest() { }

  WordSet const ws1_;
  WordSet const ws2_;
  WordSet const ws3_;
};

TEST_F(WordSetPartitionTest, PartitionErrors) {
  // Cannot partition on a non-[a-z].
  EXPECT_THROW(ws1_.partition('A'), std::invalid_argument);
  EXPECT_THROW(ws1_.partition(' '), std::invalid_argument);
  EXPECT_THROW(ws1_.partition('_'), std::invalid_argument);
  EXPECT_THROW(ws1_.partition('0'), std::invalid_argument);

  // Decided not to enforce because we cannot partition on
  // something we've already partitioned on.

  // EXPECT_THROW(ws3_.partition('a'), std::invalid_argument);
}

TEST_F(WordSetPartitionTest, Partition) {
  std::vector<WordSet> sets = ws1_.partition('a');
  EXPECT_THAT(sets.size(), Eq(0));

  sets = ws2_.partition('a');  // not present in the strings
  EXPECT_THAT(sets, ElementsAre(ws2_));

  sets = ws3_.partition('z');  // not present in the strings
  EXPECT_THAT(sets, ElementsAre(ws3_));

  sets = ws3_.partition('d');  // present in all strings in the same place
  EXPECT_THAT(sets, ElementsAre(WordSet("d__e_ae_", ws3_.words())));

  sets = ws3_.partition('b');  // different pattern of presence
  EXPECT_THAT(sets,
              UnorderedElementsAre(WordSet("_b_e_ae_",
                                           {"dblenaer", "dbrevaex"}),
                                   WordSet("___e_aeb", {"dpretaeb"}),
                                   WordSet("___e_ae_", {"dwwewaew"})));

  sets = ws3_.partition('w');  // multiple instances in one result
  EXPECT_THAT(sets,
              UnorderedElementsAre(WordSet("___e_ae_",
                                           {
                                             "dblenaer",
                                                 "dbrevaex",
                                                 "dpretaeb"
                                                 }),
                                   WordSet("_wwewaew", {"dwwewaew"})));

  sets = ws3_.partition('d');  // all instances in one result with a reveal
  EXPECT_THAT(sets, UnorderedElementsAre(WordSet("d__e_ae_", {
          "dblenaer",
              "dbrevaex",
              "dpretaeb",
              "dwwewaew"})));
}

}  // namespace testing
}  // namespace evil_hangman
