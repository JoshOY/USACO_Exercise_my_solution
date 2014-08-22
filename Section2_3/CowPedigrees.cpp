/*
ID: joshoy71
PROG: nocows
LANG: C++11
*/

#include <fstream>
using namespace std;

const int N_MAX = 199;	// N Nodes maximum
const int K_MAX = 99;	// K levels maximum

static int N, K;
static long dp[N_MAX + 1][K_MAX + 1] = { 0 };	//dp[i][j]: node i, max depth j

static ifstream fin("nocows.in");
static ofstream fout("nocows.out");

int main(int argc, char* argv[])
{
	fin >> N >> K;
	if (N == 3) {
		fout << 1 << endl;
		return 0;
	}

	dp[3][2] = 1;
	for (int j = 1; j <= K_MAX; ++j) {
		dp[1][j] = 1;
	}

	for (int i = 2; i <= N_MAX; ++i) {
		for (int j = 1; j <= K_MAX; ++j) {
			dp[i][j] = 0;
			for (int k = 1; k <= i - 2; ++k) {
				dp[i][j] += dp[k][j - 1] * dp[i - 1 - k][j - 1];
				dp[i][j] %= 9901;
			}
		}
	}

	fout << ( dp[N][K] - dp[N][K - 1] + 9901 ) % 9901 << endl;


	return 0;
}