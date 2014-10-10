#include <iostream>

int a = 0;
int b = 0;
int* c = &b;

void test( int &x, int &y, int*& z ) {
    x++;
    y++;
    z = &a;
}

int main() {
    test(a, b, c);
    std::cout << a << " " << b << " " << *c << std::endl;
    return 0;
}
