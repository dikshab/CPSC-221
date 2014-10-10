// racket_tokenizer.cc --- Defines the Racket Tokenizer class,
// including a state machine to turn input character sequences into
// tokens.

// racket_tokenizer.cc is Copyright (C) 2014 by the University of
// British Columbia, Some Rights Reserved.
//
// This work is licensed under the Creative Commons Attribution 4.0
// International License. To view a copy of this license, visit
// http://creativecommons.org/licenses/by/4.0/.


#include "./racket_tokenizer.h"

#include <istream>

namespace tokenizer {
typedef RacketTokenizer RT;

// Repeatedly consume a character and peek at another in order to
// update the state until the next token is ready to be produced.
Token RT::next_token() {
  int next_line, next_column;
  TokenizerState next_state;
  bool emit_token;
  TokenType token_type;
  char consumed_char, peek_char;
  bool is_eof;
  bool move_cr_special_case = false;

  do {
    // Setting a default value so this will be initialized in the
    // kInit/kAtEof states.  In those states, the consumed character
    // doesn't matter, since we do not consume characters before
    // starting or after hitting EOF.
    consumed_char = '\0';
    if (state_ == kInit) {
      next_line = 1;
      next_column = 1;
    } else if (state_ == kAtEof) {
      is_eof = true;
    } else {
      in_.get(consumed_char);
      data_.push_back(consumed_char);

      calculate_next_position(consumed_char, line_, column_,
                              &next_line, &next_column);
      line_ = next_line;
      column_ = next_column;
    }
    peek_char = in_.peek();
    is_eof = in_.eof();

    calculate_next_state(consumed_char, peek_char, is_eof,
                         &next_state, &emit_token, &token_type);

    // Keep track of the special case.
    move_cr_special_case =
        state_ == kAtCommentCR &&
        next_state == kAtWhitespace;

    state_ = next_state;
  } while (!emit_token);

  // Handle the \r on a comment special case by stripping it from
  // this token's data (and its column count).
  if (move_cr_special_case) {
    assert(data_.size() > 0 && data_.back() == '\r');
    data_.pop_back();
    column_--;
  }

  // Produce the token to emit.
  Token token(token_type, data_, filename_,
              start_line_, line_,
              start_column_, column_);

  // Prepare for the next token.
  data_ = "";
  start_line_ = line_;
  start_column_ = column_;

  // Handle the special case by adding the \r to this token's data
  // and patching the column count.
  if (move_cr_special_case) {
    data_.push_back('\r');
    column_++;
  }

  return token;
}

void RT::calculate_next_position(char c, int line_in, int column_in,
                                 int *line_out, int *column_out) {
  switch (c) {
    case '\n':
      (*line_out) = line_in + 1;
      (*column_out) = 1;
      break;
    default:
      (*line_out) = line_in;
      (*column_out) = column_in + 1;
      break;
  }
}

RT::TokenType RT::characteristic_type(char c, bool is_eof) {
  if (is_eof) {
    return kEof;
  }

  switch (c) {
    case '(':
      return kOpenParen;
    case '[':
      return kOpenBracket;
    case '{':
      return kOpenBrace;
    case ')':
      return kCloseParen;
    case ']':
      return kCloseBracket;
    case '}':
      return kCloseBrace;
    case '"':
      return kQuotationMark;
    case ' ':
    case '\t':
    case '\n':
    case '\r':
      return kWhitespace;
    case ';':
      return kComment;
    default:
      return kToken;
  }
}

RT::TokenizerState
RT::characteristic_next_state(TokenType characteristic_token) {
  switch (characteristic_token) {
    case kOpenParen:
    case kOpenBracket:
    case kOpenBrace:
    case kCloseParen:
    case kCloseBracket:
    case kCloseBrace:
      return kAtBraces;
    case kQuotationMark:
      return kAtStartQuote;
    case kWhitespace:
      return kAtWhitespace;
    case kComment:
      return kAtComment;
    case kToken:
      return kAtToken;
    case kEof:
      return kAtEof;
    case kStringData:
      // Not really a meaningful case, since string data has no
      // characteristic state it goes to.
      return kAtStringData;
    default:
      // Should be no other possibility.
      assert(false);
      return kAtEof;
  }
}

// This implements a DFA's transition function (think: CPSC 121).  We
// drew the DFA but did not include in the distribution.. sorry!
void RT::calculate_next_state(char consumed_char, char peek_char,
                              bool peek_is_eof,
                              RT::TokenizerState *next_state,
                              bool *emit_token,
                              RT::TokenType *token_type) {
  TokenType peek_characteristic_token =
      characteristic_type(peek_char, peek_is_eof);
  TokenType consume_characteristic_token =
      characteristic_type(consumed_char, false);

  (*next_state) = characteristic_next_state(peek_characteristic_token);
  (*emit_token) = true;
  (*token_type) = consume_characteristic_token;

  switch (state_) {
    case kInit:
      // No tokens emitted from this state.
      (*emit_token) = false;
      break;
    case kAtBraces:
      // Defaults all correct.
      break;
    case kAtStartQuote:
      if (peek_is_eof) {
        (*next_state) = kAtEof;
      } else {
        switch (peek_char) {
          case '"':
            (*next_state) = kAtEndQuote;
            break;
          case '\\':
            (*next_state) = kAtEscapedStringData;
            break;
          default:
            (*next_state) = kAtStringData;
            break;
        }
      }
      break;
    case kAtStringData:
      (*token_type) = kStringData;
      if (peek_is_eof) {
        (*next_state) = kAtEof;
      } else {
        switch (peek_char) {
          case '"':
            (*next_state) = kAtEndQuote;
            break;
          case '\\':
            (*emit_token) = false;
            (*next_state) = kAtEscapedStringData;
            break;
          default:
            (*emit_token) = false;
            (*next_state) = kAtStringData;
        }
      }
      break;
    case kAtEscapedStringData:
      (*token_type) = kStringData;
      if (peek_is_eof) {
        (*next_state) = kAtEof;
      } else {
        (*emit_token) = false;
        (*next_state) = kAtStringData;
      }
      break;
    case kAtEndQuote:
      // Defaults all correct.  COULD be merged with kAtBraces, but
      // although that's technically correct, it feels wrong.
      break;
    case kAtWhitespace:
      // Do not emit a token if we're just seeing more whitespace.
      if (peek_characteristic_token == kWhitespace)
        (*emit_token) = false;
      break;
    case kAtComment:
      (*token_type) = kComment;
      if (peek_is_eof) {
        (*next_state) = kAtEof;
      } else {
        switch (peek_char) {
          case '\n':
            (*next_state) = kAtWhitespace;
            break;
          case '\r':
            (*emit_token) = false;
            (*next_state) = kAtCommentCR;
            break;
          default:
            (*emit_token) = false;
            (*next_state) = kAtComment;
            break;
        }
      }
      break;
    case kAtCommentCR:
      (*token_type) = kComment;
      if (peek_is_eof) {
        (*next_state) = kAtEof;
      } else {
        switch (peek_char) {
          case '\n':
            (*next_state) = kAtWhitespace;
            break;
          case '\r':
            (*emit_token) = false;
            (*next_state) = kAtCommentCR;
            break;
          default:
            (*emit_token) = false;
            (*next_state) = kAtComment;
            break;
        }
      }
      break;
    case kAtToken:
      (*token_type) = kToken;
      // Do not emit a token if we're just seeing more whitespace.
      if (peek_characteristic_token == kToken)
        (*emit_token) = false;
      break;
    case kAtEof:
      (*token_type) = kEof;
      break;
    default:
      // No other possibility should exist.
      assert(false);
      break;
  }
}
}  // namespace tokenizer
