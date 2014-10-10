// mod_exp.cc --- Exponentiation in a particular modulus, used to
// explore runtime scaling of different algorithms.

// This is Copyright (C) 2014 by the University of British Columbia,
// Some Rights Reserved.  (Original author: Alan Hu.)
//
// This work is licensed under the Creative Commons Attribution 4.0
// International License. To view a copy of this license, visit
// http://creativecommons.org/licenses/by/4.0/.

#include <iostream>
#include <cassert>
#include <cstdint>

// Per the Google style guideline, we use uint64_t to specify 64-bit
// numbers rather than long or long long.
uint64_t mod_exp1(uint64_t b, uint64_t x, uint64_t m);
uint64_t mod_exp2(uint64_t b, uint64_t x, uint64_t m);
uint64_t mod_exp2o(uint64_t b, uint64_t x, uint64_t m);


int main(void) {
  // Tester program for the exponentiation operators.
  uint64_t base = 2;   // b: the number to be raised to some power
  uint64_t exp;    // x: the exponent to use
  uint64_t mod = 1000;    // m: the modulus

  std::cout << "A uint64_t has "
            << sizeof(uint64_t) << " bytes." << std::endl;
  std::cout << "Raise b the xth power, mod m." << std::endl;
  std::cout << "Enter x: ";
  std::cin >> exp;

  // You might need to adjust this loop to repeat the
  // next call to exponentiate a whole bunch of times to have
  // the runtime be long enough to measure.
  // Do not include this loop in your asymptotic analysis!
  uint64_t result;
  for (int i = 0; i < 50000000; ++i) {
    // UNCOMMENT ONE OF THE FOLLOWING CALLS TO PICK WHICH ALGORITHM TO USE
    //result = mod_exp1(base, exp, mod);
     result = mod_exp2(base, exp, mod);
    //  result = mod_exp2o(base, exp, mod);
  }

  std::cout << "The answer is: " << result << std::endl;

  return 0;
}


// Raise b to the x power, mod m
// -- First algorithm
uint64_t mod_exp1(uint64_t b, uint64_t x, uint64_t m) {
  uint64_t result = 1;

  for (uint64_t i = 0; i < x; ++i) {
    result *= b;
    result %= m;
  }

  return result;
}


// Raise b to the x power, mod m
// -- Second algorithm
uint64_t mod_exp2(uint64_t b, uint64_t x, uint64_t m) {
  if (x == 0) {
    return 1;
  }

  uint64_t result = mod_exp2(b, x/2, m);
  result *= result;
  result %= m;
  if (x%2 != 0) {
    result *= b;
  }
  result %= m;

  return result;
}


// Raise b to the x power, mod m
// -- Second algorithm "optimized"
//
// This will not pass the style-checker (surprise, surprise!)
uint64_t mod_exp2o(uint64_t b, uint64_t x, uint64_t m) {
  return (x == 0) ? 1 : (mod_exp2o(b, x/2, m)
      * mod_exp2o(b, x/2, m)
      * (x%2 != 0 ? b : 1)) % m;
}
