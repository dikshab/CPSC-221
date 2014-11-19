// evil_hangman_utils.cc --- Defines utilities for the main Evil
// Hangman program.

// evil_hangman_utils.cc is Copyright (C) 2014 by the University of
// British Columbia, Some Rights Reserved.
//
// This work is licensed under the Creative Commons Attribution 4.0
// International License. To view a copy of this license, visit
// http://creativecommons.org/licenses/by/4.0/.

#include "./evil_hangman_utils.h"

#include <cctype>
#include <cassert>

#include <algorithm>

namespace {
// Check whether the given letter is outside the range ['a','z'] after
// being converted to lowercase.
bool is_a_to_z(char letter) {
  char lower_letter = tolower(letter);
  return lower_letter >= 'a' && lower_letter <= 'z';
}
}  // namespace

namespace evil_hangman {
WordToLengthMap get_words_by_length(std::set<std::string> const &words) {
  WordToLengthMap words_by_length;

  for (std::string word : words) {
    int size = word.size();
      if (size != 0) {
        words_by_length[size].insert(word);
      }
    }



  return words_by_length;
}

// Note: our style guideline disallows non-const references. So, this
// cannot be a std::istream &input_stream.
WordList get_words_from_stream(std::istream *input_stream) {
  WordList words;
  std::string word;
  while ((*input_stream) >> word) {
    words.push_back(word);
  }
  return words;
}

// Normalize a word for the WordSet by lowercasing and removing
// letters outside the range a-z.
std::string normalize_word(std::string const &word) {
  std::string result;
  for (std::string::const_iterator i = word.cbegin();
       i != word.cend();
       ++i) {
    if (is_a_to_z(*i)) {
      result += tolower(*i);
    }
  }
  return result;
}

// precondition: word_to_length_map is well-formed in the sense that
// all words at key i are of length i, every key i is greater than
// zero and has at least one word associated with it, and the map has
// at least one non-empty word in it.
int convert_to_legal_length(int length,
                            WordToLengthMap const word_to_length_map) {
  assert(word_to_length_map.size() > 0);

  if (word_to_length_map.find(length) == word_to_length_map.cend()) {
    // The word could not be found. Maybe an upper-bound can be found?
    WordToLengthMap::const_iterator upper_bound =
        word_to_length_map.upper_bound(length);
    if (upper_bound == word_to_length_map.cend()) {
      // No upper-bound could be found either.  We want the maximum
      // length.
      length = word_to_length_map.crbegin()->first;
    } else {
      // Found an upper-bound.  We want it.
      length = upper_bound->first;
    }
  }

  // At least one word must be present, and length must be greater
  // than 0.
  assert(length > 0 && word_to_length_map.at(length).size() > 0);

  return length;
}

// precondition: word_to_length_map is well-formed in the sense that
// all words at key i are of length i, every key i is greater than
// zero and has at least one word associated with it, and the map has
// at least one non-empty word in it.
//
// Note: our style guideline disallows non-const references. So, these
// cannot be std::istream &input_stream and std::ostream
// &output_stream.
int input_legal_length(std::istream *input_stream,
                       std::ostream *output_stream,
                       WordToLengthMap const word_to_length_map) {
  assert(word_to_length_map.size() > 0);

  int length = 0;
  int minimum = word_to_length_map.cbegin()->first;
  int maximum = word_to_length_map.crbegin()->first;

  assert(minimum > 0);

  (*output_stream) << "Please enter a length between "
                   << minimum << " and " << maximum
                   << ": " << std::endl;
  if (!((*input_stream) >> length)) {
    (*output_stream) << "I wasn't able to understand that "
                     << "as an integer length." << std::endl
                     << "I'll use the smallest length ("
                     << minimum << ") instead." << std::endl;
  }

  int adjusted_length = convert_to_legal_length(length, word_to_length_map);
  if (adjusted_length != length) {
    (*output_stream) << "There weren't any words of length " << length
                     << " available. I'll use the next available length "
                     << adjusted_length << " instead." << std::endl;
  }
  return adjusted_length;
}
}  // namespace evil_hangman
