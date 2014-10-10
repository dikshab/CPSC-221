// racka_bracka.cc --- The driver file for a command-line Racket
// Bracket Checker. Complete this file; look for TODO items! Remember
// to precisely match what we did in our .out.txt files (so, no output
// if everything is fine and a particular format on an error).

// This is Copyright (C) 2014 by the University of British Columbia,
// Some Rights Reserved.
//
// This work is licensed under the Creative Commons Attribution 4.0
// International License. To view a copy of this license, visit
// http://creativecommons.org/licenses/by/4.0/.

#include <string>
#include <fstream>
#include <iostream>     // std::cout

#include "./racket_tokenizer.h"
#include "./balance_checker.h"
#include "./token.h"
#include "./tokenizer.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
    std::cerr << "\tReads in Racket program <filename> "
              << "and reports any unbalanced brackets." << std::endl;
    std::cerr << "\tPlease provide exactly one filename as an argument!"
              << std::endl;
    return -1;
  }

  // Open the file passed as an argument.
  std::string file_name = argv[1];
  std::ifstream file_stream;
  file_stream.open(file_name, std::ifstream::in);

  // Build a tokenizer over the file and a balance checker over the
  // tokenizer.
  tokenizer::RacketTokenizer tokenizer(file_stream, file_name);
  tokenizer::BalanceChecker bchecker(&tokenizer);

  // TODO(you): use the balance checker to determine if anything needs to
  // be printed and, if so, to print out the problem.

  const tokenizer::Token token = bchecker.check_balance();
  if (!token.is_eof()) {
    std::cout << token.filename() << ":"
        << token.end_line() << ":" << token.start_column() << ":  "
        << "\'" << token.data() << "\' is causing an imbalance" << std::endl;
  }

  return 0;
}
