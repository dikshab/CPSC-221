// word_set.h --- Declares the WordSet class for managing sets of words
// matching a particular revealed pattern in the common "hangman"
// game.


// word_set.h is Copyright (C) 2014 by the University of British Columbia,
// Some Rights Reserved.
//
// This work is licensed under the Creative Commons Attribution 4.0
// International License. To view a copy of this license, visit
// http://creativecommons.org/licenses/by/4.0/.

#ifndef DYNAMIC_HANGMAN_WORD_SET_H_
#define DYNAMIC_HANGMAN_WORD_SET_H_

#include <string>
#include <vector>
#include <set>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <ostream>
#include <map>

namespace evil_hangman {
class WordSet {
 public:
  typedef std::set<std::string> StrSet;
  typedef StrSet::size_type size_type;

  static void validate(std::string const & pattern,
                       StrSet const & words);

  // Constructs a wordset, ensuring that: (1) all words and the
  // pattern have the same length, (2) all letters in the words are
  // in [a-z], (3) all letters in the pattern are in [a-z_], (4)
  // every word has the same letter as the pattern at any letter in
  // the pattern that is not an underscore, (5) no word has the same
  // letter as any non-underscore at any OTHER location in the
  // pattern.  SPECIAL CASE: an empty word list must have an empty
  // pattern.
  WordSet(std::string const pattern, StrSet const words)
      : pattern_(pattern), words_(words) {
    validate(pattern_, words_);
  }

  // Copy constructor.
  WordSet(WordSet const & other)
      : pattern_(other.pattern_), words_(other.words_) { }

  virtual ~WordSet() { }

  size_type size() const {
    return words_.size();
  }

  std::string const & pattern() const {
    return pattern_;
  }

  StrSet const & words() const {
    return words_;
  }

  // Generates a new wordset by picking a random word from the current
  // wordset that contains the character guessed and generating a new
  // pattern based on it, adding all words from the current wordset
  // that matches that pattern.
  //
  // If no word contains the guess, instead just return the current
  // pattern/set of words.
  WordSet generate_new_wordset(char guess) const;

  // Given a guessed character, find all words in the word set that contain
  // that character
  std::vector<std::string> find_matching_words(char guess) const;

  // Given a word and guess, construct a new pattern by building on
  // the existing pattern.
  std::string extract_pattern(std::string word, char guess) const;

  // Given a pattern and words, extract all words that match the
  // pattern and generate a WordSet.
  WordSet generate_wordset_from_pattern(std::string pattern,
                                        char guess,
                                        std::vector<std::string> words) const;

  // Creates a list of new wordsets representing the result of
  // partitioning the current list according to the given guess.
  // That is: (1) each wordset in the new list EITHER does not
  // contain the guess in its pattern and includes all words that do
  // not contain that letter OR contains the guess in its pattern
  // and includes all of one subset of the words in the original
  // wordset that contain that letter in exactly matching locations.
  // It is a partition in the sense that the union of all sets of
  // words in the wordsets is the original set of words in the
  // wordset but no word appears in multiple produced wordsets.
  std::vector<WordSet> partition(char guess) const;

  // Choose a word at random from the set.  If the set is empty,
  // returns the empty string.
  std::string choose_random_word() const;

 private:
  typedef std::uniform_int_distribution<size_type> Distribution;

  StrSet words_;
  std::string pattern_;
};

std::ostream& operator<<(std::ostream &, WordSet const &);
inline bool operator==(WordSet const &lhs, WordSet const &rhs) {
  return lhs.pattern() == rhs.pattern() &&
      lhs.words() == rhs.words();
}
inline bool operator!=(WordSet const &lhs, WordSet const &rhs) {
  return !(lhs == rhs);
}
}  // namespace evil_hangman

#endif  // DYNAMIC_HANGMAN_WORD_SET_H_
