/*
ID: joshoy71
PROG: money
LANG: C++11
*/

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const int V_MAX = 25;
const int N_MAX = 10000;

static ifstream fin("money.in");
static ofstream fout("money.out");

static int V, N;
static vector<int> coins;
static long long dp[V_MAX + 1][N_MAX + 1] = { { 0 } };	//dp[i][j]: using maximum coin #i, j remain units

void solve()
{
	int i, j, k;
	for (int j = coins[0]; j <= N; j += coins[0]) {
		dp[0][j] = 1;
	}
	for (i = 1; i < V; ++i) {
		for (int j = coins[0]; j <= N; ++j) {
			if (coins[i] > j) {
				dp[i][j] = dp[i - 1][j];
			}
			else if (j == coins[i]) {
				dp[i][j] = dp[i - 1][j] + 1;
			}
			else {
				dp[i][j] = dp[i - 1][j] + dp[i][j - coins[i]];
			}
		}
	}
}

int main(int argc, char* argv[])
{
	fin >> V >> N;
	int tmp;
	for (int i = 1; i <= V; ++i) {
		fin >> tmp;
		coins.push_back(tmp);
	}

	std::sort(coins.begin(), coins.end());
	if (coins[0] > N) {
		fout << 0 << endl;
		return 0;
	}

	solve();
	fout << dp[V - 1][N] << endl;

	return 0;
}