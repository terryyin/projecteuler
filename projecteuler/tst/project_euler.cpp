#include "math.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "project_euler.h"
int is_prime(int num, long previous_primes[], int count)
{
	int max = sqrt(num);
	for (int i = 0; i < count && previous_primes[i] <= max; i++)
		if (num % previous_primes[i] == 0)
			return 0;
	return 1;
}
int factorial(int n) {
	int result = 1;
	for (;n>0; n--) result *= n;
	return result;
}
long long power(long long n, int e) {
	long long result = 1;
	for (int i = 0; i < e; i ++) result*= n;
	return result;
}

int get_digit_count(long long n)
{
	if (n >= 1000000000000000000)
		return 19;
	if (n >= 100000000000000000)
		return 18;
	if (n >= 10000000000000000)
		return 17;
	if (n >= 1000000000000000)
		return 16;
	if (n >= 100000000000000)
		return 15;
	if (n >= 10000000000000)
		return 14;
	if (n >= 1000000000000)
		return 13;
	if (n >= 100000000000)
		return 12;
	if (n >= 10000000000)
		return 11;
	if (n >= 1000000000)
		return 10;
	if (n >= 100000000)
		return 9;
	if (n >= 10000000)
		return 8;
	if (n >= 1000000)
		return 7;
	if (n >= 100000)
		return 6;
	if (n >= 10000)
		return 5;
	if (n >= 1000)
		return 4;
	if (n >= 100)
		return 3;
	if (n >= 10)
		return 2;
	return 1;
}

long long get_upper_scale(long long n)
{
	static const long long scales[] =
	{1000000000000, 100000000000, 10000000000, 1000000000, 100000000, 10000000, 1000000, 100000, 10000, 1000, 100, 10, 1 , -1};
	int i;
	for (i = 0; scales[i] > n; i++)
		;
	return scales[i - 1];
}

