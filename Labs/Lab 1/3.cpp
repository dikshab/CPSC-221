#include <cstdlib>   // for atoi
#include <iostream>

using std::string;
using std::cout;
using std::endl;

void moveDisks(int height, string from, string other, string to);

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " number_of_disks" << std::endl;
    return -1;
  }
  int n = atoi(argv[1]);
  moveDisks(n, "peg A", "peg B", "peg C");
  return 0;
}

void moveDisks(int height, string from, string other, string to) {
	if (height == 1) {
		cout << "Move disk from " << from << " to " << to << endl;
	}
	else {
		moveDisks(height - 1, from, to, other);
		moveDisks(1, from, other, to);
		moveDisks(height - 1, other, from, to);
	}
}
