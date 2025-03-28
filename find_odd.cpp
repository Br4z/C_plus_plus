#include <iostream>

int find_odd(int numbers[], int size) {
	int odd_number = 0;

	for (int i = 0; i < size; i++) {
		odd_number ^= numbers[i];
		std::cout << odd_number << " ";
	}

	return odd_number;
}

int main() {
	int arr[] = { 12, 12, 14, 90, 14, 14, 14 };
	int n = sizeof(arr) / sizeof(arr[0]);

	std::cout << "The odd occurring element is " << find_odd(arr, n);

	return 0;
}
