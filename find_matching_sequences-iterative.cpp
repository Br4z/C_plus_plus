#include <iostream>
#include <vector>
#include <utility>


using Sequence = std::pair <int, int>;


template <typename T>
std::vector <Sequence> find_matching_sequences(
	const std::vector <T> &a,
	const std::vector <T> &b) {

	if (a.size() != b.size())
		return {};

	std::vector <Sequence> result;
	const int n = a.size();
	int match_start_index = -1; // -1 to indicate we are NOT in a match

	for (int i = 0; i < n; i++) {
		if (a[i] == b[i]) {
			// If a match starts, record its starting position
			if (match_start_index == -1)
				match_start_index = i;
		} else {
			if (match_start_index != -1) {
				// If there is a mismatch and we WERE in a match, the sequence has ended
				result.push_back({match_start_index, i - match_start_index});
				match_start_index = -1; // Reset to indicate the match is over
			}
		}
	}

	// After the loop, check if a match was ongoing until the very end
	if (match_start_index != 1) {
		result.push_back({match_start_index, n - match_start_index});
	}

	return result;
}


int main() {
	std::vector <int> a = { 1, 2, 3, 4, 5, 6 };
	std::vector <int> b = { 1, 2, 4, 3, 5, 6 };
	std::vector <Sequence> result = find_matching_sequences(a, b);

	for (const auto &seq : result)
		std::cout << "(" << seq.first << ", " << seq.second << ")\n";
}
