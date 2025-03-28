#include <iostream>


int main() {
	int n = 5;
	int** A = new int*[n];

	for (int i = 0; i < n; i++)
		A[i] = new int[n];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			A[i][j] = 1;

	int z = 0;

	for (int i = 1; i < n; i++)
		for (int j = 0; j < n - i; j++) {
			int k = i + j;

			A[j][k] = z++;
		}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			std::cout << A[i][j] << " ";
		std::cout << std::endl;
	}

	for (int i = 0; i < n; i++)
		delete[] A[i];
	delete[] A;

	return 0;
}
