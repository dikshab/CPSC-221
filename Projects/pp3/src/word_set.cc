// word_set.cc --- Defines the WordSet class for managing sets of
// words matching a particular revealed pattern in the common
// "hangman" game.


// word_set.cc is Copyright (C) 2014 by the University of British Columbia,
// Some Rights Reserved.
//
// This work is licensed under the Creative Commons Attribution 4.0
// International License. To view a copy of this license, visit
// http://creativecommons.org/licenses/by/4.0/.


#include "./word_set.h"

#include <sstream>
#include <random>

namespace {
// Surrounds str with quotations marks: hello => "hello"
std::string make_quoted(std::string const & str) {
  return "\"" + str + "\"";
}

std::random_device rd;
std::default_random_engine generator(rd());
}  // namespace

namespace evil_hangman {

void WordSet::validate(std::string const & pattern,
                       StrSet const & words) {
  // Special case if no words:
  if (words.size() == 0) {
    if (pattern != "") {
      throw std::invalid_argument("pattern must be empty "
                                  "with an empty word set");
    }
    return;
  }

  // From here out, we know there's at least one word.

  // all letters in the pattern are in [a-z_]
  if (!std::all_of(pattern.cbegin(), pattern.cend(),
                   [](char c){ return c == '_' ||
                         (c >= 'a' && c <= 'z'); })) {
    throw std::invalid_argument("all characters in the pattern "
                                "must be lower-case letters [a-z] "
                                "or underscores _");
  }

  for (std::string word : words) {
    if (word.size() != pattern.size()) {
      throw std::invalid_argument("all words and the pattern "
                                  "must be the same length");
    }

    for (unsigned int i = 0; i < word.size(); i++) {
      char c = word[i];
      if (!(c >= 'a' && c <= 'z')) {
        throw std::invalid_argument("all characters in all words "
                                    "must be lower-case letters [a-z]");
      }

      if (pattern[i] != '_' && pattern[i] != word[i]) {
        throw std::invalid_argument("all words must match "
                                    "the letters in the pattern");
      }

      // This is an inefficient solution
      // (O(word_length^2*num_words)), but that shouldn't matter
      // because word length is not expected to be large.  In case
      // it's important, a more efficient solution would be to
      // count the number of each letter in the pattern, count the
      // number of each letter in the word, and check that they
      // match on the pattern letters (not counting underscores,
      // of course!).  This should be doable in
      // O(word_length*num_words) time.
      for (unsigned int j = i+1; j < word.size(); j++) {
        if (word[j] == pattern[i] &&
            word[j] != pattern[j]) {
          throw std::invalid_argument("the pattern must match "
                                      "ALL or NO instances of "
                                      "any letter from the words");
        }
      }
    }
  }
}

WordSet WordSet::generate_new_wordset(char guess) const {
  if (!(guess >= 'a' && guess <= 'z'))
    throw std::invalid_argument("guess must be a lower-case letter");

  // find all words that contain the guessed character
  std::vector<std::string> wordsWithGuess = find_matching_words(guess);

  if (wordsWithGuess.size() == 0)
      return *this;

  std::uniform_int_distribution<int>  distribution(0, wordsWithGuess.size()-1);
  int index = distribution(generator);
  std::string templateWord = wordsWithGuess[index];
  std::string newPattern = extract_pattern(templateWord, guess);

  return generate_wordset_from_pattern(newPattern, guess, wordsWithGuess);
}

std::vector<std::string> WordSet::find_matching_words(char guess) const {
  std::vector<std::string>  matchingWords;
  for (std::string word : words_) {
    if (word.find(guess) != std::string::npos)
      matchingWords.push_back(word);
    }

  return matchingWords;
}

std::string WordSet::extract_pattern(std::string word, char guess) const {
  std::string newPattern;

  for (int i = 0; i < word.size(); i++) {
      if (word[i] == guess)
        newPattern += word[i];
      else if (pattern_[i] != '_')
        newPattern += pattern_[i];
      else
        newPattern += '_';
    }

  return newPattern;
}

WordSet
WordSet::generate_wordset_from_pattern(std::string pattern,
                                       char guess,
                                       std::vector<std::string> words) const {
  // TODO(you): Fix the bug(s) in this method
  StrSet newWords;

  for (std::string word : words) {
    std::string wordPattern;
    for (int i = 0; i < word.size(); i++) {
      if (word[i] == guess)
        wordPattern += word[i];
      else
        wordPattern += '_';
    }

    bool acc = true;
    for (int i = 0; i < word.size(); i++) {
      if (pattern[i] =='_')
          acc &= (wordPattern[i] == '_');
      else if (pattern[i] == guess)
          acc &= (wordPattern[i] == guess);
      else
        acc &= (wordPattern[i] == '_');
    }

    if (acc)
      newWords.insert(word);
  }

  // We shouldn't "usually" fall into this case, but empty wordlists
  // must have empty patterns.
  if (newWords.size() == 0)
    pattern = "";

  return WordSet(pattern, newWords);
}

std::vector<WordSet> WordSet::partition(char guess) const {
  if (!(guess >= 'a' && guess <= 'z'))
    throw std::invalid_argument("guess must be a lower-case letter");

  std::vector<WordSet> sets;
  // TODO(you): fill in the rest of the code

  return sets;
}


std::ostream& operator<<(std::ostream & os, WordSet const & ws) {
  os << "\"" << ws.pattern() << "\", ";
  os << "{";
  if (ws.size() > 0) {
    std::transform(ws.words().cbegin(), --ws.words().cend(),
                   std::ostream_iterator<std::string>(os, ", "),
                   make_quoted);
    os << "\"" << *ws.words().crbegin() << "\"";
  }
  os << "}";
  return os;
}

std::string WordSet::choose_random_word() const {
  // Degenerate case defined to return the empty string.
  if (words_.size() == 0)
    return "";

  // Minus one because distribution generates something in the range
  // [a,b], NOT the range [a,b).
  Distribution distribution(0, words_.size() - 1);
  StrSet::const_iterator chosen_word = words_.cbegin();
  std::advance(chosen_word, distribution(generator));
  return *chosen_word;
}
}  // namespace evil_hangman
