#include <iostream>

int main() {
  int x = 5, y = 15;
  int * p1, *p2;

  p1 = &x;        // x contains 5; y contains 15;
                  // p1 contains address(x); p2 contains null;

  p2 = &y;        // x contains 5; y contains 15;
                  // p1 contains address(x); p2 contains address(y);

  *p1 = 6;        // x contains 6; y contains 15;
                  // p1 contains address(x); p2 contains address(y);

  *p1 = *p2;      // x contains 15; y contains 15;
                  // p1 contains address(x); p2 contains address(y);

  p2 = p1;        // x contains 15; y contains 15;
                  // p1 contains address(x); p2 contains address(x);

  *p1 = *p2+10;   // x contains 25; y contains 15;
                  // p1 contains address(x); p2 contains address(x);

  return 0;
}
