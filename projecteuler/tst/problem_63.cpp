/*
 * problem_62.cpp
 *
 *  Created on: Nov 2, 2011
 *      Author: yinterry
 *
 *      The 5-digit number, 16807=75, is also a fifth power. Similarly,
 *      the 9-digit number, 134217728=89, is a ninth power.

How many n-digit positive integers exist which are also an nth power?
 */

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "prime.h"
#include "project_euler.h"

typedef int integer;
int count_n_digit_positive_integers_which_are_also_nth_power(size_t n){
	integer root;
	int count = 0;
	for(root = 1; root < 10; root++) {
		size_t digit_count = get_digit_count(power(root, n));
		if (digit_count == n)
			count++;
	}

	return count;
}

TEST_GROUP(problem63)
{
};
TEST(problem63, count_1_digit_numbers){
	// 1,2,3,4,5,6,7,8,9
	LONGS_EQUAL(9, count_n_digit_positive_integers_which_are_also_nth_power(1));
}
TEST(problem63, count_2_digit_numbers){
	// 4, 5, 6, 7, 8, 9
	LONGS_EQUAL(6, count_n_digit_positive_integers_which_are_also_nth_power(2));
}
TEST(problem63, count_3_digit_numbers){
	LONGS_EQUAL(5, count_n_digit_positive_integers_which_are_also_nth_power(3));
}
TEST(problem63, count_all){
	int count = 0;
	for(size_t i = 1; ; i++) {
		size_t cnt = count_n_digit_positive_integers_which_are_also_nth_power(i);
		if (cnt == 0)
			break;
		count+= cnt;
	}
	LONGS_EQUAL(49, count+2);
}

