#include <iostream>
#include <vector>
#include <iomanip>


int main() {
	const int n = 5;
	std::vector <std::vector <int>> A(n, std::vector <int>(n, 1));

	int z = 0;

	for (int i = 1; i < n; ++i) {
		for (int j = 0; j < n - i; ++j) {
			int k = i + j;
			A[j][k] = z++;
		}
	}

	// Print the resulting matrix.
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			// std::setw(3) adds padding to align the numbers neatly.
			std::cout << std::setw(3) << A[i][j];
		}
		std::cout << std::endl;
	}

	return 0;
}
