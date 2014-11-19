// evil_hangman_utils.h --- Declares utilities for use in the Evil
// Hangman program.

// evil_hangman_utils.h is Copyright (C) 2014 by the University of
// British Columbia, Some Rights Reserved.
//
// This work is licensed under the Creative Commons Attribution 4.0
// International License. To view a copy of this license, visit
// http://creativecommons.org/licenses/by/4.0/.

#ifndef DYNAMIC_HANGMAN_EVIL_HANGMAN_UTILS_H_
#define DYNAMIC_HANGMAN_EVIL_HANGMAN_UTILS_H_

#include <map>
#include <set>
#include <string>
#include <vector>
#include <istream>
#include <ostream>

namespace evil_hangman {
typedef std::map<int /* length */,
                 std::set<std::string> /* words */> WordToLengthMap;

typedef std::vector<std::string> WordList;

// Splits the words into separate sets keyed by length, excluding the
// empty string. (So, there will never be a length key less than 1.)
//
// Note: performs no checks for leading/trailing whitespace or any
// other odd formatting.
//
// Example:
// ASSERT_EQ(get_words_by_length({"hello", "goodbye", "cards", "", " a-bC"}),
//           {{5, {"cards", " a-bC", "goodbye"}}, {7, {"goodbye"}}})
WordToLengthMap get_words_by_length(std::set<std::string> const & words);

// Fetch a list of words from the given input stream.  Words are
// defined by the behavior of the extraction operator on strings
// (i.e., whitespace delimited character sequences).  Reads until the
// stream is empty.
WordList get_words_from_stream(std::istream *input_stream);

// Normalize a word for the WordSet by lowercasing and removing
// letters outside the range a-z.
std::string normalize_word(std::string const &word);

// Convert the given length to a legal length.  A legal length must
// either be a length of at least one word in the word_to_length_map.
// Legal lengths are unchanged.  Otherwise, anything smaller than the
// largest legal length will be converted to the next larger legal
// length, and anything else will be converted to the largest legal
// length.
//
// precondition: word_to_length_map is well-formed in the sense that
// all words at key i are of length i, every key i is greater than
// zero and has at least one word associated with it, and the map has
// at least one non-empty word in it.
int convert_to_legal_length(int length,
                            WordToLengthMap const word_to_length_map);

// Get a legal length from the given input stream (i.e., a length that
// has at least one word associated with it in the map).  Communicates
// with the user (if any) on the given output_stream.
//
// precondition: word_to_length_map is well-formed in the sense that
// all words at key i are of length i, every key i is greater than
// zero and has at least one word associated with it, and the map has
// at least one non-empty word in it.
int input_legal_length(std::istream *input_stream,
                       std::ostream *output_stream,
                       WordToLengthMap const word_to_length_map);
}  // namespace evil_hangman

#endif  // DYNAMIC_HANGMAN_EVIL_HANGMAN_UTILS_H_
