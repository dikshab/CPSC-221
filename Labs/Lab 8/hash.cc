#include "hash.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

Hash::Hash(int _m) {
	//constructor
	m = _m;
	totalProbes = 0;
	numInserts = 0;
	table = new int [m];
	for (int i=0; i<m; i++) {
		table[i] = EMPTY;
	}
}

Hash::~Hash() {
	//deconstructor
	delete[] table;
}

void Hash::tallyProbes(int p) {
	// Add the number of probes, p, for one insert operation to the tally.
	totalProbes += p;
	numInserts++;
}

void Hash::printStats() {
	std::cout << "Average probes/insert = " <<
			probeRate() << " = " <<
			totalProbes << "/" << numInserts << std::endl;
}

float Hash::probeRate() {
	return (float)totalProbes / (float)numInserts;
}

int Hash::hash(int k) {
	return k % m;
}

int Hash::hash2(int k) {
  const int R = (this->m >> 3) + 3;
  return R - (k % R);
}

void Hash::qinsert(int k) {
	// Insert k in the hash table.
	// Use open addressing with quadratic probing and hash(k) = k % m.

	// Tips:
	// - Look at the lecture slides if you don't remember how to implement these.
	// - You need to prevent against infinite loops. You should limit the number
	// of times you probe and print an error message upon exceeding this limit.
	// - You're welcome to add new declarations to hash.h, add to the constructor,
	// include libraries, or anything else you need. Just make it work.
	// - You're also welcome to modify the main() method to automate your testing.
	// In fact, you should!

	// add your code here
  int probe = hash(k);
  int i = 1;
  while (this->table[probe] != EMPTY && this->table[probe] != k) {
    if (i > this->m) {
      std::cerr << "Error - Couldn't insert " << k << " into table.\n";
      exit(-1);
    }
    probe = (probe + 2*i - 1) % this->m;
    i++;
  }
  this->tallyProbes(i);
  this->table[probe] = k;
}

void Hash::linsert(int k) {
	// Insert k in the hash table.
	// Use open addressing with linear probing and hash(k) = k % m.

	//add your code here
  int i = 1;
  int probe = hash(k);
  while (this->table[probe] != EMPTY && this->table[probe] != k) {
    if (i > this->m) {
      std::cerr << "Error - Couldn't insert " << k << " into table.\n";
      exit(-1);
    }
    probe = (probe + 1) % this->m;
    i++;
  }
  this->tallyProbes(i);
  this->table[probe] = k;
}

void Hash::dinsert(int k) {
	// Insert k in the hash table.
	// Use open addressing with double hashing. Use the existing hash function
	// and also implement a second hash function.

	//add your code here
  int i = 1;
  int probe = hash(k);
  int probeInc = hash2(k);
  while (this->table[probe] != EMPTY && this->table[probe] != k) {
    if (i > this->m) {
      std::cerr << "Error - Couldn't insert " << k << " into table.\n";
      exit(-1);
    }
    probe = (probe + probeInc) % this->m;
    i++;
  }
  this->tallyProbes(i);
  this->table[probe] = k;
}

void Hash::print() {
	// Print the content of the hash table.

	for (int i=0; i<m; i++) {
		std::cout<<"["<<i<<"] ";
		if (table[i] != EMPTY)
			std::cout << table[i];
		std::cout << std::endl;
	}
}

void test(int n, int m) {

  Hash H1(m);
  for (int i=0; i<n; ++i) {
    H1.linsert(rand() + 1);
  }
  //    H.print();
  std::cout << "Linear:\t\t";
  H1.printStats();

  Hash H2(m);
  for (int i=0; i<n; ++i) {
    H2.linsert(rand() + 1);
  }
  //    H.print();
  std::cout << "Quadratic:\t";
  H2.printStats();

  Hash H3(m);
  for (int i=0; i<n; ++i) {
    H3.linsert(rand() + 1);
  }
  //    H.print();
  std::cout << "Double:\t\t";
  H3.printStats();
}

void usage(char* argv[]) {
	std::cerr << "Usage: " << argv[0] << " sizeOfTable" << std::endl;
	exit(-1);
}

int main(int argc, char *argv[]) {
	int m;
	srand(time(0));

	if (argc != 2) {
		usage(argv);
	}
	m = atoi(argv[1]);
	for (int i = 1; i <= 10; i++) {
	  std::cout << "Load factor: " << i << "/10\t"
	      << "Insertions: " << m * i / 10 << "\t"
	      << "Table Size: " << m << std::endl;
	  test(m*i/10, m);
	  std::cout << std::endl;
	}
}
