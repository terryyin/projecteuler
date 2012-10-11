#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "project_euler.h"
int triangle::_get_min_sum(int level, int pos)
{
	if (level == dim - 1)
		return data[level][pos];
	if (cache[level][pos] != NO_CACHE)
		return cache[level][pos];
	int left = _get_min_sum(level + 1, pos);
	int right = _get_min_sum(level + 1, pos + 1);
	if (right < left)
		left = right;

	return cache[level][pos] = data[level][pos] + left;
}

TEST_GROUP(problem67)
{

};

TEST(problem67, level_3_different_route)
{
	int t[4][4] =
	{
	{ 2 },
	{ 1, 4 },
	{ 10, 1, 1},
	{ 1, 1, 100 } };
	triangle tri(t[0], 4);
	LONGS_EQUAL(107, tri.get_max_sum());
}
#include "big_triangle.h"
TEST(problem67, mid)
{
	triangle tri(mid_trangle[0], 38);
	LONGS_EQUAL(2687, tri.get_max_sum());
}
TEST(problem67, big)
{
	triangle tri(big_trangle[0], 100);
	LONGS_EQUAL(7273, tri.get_max_sum());
}

