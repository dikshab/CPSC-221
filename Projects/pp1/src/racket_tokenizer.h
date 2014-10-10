// racket_tokenizer.h --- Concrete (leaf, i.e., not to be subclassed)
// class for a tokenizer for Racket programs that tokenizes braces in
// that program.  Part of the RackaBrackaStack project.

// racket_tokenizer.h is Copyright (C) 2014 by the University of
// British Columbia, Some Rights Reserved.
//
// This work is licensed under the Creative Commons Attribution 4.0
// International License. To view a copy of this license, visit
// http://creativecommons.org/licenses/by/4.0/.

#ifndef RACKET_BRACKET_STACK_RACKET_TOKENIZER_H_
#define RACKET_BRACKET_STACK_RACKET_TOKENIZER_H_

#include <string>
#include <istream>

#include <cassert>

#include "./token.h"
#include "./tokenizer.h"

namespace tokenizer {
// Note: we handle only a subset of Racket's allowable lexical
// structure.  In particular, we handle the following delimiters: (,
// ), {, }, [, ], ", ;, and whitespace (space, tab, or newline (\n or
// \r)).  Within strings, we handle \ followed by anything as a NORMAL
// component of the string (including \"), ensuring that an escaped
// backslash (\\) is one component of the string so that, e.g., "\\"
// is a single string.  Otherwise, we make NO attempt to properly
// tokenize, meaning that something like `,`'hello can be a single
// token.
//
// Note: per the R5RS spec, it looks like the linebreak at the end
// of a comment is NOT part of that comment; so, we'll proceed under
// that assumption. However, because a \r may be part of a newline
// as \r\n, we MUST read ahead through the \r before knowing whether
// it belongs as part of the comment or of the newline (e.g.,
// ";hello\rgoodbye\n" vs. ";hello\r\ngoodbye\n"; the former will
// have a \r within the comment data while the latter will have it
// within the whitespace data).
//
// Note: two quotation marks with nothing in between will produce
// only two tokens (two kQuotationMark tokens), not two quotation
// mark tokens with an empty string data token in between.
//
// Note: We do no clever handling of tabs; they are just a single
// character.  However, it might be interesting to instead be
// configurable to have tabs be single characters or to have a fixed
// tabbing width and have them proceed to the next tab stop (or even
// to take in a fixed list of tab stops).
class RacketTokenizer : public Tokenizer {
 public:
  enum TokenType {
    kEof = 0,       // EOF type == 0 is required by the Token type.
    kOpenParen,
    kCloseParen,
    kOpenBracket,
    kCloseBracket,
    kOpenBrace,
    kCloseBrace,
    kQuotationMark,
    kStringData,
    kWhitespace,
    kComment,
    kToken          // A "normal" token or Racket identifier.
  };

  // Constructs a tokenizer that will report itself as reading a
  // file with no name (empty string).
  explicit RacketTokenizer(std::istream &in) : RacketTokenizer(in, "") { }

  // Constructs a tokenizer that will report itself as reading the
  // given file.
  explicit RacketTokenizer(std::istream &in, std::string const &filename)
      : in_(in), filename_(filename) { }

  // Consume just enough input to produce the next token and return
  // that token.  Note: ALL tokenizers must be capable of producing
  // the EOF token (the token with a type of 0).
  //
  // Warning: a file that ends on an escape character in the midst
  // of a string WILL include that escape character in the string
  // data token it produces.  So, a file that has only the text in
  // single quotes here '"hello\' will produce a quotation mark
  // token at (1,1), a string data token hello\ at (1,2) through
  // (1,7), and an EOF token at (1,8).  It will NOT cause an error
  // on the call to next_token.
  //
  // Note: We DO allow endlines in strings, just like any other
  // character.
  //
  // Note: RacketTokenizers do NOT add a source tokenizer to their
  // tokens; so all Tokens have the nullptr as their source.
  virtual Token next_token();

  // Checks whether the two tokens are a matching pair, i.e., an
  // opening token and a closing token that closes it.
  virtual bool are_matching(Token const & opener, Token const & closer) const {
    return (opener.type() == kOpenParen && closer.type() == kCloseParen) ||
        (opener.type() == kOpenBracket && closer.type() == kCloseBracket) ||
        (opener.type() == kOpenBrace && closer.type() == kCloseBrace) ||
        (opener.type() == kQuotationMark && closer.type() == kQuotationMark);
  }

  // Checks whether this is an open token (one that opens a matching
  // pair).  In this tokenizer, only " can be both an opening and a
  // closing token, and the token itself doesn't "know" which one it
  // is.  (The tokenizer DOES technically know but does not expose
  // that knowledge; however, it is safe to assume that the next "
  // closes the most recent ".  As it turns out, it is also the case
  // that no other opener/closer can occur before the next ".)
  virtual bool is_opening(Token const & token) const {
    return token.type() == kOpenParen ||
        token.type() == kOpenBracket ||
        token.type() == kOpenBrace ||
        token.type() == kQuotationMark;
  }

  // Checks whether this is a closing token (one that closes a
  // matching pair).  In this tokenizer, a token cannot be both opening and
  // closing.  (An entire string is treated as a single token, and
  // nothing else would be both opener and closer besides ".)
  virtual bool is_closing(Token const & token) const {
    return token.type() == kCloseParen ||
        token.type() == kCloseBracket ||
        token.type() == kCloseBrace ||
        token.type() == kQuotationMark;
  }

 private:
  enum TokenizerState {
    kInit,
    kAtBraces,
    kAtStartQuote,
    kAtStringData,
    kAtEscapedStringData,
    kAtEndQuote,
    kAtWhitespace,
    kAtComment,
    kAtCommentCR,  // In a comment, got a \r character.
    kAtToken,
    kAtEof
  };

  // Find the next position (line/column) in the file based on the
  // given character.
  void calculate_next_position(char c, int line_in, int column_in,
                               int *line_out, int *column_out);

  // Give the "usual" token type associated with this
  // character. What's not usual? String contents, for example,
  // where a "(" and many other things are just more data.
  TokenType characteristic_type(char c, bool is_eof);

  // Give the "usual" token state associated with this type (i.e.,
  // what we'd usually transition to for this type). What's not
  // usual? String contents, for example, where a "(" and many other
  // things are just more data.
  TokenizerState characteristic_next_state(TokenType characteristic_token);

  // Determines how to transition to the next state given the
  // character we are currently consuming (the one that led to the
  // last transition), the character we're peeking at (the one that
  // is about to be consumed, if we need more characters to
  // construct a token), and a flag to indicate whether that
  // peeked-at character is actually the end-of-file.
  //
  // The transition indicates what the next state should be, whether
  // or not to emit a token (before consuming the peeked-at
  // character), what the token type should be (if so), and a corner
  // case check to see whether we need to move the consumed
  // character off of the data for the current token to emit and
  // onto the data for the next token.
  //
  // WARNING: this does not handle the special case where it's hard
  // to tell whether a \r belongs with a preceding comment or a
  // succeeding \n.  That can be handled elsewhere by checking if
  // the current state is kAtCommentCR and the next state is
  // kWhitespace.  If so, the "\r" must be moved.
  void calculate_next_state(char consumed_char, char peek_char,
                            bool peek_is_eof,
                            TokenizerState *next_state,
                            bool *emit_token,
                            TokenType *token_type);

  std::istream & in_;
  std::string filename_;
  TokenizerState state_ = kInit;
  std::string data_ = "";
  int start_line_ = 1;
  int start_column_ = 1;
  int line_ = 1;
  int column_ = 1;
};
}  // namespace tokenizer

#endif  // RACKET_BRACKET_STACK_RACKET_TOKENIZER_H_
