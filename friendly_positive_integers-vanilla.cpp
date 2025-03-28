#include <iostream>


float abundancy_index(int number) {
	float output = 0;

	for (int i = 1; i <= number; i++)
		if (number % i == 0)
			output += i;

	return (float) output / number;
}

template <typename T>
bool is_not_in(T elements[], int elements_length, T element) {
	for (int i = 0; i < elements_length; i++)
		if (elements[i] == element)
			return false;
	return true;
}

template <typename T>
T* unique_numbers(T elements[], int elements_length, int &unique_numbers_length) {
	T* unique_numbers = new T[elements_length];
	unique_numbers_length = 0;

	for (int i = 0; i < elements_length; i++) {
		T number = elements[i];

		if (is_not_in(unique_numbers, unique_numbers_length, number))
			unique_numbers[unique_numbers_length++] = number;
	}

	return unique_numbers;
}

template <typename T>
int count_element(T elements[], int elements_length, T element) {
	int total = 0;

	for (int i = 0; i < elements_length; i++)
		if (elements[i] == element)
			total++;

	return total;
}


int main() {
	int numbers[] = { 6, 28, 30, 140, 26, 35, 2480 };
	int numbers_length = sizeof(numbers) / sizeof(int);

	float* abundancy_indexes = new float[numbers_length];

	for (int i = 0; i < numbers_length; i++)
		abundancy_indexes[i] = abundancy_index(numbers[i]);

	int unique_abundancy_indexes_length = 0;
	float* unique_abundancy_indexes = unique_numbers(abundancy_indexes, numbers_length, unique_abundancy_indexes_length);


	std::string output = "The friendly numbers are\n";

	for (int i = 0; i < unique_abundancy_indexes_length; i++) {
		float abundancy_index = unique_abundancy_indexes[i];
		int abundancy_index_count = count_element(abundancy_indexes, numbers_length, abundancy_index);

		if (abundancy_index_count > 1) {
			output += "Abudancy index: " + std::to_string(abundancy_index) + '\t';
			for (int i, count = 0; count < abundancy_index_count; i++)
				if (abundancy_indexes[i] == abundancy_index) {
					output += std::to_string(numbers[i]) + '\t';
					count++;
				}
			output += '\n';
		}
	}

	std::cout << output;

	delete[] abundancy_indexes;
	delete[] unique_abundancy_indexes;

	return 0;
}
