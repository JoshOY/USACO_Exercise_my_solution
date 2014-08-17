/*
ID: joshoy71
PROG: subset
LANG: C++11
*/

#include <fstream>
#include <iostream>

using namespace std;

const int MAX_N = 39;
static int N;
static int target;
static long long dp[MAX_N + 1][(MAX_N + 1) * (MAX_N + 2) / 2] = { { 0 } };


int main(int argc, char* argv[])
{
	ifstream fin("subset.in");
	ofstream fout("subset.out");

	fin >> N;
	target = (N * (N + 1) / 4);

	if ((N % 4 != 0) && ((N + 1) % 4 != 0)) {
		fout << 0 << endl;
		return 0;
	}

	dp[1][1] = 1;
	for (int i = 2; i <= N; ++i) {
		for (int j = 1; j <= target; ++j) {
			if (j >= i) {
				dp[i][j] = dp[i - 1][j] + dp[i - 1][j - i];
			}
			else {
				dp[i][j] = dp[i - 1][j];
			}
		}
	}

	fout << dp[N][target] << endl;

	return 0;
}