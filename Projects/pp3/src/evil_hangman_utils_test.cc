// evil_hangman_utils_test.cc --- Test code for the utility functions
// of the Evil Hangman application.

// evil_hangman_utils_test.cc is Copyright (C) 2014 by CPSC 221 at the
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
#include <gtest/gtest.h>
using ::testing::Test;

#include <sstream>
#include <fstream>

#include "./evil_hangman_utils.h"

namespace evil_hangman {
namespace testing {
class EvilHangmanTest : public Test {
 protected:
  EvilHangmanTest() { }

  virtual ~EvilHangmanTest() { }

  std::set<std::string> words_empty_{},
    words_one_word_{"hello"},
    words_one_each_diff_length_{"hello", "goodbye"},
    words_several_in_several_lengths_{
      "a", "aa", "b", "bb", "cc", "d", "e", "fff"},
    words_check_empty_set_{"hello", "goodbye", "cards", "", " a-bC"};

  WordToLengthMap results_by_length_empty_{},
    results_by_length_one_word_{{5, {"hello"}}},
    results_by_length_one_each_diff_length_{{5, {"hello"}}, {7, {"goodbye"}}},
    results_by_length_several_in_several_lengths_{
      {1, {"a", "b", "d", "e"}},
      {2, {"aa", "bb", "cc"}},
      {3, {"fff"}}
    },
    results_by_length_check_empty_set_{
      {5, {"hello", "cards", " a-bC"}},
      {7, {"goodbye"}}
    };

  std::stringstream stream_empty_{"  \n\t  \n"},
    stream_one_word_{" \n \thello  "},
    stream_two_words_{"hello\ngoodbye\n\n"},
    stream_multi_words_{". !? abc-def__!ghi j"};

  std::stringstream stream_number0_{"0"},
    stream_number1_{"1"},
    stream_number4_{"4"},
    stream_number5_{"5"},
    stream_number6_{"6"},
    stream_number7_{"7"},
    stream_number8_{"8"},
    stream_number_neg1_{"-1"};

  WordList unnormalized_words_ = {
    "",
    "a",
    "abc",
    "A",
    "aBc",
    "a1",
    "a b.! 3C"
  };
  WordList normalized_words_ = {
    "",
    "a",
    "abc",
    "a",
    "abc",
    "a",
    "abc"
  };

  // uninitialized dummy output stream, used as "/dev/null"
  // equivalent.
  std::ofstream dummy_output_stream_;
};

TEST_F(EvilHangmanTest, WordsByLength) {
  EXPECT_THAT(get_words_by_length(words_empty_),
              Eq(results_by_length_empty_));
  EXPECT_THAT(get_words_by_length(words_one_word_),
              Eq(results_by_length_one_word_));
  EXPECT_THAT(get_words_by_length(words_one_each_diff_length_),
              Eq(results_by_length_one_each_diff_length_));
  EXPECT_THAT(get_words_by_length(words_several_in_several_lengths_),
              Eq(results_by_length_several_in_several_lengths_));
  EXPECT_THAT(get_words_by_length(words_check_empty_set_),
              Eq(results_by_length_check_empty_set_));
}

TEST_F(EvilHangmanTest, WordsFromStream) {
  EXPECT_THAT(get_words_from_stream(&stream_empty_),
              Eq(WordList{}));
  EXPECT_THAT(get_words_from_stream(&stream_one_word_),
              Eq(WordList{"hello"}));
  EXPECT_THAT(get_words_from_stream(&stream_two_words_),
              Eq(WordList{"hello", "goodbye"}));
  EXPECT_THAT(get_words_from_stream(&stream_multi_words_),
              Eq(WordList{".", "!?", "abc-def__!ghi", "j"}));
}

TEST_F(EvilHangmanTest, NormalizeWords) {
  ASSERT_THAT(unnormalized_words_.size(), Eq(normalized_words_.size()));

  for (int i = 0; i < unnormalized_words_.size(); i++) {
    EXPECT_THAT(normalize_word(unnormalized_words_[i]),
                Eq(normalized_words_[i]));
  }
}

TEST_F(EvilHangmanTest, ConvertToLegalLength) {
  EXPECT_THAT(convert_to_legal_length(-1, results_by_length_check_empty_set_),
              Eq(5));
  EXPECT_THAT(convert_to_legal_length(0, results_by_length_check_empty_set_),
              Eq(5));
  EXPECT_THAT(convert_to_legal_length(1, results_by_length_check_empty_set_),
              Eq(5));
  EXPECT_THAT(convert_to_legal_length(4, results_by_length_check_empty_set_),
              Eq(5));
  EXPECT_THAT(convert_to_legal_length(5, results_by_length_check_empty_set_),
              Eq(5));
  EXPECT_THAT(convert_to_legal_length(6, results_by_length_check_empty_set_),
              Eq(7));
  EXPECT_THAT(convert_to_legal_length(7, results_by_length_check_empty_set_),
              Eq(7));
  EXPECT_THAT(convert_to_legal_length(8, results_by_length_check_empty_set_),
              Eq(7));

  EXPECT_THAT(convert_to_legal_length(-1, results_by_length_one_word_),
              Eq(5));
  EXPECT_THAT(convert_to_legal_length(0, results_by_length_one_word_),
              Eq(5));
  EXPECT_THAT(convert_to_legal_length(1, results_by_length_one_word_),
              Eq(5));
  EXPECT_THAT(convert_to_legal_length(4, results_by_length_one_word_),
              Eq(5));
  EXPECT_THAT(convert_to_legal_length(5, results_by_length_one_word_),
              Eq(5));
  EXPECT_THAT(convert_to_legal_length(6, results_by_length_one_word_),
              Eq(5));
}

TEST_F(EvilHangmanTest, InputLegalLength) {
  EXPECT_THAT(input_legal_length(&stream_number_neg1_,
                                 &dummy_output_stream_,
                                 results_by_length_check_empty_set_),
              Eq(5));
  EXPECT_THAT(input_legal_length(&stream_number0_,
                                 &dummy_output_stream_,
                                 results_by_length_check_empty_set_),
              Eq(5));
  EXPECT_THAT(input_legal_length(&stream_number1_,
                                 &dummy_output_stream_,
                                 results_by_length_check_empty_set_),
              Eq(5));
  EXPECT_THAT(input_legal_length(&stream_number4_,
                                 &dummy_output_stream_,
                                 results_by_length_check_empty_set_),
              Eq(5));
  EXPECT_THAT(input_legal_length(&stream_number5_,
                                 &dummy_output_stream_,
                                 results_by_length_check_empty_set_),
              Eq(5));
  EXPECT_THAT(input_legal_length(&stream_number6_,
                                 &dummy_output_stream_,
                                 results_by_length_check_empty_set_),
              Eq(7));
  EXPECT_THAT(input_legal_length(&stream_number7_,
                                 &dummy_output_stream_,
                                 results_by_length_check_empty_set_),
              Eq(7));
  EXPECT_THAT(input_legal_length(&stream_number8_,
                                 &dummy_output_stream_,
                                 results_by_length_check_empty_set_),
              Eq(7));
  EXPECT_THAT(input_legal_length(&stream_one_word_,
                                 &dummy_output_stream_,
                                 results_by_length_check_empty_set_),
              Eq(5));
}
}  // namespace testing
}  // namespace evil_hangman
