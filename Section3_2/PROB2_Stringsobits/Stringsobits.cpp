/*
ID: joshoy71
PROG: kimbits
LANG: C++11
*/

/*
TEST RESULT:
   Test 1: TEST OK [0.008 secs, 3504 KB]
   Test 2: TEST OK [0.008 secs, 3504 KB]
   Test 3: TEST OK [0.008 secs, 3504 KB]
   Test 4: TEST OK [0.005 secs, 3504 KB]
   Test 5: TEST OK [0.005 secs, 3504 KB]
   Test 6: TEST OK [0.005 secs, 3504 KB]
   Test 7: TEST OK [0.008 secs, 3504 KB]
   Test 8: TEST OK [0.008 secs, 3504 KB]
   Test 9: TEST OK [0.005 secs, 3504 KB]
   Test 10: TEST OK [0.011 secs, 3504 KB]
   Test 11: TEST OK [0.005 secs, 3504 KB]
   Test 12: TEST OK [0.005 secs, 3504 KB]
   Test 13: TEST OK [0.005 secs, 3504 KB]
*/

#include <fstream>

using namespace std;

#define bit(N) (1 << ((N) - 1))

const int N_MAX = 31;

static ifstream fin("kimbits.in");
static ofstream fout("kimbits.out");

static int N, L;
static long long I;
static long long dp[N_MAX + 1][N_MAX + 1] = { { 0 } };

int main(int argc, char* argv[])
{
	fin >> N >> L >> I;

	if (I == 1) {
		for (int i = 1; i <= N; ++i) {
			fout << 0;
		}
		fout << endl;
		return 0;
	}
	else {
		// init
		for (int i = 0; i <= N; ++i) {
			dp[0][i] = 1;
			dp[i][0] = 1;
		}
	}

	//calculate size of (n bits number, at most m '1' bits)
	for (int n = 1; n <= N; ++n) {
		for (int m = 1; m <= N; ++m) {
			dp[n][m] = dp[n - 1][m] + dp[n - 1][m - 1];
		}
	}

	//solve
	auto maxIndex = I;
	for (int i = N; i >= 1; --i) {
		if (dp[i - 1][L] >= maxIndex) {
			fout << 0;
		} else {
			fout << 1;
			maxIndex -= (dp[i - 1][L]);
			--L;	//one less 1, don't forget
		}
	}
	fout << endl;

	return 0;
}
