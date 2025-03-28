#include <iostream>
#include <map>
#include <vector>


float abundancy_index(int number) {
	float output = 0;

	for (int i = 1; i <= number; i++)
		if (number % i == 0)
			output += i;

	return (float) output / number;
}

int main() {
	int numbers[] = { 6, 28, 30, 140, 26, 35, 2480 };
	int numbers_length = sizeof(numbers) / sizeof(int);

	std::map <float, std::vector <int>> map;

	for (int i = 0; i < numbers_length; i++) {
		int abundancy_index_ = abundancy_index(numbers[i]);

		if (map.find(abundancy_index_) != map.end())
			map[abundancy_index_].push_back(numbers[i]);
		else
			map[abundancy_index_] = std::vector <int> { numbers[i] };
	}

	std::string output = "The friendly numbers are\n";

	for (const auto &[abundancy_index, numbers] : map) {
		int numbers_size = numbers.size();
		if (numbers_size > 1) {
			output += "Abudancy index: " + std::to_string(abundancy_index) + '\t';
			for (const auto &number : numbers)
				output += std::to_string(number) + '\t';

			output += '\n';
		}
	}

	std::cout << output;

	return 0;
}
