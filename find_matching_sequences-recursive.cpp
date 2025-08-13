#include <iostream>
#include <vector>
#include <utility>


using Sequence = std::pair <int, int>;


template <typename T>
void find_matching_sequences_helper(
	std::vector <Sequence> &result,
	const std::vector <T> &a,
	const std::vector <T> &b,
	int start,
	int pos) {

	// Base case
	if (pos >= (int) a.size()) {
		// Before returning, check if we were in the middle of a matching sequence
		// if "pos" > "start" means a sequence was active right up to the end
		if (pos - start > 0)
			result.push_back({start, pos - start});
		return;
	}
	// Recursive steps
	// State 1: we are NOT currently in a matching sequence
	// This is identified by the start and current positions being the same
	else if (pos - start == 0) {
		if (a[pos] == b[pos])
			// A new match begins. Keep "start" index and advance "pos"
			find_matching_sequences_helper(result, a, b, start, pos + 1);
		else
			// Still no match. Move the potential start of the next sequence forward
			find_matching_sequences_helper(result, a, b, pos + 1, pos + 1);
	}
	// State 2: We Were in a matching sequence, but it just ended
	// This is identified by "pos" > "start" and a mismatch at the current position
	else if (a[pos] != b[pos]) {
		// The sequence has ended, so record it. Its length is "pos" - "start"
		result.push_back({start, pos - start});
		// Reset the state by making a new recursive call where "start" == "pos"
		// This effectively says, "the old sequence is done, now re-evaluate from 'pos'"
		find_matching_sequences_helper(result, a, b, pos, pos);
	}
	// State 3: we ARe in a matching sequence, and its continue
	// This is the only remaining case "pos" > "start" and the elements match
	else
		find_matching_sequences_helper(result, a, b, start, pos + 1);
}

template <typename T>
std::vector <Sequence> find_matching_sequences(
	const std::vector <T> &a,
	const std::vector <T> &b) {

	std::vector <Sequence> result;
	find_matching_sequences_helper(result, a, b, 0, 0);
	return result;
}


int main() {
	std::vector <int> a = { 1, 2, 3, 4, 5, 6 };
	std::vector <int> b = { 1, 2, 4, 3, 5, 6 };
	std::vector <Sequence> result = find_matching_sequences(a, b);

	for (const auto &seq : result)
		std::cout << "(" << seq.first << ", " << seq.second << ")\n";
}
