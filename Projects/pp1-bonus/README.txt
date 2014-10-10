README.txt file documenting a CPSC 221 programming project.

Please fill out each TODO item in the header but change nothing else,
particularly nothing before the colon ":" on each line!

=================== HEADER =======================

Student #1, Name: Calvin Cheng
Student #1, ugrad.cs.ubc.ca login: o7x8
Student #1, ID: 36090132

Student #2, Name: Stephanie Dong
Student #2, ugrad.cs.ubc.ca login: p1e9 
Student #2, ID: 31136138

Team name (for fun!): Everything is awesome

Project: RackaBrackaStack

Acknowledgment that you understand and have followed the course's
collaboration policy (READ IT at
http://www.ugrad.cs.ubc.ca/~cs221/current/syllabus.shtml#conduct):

Signed:
Calvin Cheng
Stephanie Dong

=================== BODY =======================

For the bonus, we only completed the first challenege. The linked list
implementation of the stack is included in the linkedliststack.h and
linkedliststack.cc files, and the tests are in the linkedliststack_test.cc
file. We have modified CMakeLists.txt to generate a working Makefile
with only the files in this directory. After building the project,
running the the linkedliststack_test executable should execute the tests
that we designed.

For the implementation of the stack backed by a linked list, we used a number
of structs to serve as the nodes for each element in the stack. By keeping
track of the head of the stack, implementing the push and pop functions was
fairly simple, as it only involved allocating/deleting memory as necessary,
and updating the pointer to the head of the stack.

For the tests of the linked list stack, we simply modified the provided unit
tests for the original two stack implementations in the project. As this stack
is simply a subclass of TokenStack, it was quite simple to just modify the
test file to test our implementation. Given that the tests were sufficient for
the project, we felt that these tests would be sufficient for the bonus, as
well.