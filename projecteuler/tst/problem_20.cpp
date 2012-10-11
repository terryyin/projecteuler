#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "stream.h"

const int MAX_DIGIT_COUNT_OF_BIG_NUMBER = 1000;
typedef struct {
	int digits[MAX_DIGIT_COUNT_OF_BIG_NUMBER];
	int digit_count;
} BigNumber;

void BigNumber_initialize(BigNumber * self, int initial_number)
{
	memset(self->digits, 0, sizeof self->digits);
    self->digits[0] = initial_number;
    self->digit_count = 1;
}

static void BigNumber_regulate(BigNumber * self)
{
	int j;
    for(j = 0;j <= self->digit_count;j++){
        if(self->digits[j] >= 10){
            self->digits[j + 1] += (self->digits[j] - (self->digits[j] % 10)) / 10;
            self->digits[j] = self->digits[j] % 10;
            if(j == self->digit_count)
                self->digit_count++;
        }
    }
}

void BigNumber_multiply(BigNumber * self, int factor)
{
	int j;
    for(j = 0;j <= self->digit_count;j++)
        self->digits[j] *= factor;
    BigNumber_regulate(self);
}

void getfactorial(int n, BigNumber* out_result)
{
	int i;
    BigNumber_initialize(out_result, 1);
    for(i = 2; i <= n; i++)
        BigNumber_multiply(out_result, i);
}

int getsum(int* array, int k)
{
	int i, sum = 0;
    for(i = 0; i <= k; i++)
        sum += array[i];
    return sum;
}

TEST_GROUP(problem_20){
	BigNumber big_number;
};

TEST(problem_20, Count_of_all_digits_of_factorial_100){
    getfactorial(100, &big_number);
    CHECK_EQUAL(157, big_number.digit_count);
}
TEST(problem_20, Sum_of_all_digits_of_factorial_100_new_interface){
    getfactorial(100, &big_number);
    int sum = getsum(big_number.digits, big_number.digit_count);
    CHECK_EQUAL(648, sum);
}

TEST(problem_20, factorial_0){
    getfactorial(0, &big_number);
    int sum = getsum(big_number.digits, big_number.digit_count);
    CHECK_EQUAL(1, sum);
}

