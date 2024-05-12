//[2024-05-09] outputs random numbers to a file

#include <iostream>
#include <fstream>
#include <random>
using namespace std;

int main() {
	string file_name;
	int num_count;

	cout << "  what's the file name? ";
	getline(cin, file_name);
	cout << "  how many numbers to output? ";
	cin >> num_count;
	cin.ignore();

	file_name = "../test-files/" + file_name;

	ofstream out_file(file_name);
	if (!out_file.is_open()) {
		std::cerr << "couldn't open file :(\n";
		return 1;
	}

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> distribution(1, 999999);

	cout << "  outputting " << num_count << " numbers to " << file_name << endl;

	for (int i = 0; i < num_count; ++i) {
		out_file << (int)distribution(gen) << endl;
	}

	out_file.close();

	cout << "  done!\n";

	return 0;
}
