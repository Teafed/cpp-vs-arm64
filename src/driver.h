#pragma once

#include <iostream>
#include <cstring>
#include <fstream>
#include <chrono>
using namespace std;

//bubble sorts
extern "C" void bubble_sort_ass(int*, int); //assembly bubble sort
void bubble_sort_cpp(int* nums, int num_count); //c++ bubble sort

//other prototypes
void load_file(ifstream& in_file, int*& nums, int& num_count);
void get_input(int&);
void get_input(int&, string);
void get_input(string&, string);
void print_menu(int num_elems, int c_time, int a_time);
void output_to_file(int*& nums, int num_count, string out_file_name);
void print_nums(int*& nums, int num_count);
void pause();
int time_function(void (&func)(int*, int), int*& nums, int num_count);
void reset_array(int*& nums, int& num_count);
