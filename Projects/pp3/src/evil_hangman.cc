// evil_hangman.cc --- The driver file for a command-line 'hangman'
// game that evilly late-binds its choice of hidden word.


// evil_hangman.cc is Copyright (C) 2014 by the University of British
// Columbia, Some Rights Reserved.
//
// This work is licensed under the Creative Commons Attribution 4.0
// International License. To view a copy of this license, visit
// http://creativecommons.org/licenses/by/4.0/.

#include <cassert>

#include <string>
#include <iostream>
#include <fstream>
#include <iterator>

#include "./word_set.h"
#include "./evil_hangman_utils.h"

namespace eh = evil_hangman;

int main(int argc, char *argv[]) {
  // Check for the preconfigured dictionary filename.
#ifdef DICTIONARY_FILENAME
  // If present, use it.  Some careful maneuvering is required to make
  // it a string constant.
  std::string filename{DICTIONARY_FILENAME};
#else
  // If not present, just complain, for now.
  #error No value for the preprocessor constant DICTIONARY_FILENAME supplied.
#endif

  // Load the dictionary, separating words by length.

  // Load the words from the file.
  std::ifstream dictionary_input_stream(filename);
  eh::WordList words = eh::get_words_from_stream(&dictionary_input_stream);
  std::transform(words.begin(), words.end(),
                 words.begin(), eh::normalize_word);
  dictionary_input_stream.close();

  // Convert the list to a set.
  std::set<std::string> words_as_set(words.cbegin(), words.cend());

  eh::WordToLengthMap words_by_length = eh::get_words_by_length(words_as_set);
  if (words_by_length.size() == 0) {
    std::cerr << "Error: no words were present in the dictionary at: "
              << filename << std::endl;
    return 1;
  }


  // Find out how many letters long the word should be.  Let the user
  // know their options, and ensure a legal option is chosen.  (Just
  // correct illegal options by picking the closest value; shortest if
  // <= 0, largest if >= max, next larger otherwise if numeric,
  // shortest if non-numeric.)
  int length = eh::input_legal_length(&std::cin, &std::cout, words_by_length);


  int const kNumWrongGuesses = 15;
  int num_wrong_guesses = 0;
  std::set<char> unguessed_letters;
  for (char c = 'a'; c <= 'z'; c++)
    unguessed_letters.insert(c);

  // Generate a wordset with an empty pattern of the appropriate
  // length and all the words of the appropriate length.
  std::string init_pattern(length, '_');
  eh::WordSet word_set(init_pattern, words_by_length[length]);

  char guess;

  // While the user has guesses left and hasn't guessed the word:
  while (num_wrong_guesses < kNumWrongGuesses &&
         word_set.pattern().find('_') != std::string::npos) {
    // 1. print out the status/pattern so far
    std::cout << "So far, you've got: "
              << word_set.pattern()
              << std::endl
              << "You have " << kNumWrongGuesses - num_wrong_guesses
              << " guesses left."
              << std::endl
              << std::endl;

    // 2. print out the remaining letters to guess
    std::cout << "Letters remaining to guess: ";
    std::ostream_iterator<char> out_it(std::cout, " ");
    std::copy(unguessed_letters.begin(), unguessed_letters.end(), out_it);
    std::cout << std::endl << std::endl;

    // 3. ask the user for a guess
    std::cout << "What (lowercase) letter would you like to guess? ";
    std::cin >> guess;
    if (guess < 'a' || guess > 'z') {
      std::cout << "Ooh.. I'm sorry, " << guess
                << " is not a lowercase letter, and.." << std::endl
                << "I'm evil. So, that counts against you."
                << std::endl << std::endl;
      num_wrong_guesses++;
      continue;
    } else if (unguessed_letters.find(guess) == unguessed_letters.end()) {
      std::cout << "Actually you already guessed that, and since I'm evil.."
                << std::endl << "I'll count it against you."
                << std::endl << std::endl;
      num_wrong_guesses++;
      continue;
    } else {
      unguessed_letters.erase(guess);
    }

    word_set = word_set.generate_new_wordset(guess);

    // TODO(you): use WordSet::partition to produce the list of
    // distinct WordSets induced by the guess and choose the WordSet
    // that is longest.
    //
    // Note: for the bonus, you might choose some OTHER strategy for
    // selecting the WordSet.  (The longest isn't always the best, in
    // our experience!  A REALLY good algorithm might perform a
    // "minimax" search over the "moves" available to the player
    // (guesses from a-z) and the "moves" available to the computer
    // (partition options).)


    // 5. indicate whether guess was in the word (if not, increment guesses)
    if (word_set.pattern().find(guess) == std::string::npos) {
      std::cout << "The letter '" << guess << "' was not in the word."
                << std::endl;
      num_wrong_guesses++;
    } else {
      std::cout << "Congratulations! The letter '" << guess
                << "' was in the word!" << std::endl;
    }
  }

  // indicate who won
  if (num_wrong_guesses == kNumWrongGuesses) {
    // Choose the "real word" at random, and inform the disappointed
    // user.
    std::cout << "Looks like I won. Huh.. what a surprise." << std::endl
              << "Better luck next time. My word was: "
              << word_set.choose_random_word() << std::endl;
  } else {
    std::cout << "My word was: " << *word_set.words().begin() << std::endl
              << "You beat me?!  Try that again!" << std::endl;
  }

  return 0;
}
