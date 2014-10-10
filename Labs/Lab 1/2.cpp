#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int list_of_num[10];

void fill_array(int first, int diff) {
	for (int i = 0; i < 10; i++) {
		list_of_num[i] = first + diff * i;
	}
}

int main() {
	int a, d;
	cin >> a >> d;
	fill_array(a, d);

	for (int i = 0; i < 10; i++) {
		cout << list_of_num[i] << " ";
	}
	cout << endl;
}
