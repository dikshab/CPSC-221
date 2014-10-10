# CMake generated Testfile for 
# Source directory: /Users/calvin/Dropbox/My Documents/UBC Stuff/2014W/CPSC 221/Projects/pp1/src
# Build directory: /Users/calvin/Dropbox/My Documents/UBC Stuff/2014W/CPSC 221/Projects/pp1/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(token_test "token_test")
add_test(stack_test "stack_test")
add_test(racket_tokenizer_test "racket_tokenizer_test")
add_test(balance_checker_test "balance_checker_test")
add_test(linkedliststack_test "linkedliststack_test")
subdirs(gmock)
