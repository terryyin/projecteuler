#ifndef CONTINUED_FRACTION_H_
#define CONTINUED_FRACTION_H_

#include "math.h"

typedef long long integer;

class divider_of_sqrt
{
public:
	divider_of_sqrt(int n)
	{
		number = n;
		devider = 1;
		minus = plus = sqrt(n);
	}
	divider_of_sqrt(divider_of_sqrt& prev)
	{
		number = prev.number;
		_next(prev);
	}
	void next()
	{
		_next(*this);
	}
	void _next(divider_of_sqrt& prev)
	{
		devider = (number - prev.minus * prev.minus) / prev.devider;
		plus = (prev.minus + sqrt(number)) / devider;
		minus = devider * plus - prev.minus;
	}
	bool operator ==(const divider_of_sqrt& other) const
	{
		return plus == other.plus && minus == other.minus && devider
				== other.devider;
	}
	bool operator !=(const divider_of_sqrt& other) const
	{
		return !this->operator ==(other);
	}
	int get_plus()
	{
		return plus;
	}
	int get_minus()
	{
		return minus;
	}
	int get_devider()
	{
		return devider;
	}
private:
	int plus;
	int minus;
	int number;
	int devider;
};
template <typename BigNumber>
class Fractions
{
public:
	Fractions(integer n) :
		number(n),fraction_period(0)
	{
		lead = sqrt(n);
		integer remain = n - lead * lead;
		if (remain == 0)
			return;
		divider_of_sqrt first(n);
		first.next();
		fractions[fraction_period++] = first.get_plus();
		divider_of_sqrt next(first);
		while (!(next == first))
		{
			fractions[fraction_period++] = next.get_plus();
			next.next();
		}

	}
	;
	integer getFraction(int level)
	{
		if (level == 0)
			return lead;
		return fractions[(level -1)%fraction_period];
	}
    size_t getPeriod() const{
    	return fraction_period;
    }
private:
	enum {MAX_FRACTIONS = 1000};
	integer number;
	integer lead;
	integer fractions[MAX_FRACTIONS];
	size_t fraction_period;
};
template <typename BigNumber>
class ContinuedFraction
{
public:
	ContinuedFraction(Fractions<BigNumber>* fractions, int level)
	{
		numerator = 1;
		denumerator = 0;
		for (int i = level; i >= 0; i--)
		{
			BigNumber saved_num = numerator;
			numerator *= fractions->getFraction(i);
			numerator += denumerator;
			denumerator = saved_num;
		}

	}
	BigNumber get_numerator()
	{
		return numerator;
	}
	BigNumber get_denumerator()
	{
		return denumerator;
	}
private:
	BigNumber numerator;
	BigNumber denumerator;

};



#endif /* CONTINUED_FRACTION_H_ */
