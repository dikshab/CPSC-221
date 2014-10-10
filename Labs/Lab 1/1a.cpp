#include <iostream>

float circle_area(float radius);  // declare function before main()

int main(void) {
  float circle_radius;
  std::cout << "Enter radius:" << std::endl;
  std::cin >> circle_radius;
  std::cout << "Area is: " << circle_area(circle_radius) << std::endl;
}

float circle_area(float radius) {
  return 3.14159 * radius * radius;  // = pi * r^2
}
