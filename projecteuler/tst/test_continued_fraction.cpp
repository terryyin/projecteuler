#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "continued_fraction.h"

TEST_GROUP(Fractions)
{
};

TEST(Fractions, get_period_of_sqrt_2){
	Fractions<integer> f(2);
	LONGS_EQUAL(1, f.getPeriod());
}
TEST(Fractions, get_period_of_sqrt_3){
	Fractions<integer> f(3);
	LONGS_EQUAL(2, f.getPeriod());
}
TEST(Fractions, get_fractions_of_sqrt_2){
	Fractions<integer> f(2);
	LONGS_EQUAL(1, f.getFraction(0));
	LONGS_EQUAL(2, f.getFraction(1));
	LONGS_EQUAL(2, f.getFraction(2));
	LONGS_EQUAL(2, f.getFraction(3));
}
TEST(Fractions, get_fractions_of_sqrt_3){
	Fractions<integer> f(3);
	LONGS_EQUAL(1, f.getFraction(0));
	LONGS_EQUAL(1, f.getFraction(1));
	LONGS_EQUAL(2, f.getFraction(2));
	LONGS_EQUAL(1, f.getFraction(3));
	LONGS_EQUAL(2, f.getFraction(4));
}
TEST_GROUP(continued_fraction)
{
};

TEST(continued_fraction, get_first_sqrt_of_2){
	Fractions<integer> f(2);
	ContinuedFraction<integer> cf(&f, 0);
	LONGS_EQUAL(1, cf.get_numerator());
	LONGS_EQUAL(1, cf.get_denumerator());
}
TEST(continued_fraction, get_next_sqrt_of_2){
	Fractions<integer> f(2);
	ContinuedFraction<integer> cf(&f, 1);
	LONGS_EQUAL(3, cf.get_numerator());
	LONGS_EQUAL(2, cf.get_denumerator());
}
TEST(continued_fraction, get_next_next_sqrt_of_2){
	Fractions<integer> f(2);
	ContinuedFraction<integer> cf(&f, 2);
	LONGS_EQUAL(7, cf.get_numerator());
	LONGS_EQUAL(5, cf.get_denumerator());
}
TEST(continued_fraction, get_first_sqrt_of_3){
	Fractions<integer> f(3);
	ContinuedFraction<integer> cf(&f, 0);
	LONGS_EQUAL(1, cf.get_numerator());
	LONGS_EQUAL(1, cf.get_denumerator());
}
TEST(continued_fraction, get_next_sqrt_of_3){
	Fractions<integer> f(3);
	ContinuedFraction<integer> cf(&f, 1);
	LONGS_EQUAL(2, cf.get_numerator());
	LONGS_EQUAL(1, cf.get_denumerator());
}
