/*
ID: joshoy71
PROG: stamps
LANG: C++11
*/

#include <fstream>

using namespace std;

const int STAMPS_N_MAX = 50;
const int STAMPS_K_MAX = 200;
const int STAMPS_VALUE_MAX = 10000;

static ifstream fin("stamps.in");
static ofstream fout("stamps.out");

static int stampsSet[STAMPS_N_MAX + 1] = { 0 };
static int dp[STAMPS_K_MAX * STAMPS_VALUE_MAX + 1] = { 0 };

static int K, N;
static int result;

void input()
{
	fin >> K >> N;
	for (int i = 1; i <= N; ++i) {
		fin >> stampsSet[i];
	}
	for (int i = 1; i <= STAMPS_K_MAX * STAMPS_VALUE_MAX; ++i) {
		dp[i] = -1;
	}
	return;
}

int solve()
{
	int targetValue = 0;
	bool canAssemble = true;

	while (canAssemble) {
		++targetValue;
		canAssemble = false;
		for (int i = 1; i <= N; ++i) {	
			if ((targetValue >= stampsSet[i]) && (dp[targetValue - stampsSet[i]] != -1) && ((dp[targetValue - stampsSet[i]] < K))) {
				if ((dp[targetValue] == -1) || ((dp[targetValue] != -1) && (dp[targetValue] > dp[targetValue - stampsSet[i]] + 1))) {
					dp[targetValue] = dp[targetValue - stampsSet[i]] + 1;
					canAssemble = true;
				}
			}
		}
	}

	return (targetValue - 1);
}

int main(int argc, char* argv[])
{
	input();
	fout << solve() << endl;

	return 0;
}