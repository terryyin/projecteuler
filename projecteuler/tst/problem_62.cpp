/*
 * problem_62.cpp
 *
 *  Created on: Nov 2, 2011
 *      Author: yinterry
 *
 *      The cube, 41063625 (3453), can be permuted to produce two other cubes:
 *      56623104 (3843) and 66430125 (4053). In fact, 41063625 is the smallest
 *      cube which has exactly three permutations of its digits which are also
 *      cube.
 *
 *      Find the smallest cube for which exactly five permutations of its
 *      digits are cube.
 *
 */

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "prime.h"
#include "project_euler.h"
#include <map>


typedef long long cube_number_t;

cube_number_t DIGIT(cube_number_t n, cube_number_t scale){
	return n /scale % 10;
}
cube_number_t SWITCH_DIGIT(cube_number_t n, cube_number_t scale){
	return n - DIGIT(n, scale) * 9 * (scale/10) + DIGIT(n, scale/10) * 9 * (scale/10);
}
cube_number_t get_lowest_permutation(cube_number_t number){
	cube_number_t i, old = number;
	for (i = 10; i < old;i *=10) {
		for(cube_number_t scale = 10; scale < old; scale *= 10)
			if (DIGIT(number, scale) > DIGIT(number, scale/10))
				number = SWITCH_DIGIT(number, scale);
	}
	return number+i;
}
class per_cube{
public:
	per_cube():cnt(0){}
	void add(int root){
		smallest[cnt++] = root;
	}
	int getCount() {return cnt;}
	int getSmallest() {return smallest[0];}
	int getRoot(int n) {return smallest[n];}
private:
	int smallest[5];
	int cnt;
};

class CubePermutation
{
public:
	CubePermutation(){}
	cube_number_t get_lowest_perumtation_of_cube(int root){
		return get_lowest_permutation((cube_number_t)root * root * root);
	}
	size_t add_to_cube_permutation_hash(int root)
	{
		cube_number_t cube = get_lowest_perumtation_of_cube(root);
		counts[cube].add(root);
		return counts[cube].getCount();
	}
	per_cube* get_smallest_permutation_of_cube(int root)
	{
		return &counts[get_lowest_perumtation_of_cube(root)];
	}
	per_cube* get_smallest_n_cube_permutations(size_t n)
	{
		int i = 1;
		while (add_to_cube_permutation_hash(i) < n)
			i++;
		return get_smallest_permutation_of_cube(i);
	}
private:
	std::map<cube_number_t, per_cube> counts;
};
TEST_GROUP(problem62)
{
};

TEST(problem62, get_lowest_perumtation_of_cube)
{
	LONGS_EQUAL(11,CubePermutation().get_lowest_perumtation_of_cube(1));
	LONGS_EQUAL(18,CubePermutation().get_lowest_perumtation_of_cube(2));
	LONGS_EQUAL(146,CubePermutation().get_lowest_perumtation_of_cube(4));
	LONGS_EQUAL(1125,CubePermutation().get_lowest_perumtation_of_cube(8));
	LONGS_EQUAL(10001133,CubePermutation().get_lowest_perumtation_of_cube(101));
	LONGS_EQUAL(124578,CubePermutation().get_lowest_perumtation_of_cube(35));
	LONGS_EQUAL(124578,CubePermutation().get_lowest_perumtation_of_cube(38));
	LONGS_EQUAL(11124468,CubePermutation().get_lowest_perumtation_of_cube(104));
}
TEST(problem62, get_smallest_one_cube_permutation)
{
	LONGS_EQUAL(1,CubePermutation().get_smallest_n_cube_permutations(1)->getRoot(0));
}
TEST(problem62, get_smallest_two_cube_permutation)
{
	LONGS_EQUAL(5,CubePermutation().get_smallest_n_cube_permutations(2)->getRoot(0));
	LONGS_EQUAL(8,CubePermutation().get_smallest_n_cube_permutations(2)->getRoot(1));
}
TEST(problem62, get_smallest_3_cube_permutation)
{
	LONGS_EQUAL(345,CubePermutation().get_smallest_n_cube_permutations(3)->getRoot(0));
}
TEST(problem62, get_smallest_5_cube_permutation)
{
	LONGS_EQUAL(5027,CubePermutation().get_smallest_n_cube_permutations(5)->getRoot(0));
}
TEST(problem62, get_add_to_permutation_hash)
{
	CubePermutation cp;
	LONGS_EQUAL(1, cp.add_to_cube_permutation_hash(1));
	LONGS_EQUAL(1, cp.add_to_cube_permutation_hash(2));
}
