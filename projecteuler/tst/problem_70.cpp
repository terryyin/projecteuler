#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "project_euler.h"
#include "prime.h"
#include "math.h"
#include "list"

using namespace std;

class PhiFactors {
public:
	PhiFactors(int prime_factor) {
		m_prime_factor = prime_factor;
	}
	double getRate() {
		return ((double) (m_prime_factor - 1)) / m_prime_factor;
	}
private:
	int m_prime_factor;
};
class PhiRate {
public:
	PhiRate(int prime_factor) {
		m_prime_factor = prime_factor;
		m_phis.push_back(new PhiFactors(prime_factor));
	}
	~PhiRate() {
		list<PhiFactors *>::iterator i;
		for (i = m_phis.begin(); i != m_phis.end(); ++i)
			delete *i;

	}
	double getRate() {
		return ((double) (m_prime_factor - 1)) / m_prime_factor;
	}
	PhiRate& moveToSmallerPhiRate() {
		m_prime_factor--;
		while (!p.is_prime(m_prime_factor))
			m_prime_factor--;
		return *this;
	}
private:
	list<PhiFactors *> m_phis;
	int m_prime_factor;
	prime p;
};
static int get_biggest_single_prime_factor_smaller_than(int max) {
	prime p;
	int result = sqrt(max);
	while (!p.is_prime(result))
		result--;
	return result;
}
;
static int get_phi_with_factor(int number, int factor) {
	return number * (factor - 1) / factor;
}
static int get_n_with_biggest_permutation_phi_rate(int max) {
	int max_single_prime = get_biggest_single_prime_factor_smaller_than(max);
	int number = power(max_single_prime, 2);
	if (are_permutations(number, get_phi_with_factor(number, max_single_prime)))
		return number;
	return 0;
}
TEST_GROUP(phiFactors)
{

};

TEST(phiFactors, single_factor)
{
	PhiFactors pf(5);
	DOUBLES_EQUAL(0.8, pf.getRate(), 0.0001);
}

TEST_GROUP(problem_70)
{

};

TEST(problem_70, big_prime)
{
	CHECK_EQUAL(3, get_biggest_single_prime_factor_smaller_than(10));
}
TEST(problem_70, big_prime2)
{
	CHECK_EQUAL(5, get_biggest_single_prime_factor_smaller_than(30));
}
TEST(problem_70, big_prime3)
{
	CHECK_EQUAL(5, get_biggest_single_prime_factor_smaller_than(40));
}
TEST(problem_70, big_prime4)
{
	CHECK_EQUAL(3137, get_biggest_single_prime_factor_smaller_than(10000000));
}
TEST(problem_70, phi_with_factor)
{
	CHECK_EQUAL(6, get_phi_with_factor(9,3));
}
TEST(problem_70, phi_rate)
{
	DOUBLES_EQUAL(0.8, PhiRate(5).getRate(), 0.0001);
	DOUBLES_EQUAL(2.0/3.0, PhiRate(3).getRate(), 0.0001);
}
IGNORE_TEST(problem_70, smaller_phi_rate)
{
	PhiRate phiRate(7);
	DOUBLES_EQUAL(4.0/5, phiRate.moveToSmallerPhiRate().getRate(), 0.0001);
	DOUBLES_EQUAL(0.8 * 6/7, phiRate.moveToSmallerPhiRate().getRate(), 0.0001);
}
IGNORE_TEST(problem_70, big_get_smallest_rate)
{
	CHECK_EQUAL(3137, get_n_with_biggest_permutation_phi_rate(10000000));
}

