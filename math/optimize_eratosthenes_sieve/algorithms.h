#include <vector>
#include <unordered_map>
#include <stdint.h>

using namespace std;

/*
 * Normal eratosthenes sieve algorithm
 * Time complexity: O(NloglogN)
 * */
int64_t build_sieve(int n){
	vector<int> factor(n+1);
	// factor[i] = x means that x is the smallest prime factor of i 
	for(int i = 2; i <= n; ++i)
		factor[i] = i;

	for(int i = 4; i <= n; i+=2) factor[i] = 2;
	for(int i = 3; i*i <= n; ++i)
		if(factor[i] == i)
			for(int j = i*i; j <= n; j+=i)
				if(factor[j] == j)
					factor[j] = i;
	int64_t sum = 0;
	for(int i = 2; i <= n; ++i)
		sum += factor[i] * (factor[i] == i);
	return sum;
}

/*
 * Native sieve algorithm
 * Time complexity: O(NlogN)
 * */
int64_t native_build_sieve(int n) {
	int r = sqrt(n);

	vector<int64_t> S(n+1);
	// S[i] is the sum of all primes that <= i
	for(int i = 2; i <= n; ++i)
		S[i] = i * (i + 1) / 2 - 1; // 1 is not a prime

	for(int p = 2; p <= r; ++p) {
		// is S[p] > S[p-1] => p is a prime
		if(S[p] > S[p-1])
			for(int i = n; i >= p*p; --i) {
				// is p is prime, we need to substract all values that p is a multiple of x
				// NOTE: S(i/p) - S(p-1) is the sum of all values in range [p, i/p]
				S[i] -= (S[i / p] - S[p - 1]) * p;
			}
	}
	return S[n];
}

int64_t optimized_build_seive(int n) {
	
}
