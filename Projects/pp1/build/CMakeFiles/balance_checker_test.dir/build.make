# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/calvin/Dropbox/My Documents/UBC Stuff/2014W/CPSC 221/Projects/pp1/src"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/calvin/Dropbox/My Documents/UBC Stuff/2014W/CPSC 221/Projects/pp1/build"

# Include any dependencies generated for this target.
include CMakeFiles/balance_checker_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/balance_checker_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/balance_checker_test.dir/flags.make

CMakeFiles/balance_checker_test.dir/balance_checker_test.cc.o: CMakeFiles/balance_checker_test.dir/flags.make
CMakeFiles/balance_checker_test.dir/balance_checker_test.cc.o: /Users/calvin/Dropbox/My\ Documents/UBC\ Stuff/2014W/CPSC\ 221/Projects/pp1/src/balance_checker_test.cc
	$(CMAKE_COMMAND) -E cmake_progress_report "/Users/calvin/Dropbox/My Documents/UBC Stuff/2014W/CPSC 221/Projects/pp1/build/CMakeFiles" $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/balance_checker_test.dir/balance_checker_test.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/balance_checker_test.dir/balance_checker_test.cc.o -c "/Users/calvin/Dropbox/My Documents/UBC Stuff/2014W/CPSC 221/Projects/pp1/src/balance_checker_test.cc"

CMakeFiles/balance_checker_test.dir/balance_checker_test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/balance_checker_test.dir/balance_checker_test.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E "/Users/calvin/Dropbox/My Documents/UBC Stuff/2014W/CPSC 221/Projects/pp1/src/balance_checker_test.cc" > CMakeFiles/balance_checker_test.dir/balance_checker_test.cc.i

CMakeFiles/balance_checker_test.dir/balance_checker_test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/balance_checker_test.dir/balance_checker_test.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S "/Users/calvin/Dropbox/My Documents/UBC Stuff/2014W/CPSC 221/Projects/pp1/src/balance_checker_test.cc" -o CMakeFiles/balance_checker_test.dir/balance_checker_test.cc.s

CMakeFiles/balance_checker_test.dir/balance_checker_test.cc.o.requires:
.PHONY : CMakeFiles/balance_checker_test.dir/balance_checker_test.cc.o.requires

CMakeFiles/balance_checker_test.dir/balance_checker_test.cc.o.provides: CMakeFiles/balance_checker_test.dir/balance_checker_test.cc.o.requires
	$(MAKE) -f CMakeFiles/balance_checker_test.dir/build.make CMakeFiles/balance_checker_test.dir/balance_checker_test.cc.o.provides.build
.PHONY : CMakeFiles/balance_checker_test.dir/balance_checker_test.cc.o.provides

CMakeFiles/balance_checker_test.dir/balance_checker_test.cc.o.provides.build: CMakeFiles/balance_checker_test.dir/balance_checker_test.cc.o

CMakeFiles/balance_checker_test.dir/balance_checker.cc.o: CMakeFiles/balance_checker_test.dir/flags.make
CMakeFiles/balance_checker_test.dir/balance_checker.cc.o: /Users/calvin/Dropbox/My\ Documents/UBC\ Stuff/2014W/CPSC\ 221/Projects/pp1/src/balance_checker.cc
	$(CMAKE_COMMAND) -E cmake_progress_report "/Users/calvin/Dropbox/My Documents/UBC Stuff/2014W/CPSC 221/Projects/pp1/build/CMakeFiles" $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/balance_checker_test.dir/balance_checker.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/balance_checker_test.dir/balance_checker.cc.o -c "/Users/calvin/Dropbox/My Documents/UBC Stuff/2014W/CPSC 221/Projects/pp1/src/balance_checker.cc"

CMakeFiles/balance_checker_test.dir/balance_checker.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/balance_checker_test.dir/balance_checker.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E "/Users/calvin/Dropbox/My Documents/UBC Stuff/2014W/CPSC 221/Projects/pp1/src/balance_checker.cc" > CMakeFiles/balance_checker_test.dir/balance_checker.cc.i

CMakeFiles/balance_checker_test.dir/balance_checker.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/balance_checker_test.dir/balance_checker.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S "/Users/calvin/Dropbox/My Documents/UBC Stuff/2014W/CPSC 221/Projects/pp1/src/balance_checker.cc" -o CMakeFiles/balance_checker_test.dir/balance_checker.cc.s

CMakeFiles/balance_checker_test.dir/balance_checker.cc.o.requires:
.PHONY : CMakeFiles/balance_checker_test.dir/balance_checker.cc.o.requires

CMakeFiles/balance_checker_test.dir/balance_checker.cc.o.provides: CMakeFiles/balance_checker_test.dir/balance_checker.cc.o.requires
	$(MAKE) -f CMakeFiles/balance_checker_test.dir/build.make CMakeFiles/balance_checker_test.dir/balance_checker.cc.o.provides.build
.PHONY : CMakeFiles/balance_checker_test.dir/balance_checker.cc.o.provides

CMakeFiles/balance_checker_test.dir/balance_checker.cc.o.provides.build: CMakeFiles/balance_checker_test.dir/balance_checker.cc.o

CMakeFiles/balance_checker_test.dir/racket_tokenizer.cc.o: CMakeFiles/balance_checker_test.dir/flags.make
CMakeFiles/balance_checker_test.dir/racket_tokenizer.cc.o: /Users/calvin/Dropbox/My\ Documents/UBC\ Stuff/2014W/CPSC\ 221/Projects/pp1/src/racket_tokenizer.cc
	$(CMAKE_COMMAND) -E cmake_progress_report "/Users/calvin/Dropbox/My Documents/UBC Stuff/2014W/CPSC 221/Projects/pp1/build/CMakeFiles" $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/balance_checker_test.dir/racket_tokenizer.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/balance_checker_test.dir/racket_tokenizer.cc.o -c "/Users/calvin/Dropbox/My Documents/UBC Stuff/2014W/CPSC 221/Projects/pp1/src/racket_tokenizer.cc"

CMakeFiles/balance_checker_test.dir/racket_tokenizer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/balance_checker_test.dir/racket_tokenizer.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E "/Users/calvin/Dropbox/My Documents/UBC Stuff/2014W/CPSC 221/Projects/pp1/src/racket_tokenizer.cc" > CMakeFiles/balance_checker_test.dir/racket_tokenizer.cc.i

CMakeFiles/balance_checker_test.dir/racket_tokenizer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/balance_checker_test.dir/racket_tokenizer.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S "/Users/calvin/Dropbox/My Documents/UBC Stuff/2014W/CPSC 221/Projects/pp1/src/racket_tokenizer.cc" -o CMakeFiles/balance_checker_test.dir/racket_tokenizer.cc.s

CMakeFiles/balance_checker_test.dir/racket_tokenizer.cc.o.requires:
.PHONY : CMakeFiles/balance_checker_test.dir/racket_tokenizer.cc.o.requires

CMakeFiles/balance_checker_test.dir/racket_tokenizer.cc.o.provides: CMakeFiles/balance_checker_test.dir/racket_tokenizer.cc.o.requires
	$(MAKE) -f CMakeFiles/balance_checker_test.dir/build.make CMakeFiles/balance_checker_test.dir/racket_tokenizer.cc.o.provides.build
.PHONY : CMakeFiles/balance_checker_test.dir/racket_tokenizer.cc.o.provides

CMakeFiles/balance_checker_test.dir/racket_tokenizer.cc.o.provides.build: CMakeFiles/balance_checker_test.dir/racket_tokenizer.cc.o

CMakeFiles/balance_checker_test.dir/my_stack.cc.o: CMakeFiles/balance_checker_test.dir/flags.make
CMakeFiles/balance_checker_test.dir/my_stack.cc.o: /Users/calvin/Dropbox/My\ Documents/UBC\ Stuff/2014W/CPSC\ 221/Projects/pp1/src/my_stack.cc
	$(CMAKE_COMMAND) -E cmake_progress_report "/Users/calvin/Dropbox/My Documents/UBC Stuff/2014W/CPSC 221/Projects/pp1/build/CMakeFiles" $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/balance_checker_test.dir/my_stack.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/balance_checker_test.dir/my_stack.cc.o -c "/Users/calvin/Dropbox/My Documents/UBC Stuff/2014W/CPSC 221/Projects/pp1/src/my_stack.cc"

CMakeFiles/balance_checker_test.dir/my_stack.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/balance_checker_test.dir/my_stack.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E "/Users/calvin/Dropbox/My Documents/UBC Stuff/2014W/CPSC 221/Projects/pp1/src/my_stack.cc" > CMakeFiles/balance_checker_test.dir/my_stack.cc.i

CMakeFiles/balance_checker_test.dir/my_stack.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/balance_checker_test.dir/my_stack.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S "/Users/calvin/Dropbox/My Documents/UBC Stuff/2014W/CPSC 221/Projects/pp1/src/my_stack.cc" -o CMakeFiles/balance_checker_test.dir/my_stack.cc.s

CMakeFiles/balance_checker_test.dir/my_stack.cc.o.requires:
.PHONY : CMakeFiles/balance_checker_test.dir/my_stack.cc.o.requires

CMakeFiles/balance_checker_test.dir/my_stack.cc.o.provides: CMakeFiles/balance_checker_test.dir/my_stack.cc.o.requires
	$(MAKE) -f CMakeFiles/balance_checker_test.dir/build.make CMakeFiles/balance_checker_test.dir/my_stack.cc.o.provides.build
.PHONY : CMakeFiles/balance_checker_test.dir/my_stack.cc.o.provides

CMakeFiles/balance_checker_test.dir/my_stack.cc.o.provides.build: CMakeFiles/balance_checker_test.dir/my_stack.cc.o

# Object files for target balance_checker_test
balance_checker_test_OBJECTS = \
"CMakeFiles/balance_checker_test.dir/balance_checker_test.cc.o" \
"CMakeFiles/balance_checker_test.dir/balance_checker.cc.o" \
"CMakeFiles/balance_checker_test.dir/racket_tokenizer.cc.o" \
"CMakeFiles/balance_checker_test.dir/my_stack.cc.o"

# External object files for target balance_checker_test
balance_checker_test_EXTERNAL_OBJECTS =

balance_checker_test: CMakeFiles/balance_checker_test.dir/balance_checker_test.cc.o
balance_checker_test: CMakeFiles/balance_checker_test.dir/balance_checker.cc.o
balance_checker_test: CMakeFiles/balance_checker_test.dir/racket_tokenizer.cc.o
balance_checker_test: CMakeFiles/balance_checker_test.dir/my_stack.cc.o
balance_checker_test: CMakeFiles/balance_checker_test.dir/build.make
balance_checker_test: gmock/libgmock_main.a
balance_checker_test: CMakeFiles/balance_checker_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable balance_checker_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/balance_checker_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/balance_checker_test.dir/build: balance_checker_test
.PHONY : CMakeFiles/balance_checker_test.dir/build

CMakeFiles/balance_checker_test.dir/requires: CMakeFiles/balance_checker_test.dir/balance_checker_test.cc.o.requires
CMakeFiles/balance_checker_test.dir/requires: CMakeFiles/balance_checker_test.dir/balance_checker.cc.o.requires
CMakeFiles/balance_checker_test.dir/requires: CMakeFiles/balance_checker_test.dir/racket_tokenizer.cc.o.requires
CMakeFiles/balance_checker_test.dir/requires: CMakeFiles/balance_checker_test.dir/my_stack.cc.o.requires
.PHONY : CMakeFiles/balance_checker_test.dir/requires

CMakeFiles/balance_checker_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/balance_checker_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/balance_checker_test.dir/clean

CMakeFiles/balance_checker_test.dir/depend:
	cd "/Users/calvin/Dropbox/My Documents/UBC Stuff/2014W/CPSC 221/Projects/pp1/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/calvin/Dropbox/My Documents/UBC Stuff/2014W/CPSC 221/Projects/pp1/src" "/Users/calvin/Dropbox/My Documents/UBC Stuff/2014W/CPSC 221/Projects/pp1/src" "/Users/calvin/Dropbox/My Documents/UBC Stuff/2014W/CPSC 221/Projects/pp1/build" "/Users/calvin/Dropbox/My Documents/UBC Stuff/2014W/CPSC 221/Projects/pp1/build" "/Users/calvin/Dropbox/My Documents/UBC Stuff/2014W/CPSC 221/Projects/pp1/build/CMakeFiles/balance_checker_test.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/balance_checker_test.dir/depend
