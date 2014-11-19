cmake_minimum_required (VERSION 2.8 FATAL_ERROR)

# Put the project command before everything else.  At minimum, it
# reset my compiler flags; probably other things as well!
project ("Evil Hangman")

# TODO: include resource files, move source to src directory

# Helps with compiling on Cygwin. No effect otherwise.
set(CMAKE_LEGACY_CYGWIN_WIN32 0)

# Enable C++11. TODO: ensure that this flag is available?
add_definitions("-std=c++11")

# To find my libraries 
set(MY_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}" CACHE PATH 
  "Base directory of which all libraries are subdirectories.")
set(GMOCK_DIR "${MY_LIB_DIR}/gmock-1.7.0" CACHE PATH
  "The path to the GoogleMock test framework.")
set(CPPLINT "${MY_LIB_DIR}/cpplint.py" CACHE PATH
  "The path to the C++ lint style checker.")

enable_testing()


# To make Google Test testing work correctly in MSVC, per
# http://johnlamp.net/cmake-tutorial-4-libraries-and-subdirectories.html
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # force this option to ON so that Google Test will use /MD instead
    # of /MT /MD is now the default for Visual Studio, so it should be
    # our default, too 
    option(gtest_force_shared_crt "Use shared (DLL) run-time lib even when Google Test is built as static lib."  ON)
endif()


add_subdirectory(${GMOCK_DIR} ${CMAKE_BINARY_DIR}/gmock)
set_property(TARGET gtest APPEND_STRING PROPERTY COMPILE_FLAGS " -w")
include_directories(${GMOCK_DIR}/gtest/include
                    ${GMOCK_DIR}/include)

add_executable(word_set_test word_set_test.cc word_set.cc word_set.h)
target_link_libraries(word_set_test gmock_main)
add_test(word_set_test word_set_test)

add_executable(word_set_test_partition_only word_set_test_partition_only.cc 
  word_set.cc word_set.h)
target_link_libraries(word_set_test_partition_only gmock_main)
add_test(word_set_test_partition_only word_set_test_partition_only)

add_test(conformance check_output_conformance)


# Check style on all these files.
#
# TODO: write a cmake function that will handle both the style test
# and the executable construction for me in one fell swoop.
#add_test(word_set_style_test ${CPPLINT} word_set_style_test.cc word_set.cc word_set.h)

add_executable(evil_hangman_utils_test 
  evil_hangman_utils_test.cc 
  evil_hangman_utils.cc 
  evil_hangman_utils.h)
target_link_libraries(evil_hangman_utils_test gmock_main)
add_test(evil_hangman_utils_test evil_hangman_utils_test)

add_executable(evil_hangman 
  evil_hangman.cc 
  evil_hangman_utils.cc 
  evil_hangman_utils.h 
  word_set.cc 
  word_set.h)

# Install the dictionary, both in the build and in any subsequent
# install.  Also, ensure that the executable can find it through the
# preprocessor constant DICTIONARY_FILENAME.
set(DICTIONARY_FILENAME "dictionary.txt" CACHE PATH
  "The name of the file containing the dictionary of available hangman words.")
configure_file("${DICTIONARY_FILENAME}" .)
install(FILES "${DICTIONARY_FILENAME}" DESTINATION .)
set_property(TARGET evil_hangman
  PROPERTY COMPILE_DEFINITIONS "DICTIONARY_FILENAME=\"${DICTIONARY_FILENAME}\"")


# Install the conformance testing files in the build directory.
configure_file("check_output_conformance" .)
configure_file("15letterpatterntiebreaker.in.txt" .)
configure_file("15letterpatterntiebreaker.out.txt" .)
configure_file("28letterwin.in.txt" .)
configure_file("28letterwin.out.txt" .)
configure_file("4lettergametotalfailure.in.txt" .)
configure_file("4lettergametotalfailure.out.txt" .)
configure_file("5lettergamelose2.in.txt" .)
configure_file("5lettergamelose2.out.txt" .)
configure_file("5lettergamelose.in.txt" .)
configure_file("5lettergamelose.out.txt" .)
