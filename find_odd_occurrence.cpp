#include <iostream>
#include <vector>
#include <numeric>
#include <functional>


int find_odd_occurrence(const std::vector<int> &numbers) {
	return std::accumulate(numbers.begin(), numbers.end(), 0, std::bit_xor <int>());
	// In vanilla C++ "^" is the XOR operator
}


int main() {
	const std::vector<int> my_numbers = { 12, 12, 14, 90, 14, 14, 14 };

	// The function call is cleaner, no need to pass the size manually.
	std::cout << "The element with an odd number of occurrences is "
			  << find_odd_occurrence(my_numbers) << '\n';

	return 0;
}
