#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <string>


float abundance_index(int n) {
	if (n <= 0)
		return 0;

	float sum_of_divisors = 0;
	int limit = static_cast <int>(sqrt(n));

	for (int i = 1; i <= limit; i++)
		if (n % i == 0) {
			sum_of_divisors += i;

			// Add the other half of the pair, but only if it is not the same number
			if (i * i != n)
				sum_of_divisors += n / i;
		}

	return sum_of_divisors / n;
}


int main() {
	const std::vector <int> numbers = { 6, 28, 30, 140, 26, 35, 2480 };
	std::map <double, std::vector <int>> friendly_groups;

	for (int n : numbers) {
		float index = abundance_index(n);
		friendly_groups[index].push_back(n);
	}

	std::cout << "The friendly numbers are:\n";
	for (const auto &[index, group] : friendly_groups) {
		if (group.size() > 1) {
			std::cout << "Abundance index: " << index << "\t";
			for (int number : group)
				std::cout << number << "\t";
			std::cout << '\n';
		}
	}

	return 0;
}
