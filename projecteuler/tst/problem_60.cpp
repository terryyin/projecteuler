/*

 The primes 3, 7, 109, and 673, are quite remarkable. By taking any
 two primes and concatenating them in any order the result will always
 be prime. For example, taking 7 and 109, both 7109 and 1097 are prime.
 The sum of these four primes, 792, represents the lowest sum for a
 set of four primes with this property.

 Find the lowest sum for a set of five primes for which any two primes
 concatenate to produce another prime.
 */
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "prime.h"
#include "project_euler.h"
class ConcatenatingPrimes
{
public:
	long long FindSmallestSumOf(int count, long long prevPrimes[],
			int prevPrimeCount, long long limit = 1000)
	{
		long long i = 2, sum = 0, result = 0;
		if (prevPrimeCount > 0)
			i = prevPrimes[prevPrimeCount - 1];
		do
		{
			do
				i = p.getNextPrime(i);
			while ((!concatenatable(i, prevPrimes, prevPrimeCount)) && i
					< limit / count);

			if (i >= limit / count)
				break;
			if (count == 1)
				return i;
			sum = 0;
			prevPrimes[prevPrimeCount] = i;
			sum = FindSmallestSumOf(count - 1, prevPrimes, prevPrimeCount + 1,
					limit - i);
			if (sum != 0)
			{
				result = limit = sum + i;
			}
		} while (i < limit / count);
		return result;
	}
	long long getAt(int index)
	{
		return result[index];
	}
private:
	bool concatenatable(long long n, long long prevPrimes[], int prevPrimeCount)
	{
		for (int i = 0; i < prevPrimeCount; i++)
			if ((!p.is_prime(connect(n, prevPrimes[i]))) || (!p.is_prime(
					connect(prevPrimes[i], n))))
				return false;
		return true;
	}
	long long connect(long long m, long long n)
	{
		return get_upper_scale(n) * m + n;
	}
	int result[10];
	prime p;
};
TEST_GROUP(problem60)
{

};

TEST(problem60, get_upper_scale)
{
	LONGS_EQUAL(10, get_upper_scale(1));
	LONGS_EQUAL(10, get_upper_scale(8));
	LONGS_EQUAL(100, get_upper_scale(10));
	LONGS_EQUAL(1000000000, get_upper_scale(987654321));
}
TEST(problem60, find_one)
{
	ConcatenatingPrimes cp;
	long long prev[] =
	{ 3 };
	LONGS_EQUAL(3, cp.FindSmallestSumOf(1, prev, 0));
}

TEST(problem60, find_the_last_one_with_prev_3)
{
	ConcatenatingPrimes cp;
	long long prev[] =
	{ 3 };
	LONGS_EQUAL(7, cp.FindSmallestSumOf(1, prev, 1));
}
TEST(problem60, find_the_last_one_with_prev_7)
{
	ConcatenatingPrimes cp;
	long long prev[] =
	{ 7 };
	LONGS_EQUAL(19, cp.FindSmallestSumOf(1, prev, 1));
}
TEST(problem60, find_the_last_one_with_prev_3_and_7)
{
	ConcatenatingPrimes cp;
	long long prev[] =
	{ 3, 7 };
	LONGS_EQUAL(109, cp.FindSmallestSumOf(1, prev, 2));
}
TEST(problem60, find_the_last_one_with_prev_3_7_109)
{
	ConcatenatingPrimes cp;
	long long prev[] =
	{ 3, 7, 109 };
	LONGS_EQUAL(673, cp.FindSmallestSumOf(1, prev, 3));
}
TEST(problem60, find_the_last_one_with_small_limit)
{
	ConcatenatingPrimes cp;
	long long prev[] =
	{ 3, 7, 109 };
	LONGS_EQUAL(0, cp.FindSmallestSumOf(1, prev, 3, 200));
}
TEST(problem60, find_two)
{
	ConcatenatingPrimes cp;
	long long prev[10] =
	{ };
	LONGS_EQUAL(10, cp.FindSmallestSumOf(2, prev, 0));
}
TEST(problem60, find_three)
{
	ConcatenatingPrimes cp;
	long long prev[10] =
	{ };
	LONGS_EQUAL(107, cp.FindSmallestSumOf(3, prev, 0,110));
	LONGS_EQUAL(0, cp.FindSmallestSumOf(3, prev, 0,107));
}
TEST(problem60, find_four)
{
	ConcatenatingPrimes cp;
	long long prev[10] =
	{ };
	LONGS_EQUAL(792, cp.FindSmallestSumOf(4, prev, 0));
}
IGNORE_TEST(problem60, find_five){
	ConcatenatingPrimes cp;
	long long  prev[10];
	LONGS_EQUAL(26033, cp.FindSmallestSumOf(5, prev, 0, 100000));
}


