#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "prime.h"
#include "project_euler.h"
#include "continued_fraction.h"
int get_period_of_sqrt(int n)
{
	int rt = sqrt(n);
	int remain = n - rt * rt;
	if (remain == 0)
		return 0;
	divider_of_sqrt first(n);
	first.next();
	divider_of_sqrt next(first);
	int cnt = 1;
	while (!(next == first))
	{
		cnt++;
		next.next();
	}

	return cnt;
}
TEST_GROUP(problem64)
{
};
TEST(problem64, divider_of_sqrt_2)
{
	divider_of_sqrt d(2);
	LONGS_EQUAL(1, d.get_plus());
}
TEST(problem64, divider_of_sqrt_5)
{
	divider_of_sqrt d(5);
	LONGS_EQUAL(2, d.get_plus());
}
TEST(problem64, next_divider_of_sqrt_2)
{
	divider_of_sqrt d(2);
	divider_of_sqrt d2(d);
	divider_of_sqrt d3(d2);
	LONGS_EQUAL(2, d2.get_plus());
	LONGS_EQUAL(2, d3.get_plus());
}
TEST(problem64, next_divider_of_sqrt_3)
{
	divider_of_sqrt d(3);
	divider_of_sqrt d2(d);
	divider_of_sqrt d3(d2);
	LONGS_EQUAL(1, d2.get_plus());
	LONGS_EQUAL(2, d3.get_plus());
}
TEST(problem64, next_divider_of_sqrt_23)
{
	divider_of_sqrt d(23);
	divider_of_sqrt d2(d);
	divider_of_sqrt d3(d2);
	divider_of_sqrt d4(d3);
	divider_of_sqrt d5(d4);
	divider_of_sqrt d6(d5);
	LONGS_EQUAL(1, d2.get_plus());
	LONGS_EQUAL(3, d3.get_plus());
	LONGS_EQUAL(1, d4.get_plus());
	LONGS_EQUAL(8, d5.get_plus());
	LONGS_EQUAL(1, d6.get_plus());
	CHECK(!(d2 == d4));
	CHECK((d2 == d6));
}

TEST(problem64, get_period_of_sqrtb_1)
{
	LONGS_EQUAL(0, get_period_of_sqrt(1));
}
TEST(problem64, get_period_of_sqrt_2)
{
	LONGS_EQUAL(1, get_period_of_sqrt(2));
}
TEST(problem64, get_period_of_sqrt_3)
{
	LONGS_EQUAL(2, get_period_of_sqrt(3));
}
TEST(problem64, get_period_of_sqrt_4)
{
	LONGS_EQUAL(4, get_period_of_sqrt(23));
}
TEST(problem64, problem64)
{
	int count = 0;
	for (int i = 1; i <= 10000; i++){
		int n = get_period_of_sqrt(i);
		if (n != 0 && n%2==1)
			count++;
	}
	LONGS_EQUAL(1322, count);
}
