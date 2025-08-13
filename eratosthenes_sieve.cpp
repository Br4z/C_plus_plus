#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>


std::vector <int> generate_primes_up_to(const int n) {
	if (n < 2)
		return { }; // No primes exist below 2

	std::vector <bool> is_prime(n + 1, true);
	is_prime[0] = is_prime[1] = false;

	for (int p = 2; p * p <= n; p++) // p <= sqrt(n)
		if (is_prime[p])
			for (int i = p * p; i <= n; i += p)
				is_prime[i] = false;

	std::vector <int> prime_numbers;
	for (int p = 2; p <= n; p++)
		if (is_prime[p])
			prime_numbers.push_back(p);

	return prime_numbers;
}


int main(int argc, char* argv[]) {
	// Check if the user provided a command-line argument.
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <upper_limit>" << '\n';
		return 1;
	}

	int limit;
	try {
		limit = std::stoi(argv[1]);
	} catch (const std::exception &e) {
		std::cerr << "Error: Invalid number provided. Please enter a valid integer." << '\n';
		return 1;
	}

	const auto primes = generate_primes_up_to(limit);

	std::cout << "Prime numbers up to " << limit << ":\n";
	for (const int p : primes)
		std::cout << p << " ";
	std::cout << '\n';

	return 0;
}
