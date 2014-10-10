// token.h --- Simple class for the Token type used to represent
// tokens produced as a Tokenizer consumes an input stream,
// specifically for the Racka-Bracka-Stack project.

// token.h is Copyright (C) 2014 by the University of British
// Columbia, Some Rights Reserved.
//
// This work is licensed under the Creative Commons Attribution 4.0
// International License. To view a copy of this license, visit
// http://creativecommons.org/licenses/by/4.0/.

#ifndef RACKET_BRACKET_STACK_TOKEN_H_
#define RACKET_BRACKET_STACK_TOKEN_H_

#include <string>
#include <ostream>

namespace tokenizer {
class Tokenizer;

// These tokens are not "clever" at all; rely on the associated
// tokenizer to work with them.
//
// Note that EVERY token type must reserve the token_type 0 for the
// EOF token representing the end of an input stream.
//
// Note that two Tokens can be equal even if they come from different
// file, line number, and column numbers.  Lines and columns are
// 1-based, not 0-based.
class Token {
 public:
  // Constructs a token with the given components that defaults to no
  // designated source and an empty filename.
  Token(int token_type,
        std::string const & token_data,
        int start_line, int end_line,
        int start_column, int end_column) :
      Token(token_type, token_data, nullptr,
            start_line, end_line,
            start_column, end_column) { }

  // Constructs a token with the given components that defaults to an
  // empty filename.
  Token(int token_type,
        std::string const & token_data,
        Tokenizer const * const source_tokenizer,
        int start_line, int end_line,
        int start_column, int end_column) :
      Token(token_type, token_data, source_tokenizer,
            "", start_line, end_line,
            start_column, end_column) { }

  // Constructs a token with the given components that defaults to no
  // designated source.
  Token(int token_type,
        std::string const & token_data,
        std::string const & filename,
        int start_line, int end_line,
        int start_column, int end_column) :
      Token(token_type, token_data, nullptr,
            filename, start_line, end_line,
            start_column, end_column) { }

  // Constructs a token with the given components.
  Token(int token_type,
        std::string const & token_data,
        Tokenizer const * const source_tokenizer,
        std::string const & filename,
        int start_line, int end_line,
        int start_column, int end_column) :
      token_type_(token_type),
      token_data_(token_data),
      source_tokenizer_(source_tokenizer),
      filename_(filename),
      start_line_(start_line),
      end_line_(end_line),
      start_column_(start_column),
      end_column_(end_column) { }

  int type() const {
    return token_type_;
  }

  std::string const & data() const {
    return token_data_;
  }

  Tokenizer const * const source_tokenizer() const {
    return source_tokenizer_;
  }

  std::string const & filename() const {
    return filename_;
  }

  int start_line() const {
    return start_line_;
  }

  int end_line() const {
    return end_line_;
  }

  int start_column() const {
    return start_column_;
  }

  int end_column() const {
    return end_column_;
  }

  bool is_eof() const {
    return token_type_ == kEofToken;
  }

  // 0 is always the type of an EOF (end of file) token.
  static int const kEofToken = 0;

 private:
  // Typically, an enum managed by the tokenizer that produced this
  // token.
  int const token_type_;

  // Data associated with this token, e.g., the text of a CDATA in
  // an XML document, the string representation of an opening
  // bracket in a Racket document, etc.
  std::string const token_data_;


  // The tokenizer that produced this token so that tokenizer can
  // (if they choose) refuse to handle tokens produced by other
  // tokenizers. If this is set to nullptr, then the Token records
  // no source tokenizer.
  //
  // Two tokens compare equal if they have the same type, data, and
  // source tokenizer.  (So, for the last: are from the same
  // tokenizer or were created without a tokenizer stipulated.)
  Tokenizer const * const source_tokenizer_;

  // The file and line and column range from which the token is
  // drawn.  (Note: it's conceivable as tokenizers work that a token
  // could actually come from multiple files.  We define correct
  // behaviour in that case as recording the initial file only.)
  std::string const filename_;
  int const start_line_, end_line_;
  int const start_column_, end_column_;
};


// Two Tokens are equal if they have the same type and data and
// either come from the same tokenizer source or neither have a
// source recorded.
//
// Note that two Tokens can be equal even if they come from different
// file, line number, and column numbers.  Lines and columns are
// 1-based, not 0-based.
inline bool operator==(Token const &lhs, Token const &rhs) {
  return lhs.type() == rhs.type() &&
      lhs.data() == rhs.data() &&
      lhs.source_tokenizer() == rhs.source_tokenizer();
}
inline bool operator!=(Token const &lhs, Token const &rhs) {
  return !(lhs == rhs);
}
inline std::ostream& operator<<(std::ostream &os, Token const &token) {
  os << "[output for testing only: "
     << "token of type " << token.type()
     << " with data " << token.data()
     << " from " << token.source_tokenizer()
     << " at " << token.filename()
     << ":" << token.start_line()
     << ":" << token.start_column()
     << " to " << token.end_line()
     << ":" << token.end_column()
     << "]";
  return os;
}
}  // namespace tokenizer

#endif  // RACKET_BRACKET_STACK_TOKEN_H_
