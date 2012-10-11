#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "prime.h"
#include "project_euler.h"
#include "math.h"

typedef dec big_number;

int get_nth_fraction(size_t n){
	switch(n - 1) {
	case 0:
		return 2;
	case 1:
		return 1;
	case 2:
		return 2;
	}
	return  ((n % 3) == 0) ? n/3 * 2 : 1;
}
big_number get_nth_dec_numerator_of_e(size_t n){
	big_number prev_den = 1;
	big_number prev_num = 0;
	for(size_t i = n; i > 0; i--){
		big_number saved_num = prev_den;
		prev_den *= get_nth_fraction(i);
		prev_den += prev_num;
		prev_num = saved_num;
	}
	return prev_den;
}
long long get_nth_numerator_of_e(size_t n){
	return get_nth_dec_numerator_of_e(n).to_long();
}
TEST_GROUP(problem65)
{
};
TEST(problem65, first_numerator)
{
	LONGS_EQUAL(2, get_nth_numerator_of_e(1));
}
TEST(problem65, second_numerator)
{
	LONGS_EQUAL(3, get_nth_numerator_of_e(2));
}
TEST(problem65, third_numerator)
{
	LONGS_EQUAL(8, get_nth_numerator_of_e(3));
}
TEST(problem65, fourth_numerator)
{
	LONGS_EQUAL(11, get_nth_numerator_of_e(4));
}
TEST(problem65, more_numerator)
{
	LONGS_EQUAL(19, get_nth_numerator_of_e(5));
	LONGS_EQUAL(87, get_nth_numerator_of_e(6));
	LONGS_EQUAL(106, get_nth_numerator_of_e(7));
	LONGS_EQUAL(193, get_nth_numerator_of_e(8));
	LONGS_EQUAL(1264, get_nth_numerator_of_e(9));
	LONGS_EQUAL(1457, get_nth_numerator_of_e(10));
}
TEST(problem65, hundredth_numerator)
{
	LONGS_EQUAL(272, get_nth_dec_numerator_of_e(100).digits_sum());
}
#include <sys/socket.h>

int	(*platform_socket_stub)(int a, int b, int c) = NULL;

int	platform_socket(int a, int b, int c){
	if (platform_socket_stub != NULL)
		return platform_socket_stub(a,b,c);
	return socket(a,b,c);
}


