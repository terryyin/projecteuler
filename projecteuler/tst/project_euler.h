#ifndef PROJECT_EULER_H_
#define PROJECT_EULER_H_

int factorial(int n);
long long power(long long n, int e);
int get_digit_count(long long n);
long long get_upper_scale(long long n);
int get_diagnal_of_spiral(int size, int coner);
bool are_permutations(int x, int y);



class triangle
{
public:
	triangle(int * d, int dimension)
	{
		dim = dimension;
		for (int i = 0; i < dim; i++)
			for (int j = 0; j <= i; j++){
				data[i][j] = 100-d[i * dim + j];
				cache[i][j] = NO_CACHE;
			}
	}
	int get_max_sum()
	{
		return 100 * dim  - _get_min_sum(0, 0);
	}
private:
	enum {NO_CACHE = 0};
	int _get_min_sum(int level, int pos);
	int dim;
	int data[100][100];
	int cache[100][100];
};

class dec
{
public:
	dec(int i=0)
	{
		memset(digits, 0, sizeof(digits));
		digits[0] = i;
		count = 1;
		regulate();
	}
	dec& operator *=(int n)
	{
		for (int i = 0; i < count; i++)
			digits[i] *= n;
		regulate();
		return *this;
	}
	dec operator *(int n) const
	{
		dec result = *this;
		for (int i = 0; i < count; i++)
			result.digits[i] *= n;
		result.regulate();
		return result;
	}
	dec& operator +=(dec other){
		if( count < other.count)
			count = other.count;
		for (int i = 0; i < count; i++)
			digits[i] += other.digits[i];
		regulate();
		return *this;
	}
	const dec operator *(dec& other) const
	{
		dec result(0);
		for (int i = count - 1; i >= 0; i--){
			result *= 10;
			result += other * digits[i];
		}
		return result;
	}
	const dec operator -(dec other) const
	{
		dec result(*this);
		result.count = count >= other.count ? count: other.count;
		for (int i = 0; i < result.count; i++)
			result.digits[i] -= other.digits[i];
		result.regulate();
		return result;
	}
	dec& exp(int n)
	{
		int me = to_long();
		for (int i = 0; i < n-1; i++)
			(*this) *= me;
		return *this;
	}

	long long to_long() const{
		long long me = 0;
		for (int i = count -1 ; i >=0; i--)
			me = me * 10 + digits[i];
		return me;
	}
	bool operator ==(dec& other) const{
		if( count != other.count)
			return false;
		for (int i = 0; i < count; i++)
			if(digits[i] != other.digits[i])
				return false;
		return true;
	}
	bool operator >(dec other) const{
		dec r = *this - other;
		return r.digits[r.count-1]>0;
	}
	bool operator ==(long long n) const
	{
		dec other(n);
		return *this == other;
	}
	dec& deducted_from(dec& other){
		if( count < other.count)
			count = other.count;
		for (int i = 0; i < count; i++)
			digits[i] = other.digits[i] - digits[i];
		regulate();
		return *this;
	}
	void append(int n) {
		digits[count++] = n;
	}
	int operator %(int n) {
		int mod = 0;
		for (int i = count - 1; i >=0; i--) {
			mod = (mod * 10 + digits[i]) % n;
		}
		return mod;
	}
	int digits_sum()
	{
		int sum = 0;
		for (int i = 0; i < count; i++)
			sum += digits[i];
		return sum;
	}
	int get_digit(int i)
	{
		return digits[i];
	}
	int get_count()
	{
		return count;
	}
	dec& reverse_add() {
		for (int i = 0; i < (count+1)/2; i++){
			digits[count - i -1] = (digits[i] += digits[count - i -1]);
		}
		regulate();
		return *this;
	}
	bool is_palindrome() {
		for (int i = 0; i < (count+1)/2; i++)
			if(digits[count - i -1] != digits[i])
				return false;
		return true;
	}
private:
	int digits[2000];
	int count;
	void regulate()
	{
		for (int i = 0; i < count; i++){
			if (digits[i] > 9)
			{
				digits[i + 1] += digits[i] / 10;
				digits[i] %= 10;
				if (i == count - 1)
					count++;
			}
			else if (digits[i] < 0)
			{
				digits[i + 1] += (digits[i] -9) / 10;
				digits[i] += 10;
				if (i == count - 1){
					count++;
					break;
				}
			}
		}
		for (int i = count -1; i >=0; i--)
			if (digits[i]==0)
				count--;
			else
				break;
	}
};

class number_set{
public:
	number_set() {count = 0;}
	int get_count(){return count;}
	void add(int n){
		if (!find(n))
			data[count++] = n;
	}
	int get_sum() {int sum = 0; for(int i = 0; i < count; i++)sum+=data[i];return sum;}
protected:
	int find(int n){
		for (int i =0; i < count ; i++)
			if (data[i]==n)
				return 1;
		return 0;
	}
	int count;
	int data[20000];

};


#endif /* PROJECT_EULER_H_ */
