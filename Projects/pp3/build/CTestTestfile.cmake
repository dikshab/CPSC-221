# CMake generated Testfile for 
# Source directory: /Users/calvin/Dropbox/My Documents/UBC Stuff/2014W/CPSC 221/Projects/pp3/src
# Build directory: /Users/calvin/Dropbox/My Documents/UBC Stuff/2014W/CPSC 221/Projects/pp3/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(word_set_test "word_set_test")
add_test(word_set_test_partition_only "word_set_test_partition_only")
add_test(conformance "check_output_conformance")
add_test(evil_hangman_utils_test "evil_hangman_utils_test")
subdirs(gmock)
