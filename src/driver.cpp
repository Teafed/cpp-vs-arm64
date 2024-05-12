/***********************************
 * Name:   Noëlle Abat
 * Class:  CS3B - Professor Barnett
 * Lab:    RASM-5
 * Date:   5/9/24
 ***********************************/

#include "driver.h"

int main() {
	ifstream in_file;

	int num_count = 0;	//number of elements read from file
	int c_time = 0;		//c bubble sort time
	int a_time = 0;		//assembly sort time
	int input;				//user input
	int* nums = nullptr;	//pointer to start of dynamic num array
	string out_file_name;

	print_menu(num_count, c_time, a_time);
		do {
		get_input(input, "enter menu option:");

		if ((input == 2 || input == 3) && nums == nullptr) {
			cout << "    the array hasn't been made yet silly :)\n";
			input = -1;
			pause();
		}

		switch (input) {
		case -1:
			break;
		case 1:
			load_file(in_file, nums, num_count);
			pause();
			break;

		case 2:
			//time bubble_sort_cpp execution time
			c_time = time_function(bubble_sort_cpp, nums, num_count);

			//output
			cout << "    bubblesort in c++ took " << c_time << " seconds to execute\n";
			out_file_name = "c_bubblesort.txt";
			output_to_file(nums, num_count, out_file_name);

			if (c_time != 0 && a_time != 0) {
				float ratio;
				if (a_time < c_time) {
					ratio = (float)c_time / (float)a_time;
					cout << "\n    conclusion: assembly is " << ratio << " times faster than cpp!\n";
				}
			}

			//delete array
			reset_array(nums, num_count);
			pause();
			break;
		case 3:
			//time bubble_sort_ass execution time
			a_time = time_function(bubble_sort_ass, nums, num_count);

			//output
			cout << "    bubblesort in ass took " << a_time << " seconds to execute\n";
			out_file_name = "a_bubblesort.txt";
			output_to_file(nums, num_count, out_file_name);

			//delete array
			reset_array(nums, num_count);

			if (c_time != 0 && a_time != 0) {
				float ratio;
				if (a_time < c_time) {
					ratio = (float)c_time / (float)a_time;
					cout << "\n    conclusion: assembly is " << ratio << " times faster than cpp!\n";
				}
			}

			pause();
			break;

		default:
			input = 4;
		}

	} while (input != 4);

	reset_array(nums, num_count);

	return 0;
}

void bubble_sort_cpp(int* nums, int num_count) {
	for (int i = 0; i < num_count - 1; ++i) {
		for (int j = 0; j < num_count - 1 - i; ++j) {
			if (nums[j] > nums[j + 1]) {
				swap(nums[j], nums[j + 1]);
			}
		}
	}
}

//gets file name, reads file, assigns values to nums array, counts number of elems
void load_file(ifstream& in_file, int*& nums, int& num_count) {

	//check if nums already has smth
	if (nums != nullptr) {
		cout << "    resetting array\n";
		delete[] nums;
		nums = nullptr;
		num_count = 0;
	}

	//allocate memory in chunks for speed
	const int CHUNK_SIZE = 256;
	int capacity = CHUNK_SIZE;
	int* temp = new int[capacity]; //temp array for reallocation

	//get filename
	string in_file_name;
	get_input(in_file_name, "input file name. defaults to input.txt");

	in_file.open(in_file_name);

	if (!in_file.is_open()) {
		cerr << "    couldn't open file\n";
		return;
	}

	cout << "    reading contents of " << in_file_name << "..." ;
	int n;
	while (in_file >> n) {
		//reallocate more memory if there's not enough room
		if (num_count >= capacity) {
			capacity *= 2;
			int* new_nums = new int[capacity];

			for (int i = 0; i < num_count; ++i)
				new_nums[i] = temp[i];

			delete[] temp;
			temp = new_nums;
		}
		temp[num_count++] = n;
	}

	in_file.close();
	nums = temp;
	cout << " done!\n    added " << num_count << " numbers to array\n";
}

void print_menu(int num_elems, int c_time, int a_time) {
	//clear screen, set cursor
//	cout << "\033[2J\033[1;1H";

	//print header
	cout << "               RASM-5 C vs Assembly\n"
		<< "              File Element Count: ";
	cout << num_elems;
	cout << "\n\n------------------------------------------------\n";

	//print sort times
	cout << "        C++      Bubblesort Time: " << c_time << " secs\n"
		<< "        Assembly Bubblesort Time: " << a_time << " secs\n"
		<< "------------------------------------------------\n\n";

	//print options
	cout << "<1> Load input file (integers)\n"
		<< "<2> Sort using C Bubblesort algorithm\n"
		<< "<3> Sort using Assembly Bubblesort algorithm\n"
		<< "<4> Quit\n";
}

void get_input(int& buffer) {
	cout << "  > ";
	cin >> buffer;
	cin.ignore();
}

void get_input(int& buffer, string prompt) {
	cout << "\n  " << prompt << endl
		<< "  > ";
	cin >> buffer;
	cin.ignore();
}

void get_input(string& buffer, string prompt) {
	cout << "  " << prompt << endl
		<< "  > ";
	getline(cin, buffer);
}

void pause() {
	cout << "\n  press any key to continue... ;)"; // ;)
	cin.get();
}

void print_nums(int*& nums, int num_count) {
	for (int i = 0; i < num_count; ++i)
		cout << nums[i] << endl;
}

void output_to_file(int*& nums, int num_count, string out_file_name) {
	ofstream out_file(out_file_name);

	if (!out_file.is_open()) {
		cerr << "\ncouldn't open file :\\\n\n";
		return;
	}

	for (int i = 0; i < num_count; ++i)
		out_file << nums[i] << endl;

	out_file.close();
	cout << "    output array to " << out_file_name << endl;
}

void reset_array(int*& nums, int& num_count) {
	//check if nums already has smth
	if (nums != nullptr) {
		cout << "    deleting array! reload with choice <1>\n";
		delete[] nums;
		nums = nullptr;
		num_count = 0;
	}

}

int time_function(void (&func)(int*, int), int*& nums, int num_count) {
	//never done function passing before, didn't even think it was possible!
	auto start = chrono::steady_clock::now();
	func(nums, num_count);
	auto end = chrono::steady_clock::now();
	auto duration = chrono::duration_cast<chrono::seconds>(end - start);
	return duration.count();
}

