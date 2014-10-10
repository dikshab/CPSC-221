#include <iostream>
#include <string>
#include <fstream>

int main(void) {
	std::ifstream in("infile.txt"); // Open for reading
	std::ofstream out("outfile.txt"); // Open for writing
	std::string s;
	while (getline(in, s)) // Discards newline char
	out << s << std::endl; // ... add it to the new file
	std::cout << "End of program" << std::endl;
	return 0;
}
