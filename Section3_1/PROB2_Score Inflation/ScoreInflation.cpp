/*
ID: joshoy71
PROG: inflate
LANG: C++11
*/

/*
TEST RESULT:

Compiling...
Compile: OK

Executing...
   Test 1: TEST OK [0.008 secs, 3612 KB]
   Test 2: TEST OK [0.165 secs, 3612 KB]
   Test 3: TEST OK [0.005 secs, 3612 KB]
   Test 4: TEST OK [0.027 secs, 3612 KB]
   Test 5: TEST OK [0.035 secs, 3612 KB]
   Test 6: TEST OK [0.065 secs, 3612 KB]
   Test 7: TEST OK [0.219 secs, 3612 KB]
   Test 8: TEST OK [0.586 secs, 3612 KB]
   Test 9: TEST OK [0.872 secs, 3612 KB]
   Test 10: TEST OK [1.096 secs, 3612 KB] <-- orz
   Test 11: TEST OK [0.005 secs, 3612 KB]
   Test 12: TEST OK [0.027 secs, 3612 KB]

All tests OK.
*/

#include <fstream>

using namespace std;

#define max(A, B) (((A) > (B)) ? (A) : (B))
#define min(A, B) (((A) < (B)) ? (A) : (B))

const int M_MAX = 10000;
const int N_MAX = 10000;

static ifstream fin("inflate.in");
static ofstream fout("inflate.out");

static int M, N;	//time, problem classes
static int timeneed[M_MAX + 1] = { 0 };
static int points[N_MAX + 1] = { 0 };
static int dp[M_MAX + 1] = { 0 };

void input()
{
	fin >> M >> N;
	for (int i = 1; i <= N; ++i) {
		fin >> points[i] >> timeneed[i];
	}
	return;
}

void solveKnapsack()
{
	for (int i = 1; i <= N; ++i) {
		for (int k = 1; k * timeneed[i] <= M; ++k) {
			for (int j = timeneed[i] * k; j <= M; ++j) {
				dp[j] = max(dp[j], (dp[j - (timeneed[i] * k)] + (points[i] * k)));
			}
		}
	}
	return;
}

int main(int argc, char* argv[])
{
	input();
	solveKnapsack();
	int result = dp[M];
	fout << result << endl;

	return 0;
}