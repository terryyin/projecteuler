/*
 * problem_66.cpp

 Consider quadratic Diophantine equations of the form:

 x2 Ð Dy2 = 1

 For example, when D=13, the minimal solution in x is 6492 Ð 131802 = 1.

 It can be assumed that there are no solutions in positive integers when D is square.

 By finding minimal solutions in x for D = {2, 3, 5, 6, 7}, we obtain the following:

 32 Ð 222 = 1
 22 Ð 312 = 1
 92 Ð 542 = 1
 52 Ð 622 = 1
 82 Ð 732 = 1

 Hence, by considering minimal solutions in x for D  7, the largest x is obtained when D=5.

 Find the value of D  1000 in minimal solutions of x for which the largest value of x is obtained.
 */

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "prime.h"
#include "project_euler.h"
#include "math.h"
#include "continued_fraction.h"


integer get_factor(integer n, integer last){
	integer max = sqrt(n);
	for (integer i = last; i < max; i++){
		if (n% i == 0)
			return i;
	}
	return n;
}
integer remove_factor(integer& m, integer& n, integer last){
	integer max = m > n ? m:n;
	for (integer i = 2; i <= max; i++){
		if (n%i == 0) {
			n/= i;
			return i;
		}
		if (m%i == 0) {
			m/= i;
			return i;
		}
	}
	integer saved = m * n;
	m = 1;
	n = 1;
	return saved;
}
integer remove_factor(integer& m, integer last){
	integer max = m;
	for (integer i = last; i <= max; i++){
		if (m%i == 0) {
			m/= i;
			return i;
		}
	}
	integer saved = m;
	m = 1;
	return saved;
}
bool my_sqrt(integer add1, integer sub1)
{
	bool look_for_pair = false;
	integer last_p = 2;
	while(add1!=1 || sub1 != 1){
		integer p = remove_factor(add1, sub1, last_p);
		if (look_for_pair){
			if (last_p != p)
				return false;
		}
		else {
			last_p = p;
		}
		look_for_pair = !look_for_pair;
	}
    	return !look_for_pair;
}
inline bool my_sqrt(integer add1)
{
	integer r = sqrt(add1);
	return r * r == add1;
	bool look_for_pair = false;
	integer last_p = 2;
	while(add1!=1){
		integer p = remove_factor(add1, last_p);
		if (look_for_pair){
			if (last_p != p)
				return false;
		}
		else {
			last_p = p;
		}
		look_for_pair = !look_for_pair;
	}
    	return !look_for_pair;
}

bool exist_y_for_x_and_D1(integer x, int D)
{
	integer add1 = x+1;
	integer sub1 = x -1;
	integer p = 2;
	while(D != 1){
		p = get_factor(D, p);
		D /= p;
		if (add1 %p == 0)
			add1/= p;
		else if (sub1 % p == 0)
			sub1/= p;
		else return false;
	}
	return my_sqrt(add1, sub1);
}
inline bool exist_y_for_x_and_D(integer x, integer D)
{
	integer t = x * x -1;
	if (t % D != 0)
		return false;
	t = (x * x -1)/D;
	return my_sqrt(t);
}
integer get_biggest_prime_factor(integer n){
	integer factor = 2;
	while (n != 1){
		if (n % factor == 0)
			n /= factor;
		else
			factor ++;
	}
	return factor;
}

template <typename BigNum>
BigNum get_minimal_solution_of_x(integer D)
{
	Fractions<BigNum> f(D);
	int level = 0;
	while (1)
	{
		ContinuedFraction<BigNum> cf(&f, level++);
		BigNum x = cf.get_numerator();
		BigNum y = cf.get_denumerator();
		if (x * x - y * y * D == 1)
			return cf.get_numerator();
	}
}

TEST_GROUP(problem66)
{
};
TEST(problem66, remove_factor)
{
	integer m = 2, n = 2;
	LONGS_EQUAL(2, remove_factor(m, n, 2));
}
TEST(problem66, biggest_factor)
{
	LONGS_EQUAL(2, get_biggest_prime_factor(2));
	LONGS_EQUAL(3, get_biggest_prime_factor(3));
	LONGS_EQUAL(2, get_biggest_prime_factor(4));
	LONGS_EQUAL(7, get_biggest_prime_factor(56));
}
TEST(problem66, mysqrt)
{
	CHECK(my_sqrt(2, 2));
	CHECK(!my_sqrt(2, 3));
	CHECK(my_sqrt(2, 8));
	CHECK(!my_sqrt(4, 3));
}
TEST(problem66, when_D_is_2)
{
	LONGS_EQUAL(3, get_minimal_solution_of_x<integer>(2));
}
TEST(problem66, when_D_is_3)
{
	LONGS_EQUAL(2, get_minimal_solution_of_x<integer>(3));
}
TEST(problem66, when_D_is_13)
{
	LONGS_EQUAL(649, get_minimal_solution_of_x<dec>(13).to_long());
}
TEST(problem66, when_D_is_991)
{
	LONGS_EQUAL(-2725358667350517808, get_minimal_solution_of_x<dec>(991).to_long());
}
TEST(problem66, when_D_is_61)
{
	LONGS_EQUAL(1766319049, get_minimal_solution_of_x<integer>(61));
}

int get_max_D(int MAX){
	dec max_x = 0;
	int max_D = 0;
	for (int D = 2; D <= MAX; D++)
	{
		int sqrtD = sqrt(D);
		if (sqrtD * sqrtD != D)
		{
			dec x = get_minimal_solution_of_x<dec>(D);
			fflush(0);
			if (x > max_x)
			{
				max_x = x;
				max_D = D;
			}
		}
	}
	return max_D;
}
TEST(problem66, D_for_minimal_x)
{
	LONGS_EQUAL(661, get_max_D(1000));
}
