#include <iostream>
#include <assert.h>

unsigned long fact(unsigned int x);
unsigned long fact_tail(unsigned int x);
unsigned long fact_iter(unsigned int x);

int main() {
  int n;
  std::cout << "Compute factorial of: ";
  std::cin >> n;
  std::cout << "Recursive factorial: " << fact(n) << std::endl;
  std::cout << "Tail-recursive factorial: " << fact_tail(n) << std::endl;
  std::cout << "Iterative factorial: " << fact_iter(n) << std::endl;

}

unsigned long fact(unsigned int x) {
  if (x<1)
    return 1;
  else
    return x * fact(x-1);
}

unsigned long fact_tail_acc(unsigned int x, unsigned long acc) {
  if (x < 1)
    return acc;
  else
    return fact_tail_acc(x - 1, x * acc);
}

unsigned long fact_tail(unsigned int x) {
  return fact_tail_acc(x - 1, x);
}


unsigned long fact_iter(unsigned int x) {
  unsigned long factorial = x;
  //LOOP INVARIANT: (factorial = x_0 * (x_0 - 1) * ... * x) and (1 <= x <= x_0)
  while (x > 1) {
    x--;
    factorial *= x;
  }
  return factorial;
}
