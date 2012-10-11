#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "math.h"
#include "prime.h"

TEST_GROUP(project_euler)
{

};

#include "project_euler.h"

int is_palindromic_number(long num)
{
	if (num % 10 == 0)
		return 0;
	int low = 0;
	while (num > low)
	{
		low = low * 10 + (num % 10);
		num /= 10;
	}
	return num == low;
}
TEST(project_euler, problem_4)
{
	int result = 0;
	for (int i = 1000; i >= 100; i--)
		for (int j = 1000; j >= 100; j--)
		{
			int t = i * j;
			if (t <= result)
				break;
			if (is_palindromic_number(t))
				result = t;
		}
	LONGS_EQUAL(906609, result);
}
TEST(project_euler, problem_6)
{
	int result = 0;
	int sum = 0;
	for (int i = 1; i <= 100; i++)
	{
		result += (i * i);
		sum += i;
	}
	result = sum * sum - result;
	LONGS_EQUAL(25164150, result);
}

#define TN(n) printf("%ld\n", (long)n)

TEST(project_euler, problem_7)
{
	const int MAX = 10001;
	long primes[MAX] =
	{ 2 };
	int index = 1;
	for (long candidate = 3; index < MAX; candidate += 2)
		if (is_prime(candidate, primes, index))
			primes[index++] = candidate;

	LONGS_EQUAL(104743, primes[MAX - 1]);
}

int is_prime_int(int num, int previous_primes[], int count)
{
	int biggest_possible = num / 2;
	for (int i = 0; i < count; i++)
		if (previous_primes[i] > biggest_possible)
			break;
		else if (num % previous_primes[i] == 0)
			return 0;
		else
			biggest_possible = num / previous_primes[i];
	return 1;
}

IGNORE_TEST(project_euler, problem_10)
{
	const int MAX = 2000000;
	int primes[MAX] =
	{ 2, 3 };
	int index = 2;
	long sum = 0;
	for (int candidate = 5; candidate < MAX; candidate += 2)
		if (is_prime_int(candidate, primes, index))
			primes[index++] = candidate;
	for (int i = 0; i < index; i++)
		sum += primes[i];
	LONGS_EQUAL(142913828922, sum);
}
int get_product_of_five(char * data)
{
	return data[0] * data[1] * data[2] * data[3] * data[4];
}
TEST(project_euler, problem_8)
{
	char data[] = "73167176531330624919225119674426574742355349194934"
		"96983520312774506326239578318016984801869478851843"
		"85861560789112949495459501737958331952853208805511"
		"12540698747158523863050715693290963295227443043557"
		"66896648950445244523161731856403098711121722383113"
		"62229893423380308135336276614282806444486645238749"
		"30358907296290491560440772390713810515859307960866"
		"70172427121883998797908792274921901699720888093776"
		"65727333001053367881220235421809751254540594752243"
		"52584907711670556013604839586446706324415722155397"
		"53697817977846174064955149290862569321978468622482"
		"83972241375657056057490261407972968652414535100474"
		"82166370484403199890008895243450658541227588666881"
		"16427171479924442928230863465674813919123162824586"
		"17866458359124566529476545682848912883142607690042"
		"24219022671055626321111109370544217506941658960408"
		"07198403850962455444362981230987879927244284909188"
		"84580156166097919133875499200524063689912560717606"
		"05886116467109405077541002256983155200055935729725"
		"71636269561882670428252483600823257530420752963450";
	int size = sizeof(data) - 1;
	for (int i = 0; i < size; i++)
		data[i] -= '0';
	int biggest = get_product_of_five(data);
	for (int i = 5; i < size; i++)
	{
		int five = get_product_of_five(&data[i - 4]);
		if (five > biggest)
			biggest = five;
	}
	LONGS_EQUAL(40824, biggest);

}

TEST(project_euler, problem_9)
{
	int total = 1000;
	int a, b;
	for (a = 1; a <= total / 3; a++)
		for (b = a + 1; b <= (total - a) / 2; b++)
			if (a * a + b * b == (total - a - b) * (total - a - b))
				goto out;
	out:
	LONGS_EQUAL(31875000, a * b * (1000-a-b));
}

TEST(project_euler, problem_11)
{
	const int size = 20;
	const int conseq_count = 4;
	int data[size][size] =
	{
	{ 8, 2, 22, 97, 38, 15, 0, 40, 0, 75, 4, 5, 7, 78, 52, 12, 50, 77, 91, 8 },
	{ 49, 49, 99, 40, 17, 81, 18, 57, 60, 87, 17, 40, 98, 43, 69, 48, 4, 56,
			62, 0 },
	{ 81, 49, 31, 73, 55, 79, 14, 29, 93, 71, 40, 67, 53, 88, 30, 3, 49, 13,
			36, 65 },
	{ 52, 70, 95, 23, 4, 60, 11, 42, 69, 24, 68, 56, 1, 32, 56, 71, 37, 2, 36,
			91 },
	{ 22, 31, 16, 71, 51, 67, 63, 89, 41, 92, 36, 54, 22, 40, 40, 28, 66, 33,
			13, 80 },
	{ 24, 47, 32, 60, 99, 3, 45, 2, 44, 75, 33, 53, 78, 36, 84, 20, 35, 17, 12,
			50 },
	{ 32, 98, 81, 28, 64, 23, 67, 10, 26, 38, 40, 67, 59, 54, 70, 66, 18, 38,
			64, 70 },
	{ 67, 26, 20, 68, 2, 62, 12, 20, 95, 63, 94, 39, 63, 8, 40, 91, 66, 49, 94,
			21 },
	{ 24, 55, 58, 5, 66, 73, 99, 26, 97, 17, 78, 78, 96, 83, 14, 88, 34, 89,
			63, 72 },
	{ 21, 36, 23, 9, 75, 0, 76, 44, 20, 45, 35, 14, 0, 61, 33, 97, 34, 31, 33,
			95 },
	{ 78, 17, 53, 28, 22, 75, 31, 67, 15, 94, 3, 80, 4, 62, 16, 14, 9, 53, 56,
			92 },
	{ 16, 39, 5, 42, 96, 35, 31, 47, 55, 58, 88, 24, 0, 17, 54, 24, 36, 29, 85,
			57 },
	{ 86, 56, 0, 48, 35, 71, 89, 7, 5, 44, 44, 37, 44, 60, 21, 58, 51, 54, 17,
			58 },
	{ 19, 80, 81, 68, 5, 94, 47, 69, 28, 73, 92, 13, 86, 52, 17, 77, 4, 89, 55,
			40 },
	{ 4, 52, 8, 83, 97, 35, 99, 16, 7, 97, 57, 32, 16, 26, 26, 79, 33, 27, 98,
			66 },
	{ 88, 36, 68, 87, 57, 62, 20, 72, 3, 46, 33, 67, 46, 55, 12, 32, 63, 93,
			53, 69 },
	{ 4, 42, 16, 73, 38, 25, 39, 11, 24, 94, 72, 18, 8, 46, 29, 32, 40, 62, 76,
			36 },
	{ 20, 69, 36, 41, 72, 30, 23, 88, 34, 62, 99, 69, 82, 67, 59, 85, 74, 4,
			36, 16 },
	{ 20, 73, 35, 29, 78, 31, 90, 1, 74, 31, 49, 71, 48, 86, 81, 16, 23, 57, 5,
			54 },
	{ 1, 70, 54, 71, 83, 51, 54, 69, 16, 92, 33, 48, 61, 43, 52, 1, 89, 19, 67,
			48 } };
	int dir[][2] =
	{
	{ 1, 0 },
	{ 0, 1 },
	{ 1, 1 },
	{ 1, -1 } };
	int biggest = 0;
	for (int x = 0; x < size; x++)
		for (int y = 0; y < size; y++)
		{
			for (int d = 0; d < 4; d++)
			{
				if (x + dir[d][0] * conseq_count >= size || y + dir[d][1]
						* conseq_count >= size || y + dir[d][1] * conseq_count
						< 0)
					break;
				int product = 1;
				for (int i = 0; i < 4; i++)
				{
					product *= data[x + dir[d][0] * i][y + dir[d][1] * i];
					if (biggest < product)
						biggest = product;
				}
			}
		}
	LONGS_EQUAL(70600674, biggest);
}
static int get_divisor_count(int num)
{
	int count = 2;
	for (int d = 2; d < num; d++)
	{
		if (num % d == 0)
		{
			count++;
		}
	}
	return count;
}
IGNORE_TEST(project_euler, problem_12)
{
	int i;
	for (i = 1;; i++)
	{
		if (i % 2)
		{
			if (get_divisor_count(i) * get_divisor_count((i + 1) / 2) > 500)
				break;
		}
		else
		{
			if (get_divisor_count(i / 2) * get_divisor_count((i + 1)) > 500)
				break;

		}
	}
	LONGS_EQUAL(76576500, i * (i+1) / 2);
}
TEST(project_euler, problem_13)
{
	const int len = 50;
	char data[][len + 1] =
	{ "37107287533902102798797998220837590246510135740250",
			"46376937677490009712648124896970078050417018260538",
			"74324986199524741059474233309513058123726617309629",
			"91942213363574161572522430563301811072406154908250",
			"23067588207539346171171980310421047513778063246676",
			"89261670696623633820136378418383684178734361726757",
			"28112879812849979408065481931592621691275889832738",
			"44274228917432520321923589422876796487670272189318",
			"47451445736001306439091167216856844588711603153276",
			"70386486105843025439939619828917593665686757934951",
			"62176457141856560629502157223196586755079324193331",
			"64906352462741904929101432445813822663347944758178",
			"92575867718337217661963751590579239728245598838407",
			"58203565325359399008402633568948830189458628227828",
			"80181199384826282014278194139940567587151170094390",
			"35398664372827112653829987240784473053190104293586",
			"86515506006295864861532075273371959191420517255829",
			"71693888707715466499115593487603532921714970056938",
			"54370070576826684624621495650076471787294438377604",
			"53282654108756828443191190634694037855217779295145",
			"36123272525000296071075082563815656710885258350721",
			"45876576172410976447339110607218265236877223636045",
			"17423706905851860660448207621209813287860733969412",
			"81142660418086830619328460811191061556940512689692",
			"51934325451728388641918047049293215058642563049483",
			"62467221648435076201727918039944693004732956340691",
			"15732444386908125794514089057706229429197107928209",
			"55037687525678773091862540744969844508330393682126",
			"18336384825330154686196124348767681297534375946515",
			"80386287592878490201521685554828717201219257766954",
			"78182833757993103614740356856449095527097864797581",
			"16726320100436897842553539920931837441497806860984",
			"48403098129077791799088218795327364475675590848030",
			"87086987551392711854517078544161852424320693150332",
			"59959406895756536782107074926966537676326235447210",
			"69793950679652694742597709739166693763042633987085",
			"41052684708299085211399427365734116182760315001271",
			"65378607361501080857009149939512557028198746004375",
			"35829035317434717326932123578154982629742552737307",
			"94953759765105305946966067683156574377167401875275",
			"88902802571733229619176668713819931811048770190271",
			"25267680276078003013678680992525463401061632866526",
			"36270218540497705585629946580636237993140746255962",
			"24074486908231174977792365466257246923322810917141",
			"91430288197103288597806669760892938638285025333403",
			"34413065578016127815921815005561868836468420090470",
			"23053081172816430487623791969842487255036638784583",
			"11487696932154902810424020138335124462181441773470",
			"63783299490636259666498587618221225225512486764533",
			"67720186971698544312419572409913959008952310058822",
			"95548255300263520781532296796249481641953868218774",
			"76085327132285723110424803456124867697064507995236",
			"37774242535411291684276865538926205024910326572967",
			"23701913275725675285653248258265463092207058596522",
			"29798860272258331913126375147341994889534765745501",
			"18495701454879288984856827726077713721403798879715",
			"38298203783031473527721580348144513491373226651381",
			"34829543829199918180278916522431027392251122869539",
			"40957953066405232632538044100059654939159879593635",
			"29746152185502371307642255121183693803580388584903",
			"41698116222072977186158236678424689157993532961922",
			"62467957194401269043877107275048102390895523597457",
			"23189706772547915061505504953922979530901129967519",
			"86188088225875314529584099251203829009407770775672",
			"11306739708304724483816533873502340845647058077308",
			"82959174767140363198008187129011875491310547126581",
			"97623331044818386269515456334926366572897563400500",
			"42846280183517070527831839425882145521227251250327",
			"55121603546981200581762165212827652751691296897789",
			"32238195734329339946437501907836945765883352399886",
			"75506164965184775180738168837861091527357929701337",
			"62177842752192623401942399639168044983993173312731",
			"32924185707147349566916674687634660915035914677504",
			"99518671430235219628894890102423325116913619626622",
			"73267460800591547471830798392868535206946944540724",
			"76841822524674417161514036427982273348055556214818",
			"97142617910342598647204516893989422179826088076852",
			"87783646182799346313767754307809363333018982642090",
			"10848802521674670883215120185883543223812876952786",
			"71329612474782464538636993009049310363619763878039",
			"62184073572399794223406235393808339651327408011116",
			"66627891981488087797941876876144230030984490851411",
			"60661826293682836764744779239180335110989069790714",
			"85786944089552990653640447425576083659976645795096",
			"66024396409905389607120198219976047599490197230297",
			"64913982680032973156037120041377903785566085089252",
			"16730939319872750275468906903707539413042652315011",
			"94809377245048795150954100921645863754710598436791",
			"78639167021187492431995700641917969777599028300699",
			"15368713711936614952811305876380278410754449733078",
			"40789923115535562561142322423255033685442488917353",
			"44889911501440648020369068063960672322193204149535",
			"41503128880339536053299340368006977710650566631954",
			"81234880673210146739058568557934581403627822703280",
			"82616570773948327592232845941706525094512325230608",
			"22918802058777319719839450180888072429661980811197",
			"77158542502016545090413245809786882778948721859617",
			"72107838435069186155435662884062257473692284509516",
			"20849603980134001723930671666823555245252804609722",
			"5350353422647252425087405407559178978126433033169" };
	const int count = sizeof(data) / sizeof(data[0]);
	for (int i = 0; i < count; i++)
		for (int j = 0; j < len; j++)
			data[i][j] -= '0';
	long long sum = 0;
	long long base = 1;
	for (int j = 49; j >= 0; j--)
	{
		for (int i = 0; i < count; i++)
		{
			sum += data[i][j] * base;
		}
		if (sum > 9999999999)
			sum /= 10;
		else
			base *= 10;
	}
	LONGS_EQUAL(5537376230, sum);

}

const int hash_size = 97;
int hash[hash_size];

static void hash_set(long n, int cnt)
{
	if (n < hash_size)
		hash[n] = cnt;
}
static int hash_get(long n)
{
	if (n < hash_size)
		return hash[n];
	return 0;
}
static int get_Collatz_length(long n)
{
	int cnt = 1;
	while (n != 1)
	{
		int hashed = hash_get(n);
		if (hashed)
		{
			cnt += hashed;
			break;
		}
		if (n % 2)
			n = n * 3 + 1;
		else
			n /= 2;
		cnt++;
	}
	hash_set(n, cnt);

	return cnt;
}
static void init_hash()
{
	memset(hash, 0, sizeof(hash));
}
IGNORE_TEST(project_euler, problem_14)
{
	int n;
	int max = 0;
	int num = 0;
	init_hash();
	for (n = 1; n < 1000000; n++)
	{
		int len = get_Collatz_length(n);
		if (len > max)
		{
			max = len;
			num = n;
		}
	}
	LONGS_EQUAL(837799, num);
}
static long possible_comb(int a, int b)
{
	if (a > b)
		return possible_comb(b, a);
	if (a == 2)
		return (1 + b) * (b + 2) / 2;
	return possible_comb(a - 1, b) + possible_comb(a, b - 1);
}
IGNORE_TEST(project_euler, problem_15)
{
	long count = possible_comb(20, 20);
	LONGS_EQUAL(137846528820, count);
}
TEST(project_euler, problem_16)
{
	const int len = 1000;
	int count = 1;
	int digits[1000] =
	{ 1, };

	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < count; j++)
			digits[j] *= 2;
		for (int j = 0; j < count; j++)
			if (digits[j] > 9)
			{
				digits[j + 1] += (digits[j] / 10);
				digits[j] %= 10;
				if (j + 1 == count)
					count++;
			}

	}
	int sum = 0;
	while (count > 0)
		sum += digits[--count];
	LONGS_EQUAL(1366, sum);
}
class cached_number_counter
{
	int size[1001];
public:
	cached_number_counter()
	{
		static const int known[1001] =
		{ 0, 3, 3, 5, 4, 4, 3, 5, 5, 4, 3, 6, 6, 8, 8, 7, 7, 9, 8, 8, 6, };
		memcpy(size, known, sizeof(size));
		size[30] = 6;
		size[40] = 5;
		size[50] = 5;
		size[60] = 5;
		size[70] = 7;
		size[80] = 6;
		size[90] = 6;
		size[100] = 10;
		size[200] = size[2] + 7;
		size[300] = size[3] + 7;
		size[400] = size[4] + 7;
		size[500] = size[5] + 7;
		size[600] = size[6] + 7;
		size[700] = size[7] + 7;
		size[800] = size[8] + 7;
		size[900] = size[9] + 7;
		size[1000] = 11;
	}
	int get_count_of(int i)
	{
		if (size[i] == 0)
		{
			int high = get_the_highest_digit(i);
			int cnt = size[high] + get_count_of(i - high);
			if ((i / 100) && (i % 100))
				cnt += 3;
			return cnt;
		}
		return size[i];
	}
	int count_all()
	{
		int sum = 0;
		for (int i = 1; i <= 1000; i++)
		{
			size[i] = get_count_of(i);
			sum += size[i];
		}
		return sum;
	}
	int get_the_highest_digit(int n)
	{
		return n < 10 ? n : n < 100 ? n / 10 * 10 : n < 1000 ? n / 100 * 100
				: 1000;
	}
};
TEST(project_euler, problem_17_count)
{
	LONGS_EQUAL(3, cached_number_counter().get_count_of(1));
	LONGS_EQUAL(6, cached_number_counter().get_count_of(11));
	LONGS_EQUAL(8, cached_number_counter().get_count_of(42));
	LONGS_EQUAL(12, cached_number_counter().get_count_of(300));
	LONGS_EQUAL(23, cached_number_counter().get_count_of(342));
}
TEST(project_euler, problem_17)
{
	LONGS_EQUAL(21124, cached_number_counter().count_all());
}

TEST(project_euler, problem_18)
{
	int data[][15] =
	{
	{ 75 },
	{ 95, 64 },
	{ 17, 47, 82 },
	{ 18, 35, 87, 10 },
	{ 20, 4, 82, 47, 65 },
	{ 19, 1, 23, 75, 3, 34 },
	{ 88, 2, 77, 73, 7, 63, 67 },
	{ 99, 65, 4, 28, 6, 16, 70, 92 },
	{ 41, 41, 26, 56, 83, 40, 80, 70, 33 },
	{ 41, 48, 72, 33, 47, 32, 37, 16, 94, 29 },
	{ 53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14 },
	{ 70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57 },
	{ 91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48 },
	{ 63, 66, 4, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31 },
	{ 4, 62, 98, 27, 23, 9, 70, 98, 73, 93, 38, 53, 60, 4, 23 } };

	LONGS_EQUAL(1074, triangle(data[0], 15).get_max_sum());
}

static int get_days_of_year_before_month(int year, int month)
{
	static const int month_days[] =
	{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int days = 0;
	for (int i = 0; i < month - 1; i++)
		days += month_days[i];
	if (month > 2 && year % 4 == 0)
		days++;

	return days;
}
static int days_since_1_jan_1901(int year, int month, int day)
{
	int days = (year - 1901) * 365 + (year - 1901) / 4;
	days += get_days_of_year_before_month(year, month);
	return days + day;
}
static int is_sunday(int year, int month, int day)
{
	return (days_since_1_jan_1901(year, month, day) + 2) % 7 == 0;
}
TEST(project_euler, problem_19)
{
	int cnt = 0;
	for (int y = 1901; y <= 2000; y++)
		for (int m = 1; m <= 12; m++)
			if (is_sunday(y, m, 1))
				cnt++;
	LONGS_EQUAL(171, cnt);
}
TEST(project_euler, problem_20)
{
	dec d(1);
	for (int i = 1; i <= 100; i++)
		d *= i;
	LONGS_EQUAL(648, d.digits_sum());
}

static int get_sum_divisor(int n)
{
	int sum = 1;
	int s = sqrt(n);
	for (int i = 2; i <= s; i++)
		if (n % i == 0)
			sum += (i + n / i);

	if (s * s == n)
		sum -= s;

	return sum;
}
TEST(project_euler, problem_21)
{
	int total = 0;
	const int max = 10000;
	for (int i = 4; i < max; i++)
	{
		int sum = get_sum_divisor(i);
		if (sum < max && sum != i && i == get_sum_divisor(sum))
			total += (sum + i);
	}
	LONGS_EQUAL(31626, total/2);
}

static int cmp_string(const void * s1, const void * s2)
{
	return strcmp(*(char **) s1, *(char **) s2);
}
static int get_string_value(const char *p)
{
	int sum = 0;
	while (*p)
		sum += ((*(p++)) - 'A' + 1);
	return sum;
}
TEST(project_euler, problem_22)
{
#include "names.h"
	int count = sizeof(names) / sizeof(names[0]);
	qsort(names, count, sizeof(names[0]), cmp_string);
	long total = 0;
	for (int i = 0; i < count; i++)
	{
		total += (get_string_value(names[i]) * (i + 1));
	}
	STRCMP_EQUAL("COLIN",names[937]);
	LONGS_EQUAL(53,get_string_value(names[937]));

	LONGS_EQUAL(871198282, total);
}

class abundant_numbers
{
public:
	enum
	{
		LESS = 1, ABUNDANT = 2
	};
	abundant_numbers()
	{
		memset(numbers, 0, sizeof(numbers));
		memset(flags, 0, sizeof(flags));
		numbers[0] = 12;
	}
	;
	int get_nth_abundant_number(int index)
	{
		if (numbers[index])
			return numbers[index];
		int i;
		for (i = get_nth_abundant_number(index - 1) + 1; !is_abundant(i); i++)
			;
		numbers[index] = i;
		return i;
	}
	int is_abundant(int n)
	{
		if (!flags[n])
			flags[n] = get_sum_divisor(n) > n ? ABUNDANT : LESS;
		return flags[n] == ABUNDANT;
	}
private:
	int numbers[30000];
	int flags[30000];
};
TEST(project_euler, abuntant)
{
	abundant_numbers an;
	LONGS_EQUAL(16, get_sum_divisor(12));
	CHECK(an.is_abundant(12));
	LONGS_EQUAL(12, an.get_nth_abundant_number(0));
	LONGS_EQUAL(18, an.get_nth_abundant_number(1));
}
TEST(project_euler, problem_23)
{
	int total = 0;
	abundant_numbers an;
	for (int i = 1; i < 29125; i++)
	{
		int cannot = 1;
		for (int j = 0;; j++)
		{
			int abundant = an.get_nth_abundant_number(j);
			if (abundant > i / 2)
				break;
			if (an.is_abundant(i - abundant))
			{
				cannot = 0;
				break;
			}
		}
		if (cannot)
		{
			total += i;
		}
	}
	LONGS_EQUAL(4179871, total);
}
static int get_unused(char * slots, int n)
{
	int i;
	for (i = 0; i < 10; i++)
		if (slots[i] == 0)
		{
			if (n == 0)
				break;
			n--;
		}
	slots[i] = 1;
	return i;
}
TEST(project_euler, problem_24)
{
	int order = 1000000 - 1;
	char digits[11];
	char slots[10] =
	{ 0, };
	digits[10] = 0;
	for (int s = 0; s < 10; s++)
	{
		int step = factorial(9 - s);
		digits[s] = get_unused(slots, order / step) + '0';
		order %= step;
	}
	STRCMP_EQUAL("2783915460", digits);
}
TEST(project_euler, problem_25)
{
	dec d[2] =
	{ dec(1), dec(1) };
	int i = 2;
	while (d[i % 2].get_count() < 1000)
	{
		i++;
		d[i % 2] += d[1 - i % 2];
	}
	LONGS_EQUAL(4782, i);
}
static int get_rid_of25(int n)
{
	while (n % 2 == 0)
		n /= 2;
	while (n % 5 == 0)
		n /= 5;
	return n;
}
TEST(project_euler, problem_26)
{
	int max = 0;
	int longest = 0;
	for (int i = 2; i < 1000; i++)
	{
		int n = get_rid_of25(i);
		dec j(9);
		for (; (j % n); j.append(9))
			;
		if (j.get_count() > max)
		{
			max = j.get_count();
			longest = i;
		}
	}
	LONGS_EQUAL(983, longest);
}

static int get_consecutive_primes_count(int a, int b, prime& p)
{
	int n = 0;
	while (p.is_prime(n * n + a * n + b))
		n++;
	return n;
}
TEST(project_euler, problem_27)
{
	const int MAX_A = 1000;
	const int MAX_B = 1000;
	int max_len = 0;
	int product = 0;
	prime p;
	for (int a = -MAX_A + 1; a < MAX_A; a++)
	{
		for (int b = -MAX_B + 1; b < MAX_B; b++)
		{
			int len = get_consecutive_primes_count(a, b, p);
			if (len > max_len)
			{
				product = a * b;
				max_len = len;
			}
		}
	}
	LONGS_EQUAL(-59231, product);
}
static int get_spiral_diag(int n)
{
	return 16 * n * n + 4 * n + 4;
}
TEST(project_euler, problem_28)
{
	LONGS_EQUAL(24, get_spiral_diag(1));
	LONGS_EQUAL(76, get_spiral_diag(2));
	LONGS_EQUAL(160, get_spiral_diag(3));
	const int size = 1001;
	int sum = 1;
	for (int i = 1; i <= size / 2; i++)
		sum += get_spiral_diag(i);

	LONGS_EQUAL(669171001, sum);
}
TEST(project_euler, number_set)
{
	number_set set;
	LONGS_EQUAL(0,set.get_count());
	set.add(1);
	LONGS_EQUAL(1,set.get_count());
	set.add(1);
	LONGS_EQUAL(1,set.get_count());
	set.add(2);
	LONGS_EQUAL(2,set.get_count());
}
static int get_base(int n, int * e)
{
	for (int i = 2; i <= sqrt(n); i++)
	{
		int result = i;
		*e = 1;
		while (result < n)
		{
			result *= i;
			(*e)++;
		}
		if (result == n)
		{
			return i;
		}
	}
	*e = 1;
	return n;
}
TEST(project_euler, problem_29)
{
	int e = 0;
	LONGS_EQUAL(2,get_base(2, &e));
	LONGS_EQUAL(1,e);
	LONGS_EQUAL(2,get_base(4, &e));
	LONGS_EQUAL(2,e);
	LONGS_EQUAL(6,get_base(36, &e));
	LONGS_EQUAL(2,e);
	LONGS_EQUAL(2,get_base(8, &e));
	LONGS_EQUAL(3,e);
	const int max = 100;
	number_set set;
	for (int a = 2; a <= max; a++)
	{
		int A = get_base(a, &e);
		for (int b = 2; b <= max; b++)
		{
			set.add(b * e * 100 + A);
		}
	}
	LONGS_EQUAL(9183, set.get_count());
}
TEST(project_euler, problem_30)
{
	int sum = 0;
	int exp = 5;
	int max_digit = power(9, exp);

	int digits = 1;
	int ten = 10;
	for (; ten <= max_digit * digits; digits++, ten *= 10)
		;
	for (int i = 10; i < ten; i++)
	{
		int s = 0;
		int remain = i;
		while (remain != 0)
		{
			s += power(remain % 10, exp);
			remain /= 10;
		}
		if (s == i)
			sum += i;
	}

	LONGS_EQUAL(443839, sum);

}
static int get_coin_combines_with(int total, const int * coins, int types)
{
	if (types == 1 || total == 0)
		return 1;
	int count = 0;
	while (total >= 0)
	{
		count += get_coin_combines_with(total, coins + 1, types - 1);
		total -= *coins;
	}
	return count;
}
TEST(project_euler, problem_31)
{
	int count = 0;
	const int coins[] =
	{ 200, 100, 50, 20, 10, 5, 2, 1 };
	const int coin_types = sizeof(coins) / sizeof(coins[0]);
	count = get_coin_combines_with(200, coins, coin_types);
	LONGS_EQUAL(73682, count);

}
#define BIT(n) (1<<(n - 1))
unsigned int remove_bits(unsigned int flags, int number)
{
	for (int i = number; i > 0; i /= 10)
		flags ^= BIT(i%10);
	return flags;
}
unsigned int check_bits(unsigned int flags, int number)
{
	for (int i = number; i > 0; i /= 10)
		if ((i % 10 == 0) || ((flags & BIT(i%10)) == 0))
			return 0;
		else
			flags ^= BIT(i%10);

	return flags == 0;
}
static int get_next_number(unsigned int available_flag, int pre)
{
	unsigned int saved = available_flag;
	available_flag = remove_bits(available_flag, pre / 10);
	int n;
	for (n = (pre % 10) + 1; n < 10; n++)
		if (available_flag & BIT(n))
			break;
	int ten = pre / 10;
	if (n == 10)
	{
		ten = get_next_number(saved, ten);
		n = get_next_number(remove_bits(saved, ten), 0);
	}
	n += ten * 10;
	return n;
}
TEST(project_euler, problem_32)
{

	LONGS_EQUAL(1, get_next_number(0xFFFF,0));
	LONGS_EQUAL(2, get_next_number(0xFFFF,1));
	LONGS_EQUAL(3, get_next_number(0xFFFF&(~BIT(2)),1));
	LONGS_EQUAL(12, get_next_number(0xFFFF,9));
	LONGS_EQUAL(14, get_next_number(0xFFFF&(~BIT(3)),12));
	LONGS_EQUAL(21, get_next_number(0xFFFF,19));
	LONGS_EQUAL(23, get_next_number(0xFFFF,21));
	LONGS_EQUAL(91, get_next_number(0xFFFF,89));
	LONGS_EQUAL(123, get_next_number(0xFFFF,98));
	LONGS_EQUAL(123, get_next_number(0xFFFF,99));
	LONGS_EQUAL(987654321, get_next_number(0xFFFF,987654312));
	LONGS_EQUAL(0, remove_bits(511,987654312));
	LONGS_EQUAL(0, check_bits(remove_bits(511,9876543), 1));
	LONGS_EQUAL(1, check_bits(remove_bits(511,9876543), 12));
	LONGS_EQUAL(0, check_bits(remove_bits(511,9876543), 123));
	LONGS_EQUAL(0, check_bits(remove_bits(511,9876543), 12333));
	number_set set;
	for (int i = get_next_number(-1, 0); i < get_next_number(-1, 99); i
			= get_next_number(-1, i))
	{
		unsigned int f = remove_bits(511, i);
		for (int j = get_next_number(f, 99); j < get_next_number(f, 9999); j
				= get_next_number(f, j))
		{
			if (check_bits(remove_bits(f, j), i * j))
			{
				set.add(i * j);
			}
		}
	}

	LONGS_EQUAL(45228, set.get_sum());

}
static int get_common(int a, int b)
{
	if (a == 0)
		return b;
	return get_common(b % a, a);
}
TEST(project_euler, problem_33)
{
	LONGS_EQUAL(1, get_common(1,1));
	LONGS_EQUAL(1, get_common(1,2));
	LONGS_EQUAL(1, get_common(2,5));
	LONGS_EQUAL(2, get_common(2,4));
	LONGS_EQUAL(3, get_common(6,9));
	int count = 0;
	int numerators[10];
	int denominator[10];
	for (int i = 1; i <= 9; i++)
		for (int j = 1; j <= 9; j++)
		{
			int n = i * 10 + j;
			for (int k = 1; k <= 9; k++)
			{
				int m = k * 10 + i;
				if (m > n && n * 10000 / m == j * 10000 / k)
				{
					numerators[count] = n;
					denominator[count++] = m;
				}
			}
			n = j * 10 + i;
			for (int k = 1; k <= 9; k++)
			{
				int m = i * 10 + k;
				if (m > n && n * 10000 / m == j * 10000 / k)
				{
					numerators[count] = n;
					denominator[count++] = m;
				}
			}

		}
	LONGS_EQUAL(4, count);
	int n = 1, d = 1;
	for (int i = 0; i < count; i++)
	{
		n *= numerators[i];
		d *= denominator[i];
	}

	LONGS_EQUAL(100, d / get_common(n, d));
}

TEST(project_euler, problem_34)
{
	int max = factorial(9) * 7;
	int f[10];
	for (int i = 0; i < 10; i++)
		f[i] = factorial(i);
	int sum = 0;
	for (int i = 10; i < max; i++)
	{
		int r = 0, n;
		for (n = i; n > 0; n /= 10)
			r += f[n % 10];
		if (r == i)
			sum += r;
	}
	LONGS_EQUAL(40730, sum);
}
int get_next_asc_number(int n)
{
	n = n + 1;
	int i = 0;
	int last;
	for (last = n % 10; last == 0; last = n % 10)
	{
		n /= 10;
		i++;
	}
	for (; i > 0; i--)
		n = n * 10 + last;
	return n;
}
class number_arranger
{
public:
	number_arranger(int num)
	{
		memset(numbers, 0, sizeof numbers);
		memset(scales, 0, sizeof scales);
		memset(current, 0, sizeof current);
		next_level(0, num);
	}
	int next()
	{
		return next_with_param(0);
	}
private:
	int next_with_param(int index)
	{
		int number = numbers[index];
		int scale = scales[index];
		int rest = 0;
		int n, m = 0;
		do
		{
			n = number % (scale * 10) / scale;
			if (scale > 1)
				m = number % (scale) / (scale / 10);
			if (n == m)
				scale *= 10;
		} while (n == m && scale < number);
		if (scale < number)
		{
			current[index] = n;
			rest = number / (scale * 10) * scale + number % scale;
			if (rest > 9)
			{
				next_level(index + 1, rest);
				rest = next_with_param(index + 1);
				if (rest == 0)
				{
					scales[index] *= 10;
					return next_with_param(index);
				}
			}
			else
				scales[index] *= 10;

		}
		else
		{
			scales[index] = 0;
			current[index] = 0;
		}
		return rest * 10 + current[index];
	}
	void next_level(int index, int rest)
	{
		if (scales[index] == 0)
		{
			numbers[index] = rest;
			scales[index] = 1;
		}
	}
	int numbers[10];
	int scales[10];
	int current[10];
};
TEST(project_euler, problem_35x)
{
	LONGS_EQUAL(2,get_next_asc_number(1));
	LONGS_EQUAL(9,get_next_asc_number(8));
	LONGS_EQUAL(11,get_next_asc_number(9));
	LONGS_EQUAL(111,get_next_asc_number(99));
	LONGS_EQUAL(1333,get_next_asc_number(1299));
	{
		number_arranger iter(2);
		LONGS_EQUAL(2,iter.next());
		LONGS_EQUAL(0,iter.next());
	}
	{
		number_arranger iter(12);
		LONGS_EQUAL(12,iter.next());
		LONGS_EQUAL(21,iter.next());
		LONGS_EQUAL(0,iter.next());
	}
	{
		number_arranger iter(123);
		LONGS_EQUAL(123,iter.next());
		LONGS_EQUAL(213,iter.next());
		LONGS_EQUAL(132,iter.next());
		LONGS_EQUAL(312,iter.next());
		LONGS_EQUAL(231,iter.next());
		LONGS_EQUAL(321,iter.next());
		LONGS_EQUAL(0,iter.next());
	}
	{
		number_arranger iter(1234);
		LONGS_EQUAL(1234,iter.next());
		LONGS_EQUAL(2134,iter.next());
		LONGS_EQUAL(1324,iter.next());
		LONGS_EQUAL(3124,iter.next());
		LONGS_EQUAL(2314,iter.next());
		LONGS_EQUAL(3214,iter.next());
		LONGS_EQUAL(1243,iter.next());
	}
	{
		number_arranger iter(11);
		LONGS_EQUAL(11,iter.next());
		LONGS_EQUAL(0,iter.next());
	}
	int count = 0;
	const int max = 1000000;
	prime p;
	for (int i = 2; i < max; i = get_next_asc_number(i))
	{
		number_arranger iter(i);
		int n;
		int cnt = 0;
		for (n = iter.next(); n != 0; n = iter.next(), cnt++)
			if (!p.is_prime(n))
				break;
		if (n == 0)
		{
			count += cnt;
		}
	}

	LONGS_EQUAL(23, count);
}
class number_rotator
{
public:
	number_rotator(int n)
	{
		number = n;
		scale = 1;
		static const int scales[] =
		{ 1000000, 100000, 10000, 1000, 100, 10, 1 };
		int i;
		for (i = 0; scales[i] > n; i++)
			;
		total = scales[i] * 10;
	}
	int next()
	{
		if (scale > number)
			return 0;
		int n = number / scale + (number % scale) * (total / scale);
		scale *= 10;
		return n;
	}
private:
	int number;
	int scale;
	int total;
};
IGNORE_TEST(project_euler, problem_35)
{

	{
		number_rotator iter(2);
		LONGS_EQUAL(2,iter.next());
		LONGS_EQUAL(0,iter.next());
	}
	{
		number_rotator iter(12);
		LONGS_EQUAL(12,iter.next());
		LONGS_EQUAL(21,iter.next());
		LONGS_EQUAL(0,iter.next());
	}
	{
		number_rotator iter(123);
		LONGS_EQUAL(123,iter.next());
		LONGS_EQUAL(312,iter.next());
		LONGS_EQUAL(231,iter.next());
		LONGS_EQUAL(0,iter.next());
	}
	number_set set;
	const int max = 1000000;
	prime p;
	for (int i = 3; i < max; i += 2)
	{
		if (!p.is_prime(i))
			continue;
		number_rotator iter(i);
		int n;
		for (n = iter.next(); n != 0; n = iter.next())
			if (!p.is_prime(n))
				break;
		if (n == 0)
		{
			number_rotator iter(i);
			int n;
			for (n = iter.next(); n != 0; n = iter.next())
			{
				set.add(n);
			}
		}
	}

	LONGS_EQUAL(55, set.get_count()+1);
}
int is_palindromic_binary(long num)
{
	if (num % 2 == 0)
		return 0;
	int low = 0;
	while (num > low)
	{
		low = low * 2 + (num % 2);
		if (low == num)
			return 1;
		num /= 2;
	}
	return num == low;
}
int make_palindromic_number(long num, int overlap)
{
	int result = num;
	int digit;
	if (overlap)
		result /= 10;

	do
	{
		digit = num % 10;
		result = result * 10 + digit;
	} while (num /= 10);

	return result;
}

TEST(project_euler, problem_36)
{

	LONGS_EQUAL(11,make_palindromic_number(1,0));
	LONGS_EQUAL(1,make_palindromic_number(1,1));
	LONGS_EQUAL(1221,make_palindromic_number(12,0));
	LONGS_EQUAL(121,make_palindromic_number(12,1));
	CHECK(is_palindromic_binary(3));
	CHECK(!is_palindromic_binary(4));
	CHECK(is_palindromic_binary(21));
	const int max = 1000;
	int cnt = 0;
	int sum = 0;

	for (int j = 0; j < 2; j++)
		for (int i = 1; i < max; i++)
		{
			int dec = make_palindromic_number(i, j);
			if (is_palindromic_binary(dec))
			{
				sum += dec;
				cnt++;
			}
		}
	LONGS_EQUAL(872187, sum);
}
class truncatable_primers
{
public:
	truncatable_primers() :
		index(0), mover(1)
	{
		add(2);
		add(3);
		add(5);
		add(7);
	}
	;
	bool has(int n)
	{
		return find(n);
	}
	int next()
	{
		int raw;
		do
		{
			raw = next_raw();
		} while (!p.is_prime(raw) && raw != 0);
		add(raw);
		return raw;
	}
	int get_count()
	{
		return count;
	}
	bool is_left_truncatable(int n)
	{
		for (int scale = 10; scale < n; scale *= 10)
			if (!p.is_prime(n % scale))
				return false;
		return true;
	}
private:
	void add(int n)
	{
		data[count++] = n;
	}
	int find(int n)
	{
		for (int i = 0; i < count; i++)
			if (data[i] == n)
				return 1;
		return 0;
	}
	int next_raw()
	{
		if (mover > 9)
		{
			mover = 1;
			index++;
			if (index >= count)
				return 0;
		}
		int raw = data[index] * 10 + mover;
		mover += 2;
		return raw;
	}
	prime p;
	int index;
	int mover;
	int count;
	int data[20000];
};
TEST(project_euler, problem_37)
{
	truncatable_primers tp;
	CHECK(!tp.has(1));
	CHECK(tp.has(3));
	LONGS_EQUAL(23, tp.next());
	LONGS_EQUAL(29, tp.next());
	LONGS_EQUAL(31, tp.next());
	LONGS_EQUAL(37, tp.next());
	LONGS_EQUAL(53, tp.next());
	LONGS_EQUAL(59, tp.next());
	LONGS_EQUAL(71, tp.next());
	LONGS_EQUAL(73, tp.next());
	LONGS_EQUAL(79, tp.next());
	LONGS_EQUAL(233, tp.next());
	LONGS_EQUAL(239, tp.next());
	CHECK(!tp.is_left_truncatable(34));
	CHECK(tp.is_left_truncatable(13));
	truncatable_primers t;
	int sum = 0;
	for (int n = t.next(), count = 0; count < 11; n = t.next())
	{
		if (t.is_left_truncatable(n))
		{
			sum += n;
			count++;
		}
	}
	LONGS_EQUAL(748317, sum);
}
TEST(project_euler, problem_39)
{
	int max_count = 0;
	int max = 0;
	for (int i = 5; i < 1000; i++)
	{
		int count = 0;
		for (int c = i / 3; c < i / 2; c++)
			for (int b = sqrt(c * c / 2); b < c; b++)
			{
				int a = i - c - b;
				if (a * a + b * b == c * c)
					count++;
			}
		if (count > max_count)
		{
			max = i;
			max_count = count;
		}
	}
	LONGS_EQUAL(840, max);
}

int get_digit(int n, int offset)
{
	int scale = 1;
	for (; offset > 0; offset--)
		scale *= 10;
	return n % (scale * 10) / scale;
}
TEST(project_euler, problem_40)
{
	LONGS_EQUAL(1, get_digit_count(1));
	LONGS_EQUAL(1, get_digit_count(2));
	LONGS_EQUAL(2, get_digit_count(10));
	LONGS_EQUAL(3, get_digit_count(123));
	LONGS_EQUAL(1, get_digit(1,0));
	LONGS_EQUAL(3, get_digit(1234,1));
	const int indice[] =
	{ 1, 10, 100, 1000, 10000, 100000, 1000000 };
	int index = 0;
	const int size = sizeof indice / sizeof indice[0];
	int count = 0;
	int product = 1;
	for (int i = 1; index < size; i++)
	{
		count += get_digit_count(i);
		if (count >= indice[index])
		{
			product *= (get_digit(i, count - indice[index]));
			index++;
		}
	}
	LONGS_EQUAL(210, product);
}
long long get_prev_pandigital1(long long n)
{

	int digit[10];
	int idx = 1;
	digit[0] = n % 10;
	n /= 10;
	while (n > 0)
	{
		int d = n % 10;
		n /= 10;
		if (d > digit[idx - 1])
		{
			int temp = 0;
			int next = 0;
			for (int i = 0; i < idx; i++)
				if (temp <= digit[i] && digit[i] < d)
				{
					temp = digit[i];
					next = i;
				}

			digit[next] = d;
			n = n * 10 + temp;
			for (int i = 0; i < idx; i++)
				n = n * 10 + digit[i];
			return n;
		}
		digit[idx++] = d;
	}
	return 0;
}

TEST(project_euler, problem_41)
{
	LONGS_EQUAL(0, get_prev_pandigital1(1));
	LONGS_EQUAL(12, get_prev_pandigital1(21));
	LONGS_EQUAL(312, get_prev_pandigital1(321));
	LONGS_EQUAL(7654312, get_prev_pandigital1(7654321));
	LONGS_EQUAL(76542, get_prev_pandigital1(7654312)/100);
	LONGS_EQUAL(7654231, get_prev_pandigital1(7654312));
	LONGS_EQUAL(7654213, get_prev_pandigital1(7654231));
	LONGS_EQUAL(7654132, get_prev_pandigital1(7654213));
	LONGS_EQUAL(7654123, get_prev_pandigital1(7654132));
	LONGS_EQUAL(7653421, get_prev_pandigital1(7654123));
	LONGS_EQUAL(0, get_prev_pandigital1(1234567));
	LONGS_EQUAL(0, get_prev_pandigital1(1478));
	int i = 0;
	prime p;
	for (i = 7654321; i > 0; i = get_prev_pandigital1(i))
		if (p.is_prime(i))
			break;
	LONGS_EQUAL(7652413, i);
}
const int triangleNumberCount = 100;
class triangle_word
{
public:
	triangle_word()
	{
		for (int i = 1; i < triangleNumberCount; i++)
			triangleNumbers[i] = i * (i + 1) / 2;
	}
	bool isTriangleWord(const char * word)
	{
		int sum = 0;
		while (*word != 0)
			sum += *(word++) - 'A' + 1;
		return isTriangleNumber(sum);
	}
	bool isTriangleNumber(int n)
	{
		for (int i = 0; i < triangleNumberCount; i++)
			if (triangleNumbers[i] == n)
				return true;
		return false;
	}
private:
	int triangleNumbers[triangleNumberCount];
};
TEST(project_euler, problem_42)
{
	triangle_word tw;
	CHECK(tw.isTriangleWord("SKY"));
	CHECK(!tw.isTriangleWord("SKX"));
#include "words.h"
	int count = 0;
	int max = sizeof words / sizeof words[0];
	for (int i = 0; i < max; i++)
		if (tw.isTriangleWord(words[i]))
			count++;
	LONGS_EQUAL(162, count);
}
bool divisible(long long n, int d)
{
	return n / d * d == n;
}
bool is_problem_43(long long n)
{
	return (divisible(n % 1000, 17) && divisible(n / 10 % 1000, 13)
			&& divisible(n / 100 % 1000, 11) && divisible(n / 1000 % 1000, 7)
			&& divisible(n / 10000 % 1000, 5)
			&& divisible(n / 100000 % 1000, 3) && divisible(n / 1000000 % 1000,
			2));
}
IGNORE_TEST(project_euler, problem_43)
{
	LONGS_EQUAL(1, get_prev_pandigital1(10));
	LONGS_EQUAL(201, get_prev_pandigital1(210));
	LONGS_EQUAL(21, get_prev_pandigital1(102));
	CHECK(is_problem_43(1406357289));
	CHECK(!is_problem_43(1406357288));
	CHECK(!is_problem_43(1406356289));
	CHECK(!is_problem_43(1406347289));
	CHECK(!is_problem_43(1406257289));
	CHECK(!is_problem_43(1416357289));
	long long i = 0;
	prime p;
	long long sum = 0;
	for (i = 9876543210; i > 987654321; i = get_prev_pandigital1(i))
		if (is_problem_43(i))
			sum += i;
	LONGS_EQUAL(16695334890, sum);
}

class Pentagonal
{
public:
	Pentagonal()
	{
	}
	long long get_Pentagonal(long long n)
	{
		return n * (3 * n - 1) / 2;
	}
	bool is_Pentagonal(long long pen)
	{
		long long i = sqrt(2 * pen / 3) + 1;
		for (long long p = get_Pentagonal(i); p <= pen; p = get_Pentagonal(i++))
			if (p == pen)
				return true;
		return false;
	}
};
TEST(project_euler, problem_44)
{
	LONGS_EQUAL(1, Pentagonal().get_Pentagonal(1));
	LONGS_EQUAL(5, Pentagonal().get_Pentagonal(2));
	CHECK(!Pentagonal().is_Pentagonal(2));
	CHECK(Pentagonal().is_Pentagonal(5));
	CHECK(Pentagonal().is_Pentagonal(145));
	CHECK(Pentagonal().is_Pentagonal(145));
	Pentagonal p;
	int n = p.get_Pentagonal(196) + 2 * p.get_Pentagonal(19175);
	CHECK(!Pentagonal().is_Pentagonal(n));

	int pd = 0;
	int d = 1;
	bool found = false;
	long long pk, pj;
	while (!found && d < 10000)
	{
		pd = p.get_Pentagonal(d);
		for (int n = 1; n < d; n++)
		{
			int k = (pd - p.get_Pentagonal(n));
			if (k / (3 * n) * (3 * n) == k)
			{
				k /= (3 * n);
				pk = p.get_Pentagonal(k);
				pj = pk + pd;
				if (p.is_Pentagonal(pj + pk))
				{
					found = true;
					break;
				}
			}

		}
		d++;
	}
	CHECK(found);
	LONGS_EQUAL(5482660, pd);
}
long long get_Pentagonal(long long n)
{
	return n * (3 * n - 1) / 2;
}
long long get_Triangle(long long n)
{
	return n * (n + 1) / 2;
}
TEST(project_euler, problem_45)
{
	int h = 144, p = 166, t = 286;
	int H;
	while (1)
	{
		H = h * (2 * h - 1);
		for (; get_Pentagonal(p) < H; p++)
			;
		for (; get_Triangle(t) < H; t++)
			;
		if (H == get_Pentagonal(p) && H == get_Triangle(t))
			break;
		h++;
	}
	LONGS_EQUAL(1533776805, H);
}
class OddComposedNumber
{
public:
	int isDecomposable(int n)
	{
		for (int i = 0; n > 2 * i * i; i++)
		{
			if (p.is_prime(n - 2 * i * i))
				return i;
		}
		return -1;
	}
private:
	prime p;
};
TEST(project_euler, problem_46)
{
	OddComposedNumber cn;
	LONGS_EQUAL(1, cn.isDecomposable(9));
	LONGS_EQUAL(0, cn.isDecomposable(11));
	LONGS_EQUAL(2, cn.isDecomposable(27));
	LONGS_EQUAL(-1, cn.isDecomposable(12));
	int i = 9;
	for (; i < 10000; i += 2)
	{
		if (-1 == cn.isDecomposable(i))
			break;
	}
	LONGS_EQUAL(5777, i);
}
int get_distinct_factor_count(int n, int max = 4)
{
	int count = 0;

	for (int i = 2; n > 1; i++)
	{
		if (n / i * i == n)
		{
			count++;
			while (n / i * i == n)
				n /= i;
			if (count == max && n != 1)
				return count + 1;
		}
		if (i != 2)
			i++;
	}
	return count;
}
IGNORE_TEST(project_euler, problem_47)
{
	LONGS_EQUAL(1, get_distinct_factor_count(2));
	LONGS_EQUAL(1, get_distinct_factor_count(3));
	LONGS_EQUAL(1, get_distinct_factor_count(4));
	LONGS_EQUAL(1, get_distinct_factor_count(5));
	LONGS_EQUAL(2, get_distinct_factor_count(6));
	LONGS_EQUAL(1, get_distinct_factor_count(8));
	LONGS_EQUAL(3, get_distinct_factor_count(644));
	LONGS_EQUAL(3, get_distinct_factor_count(644, 3));
	LONGS_EQUAL(3, get_distinct_factor_count(644, 2));
	LONGS_EQUAL(2, get_distinct_factor_count(644, 1));

	int i;
	for (i = 2; i < 1000000; i++)
	{
		int j = i;
		for (; j < i + 4; j++)
			if (get_distinct_factor_count(j, 4) != 4)
				break;
		if (j == i + 4)
			break;
		i = j + 1;
	}
	LONGS_EQUAL(134043, i);
}
long long get_last_digits_of_self_exp(long long x, long long n)
{
	long long prod = 1;
	for (int i = 0; i < x; i++)
		prod = prod * x % n;
	return prod % n;
}
TEST(project_euler, problem_48)
{
	LONGS_EQUAL(1, get_last_digits_of_self_exp(1,10));
	LONGS_EQUAL(4, get_last_digits_of_self_exp(2,10));
	LONGS_EQUAL(7, get_last_digits_of_self_exp(3,10));
	LONGS_EQUAL(25, get_last_digits_of_self_exp(5,100));
	LONGS_EQUAL(16%100, get_last_digits_of_self_exp(8,100));
	LONGS_EQUAL(67, get_last_digits_of_self_exp(123,100));
	long long sum = 0;
	for (int i = 1; i <= 1000; i++)
	{
		sum += get_last_digits_of_self_exp(i, 10000000000);
		sum %= 10000000000;
	}
	LONGS_EQUAL(9110846700, sum);
}
int binarySearch(const int *data, int size, int n)
{
	int begin = 0;
	int end = size - 1;
	while (begin <= end)
	{
		int mid = (begin + end) / 2;
		if (data[mid] == n)
			return mid;
		else if (data[mid] > n)
			end = mid - 1;
		else
			begin = mid + 1;
	}
	return -1;
}

bool are_permutations(int x, int y)
{
	while (x > 0)
	{
		int dx = x % 10;
		x /= 10;
		int yscale = 1;
		while (yscale <= y)
		{
			int dy = y / yscale % 10;
			if (dx == dy)
			{
				y = y / yscale / 10 * yscale + y % yscale;
				break;
			}
			yscale *= 10;
		}
		if (yscale / 10 > y)
			return false;
	}
	return y == 0;
}
TEST(project_euler, problem_49)
{
	int data[] =
	{ 1, 2, 3, 6, 7, 9 };
	LONGS_EQUAL(-1, binarySearch(data, 1, 3));
	LONGS_EQUAL(-1, binarySearch(data, 2, 3));
	LONGS_EQUAL(0, binarySearch(data, 1, 1));
	LONGS_EQUAL(1, binarySearch(data, 3, 2));
	LONGS_EQUAL(0, binarySearch(data, 3, 1));
	LONGS_EQUAL(2, binarySearch(data, 3, 3));
	LONGS_EQUAL(1, binarySearch(data, 5, 2));
	CHECK(are_permutations(1,1));
	CHECK(!are_permutations(1,2));
	CHECK(are_permutations(12,21));
	CHECK(!are_permutations(5781,5881));
	CHECK(!are_permutations(5581,5881));
	int primes[5000];
	int prime_count = 0;
	prime p;
	for (int i = 1000; i < 10000; i++)
		if (p.is_prime(i))
			primes[prime_count++] = i;
	long long result[3];
	for (int i = prime_count - 1; i >= 0; i--)
	{
		int i1;
		for (i1 = get_prev_pandigital1(primes[i]); i1 != 0; i1
				= get_prev_pandigital1(i1))
		{
			if (-1 != binarySearch(primes, prime_count, i1))
			{
				if (-1 != binarySearch(primes, prime_count, i1 * 2 - primes[i]))
				{
					if (are_permutations(primes[i], i1 * 2 - primes[i])
							&& primes[i] != 8147)
					{
						result[2] = primes[i];
						result[1] = i1;
						result[0] = i1 * 2 - primes[i];
					}
				}
			}
		}
	}
	LONGS_EQUAL(2969, result[0]);
	LONGS_EQUAL(6299, result[1]);
	LONGS_EQUAL(9629, result[2]);
}

int get_longest_prime_sum_starts_from(int start, int max, int * last)
{
	int i = start;
	int sum = 0;
	*last = 0;
	int count = 0;
	int last_count = 0;
	prime p;
	while (sum + i < max)
	{
		if (p.is_prime(i))
		{
			count++;
			sum += i;
			if (p.is_prime(sum))
			{
				*last = sum;
				last_count = count;
			}

		}
		i++;
	}
	return last_count;
}
IGNORE_TEST(project_euler, problem_50)
{
	int count, last, max_count = 0, max_last = 0;
	int max = 1000000;
	prime p;
	for (int i = 2; i < max; i++)
	{
		if (p.is_prime(i))
		{
			count = get_longest_prime_sum_starts_from(i, max, &last);
			if (count > max_count)
			{
				max_count = count;
				max_last = last;
			}
		}
	}
	LONGS_EQUAL(543, max_count);
	LONGS_EQUAL(997651, max_last);
}
class elevenCimal
{
public:
	elevenCimal(int n)
	{
		data = n;
		init();
	}
	elevenCimal(int n1, int n2)
	{
		data = n1 * 11 + n2;
		init();
	}
	int replaceWith(int digit)
	{
		return decimal + changer * digit;
	}
	int getRaw()
	{
		return data;
	}
	int primeFamilyMemberCount(int expect = 1)
	{
		int count = 0;
		for (int i = 0; i < 10; i++)
		{
			if (10 - i + count < expect)
				return 0;
			if (p.is_prime(replaceWith(i)))
				count++;
		}
		return count;
	}
private:
	void init()
	{
		changer = decimal = 0;
		int d = data;
		int scale = 1;
		while (d > 0)
		{
			int new_digit = d % 11;
			if (new_digit == 10)
				changer += scale;
			else
				decimal += new_digit * scale;
			scale *= 10;
			d /= 11;
		}
	}
	int data;
	int decimal;
	int changer;
	prime p;
};
IGNORE_TEST(project_euler, problem_51)
{
	LONGS_EQUAL(10, elevenCimal(1,10).replaceWith(0));
	LONGS_EQUAL(13, elevenCimal(1,10).replaceWith(3));
	LONGS_EQUAL(13, elevenCimal(1,10).replaceWith(3));
	LONGS_EQUAL(7, elevenCimal(10,3).primeFamilyMemberCount());
	int i;
	for (i = 11; i < 10000000; i += 2)
	{
		elevenCimal ec(i);
		if (ec.replaceWith(0) != 0 && ec.replaceWith(1) != ec.replaceWith(0))
			if (ec.primeFamilyMemberCount(8) > 7)
			{
				break;
			}
	}
	CHECK(prime().is_prime(elevenCimal(i).replaceWith(1)));
}
int get_upper_scale(int n)
{
	static const int scales[] =
	{ 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000 };
	static const int size = sizeof scales / sizeof scales[0];
	for (int i = 0; i < size; i++)
		if (scales[i] > n)
			return scales[i];
	return -1;
}
TEST(project_euler, problem_52)
{
	LONGS_EQUAL(10, get_upper_scale(1));
	LONGS_EQUAL(100, get_upper_scale(22));
	int d;
	for (int i = 0; i < 100000; i++)
	{
		d = get_upper_scale(i) + i;
		if (are_permutations(d, d * 6) && are_permutations(d, d * 5)
				&& are_permutations(d, d * 4) && are_permutations(d, d * 3)
				&& are_permutations(d, d * 2))
			break;
	}
	LONGS_EQUAL(142857, d);
}

int get_combination(int n, int R)
{
	int v = 1;
	int r;
	for (r = n - 1; r >= R; r--)
	{
		v = v * (r + 1) / (n - r);
	}
	return v;
}
int get_count_of_combination_greater_than(int n, int big)
{
	long long v = 1;
	int r;
	for (r = n - 1; r >= n / 2; r--)
	{
		v = v * (r + 1) / (n - r);
		if (v > big)
			break;
	}
	if (r < n / 2)
		return 0;
	return (r - n / 2) * 2 + 1 - n % 2;
}
TEST(project_euler, problem_53)
{
	const int big = 1000000;
	LONGS_EQUAL(5, get_combination(5, 1));
	LONGS_EQUAL(0, get_count_of_combination_greater_than(5, big));
	LONGS_EQUAL(3, get_count_of_combination_greater_than(6, 10));//1,6,30,30,6,1
	LONGS_EQUAL(0, get_count_of_combination_greater_than(22, big));
	LONGS_EQUAL(4, get_count_of_combination_greater_than(23, big));
	LONGS_EQUAL(7, get_count_of_combination_greater_than(24, big));
	int count = 0;
	for (int n = 23; n <= 100; n++)
		count += get_count_of_combination_greater_than(n, big);
	LONGS_EQUAL(4075, count);
}
#include "poker.h"
#include "pokerHand.h"
TEST(project_euler, problem_54)
{
	int count = 0;
	const int MAX = sizeof poker_pairs / sizeof poker_pairs[0];
	for (int i = 0; i < MAX; i++)
		if (pokerHand(poker_pairs[i]) > pokerHand(poker_pairs[i] + 15))
			count++;
	LONGS_EQUAL(376, count);
}
TEST(project_euler, problem_55)
{
	LONGS_EQUAL(2, dec(1).reverse_add().to_long());
	LONGS_EQUAL(14, dec(7).reverse_add().to_long());
	LONGS_EQUAL(88, dec(17).reverse_add().to_long());
	LONGS_EQUAL(1292, dec(349).reverse_add().to_long());
	LONGS_EQUAL(121, dec(47).reverse_add().to_long());
	CHECK(!dec(47).is_palindrome());
	CHECK(dec(474).is_palindrome());
	CHECK(dec(4774).is_palindrome());
	int count = 0;
	for (int i = 1; i < 10000; i++)
	{
		dec d(i);
		int j;
		for (j = 0; j < 50; j++)
		{
			d.reverse_add();
			if (d.is_palindrome())
				break;
		}
		if (j == 50)
			count++;
	}
	LONGS_EQUAL(249, count);
}
TEST(project_euler, problem_56)
{
	LONGS_EQUAL(1, dec(1).exp(10).to_long());
	LONGS_EQUAL(8, dec(2).exp(3).to_long());
	int max = 0;
	for (int i = 1; i < 100; i++)
	{
		dec d(i);
		for (int j = 2; j < 100; j++)
		{
			d *= i;
			int sum = d.digits_sum();
			if (sum > max)
				max = sum;
		}
	}
	LONGS_EQUAL(972, max);
}

dec deduct_from(int d1, int n1)
{
	dec d(d1), n(n1);
	return d.deducted_from(n);
}
TEST(project_euler, problem_57)
{
	LONGS_EQUAL(1, deduct_from(2, 3).to_long());
	LONGS_EQUAL(11, deduct_from(2, 13).to_long());
	LONGS_EQUAL(3, deduct_from(9, 12).to_long());
	LONGS_EQUAL(3, deduct_from(9, 12).get_digit(0));
	LONGS_EQUAL(1, deduct_from(9, 12).get_count());
	int count = 0;
	dec n(3), d(2);
	for (long long i = 0; i < 1000; i++)
	{
		if (n.get_count() > d.get_count())
			count++;
		n += d;
		n += d;
		d.deducted_from(n);
	}
	LONGS_EQUAL(153, count);
}
TEST(project_euler, problem_58)
{
	int count = 0;
	prime p;
	int i;
	for (i = 1; i < 20000; i++)
	{
		for (int j = 1; j < 4; j++)
			if (p.is_prime(get_diagnal_of_spiral(i, j)))
				count++;
		if (count * 100 / (i * 4 + 1) < 10)
			break;
	}
	LONGS_EQUAL(26241, i*2+1);
}
char cipher[] =
{ 79, 59, 12, 2, 79, 35, 8, 28, 20, 2, 3, 68, 8, 9, 68, 45, 0, 12, 9, 67, 68,
		4, 7, 5, 23, 27, 1, 21, 79, 85, 78, 79, 85, 71, 38, 10, 71, 27, 12, 2,
		79, 6, 2, 8, 13, 9, 1, 13, 9, 8, 68, 19, 7, 1, 71, 56, 11, 21, 11, 68,
		6, 3, 22, 2, 14, 0, 30, 79, 1, 31, 6, 23, 19, 10, 0, 73, 79, 44, 2, 79,
		19, 6, 28, 68, 16, 6, 16, 15, 79, 35, 8, 11, 72, 71, 14, 10, 3, 79, 12,
		2, 79, 19, 6, 28, 68, 32, 0, 0, 73, 79, 86, 71, 39, 1, 71, 24, 5, 20,
		79, 13, 9, 79, 16, 15, 10, 68, 5, 10, 3, 14, 1, 10, 14, 1, 3, 71, 24,
		13, 19, 7, 68, 32, 0, 0, 73, 79, 87, 71, 39, 1, 71, 12, 22, 2, 14, 16,
		2, 11, 68, 2, 25, 1, 21, 22, 16, 15, 6, 10, 0, 79, 16, 15, 10, 22, 2,
		79, 13, 20, 65, 68, 41, 0, 16, 15, 6, 10, 0, 79, 1, 31, 6, 23, 19, 28,
		68, 19, 7, 5, 19, 79, 12, 2, 79, 0, 14, 11, 10, 64, 27, 68, 10, 14, 15,
		2, 65, 68, 83, 79, 40, 14, 9, 1, 71, 6, 16, 20, 10, 8, 1, 79, 19, 6,
		28, 68, 14, 1, 68, 15, 6, 9, 75, 79, 5, 9, 11, 68, 19, 7, 13, 20, 79,
		8, 14, 9, 1, 71, 8, 13, 17, 10, 23, 71, 3, 13, 0, 7, 16, 71, 27, 11,
		71, 10, 18, 2, 29, 29, 8, 1, 1, 73, 79, 81, 71, 59, 12, 2, 79, 8, 14,
		8, 12, 19, 79, 23, 15, 6, 10, 2, 28, 68, 19, 7, 22, 8, 26, 3, 15, 79,
		16, 15, 10, 68, 3, 14, 22, 12, 1, 1, 20, 28, 72, 71, 14, 10, 3, 79, 16,
		15, 10, 68, 3, 14, 22, 12, 1, 1, 20, 28, 68, 4, 14, 10, 71, 1, 1, 17,
		10, 22, 71, 10, 28, 19, 6, 10, 0, 26, 13, 20, 7, 68, 14, 27, 74, 71,
		89, 68, 32, 0, 0, 71, 28, 1, 9, 27, 68, 45, 0, 12, 9, 79, 16, 15, 10,
		68, 37, 14, 20, 19, 6, 23, 19, 79, 83, 71, 27, 11, 71, 27, 1, 11, 3,
		68, 2, 25, 1, 21, 22, 11, 9, 10, 68, 6, 13, 11, 18, 27, 68, 19, 7, 1,
		71, 3, 13, 0, 7, 16, 71, 28, 11, 71, 27, 12, 6, 27, 68, 2, 25, 1, 21,
		22, 11, 9, 10, 68, 10, 6, 3, 15, 27, 68, 5, 10, 8, 14, 10, 18, 2, 79,
		6, 2, 12, 5, 18, 28, 1, 71, 0, 2, 71, 7, 13, 20, 79, 16, 2, 28, 16, 14,
		2, 11, 9, 22, 74, 71, 87, 68, 45, 0, 12, 9, 79, 12, 14, 2, 23, 2, 3, 2,
		71, 24, 5, 20, 79, 10, 8, 27, 68, 19, 7, 1, 71, 3, 13, 0, 7, 16, 92,
		79, 12, 2, 79, 19, 6, 28, 68, 8, 1, 8, 30, 79, 5, 71, 24, 13, 19, 1, 1,
		20, 28, 68, 19, 0, 68, 19, 7, 1, 71, 3, 13, 0, 7, 16, 73, 79, 93, 71,
		59, 12, 2, 79, 11, 9, 10, 68, 16, 7, 11, 71, 6, 23, 71, 27, 12, 2, 79,
		16, 21, 26, 1, 71, 3, 13, 0, 7, 16, 75, 79, 19, 15, 0, 68, 0, 6, 18, 2,
		28, 68, 11, 6, 3, 15, 27, 68, 19, 0, 68, 2, 25, 1, 21, 22, 11, 9, 10,
		72, 71, 24, 5, 20, 79, 3, 8, 6, 10, 0, 79, 16, 8, 79, 7, 8, 2, 1, 71,
		6, 10, 19, 0, 68, 19, 7, 1, 71, 24, 11, 21, 3, 0, 73, 79, 85, 87, 79,
		38, 18, 27, 68, 6, 3, 16, 15, 0, 17, 0, 7, 68, 19, 7, 1, 71, 24, 11,
		21, 3, 0, 71, 24, 5, 20, 79, 9, 6, 11, 1, 71, 27, 12, 21, 0, 17, 0, 7,
		68, 15, 6, 9, 75, 79, 16, 15, 10, 68, 16, 0, 22, 11, 11, 68, 3, 6, 0,
		9, 72, 16, 71, 29, 1, 4, 0, 3, 9, 6, 30, 2, 79, 12, 14, 2, 68, 16, 7,
		1, 9, 79, 12, 2, 79, 7, 6, 2, 1, 73, 79, 85, 86, 79, 33, 17, 10, 10,
		71, 6, 10, 71, 7, 13, 20, 79, 11, 16, 1, 68, 11, 14, 10, 3, 79, 5, 9,
		11, 68, 6, 2, 11, 9, 8, 68, 15, 6, 23, 71, 0, 19, 9, 79, 20, 2, 0, 20,
		11, 10, 72, 71, 7, 1, 71, 24, 5, 20, 79, 10, 8, 27, 68, 6, 12, 7, 2,
		31, 16, 2, 11, 74, 71, 94, 86, 71, 45, 17, 19, 79, 16, 8, 79, 5, 11, 3,
		68, 16, 7, 11, 71, 13, 1, 11, 6, 1, 17, 10, 0, 71, 7, 13, 10, 79, 5, 9,
		11, 68, 6, 12, 7, 2, 31, 16, 2, 11, 68, 15, 6, 9, 75, 79, 12, 2, 79, 3,
		6, 25, 1, 71, 27, 12, 2, 79, 22, 14, 8, 12, 19, 79, 16, 8, 79, 6, 2,
		12, 11, 10, 10, 68, 4, 7, 13, 11, 11, 22, 2, 1, 68, 8, 9, 68, 32, 0, 0,
		73, 79, 85, 84, 79, 48, 15, 10, 29, 71, 14, 22, 2, 79, 22, 2, 13, 11,
		21, 1, 69, 71, 59, 12, 14, 28, 68, 14, 28, 68, 9, 0, 16, 71, 14, 68,
		23, 7, 29, 20, 6, 7, 6, 3, 68, 5, 6, 22, 19, 7, 68, 21, 10, 23, 18, 3,
		16, 14, 1, 3, 71, 9, 22, 8, 2, 68, 15, 26, 9, 6, 1, 68, 23, 14, 23, 20,
		6, 11, 9, 79, 11, 21, 79, 20, 11, 14, 10, 75, 79, 16, 15, 6, 23, 71,
		29, 1, 5, 6, 22, 19, 7, 68, 4, 0, 9, 2, 28, 68, 1, 29, 11, 10, 79, 35,
		8, 11, 74, 86, 91, 68, 52, 0, 68, 19, 7, 1, 71, 56, 11, 21, 11, 68, 5,
		10, 7, 6, 2, 1, 71, 7, 17, 10, 14, 10, 71, 14, 10, 3, 79, 8, 14, 25, 1,
		3, 79, 12, 2, 29, 1, 71, 0, 10, 71, 10, 5, 21, 27, 12, 71, 14, 9, 8, 1,
		3, 71, 26, 23, 73, 79, 44, 2, 79, 19, 6, 28, 68, 1, 26, 8, 11, 79, 11,
		1, 79, 17, 9, 9, 5, 14, 3, 13, 9, 8, 68, 11, 0, 18, 2, 79, 5, 9, 11,
		68, 1, 14, 13, 19, 7, 2, 18, 3, 10, 2, 28, 23, 73, 79, 37, 9, 11, 68,
		16, 10, 68, 15, 14, 18, 2, 79, 23, 2, 10, 10, 71, 7, 13, 20, 79, 3, 11,
		0, 22, 30, 67, 68, 19, 7, 1, 71, 8, 8, 8, 29, 29, 71, 0, 2, 71, 27, 12,
		2, 79, 11, 9, 3, 29, 71, 60, 11, 9, 79, 11, 1, 79, 16, 15, 10, 68, 33,
		14, 16, 15, 10, 22, 73 };

bool is_space(char ch){
	return ch == ' ';
}
bool is_lower(char ch){
	return ch >= 'a' && ch <='z';
}
bool is_upper(char ch){
	return ch >= 'A' && ch <='Z';
}
TEST(project_euler, problem_59)
{
	const int size = sizeof(cipher)/sizeof(cipher[0]);
	const int password_size = 3;
	char password[password_size+1];
	password[password_size] = 0;
	for (int j = 0; j < password_size; j++)
		for (char p='a'; p <='z'; p++){
			int i;
			int lower = 0;
			int upper = 0;
			int space = 0;
			int note = 0;
			for(i = j; i < size; i+= password_size) {
				char decipher = p ^ cipher[i];
				if (decipher <' ' || decipher>'~')
					break;
				if (is_space(decipher)) space++;
				else if (is_lower(decipher)) lower++;
				else if (is_upper(decipher)) upper++;
				else note++;
			}
			if (i >= size && space > 2) {
				password[j] = p;
				break;
			}
		}
	char decipher[size +1];
	decipher[size]= 0;
	int sum = 0;
	for (int i = 0; i < size; i++)
		sum +=(decipher[i]= cipher[i] ^ password[i %3]);
	LONGS_EQUAL(107359, sum);

}

