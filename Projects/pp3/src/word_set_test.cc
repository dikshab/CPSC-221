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

// NOTE: NOT testing partition here.  See
// word_set_test_partition_only.cc instead.

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
class WordSetTest : public Test {
 protected:
  WordSetTest() :
      ws1_("", {}),
      ws2_("_____", {"hello", "gdbye", "rectl"}),
      ws3_("___e_ae_", {"dbrevaex", "dpretaeb", "dblenaer", "dwwewaew"}) {
  }

  virtual ~WordSetTest() { }

  WordSet const ws1_;
  WordSet const ws2_;
  WordSet const ws3_;
};
TEST_F(WordSetTest, Printing) {
  std::stringstream ws1ss;
  ws1ss << ws1_;
  EXPECT_THAT(ws1ss.str(), Eq("\"\", {}"));

  std::stringstream ws2ss;
  ws2ss << ws2_;
  EXPECT_THAT(ws2ss.str(),
              Eq("\"_____\", {\"gdbye\", \"hello\", \"rectl\"}"));

  std::stringstream ws3ss;
  ws3ss << ws3_;
  EXPECT_THAT(ws3ss.str(),
              Eq("\"___e_ae_\", "
                 "{\"dblenaer\", "
                 "\"dbrevaex\", "
                 "\"dpretaeb\", "
                 "\"dwwewaew\"}"));
}
TEST_F(WordSetTest, Equality) {
  // Mutual tries on the fixtures first
  EXPECT_THAT(ws1_, Eq(ws1_));
  EXPECT_THAT(ws2_, Eq(ws2_));
  EXPECT_THAT(ws3_, Eq(ws3_));
  EXPECT_THAT(ws1_, Ne(ws2_));
  EXPECT_THAT(ws2_, Ne(ws3_));
  EXPECT_THAT(ws1_, Ne(ws3_));
  EXPECT_THAT(ws2_, Ne(ws1_));
  EXPECT_THAT(ws3_, Ne(ws2_));
  EXPECT_THAT(ws3_, Ne(ws1_));

  // Now, actually test things out.
  WordSet::StrSet wrongPattern, oneExtra, oneDiff;
  wrongPattern.insert("dbrevaex");
  wrongPattern.insert("dpretaeb");
  wrongPattern.insert("dblenaer");
  wrongPattern.insert("dwwewaew");

  oneExtra.insert("dbrevaex");
  oneExtra.insert("dpretaeb");
  oneExtra.insert("dblenaer");
  oneExtra.insert("dtrenaer");  // one extra
  oneExtra.insert("dwwewaew");

  oneDiff.insert("dbrevaex");
  oneDiff.insert("dpregaeb");   // g rather than t
  oneDiff.insert("dblenaer");
  oneDiff.insert("dwwewaew");

  WordSet ws3WrongPattern("___e__e_", wrongPattern),
      ws3OneExtra("___e_ae_", oneExtra),
      ws3OneDiff("___e_ae_", oneDiff);

  EXPECT_THAT(ws3_, Ne(ws3WrongPattern));
  EXPECT_THAT(ws3_, Ne(ws3OneExtra));
  EXPECT_THAT(ws3_, Ne(ws3OneDiff));
  EXPECT_THAT(ws3WrongPattern, Ne(ws3_));
  EXPECT_THAT(ws3OneExtra, Ne(ws3_));
  EXPECT_THAT(ws3OneDiff, Ne(ws3_));
}
TEST_F(WordSetTest, PatternAccessor) {
  EXPECT_THAT(ws1_.pattern(), Eq(""));
  EXPECT_THAT(ws2_.pattern(), Eq("_____"));
  EXPECT_THAT(ws3_.pattern(), Eq("___e_ae_"));
}
TEST_F(WordSetTest, WordsAccessor) {
  EXPECT_THAT(ws1_.words().size(), Eq(0));

  // Not sure whether this will work w/out decorating, e.g.,
  // "hello" as std::string("hello").
  EXPECT_THAT(ws2_.words(), UnorderedElementsAre("hello",
                                                 "gdbye",
                                                 "rectl"));

  EXPECT_THAT(ws3_.words(), UnorderedElementsAre("dbrevaex",
                                                 "dpretaeb",
                                                 "dblenaer",
                                                 "dwwewaew"));
}

TEST_F(WordSetTest, Size) {
  EXPECT_THAT(ws1_.size(), Eq(0));
  EXPECT_THAT(ws2_.size(), Eq(3));
  EXPECT_THAT(ws3_.size(), Eq(4));
}

TEST_F(WordSetTest, BadConstructorCalls) {
  WordSet::StrSet words1, words2, words3, words4, words5, words6;
  words2.insert("abc");
  words3.insert("a"); words3.insert("bc");
  words4.insert("abc"); words4.insert("xYz");
  words5.insert("a b");
  words6.insert("hello"); words6.insert("belle");

  // (1) all words and the pattern have the same length
  EXPECT_THROW(WordSet("__", words2), std::invalid_argument);
  EXPECT_THROW(WordSet("____", words2), std::invalid_argument);
  EXPECT_THROW(WordSet("_", words3), std::invalid_argument);
  EXPECT_THROW(WordSet("__", words3), std::invalid_argument);

  // (2) all letters in the words are in [a-z]
  EXPECT_THROW(WordSet("___", words4), std::invalid_argument);
  EXPECT_THROW(WordSet("___", words5), std::invalid_argument);

  // (3) all letters in the pattern are in [a-z_]
  EXPECT_THROW(WordSet("_A_", words2), std::invalid_argument);
  EXPECT_THROW(WordSet("1__", words2), std::invalid_argument);
  EXPECT_THROW(WordSet("__ ", words2), std::invalid_argument);

  // (4) every word has the same letter as the pattern at any
  // letter in the pattern that is not an underscore
  EXPECT_THROW(WordSet("b__", words2), std::invalid_argument);
  EXPECT_THROW(WordSet("_e__e", words6), std::invalid_argument);
  EXPECT_THROW(WordSet("_all_", words6), std::invalid_argument);


  // (5) no word has the same letter as any non-underscore at any
  // OTHER location in the pattern.
  EXPECT_THROW(WordSet("__l__", words6), std::invalid_argument);
  EXPECT_THROW(WordSet("_ell_", words6), std::invalid_argument);

  // SPECIAL CASE: an empty word list must have an empty pattern.
  EXPECT_THROW(WordSet("_", words1), std::invalid_argument);
  EXPECT_THROW(WordSet("a", words1), std::invalid_argument);

  // Double-check that the possibly legal patterns work.
  EXPECT_NO_THROW(WordSet("", words1));

  EXPECT_NO_THROW(WordSet("___", words2));
  EXPECT_NO_THROW(WordSet("a__", words2));
  EXPECT_NO_THROW(WordSet("_b_", words2));
  EXPECT_NO_THROW(WordSet("__c", words2));
  EXPECT_NO_THROW(WordSet("ab_", words2));
  EXPECT_NO_THROW(WordSet("a_c", words2));
  EXPECT_NO_THROW(WordSet("_bc", words2));
  EXPECT_NO_THROW(WordSet("abc", words2));

  EXPECT_NO_THROW(WordSet("_____", words6));
  EXPECT_NO_THROW(WordSet("__ll_", words6));
}

TEST_F(WordSetTest, FindMatchingWords) {
  std::vector<std::string> sets = ws1_.find_matching_words('a');
  EXPECT_THAT(sets.size(), Eq(0));

  sets = ws2_.find_matching_words('a');
  EXPECT_THAT(sets.size(), Eq(0));

  sets = ws2_.find_matching_words('e');
  EXPECT_THAT(sets.size(), Eq(3));
  EXPECT_THAT(sets, UnorderedElementsAre("hello", "gdbye", "rectl"));

  sets = ws2_.find_matching_words('l');
  EXPECT_THAT(sets.size(), Eq(2));
  EXPECT_THAT(sets, UnorderedElementsAre("hello", "rectl"));

  sets = ws3_.find_matching_words('r');
  EXPECT_THAT(sets.size(), Eq(3));
  EXPECT_THAT(sets, UnorderedElementsAre("dbrevaex", "dpretaeb", "dblenaer"));
}

TEST_F(WordSetTest, ExtractPattern) {
  std::string newPattern = ws2_.extract_pattern("abcde", 'e');
  EXPECT_THAT(newPattern, Eq("____e"));

  newPattern = ws2_.extract_pattern("abcbe", 'b');
  EXPECT_THAT(newPattern, Eq("_b_b_"));

  newPattern = ws3_.extract_pattern("dtrelaey", 'y');
  EXPECT_THAT(newPattern, Eq("___e_aey"));

  newPattern = ws3_.extract_pattern("isdeiaed", 'i');
  EXPECT_THAT(newPattern, Eq("i__eiae_"));
}

TEST_F(WordSetTest, GenerateWordSetFromPattern) {
  std::vector<std::string> words;
  words.push_back("hello");
  words.push_back("jello");
  words.push_back("lolli");
  words.push_back("candl");
  WordSet result = ws2_.generate_wordset_from_pattern("__ll_", 'l', words);
  EXPECT_THAT(result.pattern(), Eq("__ll_"));
  EXPECT_THAT(result.words(), UnorderedElementsAre("hello", "jello"));

  words.clear();
  words.push_back("dbrevaex");
  words.push_back("dpretaeb");
  words.push_back("dblenaer");
  words.push_back("dwwewaew");

  result = ws3_.generate_wordset_from_pattern("__re_ae_", 'r', words);
  EXPECT_THAT(result.pattern(), Eq("__re_ae_"));
  EXPECT_THAT(result.words(), UnorderedElementsAre("dbrevaex", "dpretaeb"));
}

TEST_F(WordSetTest, GenerateNewWordSet) {
  // Note: because the generate_new_wordset is non-deterministic when more
  // than one word in the wordset contains the character, only the
  // deterministic cases are tested
  WordSet result = ws2_.generate_new_wordset('o');
  EXPECT_THAT(result.pattern(), Eq("____o"));
  EXPECT_THAT(result.words(), ElementsAre("hello"));

  result = ws3_.generate_new_wordset('w');
  EXPECT_THAT(result.pattern(), Eq("_wwewaew"));
  EXPECT_THAT(result.words(), ElementsAre("dwwewaew"));


  result = ws3_.generate_new_wordset('y');
  EXPECT_THAT(result.pattern(), Eq(ws3_.pattern()));
  EXPECT_THAT(result.words(),
              UnorderedElementsAre("dwwewaew",
                                   "dbrevaex",
                                   "dpretaeb",
                                   "dblenaer"));
}

// TEST_F(WordSetTest, PartitionErrors) {
//   // Cannot partition on a non-[a-z].
//   EXPECT_THROW(ws1_.partition('A'), std::invalid_argument);
//   EXPECT_THROW(ws1_.partition(' '), std::invalid_argument);
//   EXPECT_THROW(ws1_.partition('_'), std::invalid_argument);
//   EXPECT_THROW(ws1_.partition('0'), std::invalid_argument);

//   // Decided not to enforce because we cannot partition on
//   // something we've already partitioned on.

//   // EXPECT_THROW(ws3_.partition('a'), std::invalid_argument);
// }

// TEST_F(WordSetTest, Partition) {
//   std::vector<WordSet> sets = ws1_.partition('a');
//   EXPECT_THAT(sets.size(), Eq(0));

//   sets = ws2_.partition('a');  // not present in the strings
//   EXPECT_THAT(sets, ElementsAre(ws2_));

//   sets = ws3_.partition('z');  // not present in the strings
//   EXPECT_THAT(sets, ElementsAre(ws3_));

//   sets = ws3_.partition('d');  // present in all strings in the same place
//   EXPECT_THAT(sets, ElementsAre(WordSet("d__e_ae_", ws3_.words())));

//   sets = ws3_.partition('b');  // different pattern of presence
//   EXPECT_THAT(sets,
//               UnorderedElementsAre(WordSet("_b_e_ae_",
//                                            {"dblenaer", "dbrevaex"}),
//                                    WordSet("___e_aeb", {"dpretaeb"}),
//                                    WordSet("___e_ae_", {"dwwewaew"})));

//   sets = ws3_.partition('w');  // multiple instances in one result
//   EXPECT_THAT(sets,
//               UnorderedElementsAre(WordSet("___e_ae_",
//                                            {
//                                              "dblenaer",
//                                                  "dbrevaex",
//                                                  "dpretaeb"
//                                                  }),
//                                    WordSet("_wwewaew", {"dwwewaew"})));

//   sets = ws3_.partition('d');  // all instances in one result with a reveal
//   EXPECT_THAT(sets, UnorderedElementsAre(WordSet("d__e_ae_", {
//           "dblenaer",
//               "dbrevaex",
//               "dpretaeb",
//               "dwwewaew"})));
// }

// Currently immutable; so, there's no black-box testing for
// identity/deep-copy possible.
TEST_F(WordSetTest, CopyConstructor) {
  WordSet other1(ws1_), other2(ws2_), other3(ws3_);

  EXPECT_THAT(other1, Eq(ws1_));
  EXPECT_THAT(other2, Eq(ws2_));
  EXPECT_THAT(other3, Eq(ws3_));
}
TEST_F(WordSetTest, ChooseRandomWord) {
  // Just test a few times.
  EXPECT_THAT(ws3_.words(), Contains(ws3_.choose_random_word()));
  EXPECT_THAT(ws3_.words(), Contains(ws3_.choose_random_word()));
  EXPECT_THAT(ws3_.words(), Contains(ws3_.choose_random_word()));
  EXPECT_THAT(ws3_.words(), Contains(ws3_.choose_random_word()));

  // Probabilistic test.  This COULD fail with tremendously low
  // probability.
  WordSet ws("____", {"abcd", "efgh", "ijkl"});
  WordSet::StrSet result_set;
  for (int i = 0; i < 10000; i++)
    result_set.insert(ws.choose_random_word());
  EXPECT_THAT(result_set, UnorderedElementsAre("abcd", "efgh", "ijkl"));

  // Degenerate case returns the empty string.
  EXPECT_THAT(ws1_.choose_random_word(), Eq(""));
}
}  // namespace testing
}  // namespace evil_hangman
