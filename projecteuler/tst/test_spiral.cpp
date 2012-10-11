#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

int get_diagnal_of_spiral(int size, int coner){
	return (2* size + 1) * (2*size+1) - coner * size * 2;
}
TEST_GROUP(spiral){

};

TEST(spiral, first_coner){
	LONGS_EQUAL(9, get_diagnal_of_spiral(1, 0));
}
TEST(spiral, second_coner){
	LONGS_EQUAL(7, get_diagnal_of_spiral(1, 1));
}
TEST(spiral, third_coner){
	LONGS_EQUAL(5, get_diagnal_of_spiral(1, 2));
}
TEST(spiral, fourth_coner){
	LONGS_EQUAL(3, get_diagnal_of_spiral(1, 3));
}
TEST(spiral, next_circle1){
	LONGS_EQUAL(25, get_diagnal_of_spiral(2, 0));
}
TEST(spiral, next_circle2){
	LONGS_EQUAL(21, get_diagnal_of_spiral(2, 1));
}
TEST(spiral, next_circle3){
	LONGS_EQUAL(17, get_diagnal_of_spiral(2, 2));
}
TEST(spiral, next_circle4){
	LONGS_EQUAL(13, get_diagnal_of_spiral(2, 3));
}
TEST(spiral, next_next){
	LONGS_EQUAL(49, get_diagnal_of_spiral(3, 0));
	LONGS_EQUAL(43, get_diagnal_of_spiral(3, 1));
}
