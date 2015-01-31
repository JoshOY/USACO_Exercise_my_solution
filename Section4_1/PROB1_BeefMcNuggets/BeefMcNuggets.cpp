/*
ID: joshoy71
PROG: nuggets
LANG: C++11
*/

/*
解法：很有趣的一题。
这里先说一下裴蜀定理：
如果已知两个数a和b，现有任意正整数m，
若存在两个正整数x, y使得ax + by = m，那么等价于m是a, b最大公约数gcd(a, b)的整数倍数。
顺带一提，那个2,000,000,000没什么用……范围限制在256 * 256即可。
然后就是一个背包问题了。

Compiling...
Compile: OK

Executing...
   Test 1: TEST OK [0.005 secs, 3560 KB]
   Test 2: TEST OK [0.003 secs, 3560 KB]
   Test 3: TEST OK [0.003 secs, 3560 KB]
   Test 4: TEST OK [0.005 secs, 3560 KB]
   Test 5: TEST OK [0.003 secs, 3560 KB]
   Test 6: TEST OK [0.005 secs, 3560 KB]
   Test 7: TEST OK [0.008 secs, 3560 KB]

All tests OK.
YOUR PROGRAM ('nuggets') WORKED FIRST TIME!  That's fantastic
-- and a rare thing.  Please accept these special automated
congratulations.
*/

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const long long N_MAX = 256;

static ifstream fin("nuggets.in", ios::in);
static ofstream fout("nuggets.out", ios::out);

static int N;
static vector<long long> box_size_vec;
static long long min_gcd = 1;
static bool can_combined[N_MAX * N_MAX + 1] = { false };
static long long result = 0;

long long gcd(long long x,long long y )
{
    if (x < y) return gcd(y, x);
    if (y == 0) return x;
    else
    {
         if (x % 2 == 0) {                 
           if (y % 2 == 0)
               return 2 * gcd(x >> 1, y >> 1);    
           else
               return gcd(x >> 1, y ); 
         }
         else {
           if (y % 2 == 0)
               return gcd(x, y >> 1);
           else
               return gcd(y,x-y); 
         }
    }
}

int main(int argc, char* argv[])
{
	//Input
	fin >> N;
	long long tmp;
	for (int i = 0; i < N; i++) {
		fin >> tmp;
		min_gcd *= tmp;
		//如果包装中有1那就一定没有无法组成的数了
		if (tmp == 1) {
			fout << 0 << endl;
			return 0;
		}
		box_size_vec.push_back(tmp);
		can_combined[tmp] = true;
	}
	std::sort(box_size_vec.begin(), box_size_vec.end());

	for (int i = 0; i < N; i++) {
		min_gcd = gcd(min_gcd, box_size_vec[i]);
	}
	if (min_gcd != 1) {
		fout << 0 << endl;
		return 0;
	}

	int index;
	for (int i = 1; i < N_MAX * N_MAX; ++i) {
		for (index = 0; index < N; ++index) {
			if ((box_size_vec[index] < i) && (can_combined[i - box_size_vec[index]])) {
				can_combined[i] = true;
				break;
			}
		}
	}

	for (int i = 1; i < N_MAX * N_MAX; ++i) {
		if (can_combined[i] == false) {
			result = i;
		}
	}

	fout << result << endl;

	return 0;
}