#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "project_euler.h"
TEST_GROUP(phi){

};

TEST(phi, big){
	CHECK_EQUAL(510510, 2*3*5*7*11*13*17);
}

int largest_prime_no_greater_than(int n){
	int candidate = 2;
	while (n > candidate){
//		printf("n:%d, candidate:%d\n", n, candidate);
		if (n % candidate == 0){
			n--;
		}
		else {
			candidate++;
		}
	}
	return n;
}
TEST(phi, largest_prime){
	CHECK_EQUAL(2, largest_prime_no_greater_than(2));
	CHECK_EQUAL(47, largest_prime_no_greater_than(50));
//	CHECK_EQUAL(2, largest_prime_no_greater_than(96));
}
