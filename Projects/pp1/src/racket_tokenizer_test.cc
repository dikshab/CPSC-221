// racket_tokenizer_test.cc --- Test code for the RacketTokenizer
// class

// racket_tokenizer_test is Copyright (C) 2014 by CPSC 221 at the
// University of British Columbia, Some Rights Reserved.
//
// This work is licensed under the Creative Commons Attribution 4.0
// International License. To view a copy of this license, visit
// http://creativecommons.org/licenses/by/4.0/.

// Basing testing on:
// http://johnlamp.net/cmake-tutorial-4-libraries-and-subdirectories.html
// along with MANY other references.

#include <gmock/gmock.h>
using ::testing::Eq;
using ::testing::NotNull;
#include <gtest/gtest.h>
using ::testing::Test;

#include <sstream>

#include "./racket_tokenizer.h"

namespace tokenizer {
class RacketTokenizerTest : public Test {
 protected:
  RacketTokenizerTest() { }

  virtual ~RacketTokenizerTest() { }

  // Check that the next token matches the given one.
  void check_token(Tokenizer *tokenizer, Token const &match_token) {
    Token token = tokenizer->next_token();
    EXPECT_THAT(token, Eq(match_token));
    EXPECT_THAT(token.filename(), Eq(match_token.filename()));
    EXPECT_THAT(token.start_line(), Eq(match_token.start_line()));
    EXPECT_THAT(token.start_column(), Eq(match_token.start_column()));
    EXPECT_THAT(token.end_line(), Eq(match_token.end_line()));
    EXPECT_THAT(token.end_column(), Eq(match_token.end_column()));
  }

  std::stringstream stream_empty_{""},
    stream_open_paren_{"("},
    stream_open_bracket_{"["},
    stream_open_brace_{"{"},
    stream_close_paren_{")"},
    stream_close_bracket_{"]"},
    stream_close_brace_{"}"},

    stream_comment_eof_{";"},
    stream_comment_eol_{";\n"},
    stream_comment_with_content_{";hello\n"},

    stream_space_{" "},
    stream_tab_{"\t"},
    stream_endline_{"\n"},    // whitespace and a line advance
    stream_cr_{"\r"},         // whitespace but no line advance
    stream_crlf_{"\r\n"},     // whitespace and a line advance
    stream_lfcr_{"\n\r"},     // whitespace and a line & column advance
    stream_big_blob_of_whitespace_{"  \t\n  \n\t  \t\r\n bye"},

    stream_quotation_mark_{"\""},
    stream_empty_string_{"\"\""},
    stream_normal_string_{"\"hello\""},
    stream_string_with_normal_escape_{"\"he\\llo\""},
    stream_string_with_escaped_quote_{"\"he\\\"llo\""},
    stream_string_with_escaped_backslash_{"\"he\\\\llo\""},
    // This should yield he\ in one string and then llo in another:
    stream_string_with_escaped_backslash_unescaped_quote_{"\"he\\\\\"llo\""},
    stream_string_hides_other_delimiters_{"\"([{}]) \t\r\n;\""},
    stream_string_hides_escaped_delimiters_{
      "\"\\\"\\(\\[\\{\\}\\]\\)\\ \\\t\\\r\\\n\\;\""
          },
    stream_string_cut_off_at_escape_{"\"hello\\"},

    stream_open_paren_ends_token_{"hello("},
    stream_open_bracket_ends_token_{"hello["},
    stream_open_brace_ends_token_{"hello{"},
    stream_close_paren_ends_token_{"hello)"},
    stream_close_bracket_ends_token_{"hello]"},
    stream_close_brace_ends_token_{"hello}"},
    stream_string_ends_token_{"hello\""},
    stream_comment_ends_token_{"hello;"},
    stream_space_ends_token_{"hello "},
    stream_tab_ends_token_{"hello\t"},
    stream_endline_ends_token_{"hello\n"},
    stream_cr_ends_token_{"hello\r"},

    stream_open_paren_then_token_{"(hello"},
    stream_open_bracket_then_token_{"[hello"},
    stream_open_brace_then_token_{"{hello"},
    stream_close_paren_then_token_{")hello"},
    stream_close_bracket_then_token_{"]hello"},
    stream_close_brace_then_token_{"}hello"},
    stream_string_then_token_{"\"\"hello"},
    stream_comment_then_token_{";hello\nhello"},
    stream_space_then_token_{" hello"},
    stream_tab_then_token_{"\thello"},
    stream_endline_then_token_{"\nhello"},
    stream_cr_then_token_{"\rhello"},

    stream_comment_cr_more_comment_{";\r \n"},
    stream_comment_cr_endline_{";\r\n"},

    stream_rich_example_{
      "(+ (fun [1 2 3]) \n({hello\"goodbye\"]](({[  \t5\nis a ;; cmt\n the end)"
          };
};
TEST_F(RacketTokenizerTest, EmptyFile) {
  RacketTokenizer tokenizer_empty_(stream_empty_);
  check_token(&tokenizer_empty_,
              Token(RacketTokenizer::kEof, "", 1, 1, 1, 1));
}
TEST_F(RacketTokenizerTest, BracketVariants) {
  RacketTokenizer tokenizer_open_paren_(stream_open_paren_);
  check_token(&tokenizer_open_paren_,
              Token(RacketTokenizer::kOpenParen, "(", 1, 1, 1, 2));
  check_token(&tokenizer_open_paren_,
              Token(RacketTokenizer::kEof, "", 1, 1, 2, 2));

  RacketTokenizer tokenizer_open_bracket_(stream_open_bracket_);
  check_token(&tokenizer_open_bracket_,
              Token(RacketTokenizer::kOpenBracket, "[", 1, 1, 1, 2));
  check_token(&tokenizer_open_bracket_,
              Token(RacketTokenizer::kEof, "", 1, 1, 2, 2));

  RacketTokenizer tokenizer_open_brace_(stream_open_brace_);
  check_token(&tokenizer_open_brace_,
              Token(RacketTokenizer::kOpenBrace, "{", 1, 1, 1, 2));
  check_token(&tokenizer_open_brace_,
              Token(RacketTokenizer::kEof, "", 1, 1, 2, 2));

  RacketTokenizer tokenizer_close_paren_(stream_close_paren_);
  check_token(&tokenizer_close_paren_,
              Token(RacketTokenizer::kCloseParen, ")", 1, 1, 1, 2));
  check_token(&tokenizer_close_paren_,
              Token(RacketTokenizer::kEof, "", 1, 1, 2, 2));

  RacketTokenizer tokenizer_close_bracket_(stream_close_bracket_);
  check_token(&tokenizer_close_bracket_,
              Token(RacketTokenizer::kCloseBracket, "]", 1, 1, 1, 2));
  check_token(&tokenizer_close_bracket_,
              Token(RacketTokenizer::kEof, "", 1, 1, 2, 2));

  RacketTokenizer tokenizer_close_brace_(stream_close_brace_);
  check_token(&tokenizer_close_brace_,
              Token(RacketTokenizer::kCloseBrace, "}", 1, 1, 1, 2));
  check_token(&tokenizer_close_brace_,
              Token(RacketTokenizer::kEof, "", 1, 1, 2, 2));
}
TEST_F(RacketTokenizerTest, SimpleComments) {
  RacketTokenizer tokenizer_comment_eof_(stream_comment_eof_);
  check_token(&tokenizer_comment_eof_,
              Token(RacketTokenizer::kComment, ";", 1, 1, 1, 2));
  check_token(&tokenizer_comment_eof_,
              Token(RacketTokenizer::kEof, "", 1, 1, 2, 2));

  RacketTokenizer tokenizer_comment_eol_(stream_comment_eol_);
  check_token(&tokenizer_comment_eol_,
              Token(RacketTokenizer::kComment, ";", 1, 1, 1, 2));
  check_token(&tokenizer_comment_eol_,
              Token(RacketTokenizer::kWhitespace, "\n", 1, 2, 2, 1));
  check_token(&tokenizer_comment_eol_,
              Token(RacketTokenizer::kEof, "", 2, 2, 1, 1));

  RacketTokenizer tokenizer_comment_with_content_(stream_comment_with_content_);
  check_token(&tokenizer_comment_with_content_,
              Token(RacketTokenizer::kComment, ";hello", 1, 1, 1, 7));
  check_token(&tokenizer_comment_with_content_,
              Token(RacketTokenizer::kWhitespace, "\n", 1, 2, 7, 1));
  check_token(&tokenizer_comment_with_content_,
              Token(RacketTokenizer::kEof, "", 2, 2, 1, 1));
}
TEST_F(RacketTokenizerTest, SimpleWhitespace) {
  RacketTokenizer tokenizer_space_(stream_space_);
  check_token(&tokenizer_space_,
              Token(RacketTokenizer::kWhitespace, " ", 1, 1, 1, 2));
  check_token(&tokenizer_space_,
              Token(RacketTokenizer::kEof, "", 1, 1, 2, 2));

  RacketTokenizer tokenizer_tab_(stream_tab_);
  check_token(&tokenizer_tab_,
              Token(RacketTokenizer::kWhitespace, "\t", 1, 1, 1, 2));
  check_token(&tokenizer_tab_,
              Token(RacketTokenizer::kEof, "", 1, 1, 2, 2));

  RacketTokenizer tokenizer_endline_(stream_endline_);
  check_token(&tokenizer_endline_,
              Token(RacketTokenizer::kWhitespace, "\n", 1, 2, 1, 1));
  check_token(&tokenizer_endline_,
              Token(RacketTokenizer::kEof, "", 2, 2, 1, 1));

  RacketTokenizer tokenizer_cr_(stream_cr_);
  check_token(&tokenizer_cr_,
              Token(RacketTokenizer::kWhitespace, "\r", 1, 1, 1, 2));
  check_token(&tokenizer_cr_,
              Token(RacketTokenizer::kEof, "", 1, 1, 2, 2));

  RacketTokenizer tokenizer_crlf_(stream_crlf_);
  check_token(&tokenizer_crlf_,
              Token(RacketTokenizer::kWhitespace, "\r\n", 1, 2, 1, 1));
  check_token(&tokenizer_crlf_,
              Token(RacketTokenizer::kEof, "", 2, 2, 1, 1));

  RacketTokenizer tokenizer_lfcr_(stream_lfcr_);
  check_token(&tokenizer_lfcr_,
              Token(RacketTokenizer::kWhitespace, "\n\r", 1, 2, 1, 2));
  check_token(&tokenizer_lfcr_,
              Token(RacketTokenizer::kEof, "", 2, 2, 2, 2));

  RacketTokenizer
      tokenizer_big_blob_of_whitespace_(stream_big_blob_of_whitespace_);
  check_token(&tokenizer_big_blob_of_whitespace_,
              Token(RacketTokenizer::kWhitespace, "  \t\n  \n\t  \t\r\n ",
                    1, 4, 1, 2));
  check_token(&tokenizer_big_blob_of_whitespace_,

              Token(RacketTokenizer::kToken, "bye", 4, 4, 2, 5));
  check_token(&tokenizer_big_blob_of_whitespace_,
              Token(RacketTokenizer::kEof, "", 4, 4, 5, 5));
}
TEST_F(RacketTokenizerTest, Strings) {
  RacketTokenizer tokenizer_quotation_mark_(stream_quotation_mark_);
  check_token(&tokenizer_quotation_mark_,
              Token(RacketTokenizer::kQuotationMark, "\"", 1, 1, 1, 2));
  check_token(&tokenizer_quotation_mark_,
              Token(RacketTokenizer::kEof, "", 1, 1, 2, 2));

  RacketTokenizer tokenizer_empty_string_(stream_empty_string_);
  check_token(&tokenizer_empty_string_,
              Token(RacketTokenizer::kQuotationMark, "\"", 1, 1, 1, 2));
  check_token(&tokenizer_empty_string_,
              Token(RacketTokenizer::kQuotationMark, "\"", 1, 1, 2, 3));
  check_token(&tokenizer_empty_string_,
              Token(RacketTokenizer::kEof, "", 1, 1, 3, 3));

  RacketTokenizer tokenizer_normal_string_(stream_normal_string_);
  check_token(&tokenizer_normal_string_,
              Token(RacketTokenizer::kQuotationMark, "\"", 1, 1, 1, 2));
  check_token(&tokenizer_normal_string_,
              Token(RacketTokenizer::kStringData, "hello", 1, 1, 2, 7));
  check_token(&tokenizer_normal_string_,
              Token(RacketTokenizer::kQuotationMark, "\"", 1, 1, 7, 8));
  check_token(&tokenizer_normal_string_,
              Token(RacketTokenizer::kEof, "", 1, 1, 8, 8));

  RacketTokenizer
      tokenizer_string_with_normal_escape_(stream_string_with_normal_escape_);
  check_token(&tokenizer_string_with_normal_escape_,
              Token(RacketTokenizer::kQuotationMark, "\"", 1, 1, 1, 2));
  check_token(&tokenizer_string_with_normal_escape_,
              Token(RacketTokenizer::kStringData, "he\\llo", 1, 1, 2, 8));
  check_token(&tokenizer_string_with_normal_escape_,
              Token(RacketTokenizer::kQuotationMark, "\"", 1, 1, 8, 9));
  check_token(&tokenizer_string_with_normal_escape_,
              Token(RacketTokenizer::kEof, "", 1, 1, 9, 9));

  RacketTokenizer
      tokenizer_string_with_escaped_quote_(stream_string_with_escaped_quote_);
  check_token(&tokenizer_string_with_escaped_quote_,
              Token(RacketTokenizer::kQuotationMark, "\"", 1, 1, 1, 2));
  check_token(&tokenizer_string_with_escaped_quote_,
              Token(RacketTokenizer::kStringData, "he\\\"llo", 1, 1, 2, 9));
  check_token(&tokenizer_string_with_escaped_quote_,
              Token(RacketTokenizer::kQuotationMark, "\"", 1, 1, 9, 10));
  check_token(&tokenizer_string_with_escaped_quote_,
              Token(RacketTokenizer::kEof, "", 1, 1, 10, 10));

  RacketTokenizer tokenizer_string_with_escaped_backslash_
      (stream_string_with_escaped_backslash_);
  check_token(&tokenizer_string_with_escaped_backslash_,
              Token(RacketTokenizer::kQuotationMark, "\"", 1, 1, 1, 2));
  check_token(&tokenizer_string_with_escaped_backslash_,
              Token(RacketTokenizer::kStringData, "he\\\\llo", 1, 1, 2, 9));
  check_token(&tokenizer_string_with_escaped_backslash_,
              Token(RacketTokenizer::kQuotationMark, "\"", 1, 1, 9, 10));
  check_token(&tokenizer_string_with_escaped_backslash_,
              Token(RacketTokenizer::kEof, "", 1, 1, 10, 10));

  RacketTokenizer tokenizer_string_with_escaped_backslash_unescaped_quote_
      (stream_string_with_escaped_backslash_unescaped_quote_);
  check_token(&tokenizer_string_with_escaped_backslash_unescaped_quote_,
              Token(RacketTokenizer::kQuotationMark, "\"", 1, 1, 1, 2));
  check_token(&tokenizer_string_with_escaped_backslash_unescaped_quote_,
              Token(RacketTokenizer::kStringData, "he\\\\", 1, 1, 2, 6));
  check_token(&tokenizer_string_with_escaped_backslash_unescaped_quote_,
              Token(RacketTokenizer::kQuotationMark, "\"", 1, 1, 6, 7));
  check_token(&tokenizer_string_with_escaped_backslash_unescaped_quote_,
              Token(RacketTokenizer::kToken, "llo", 1, 1, 7, 10));
  check_token(&tokenizer_string_with_escaped_backslash_unescaped_quote_,
              Token(RacketTokenizer::kQuotationMark, "\"", 1, 1, 10, 11));
  check_token(&tokenizer_string_with_escaped_backslash_unescaped_quote_,
              Token(RacketTokenizer::kEof, "", 1, 1, 11, 11));

  RacketTokenizer tokenizer_string_hides_other_delimiters_
      (stream_string_hides_other_delimiters_);
  check_token(&tokenizer_string_hides_other_delimiters_,
              Token(RacketTokenizer::kQuotationMark, "\"", 1, 1, 1, 2));
  check_token(&tokenizer_string_hides_other_delimiters_,
              Token(RacketTokenizer::kStringData, "([{}]) \t\r\n;",
                    1, 2, 2, 2));
  check_token(&tokenizer_string_hides_other_delimiters_,
              Token(RacketTokenizer::kQuotationMark, "\"", 2, 2, 2, 3));
  check_token(&tokenizer_string_hides_other_delimiters_,
              Token(RacketTokenizer::kEof, "", 2, 2, 3, 3));

  RacketTokenizer tokenizer_string_hides_escaped_delimiters_
      (stream_string_hides_escaped_delimiters_);
  check_token(&tokenizer_string_hides_escaped_delimiters_,
              Token(RacketTokenizer::kQuotationMark, "\"", 1, 1, 1, 2));
  check_token(&tokenizer_string_hides_escaped_delimiters_,
              Token(RacketTokenizer::kStringData,
                    "\\\"\\(\\[\\{\\}\\]\\)\\ \\\t\\\r\\\n\\;",
                    1, 2, 2, 3));
  check_token(&tokenizer_string_hides_escaped_delimiters_,
              Token(RacketTokenizer::kQuotationMark, "\"", 2, 2, 3, 4));
  check_token(&tokenizer_string_hides_escaped_delimiters_,
              Token(RacketTokenizer::kEof, "", 2, 2, 4, 4));

  RacketTokenizer tokenizer_string_cut_off_at_escape_
      (stream_string_cut_off_at_escape_);
  check_token(&tokenizer_string_cut_off_at_escape_,
              Token(RacketTokenizer::kQuotationMark, "\"", 1, 1, 1, 2));
  check_token(&tokenizer_string_cut_off_at_escape_,
              Token(RacketTokenizer::kStringData, "hello\\", 1, 1, 2, 8));
  check_token(&tokenizer_string_cut_off_at_escape_,
              Token(RacketTokenizer::kEof, "", 1, 1, 8, 8));
}
TEST_F(RacketTokenizerTest, DelimitersEndTokens) {
  RacketTokenizer tokenizer_open_paren_ends_token_
      (stream_open_paren_ends_token_);
  check_token(&tokenizer_open_paren_ends_token_,
              Token(RacketTokenizer::kToken, "hello", 1, 1, 1, 6));
  check_token(&tokenizer_open_paren_ends_token_,
              Token(RacketTokenizer::kOpenParen, "(", 1, 1, 6, 7));
  check_token(&tokenizer_open_paren_ends_token_,
              Token(RacketTokenizer::kEof, "", 1, 1, 7, 7));

  RacketTokenizer tokenizer_open_bracket_ends_token_
      (stream_open_bracket_ends_token_);
  check_token(&tokenizer_open_bracket_ends_token_,
              Token(RacketTokenizer::kToken, "hello", 1, 1, 1, 6));
  check_token(&tokenizer_open_bracket_ends_token_,
              Token(RacketTokenizer::kOpenBracket, "[", 1, 1, 6, 7));
  check_token(&tokenizer_open_bracket_ends_token_,
              Token(RacketTokenizer::kEof, "", 1, 1, 7, 7));

  RacketTokenizer tokenizer_open_brace_ends_token_
      (stream_open_brace_ends_token_);
  check_token(&tokenizer_open_brace_ends_token_,
              Token(RacketTokenizer::kToken, "hello", 1, 1, 1, 6));
  check_token(&tokenizer_open_brace_ends_token_,
              Token(RacketTokenizer::kOpenBrace, "{", 1, 1, 6, 7));
  check_token(&tokenizer_open_brace_ends_token_,
              Token(RacketTokenizer::kEof, "", 1, 1, 7, 7));

  RacketTokenizer tokenizer_close_paren_ends_token_
      (stream_close_paren_ends_token_);
  check_token(&tokenizer_close_paren_ends_token_,
              Token(RacketTokenizer::kToken, "hello", 1, 1, 1, 6));
  check_token(&tokenizer_close_paren_ends_token_,
              Token(RacketTokenizer::kCloseParen, ")", 1, 1, 6, 7));
  check_token(&tokenizer_close_paren_ends_token_,
              Token(RacketTokenizer::kEof, "", 1, 1, 7, 7));

  RacketTokenizer tokenizer_close_bracket_ends_token_
      (stream_close_bracket_ends_token_);
  check_token(&tokenizer_close_bracket_ends_token_,
              Token(RacketTokenizer::kToken, "hello", 1, 1, 1, 6));
  check_token(&tokenizer_close_bracket_ends_token_,
              Token(RacketTokenizer::kCloseBracket, "]", 1, 1, 6, 7));
  check_token(&tokenizer_close_bracket_ends_token_,
              Token(RacketTokenizer::kEof, "", 1, 1, 7, 7));

  RacketTokenizer tokenizer_close_brace_ends_token_
      (stream_close_brace_ends_token_);
  check_token(&tokenizer_close_brace_ends_token_,
              Token(RacketTokenizer::kToken, "hello", 1, 1, 1, 6));
  check_token(&tokenizer_close_brace_ends_token_,
              Token(RacketTokenizer::kCloseBrace, "}", 1, 1, 6, 7));
  check_token(&tokenizer_close_brace_ends_token_,
              Token(RacketTokenizer::kEof, "", 1, 1, 7, 7));

  RacketTokenizer tokenizer_string_ends_token_(stream_string_ends_token_);
  check_token(&tokenizer_string_ends_token_,
              Token(RacketTokenizer::kToken, "hello", 1, 1, 1, 6));
  check_token(&tokenizer_string_ends_token_,
              Token(RacketTokenizer::kQuotationMark, "\"", 1, 1, 6, 7));
  check_token(&tokenizer_string_ends_token_,
              Token(RacketTokenizer::kEof, "", 1, 1, 7, 7));

  RacketTokenizer tokenizer_comment_ends_token_(stream_comment_ends_token_);
  check_token(&tokenizer_comment_ends_token_,
              Token(RacketTokenizer::kToken, "hello", 1, 1, 1, 6));
  check_token(&tokenizer_comment_ends_token_,
              Token(RacketTokenizer::kComment, ";", 1, 1, 6, 7));
  check_token(&tokenizer_comment_ends_token_,
              Token(RacketTokenizer::kEof, "", 1, 1, 7, 7));

  RacketTokenizer tokenizer_space_ends_token_(stream_space_ends_token_);
  check_token(&tokenizer_space_ends_token_,
              Token(RacketTokenizer::kToken, "hello", 1, 1, 1, 6));
  check_token(&tokenizer_space_ends_token_,
              Token(RacketTokenizer::kWhitespace, " ", 1, 1, 6, 7));
  check_token(&tokenizer_space_ends_token_,
              Token(RacketTokenizer::kEof, "", 1, 1, 7, 7));

  RacketTokenizer tokenizer_tab_ends_token_(stream_tab_ends_token_);
  check_token(&tokenizer_tab_ends_token_,
              Token(RacketTokenizer::kToken, "hello", 1, 1, 1, 6));
  check_token(&tokenizer_tab_ends_token_,
              Token(RacketTokenizer::kWhitespace, "\t", 1, 1, 6, 7));
  check_token(&tokenizer_tab_ends_token_,
              Token(RacketTokenizer::kEof, "", 1, 1, 7, 7));

  RacketTokenizer tokenizer_endline_ends_token_(stream_endline_ends_token_);
  check_token(&tokenizer_endline_ends_token_,
              Token(RacketTokenizer::kToken, "hello", 1, 1, 1, 6));
  check_token(&tokenizer_endline_ends_token_,
              Token(RacketTokenizer::kWhitespace, "\n", 1, 2, 6, 1));
  check_token(&tokenizer_endline_ends_token_,
              Token(RacketTokenizer::kEof, "", 2, 2, 1, 1));

  RacketTokenizer tokenizer_cr_ends_token_(stream_cr_ends_token_);
  check_token(&tokenizer_cr_ends_token_,
              Token(RacketTokenizer::kToken, "hello", 1, 1, 1, 6));
  check_token(&tokenizer_cr_ends_token_,
              Token(RacketTokenizer::kWhitespace, "\r", 1, 1, 6, 7));
  check_token(&tokenizer_cr_ends_token_,
              Token(RacketTokenizer::kEof, "", 1, 1, 7, 7));
}
TEST_F(RacketTokenizerTest, DelimiterThenToken) {
  RacketTokenizer tokenizer_open_paren_then_token_
      (stream_open_paren_then_token_);
  check_token(&tokenizer_open_paren_then_token_,
              Token(RacketTokenizer::kOpenParen, "(", 1, 1, 1, 2));
  check_token(&tokenizer_open_paren_then_token_,
              Token(RacketTokenizer::kToken, "hello", 1, 1, 2, 7));
  check_token(&tokenizer_open_paren_then_token_,
              Token(RacketTokenizer::kEof, "", 1, 1, 7, 7));

  RacketTokenizer tokenizer_open_bracket_then_token_
      (stream_open_bracket_then_token_);
  check_token(&tokenizer_open_bracket_then_token_,
              Token(RacketTokenizer::kOpenBracket, "[", 1, 1, 1, 2));
  check_token(&tokenizer_open_bracket_then_token_,
              Token(RacketTokenizer::kToken, "hello", 1, 1, 2, 7));
  check_token(&tokenizer_open_bracket_then_token_,
              Token(RacketTokenizer::kEof, "", 1, 1, 7, 7));

  RacketTokenizer tokenizer_open_brace_then_token_
      (stream_open_brace_then_token_);
  check_token(&tokenizer_open_brace_then_token_,
              Token(RacketTokenizer::kOpenBrace, "{", 1, 1, 1, 2));
  check_token(&tokenizer_open_brace_then_token_,
              Token(RacketTokenizer::kToken, "hello", 1, 1, 2, 7));
  check_token(&tokenizer_open_brace_then_token_,
              Token(RacketTokenizer::kEof, "", 1, 1, 7, 7));

  RacketTokenizer tokenizer_close_paren_then_token_
      (stream_close_paren_then_token_);
  check_token(&tokenizer_close_paren_then_token_,
              Token(RacketTokenizer::kCloseParen, ")", 1, 1, 1, 2));
  check_token(&tokenizer_close_paren_then_token_,
              Token(RacketTokenizer::kToken, "hello", 1, 1, 2, 7));
  check_token(&tokenizer_close_paren_then_token_,
              Token(RacketTokenizer::kEof, "", 1, 1, 7, 7));

  RacketTokenizer tokenizer_close_bracket_then_token_
      (stream_close_bracket_then_token_);
  check_token(&tokenizer_close_bracket_then_token_,
              Token(RacketTokenizer::kCloseBracket, "]", 1, 1, 1, 2));
  check_token(&tokenizer_close_bracket_then_token_,
              Token(RacketTokenizer::kToken, "hello", 1, 1, 2, 7));
  check_token(&tokenizer_close_bracket_then_token_,
              Token(RacketTokenizer::kEof, "", 1, 1, 7, 7));

  RacketTokenizer tokenizer_close_brace_then_token_
      (stream_close_brace_then_token_);
  check_token(&tokenizer_close_brace_then_token_,
              Token(RacketTokenizer::kCloseBrace, "}", 1, 1, 1, 2));
  check_token(&tokenizer_close_brace_then_token_,
              Token(RacketTokenizer::kToken, "hello", 1, 1, 2, 7));
  check_token(&tokenizer_close_brace_then_token_,
              Token(RacketTokenizer::kEof, "", 1, 1, 7, 7));

  RacketTokenizer tokenizer_string_then_token_(stream_string_then_token_);
  check_token(&tokenizer_string_then_token_,
              Token(RacketTokenizer::kQuotationMark, "\"", 1, 1, 1, 2));
  check_token(&tokenizer_string_then_token_,
              Token(RacketTokenizer::kQuotationMark, "\"", 1, 1, 2, 3));
  check_token(&tokenizer_string_then_token_,
              Token(RacketTokenizer::kToken, "hello", 1, 1, 3, 8));
  check_token(&tokenizer_string_then_token_,
              Token(RacketTokenizer::kEof, "", 1, 1, 8, 8));

  RacketTokenizer tokenizer_comment_then_token_(stream_comment_then_token_);
  check_token(&tokenizer_comment_then_token_,
              Token(RacketTokenizer::kComment, ";hello", 1, 1, 1, 7));
  check_token(&tokenizer_comment_then_token_,
              Token(RacketTokenizer::kWhitespace, "\n", 1, 2, 7, 1));
  check_token(&tokenizer_comment_then_token_,
              Token(RacketTokenizer::kToken, "hello", 2, 2, 1, 6));
  check_token(&tokenizer_comment_then_token_,
              Token(RacketTokenizer::kEof, "", 2, 2, 6, 6));

  RacketTokenizer tokenizer_space_then_token_(stream_space_then_token_);
  check_token(&tokenizer_space_then_token_,
              Token(RacketTokenizer::kWhitespace, " ", 1, 1, 1, 2));
  check_token(&tokenizer_space_then_token_,
              Token(RacketTokenizer::kToken, "hello", 1, 1, 2, 7));
  check_token(&tokenizer_space_then_token_,
              Token(RacketTokenizer::kEof, "", 1, 1, 7, 7));

  RacketTokenizer tokenizer_tab_then_token_(stream_tab_then_token_);
  check_token(&tokenizer_tab_then_token_,
              Token(RacketTokenizer::kWhitespace, "\t", 1, 1, 1, 2));
  check_token(&tokenizer_tab_then_token_,
              Token(RacketTokenizer::kToken, "hello", 1, 1, 2, 7));
  check_token(&tokenizer_tab_then_token_,
              Token(RacketTokenizer::kEof, "", 1, 1, 7, 7));

  RacketTokenizer tokenizer_endline_then_token_(stream_endline_then_token_);
  check_token(&tokenizer_endline_then_token_,
              Token(RacketTokenizer::kWhitespace, "\n", 1, 2, 1, 1));
  check_token(&tokenizer_endline_then_token_,
              Token(RacketTokenizer::kToken, "hello", 2, 2, 1, 6));
  check_token(&tokenizer_endline_then_token_,
              Token(RacketTokenizer::kEof, "", 2, 2, 6, 6));

  RacketTokenizer tokenizer_cr_then_token_(stream_cr_then_token_);
  check_token(&tokenizer_cr_then_token_,
              Token(RacketTokenizer::kWhitespace, "\r", 1, 1, 1, 2));
  check_token(&tokenizer_cr_then_token_,
              Token(RacketTokenizer::kToken, "hello", 1, 1, 2, 7));
  check_token(&tokenizer_cr_then_token_,
              Token(RacketTokenizer::kEof, "", 1, 1, 7, 7));
}
TEST_F(RacketTokenizerTest, CommentCarriageReturn) {
  RacketTokenizer tokenizer_comment_cr_more_comment_
      (stream_comment_cr_more_comment_);
  check_token(&tokenizer_comment_cr_more_comment_,
              Token(RacketTokenizer::kComment, ";\r ", 1, 1, 1, 4));
  check_token(&tokenizer_comment_cr_more_comment_,
              Token(RacketTokenizer::kWhitespace, "\n", 1, 2, 4, 1));
  check_token(&tokenizer_comment_cr_more_comment_,
              Token(RacketTokenizer::kEof, "", 2, 2, 1, 1));

  RacketTokenizer tokenizer_comment_cr_endline_(stream_comment_cr_endline_);
  check_token(&tokenizer_comment_cr_endline_,
              Token(RacketTokenizer::kComment, ";", 1, 1, 1, 2));
  check_token(&tokenizer_comment_cr_endline_,
              Token(RacketTokenizer::kWhitespace, "\r\n", 1, 2, 2, 1));
  check_token(&tokenizer_comment_cr_endline_,
              Token(RacketTokenizer::kEof, "", 2, 2, 1, 1));
}
TEST_F(RacketTokenizerTest, RichTest) {
  RacketTokenizer tokenizer_rich_example_(stream_rich_example_);
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kOpenParen, "(", 1, 1, 1, 2));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kToken, "+", 1, 1, 2, 3));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kWhitespace, " ", 1, 1, 3, 4));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kOpenParen, "(", 1, 1, 4, 5));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kToken, "fun", 1, 1, 5, 8));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kWhitespace, " ", 1, 1, 8, 9));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kOpenBracket, "[", 1, 1, 9, 10));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kToken, "1", 1, 1, 10, 11));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kWhitespace, " ", 1, 1, 11, 12));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kToken, "2", 1, 1, 12, 13));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kWhitespace, " ", 1, 1, 13, 14));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kToken, "3", 1, 1, 14, 15));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kCloseBracket, "]", 1, 1, 15, 16));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kCloseParen, ")", 1, 1, 16, 17));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kWhitespace, " \n", 1, 2, 17, 1));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kOpenParen, "(", 2, 2, 1, 2));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kOpenBrace, "{", 2, 2, 2, 3));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kToken, "hello", 2, 2, 3, 8));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kQuotationMark, "\"", 2, 2, 8, 9));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kStringData, "goodbye", 2, 2, 9, 16));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kQuotationMark, "\"", 2, 2, 16, 17));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kCloseBracket, "]", 2, 2, 17, 18));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kCloseBracket, "]", 2, 2, 18, 19));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kOpenParen, "(", 2, 2, 19, 20));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kOpenParen, "(", 2, 2, 20, 21));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kOpenBrace, "{", 2, 2, 21, 22));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kOpenBracket, "[", 2, 2, 22, 23));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kWhitespace, "  \t", 2, 2, 23, 26));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kToken, "5", 2, 2, 26, 27));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kWhitespace, "\n", 2, 3, 27, 1));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kToken, "is", 3, 3, 1, 3));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kWhitespace, " ", 3, 3, 3, 4));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kToken, "a", 3, 3, 4, 5));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kWhitespace, " ", 3, 3, 5, 6));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kComment, ";; cmt", 3, 3, 6, 12));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kWhitespace, "\n ", 3, 4, 12, 2));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kToken, "the", 4, 4, 2, 5));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kWhitespace, " ", 4, 4, 5, 6));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kToken, "end", 4, 4, 6, 9));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kCloseParen, ")", 4, 4, 9, 10));
  check_token(&tokenizer_rich_example_,
              Token(RacketTokenizer::kEof, "", 4, 4, 10, 10));
}
}  // namespace tokenizer
