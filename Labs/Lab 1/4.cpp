#include <cstdlib>
#include <iostream>
#include <ctime>

using std::string;
using std::cin;
using std::cout;
using std::endl;

const int MIN = 1;
const int MAX = 100;

int main() {
	srand(time(NULL));
	string input;
	int input_num;
	int random = rand() % MAX + MIN;
	do {
		cout << "Enter a number ";
		cout << "(from " << MIN << " to " << MAX << "), press 'q' to quit: ";
		cin >> input;
		if (input == "q") {
			break;
		}
		else {
			input_num = stoi(input);
			if (input_num == random) {
				cout << "Congratulations! You guessed the number. ";
				cout << "The number was " << random <<"." << endl;
				break;
			}
			else if (input_num < random){
				cout << "Sorry, " << input_num;
				cout << " is not the right number. Guess higher!" << endl;
			}
			else {
				cout << "Sorry, " << input_num;
				cout << " is not the right number. Guess lower!" << endl;
			}
		}
	} while (input_num != random);

	cout << "Program complete." << endl;
	return 0;
}
