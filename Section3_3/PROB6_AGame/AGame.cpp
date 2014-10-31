/*
ID: joshoy71
PROG: game1
LANG: C++11
*/

/*
TEST RESULT:
Executing...
   Test 1: TEST OK [0.008 secs, 3656 KB]
   Test 2: TEST OK [0.008 secs, 3656 KB]
   Test 3: TEST OK [0.005 secs, 3656 KB]
   Test 4: TEST OK [0.005 secs, 3656 KB]
   Test 5: TEST OK [0.005 secs, 3656 KB]
   Test 6: TEST OK [0.005 secs, 3656 KB]
   Test 7: TEST OK [0.005 secs, 3656 KB]
   Test 8: TEST OK [0.008 secs, 3656 KB]
   Test 9: TEST OK [0.005 secs, 3656 KB]
   Test 10: TEST OK [0.005 secs, 3656 KB]
   Test 11: TEST OK [0.005 secs, 3656 KB]
   Test 12: TEST OK [0.011 secs, 3656 KB]
   Test 13: TEST OK [0.008 secs, 3656 KB]
   Test 14: TEST OK [0.008 secs, 3656 KB]
   Test 15: TEST OK [0.008 secs, 3656 KB]
   Test 16: TEST OK [0.005 secs, 3656 KB]

All tests OK.
YOUR PROGRAM ('game1') WORKED FIRST TIME!  That's fantastic
-- and a rare thing.  Please accept these special automated
congratulations.
*/

#include <fstream>
#include <vector>
using namespace std;

#define min(_A_, _B_) (((_A_) < (_B_)) ? (_A_) : (_B_))
const int N_MAX = 200;

static ifstream fin("game1.in");
static ofstream fout("game1.out");

static int N;
static vector<int> v, s;
static int dp[N_MAX + 1][N_MAX + 1] = { { 0 } };

int main(int argc, char* argv[])
{
	fin >> N;
	int tmp, sum = 0;
	s.push_back(0); v.push_back(0);
	for (int i = 1; i <= N; i++) {
		fin >> tmp;
		sum += tmp;
		v.push_back(tmp);
		s.push_back(sum);
		dp[i][i] = tmp;
	}

	sum = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j + i <= N; j++) {
			sum = s[j + i] - s[j - 1];
			dp[j][j + i] = sum - min(dp[j][j + i - 1], dp[j + 1][j + i]);
		}
	}

	fout << dp[1][N] << " " << min(dp[1][N - 1], dp[2][N]) << endl;

	return 0;
}