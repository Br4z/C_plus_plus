#include <iostream>
#include <bits/stdc++.h>
#include <vector>


void eratosthenes_sieve(int n) {
	bool primes[n + 1];
	std::memset(primes, true, sizeof(primes));

	for (int i = 2; i * i <= n; i++) {
		if (primes[i]) {
			for (int j = i * i; j <= n; j += i) {
				primes[j] = false;
			}
		}
	}

	for (int i = 2; i <= n; i++) {
		if (primes[i]) std::cout << i << " ";
	}
}

int main(int argc, char* argv[]) {
	eratosthenes_sieve(std::stoi(argv[1]));
}
