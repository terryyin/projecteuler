#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "project_euler.h"
#include "memory.h"

class NGonSolution{
public:
	NGonSolution(int first):
	index(0){
		memset(m_data, 0, sizeof m_data);
		m_data[1] = first;
	}
	void Append(int number1, int number2){
		m_data[index++] = number1;
		if (index == 1)
			index = 2;
		m_data[index++] = number2;
 	}
	void Append(int number1){
		m_data[index++] = number1;
 	}
	void Pop() {
		if (index % 2 == 0)
			index -= 1;
		else {
			index -= 2;
			if (index == 1)
				index = 0;
		}
	}
	void append_buffer(char * buffer, int&bid, int data) const{
		if (data == 10){
			buffer[bid++] = '1';
			buffer[bid++] = '0';
		}
		else
			buffer[bid++] = data+ '0';
	}
	std::string GetSequence() const{
		int i = 3;
		int min = m_data[1];
		int min_index = 1;
		for(; i < index; i+=2){
			if (m_data[i] < min){
				min = m_data[i];
				min_index = i;
			}
		}
		char buffer[100];
		int bid = 0;
		memset(buffer, 0, sizeof buffer);
		for (i = 0; i < index/2; i++){
			int id = min_index + i * 2;
			append_buffer(buffer, bid, m_data[id%index]);
			append_buffer(buffer, bid, m_data[(id-1)%index]);
			append_buffer(buffer, bid, m_data[(id+1)%index]);

		}
		std::string s = buffer;
		return s;
	}
	bool operator >(const NGonSolution& other) const{
		return strcmp(this->GetSequence().c_str(), other.GetSequence().c_str()) > 0;
	}
	int SumLine(int id){
		int sum = 0;
		int base = 2 * id;
		for (int i = 0; i < 3; i++)
				sum += m_data[(base+i)%index];

		return sum;
	}
	int GetLast(){
		if (index == 0)
			return m_data[1];
		return m_data[index - 1];
	}
	int GetFirst(){
		return m_data[0];
	}
private:
	int m_data[10];
	int index;
};

class NGonIterator{
public:
	NGonIterator(size_t sz, int must_in_outer):
	m_size(sz),m_must_in_outer(must_in_outer),max_gs(m_must_in_outer){

	}

    int is_available(size_t i, unsigned  available)
    {
        return (1 << (i - 1)) & available;
    }

    bool GetSolution(int level, int total, unsigned  available, NGonSolution & gs)
    {
    	if (level == 0)
    	{
    		int rest = total - gs.GetLast() - gs.GetFirst();
    		if (is_available(rest, available)){
    			gs.Append(rest);
    			if (gs > max_gs)
    				max_gs = gs;
				gs.Pop();
    			return true;
    		}
    	}
    	else {
			int rest = total - gs.GetLast();
			int i = 1;
			for(;i < rest;i++){
				if(i != rest - i && is_available(i, available) && is_available(rest - i, available)){
					unsigned new_available = available;
					RemoveAvailable(new_available, i);
					RemoveAvailable(new_available, rest-i);
					gs.Append(i, rest - i);
					GetSolution(level - 1, total, new_available, gs);
					gs.Pop();
				}
			}
    	}
        return false;
    }

    void RemoveAvailable(unsigned  & available, int i)
    {
        available &= ~((1 << (i - 1)));
    }

    NGonSolution GetMax(int total)
    {
        NGonSolution gs(m_must_in_outer);
        unsigned available = (1 << (m_size * 2)) - 1;
        RemoveAvailable(available, m_must_in_outer);
        GetSolution(m_size -1, total, available, gs);
        return max_gs;
	}
private:
	size_t m_size;
	int m_must_in_outer;
	NGonSolution max_gs;
};
NGonSolution GetBiggestNGon(size_t size, int must_in_outer){
	return NGonSolution( must_in_outer);
}
TEST_GROUP(problem68){

};

TEST(problem68, xx){
	const int smallest_sum = ((10+9+8+7+6) + (1+2+3+4+5) * 2)/5;
	const int biggest_sum = ((10+1+2+3+4) + (5+6+7+8+9) * 2)/5;
	CHECK_EQUAL(14, smallest_sum);
	CHECK_EQUAL(18, biggest_sum);

}
TEST(problem68, GetBiggest3Gon){
	NGonSolution gon = GetBiggestNGon(3, 4);
	std::string str = gon.GetSequence();
	STRCMP_EQUAL("", str.c_str());
}
TEST(problem68, GetFirst3Gon){
	NGonIterator iterator(3, 4);
	NGonSolution gon = iterator.GetMax(9);
	std::string str = gon.GetSequence();
	STRCMP_EQUAL("432621513", str.c_str());
}
TEST(problem68, GetMax5Gon){
	NGonIterator iterator(5, 10);
	NGonSolution gon = iterator.GetMax(14);
	STRCMP_EQUAL("6531031914842725", gon.GetSequence().c_str());
	STRCMP_EQUAL("6531031914842725", iterator.GetMax(15).GetSequence().c_str());
	STRCMP_EQUAL("6531031914842725", iterator.GetMax(16).GetSequence().c_str());
	STRCMP_EQUAL("6531031914842725", iterator.GetMax(17).GetSequence().c_str());
	STRCMP_EQUAL("6531031914842725", iterator.GetMax(18).GetSequence().c_str());
}
TEST(problem68, Gon_Append){
	NGonSolution gon(4);
	CHECK_EQUAL(4, gon.GetLast());
	gon.Append(3, 2);
	CHECK_EQUAL(2, gon.GetLast());
	gon.Append(6, 5);
	CHECK_EQUAL(5, gon.GetLast());
	gon.Append(8, 7);
	gon.Append(2);
	CHECK_EQUAL(9,gon.SumLine(0));
	CHECK_EQUAL(13,gon.SumLine(1));
	CHECK_EQUAL(20,gon.SumLine(2));
	CHECK_EQUAL(12,gon.SumLine(3));
}
TEST(problem68, Gon_Sequence){
	NGonSolution gon = GetBiggestNGon(3, 4);
	gon.Append(3, 1);
	gon.Append(6, 5);
	gon.Append(8, 7);
	gon.Append(2);
	STRCMP_EQUAL("273431615857",gon.GetSequence().c_str());
}
TEST(problem68, Gon_Sequence2){
	NGonSolution gon = GetBiggestNGon(3, 4);
	gon.Append(3, 1);
	gon.Append(6, 5);
	gon.Append(8, 7);
	gon.Append(9);
	STRCMP_EQUAL("431615857973",gon.GetSequence().c_str());
}

