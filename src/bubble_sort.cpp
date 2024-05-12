#include "driver.h"

void bubble_sort_cpp(int* nums, int num_count) {
	for (int i = 0; i < num_count - 1; ++i) {
		for (int j = 0; j < num_count - 1 - i; ++j) {
			if (nums[j] > nums[j + 1]) {
				swap(nums[j], nums[j + 1]);
			}
		}
	}
}
