#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "prime.h"
#include "project_euler.h"
TEST_GROUP(dec){

};
TEST(dec, mulitply_equal)
{
	dec d(1);
	LONGS_EQUAL(1, d.get_digit(0));
	LONGS_EQUAL(1, d.get_count());
	d *= 2;
	LONGS_EQUAL(2, d.get_digit(0));
	LONGS_EQUAL(1, d.get_count());
	d *= 99;
	LONGS_EQUAL(3, d.get_count());
	LONGS_EQUAL(8, d.get_digit(0));
	LONGS_EQUAL(9, d.get_digit(1));
	LONGS_EQUAL(1, d.get_digit(2));
}
TEST(dec, mulitply)
{
	dec d1(2), d2(3);
	LONGS_EQUAL(6, (d1*d2).to_long());
}
TEST(dec, mulitply_bigger_number)
{
	dec d1(123), d2(456);
	LONGS_EQUAL(123*456, (d1*d2).to_long());
}
TEST(dec, mulitply_dec_and_integer)
{
	dec d1(2), d2(3);
	LONGS_EQUAL(24, (d1*d2*4).to_long());
}
IGNORE_TEST(dec, subtract)
{
	dec d1(2), d2(3);
	LONGS_EQUAL(18, (d1*d2*4 - d1*d2).to_long());
}
TEST(dec, subtract_0s)
{
	dec d1(0), d2(0);
	LONGS_EQUAL(0, (d1-d2).to_long());
}
TEST(dec, subtract_234_23)
{
	dec d1(234), d2(23);
	LONGS_EQUAL(211, (d1-d2).to_long());
}
TEST(dec, subtract_12_3)
{
	dec d1(12), d2(3);
	LONGS_EQUAL(9, (d1-d2).to_long());
}
TEST(dec, subtract_1234_567)
{
	dec d1(1234), d2(567);
	LONGS_EQUAL(1234-567, (d1-d2).to_long());
}
TEST(dec, subtract_1_2)
{
	dec d1(1), d2(2);
	LONGS_EQUAL(1-2, (d1-d2).to_long());
}
TEST(dec, subtract_1_23)
{
	dec d1(1), d2(23);
	LONGS_EQUAL(1-23, (d1-d2).to_long());
}
TEST(dec, equal)
{
	dec d1(1), d2(23);
	CHECK(d1 * d2 == 23);
}
TEST(dec, great)
{
	CHECK(dec(2)>dec(1));
}
TEST(dec, not_great)
{
	CHECK(!(dec(2)>dec(3)));
}
