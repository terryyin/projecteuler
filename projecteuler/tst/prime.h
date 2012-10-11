#ifndef PRIME_H_
#define PRIME_H_

#include "math.h"
int is_prime(int num, long previous_primes[], int count);
class prime {
public:
	prime() {memset(previous_primes, 0, sizeof(previous_primes));count = 0;}
	bool is_prime(long long num){
		if (num < 2)
			return 0;
		long long  max = sqrt(num);
		if (num != 2 && num % 2 == 0)
			return 0;
		for (long long i = 3; i <= max;i+=2)
			if (num % i == 0)
				return false;

		return true;
	}
	int getNextPrime(int p){
		do p++; while (!is_prime(p));
		return p;
	}
private:
	static const int buf_size = 30000;
	int previous_primes[buf_size];
	int count;
};

#endif /* PRIME_H_ */
