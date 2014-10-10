// tokenizer.h --- Abstract base class for a tokenizer, which consumes
// an input stream to produce a series of tokens, targeted at matching
// "brackets" in different languages.  Part of the RackaBrackaStack
// project.

// This file is Copyright (C) 2014 by the University of British
// Columbia, Some Rights Reserved.
//
// This work is licensed under the Creative Commons Attribution 4.0
// International License. To view a copy of this license, visit
// http://creativecommons.org/licenses/by/4.0/.

#ifndef RACKET_BRACKET_STACK_TOKENIZER_H_
#define RACKET_BRACKET_STACK_TOKENIZER_H_

#include <string>

#include "./token.h"

namespace tokenizer {

// A concrete Tokenizer implementation needs to "feed" from some
// stream of input.  Typically, they'll accept an input stream in the
// constructor, but that's left to the specific implementation.
class Tokenizer {
 public:
  // Consume just enough input to produce the next token and return
  // that token.  Note: ALL tokenizers must be capable of producing
  // the EOF token (the token with a type of 0).
  virtual Token next_token() = 0;

  // Checks whether the two tokens are a matching pair, i.e., an
  // opening token and a closing token that closes it.
  virtual bool are_matching
  (Token const & opener, Token const & closer) const = 0;

  // Checks whether this is an open token (one that opens a matching
  // pair).  Note that a return value of true does not preclude this
  // from being a CLOSING token as well (e.g., in many languages "
  // is both an opening and a closing token).
  virtual bool is_opening(Token const & token) const = 0;

  // Checks whether this is a closing token (one that closes a
  // matching pair).  Note that a return value of true does not
  // preclude this from being an OPENING token as well (e.g., in
  // many languages " is both an opening and a closing token).
  virtual bool is_closing(Token const & token) const = 0;

  // Checks whether the token is an EOF token.
  //
  // ALL Token types must reserve Token::kEofToken (0) as a token
  // representing the end of an input stream.
  bool is_eof(Token const & token) const {
    return token.is_eof();
  }
};
}  // namespace tokenizer

#endif  // RACKET_BRACKET_STACK_TOKENIZER_H_
