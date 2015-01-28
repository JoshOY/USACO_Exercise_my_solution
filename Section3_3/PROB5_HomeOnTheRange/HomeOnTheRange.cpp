/*
ID: joshoy71
PROG: range
LANG: C++11
*/

/*
Executing...
   Test 1: TEST OK [0.003 secs, 3988 KB]
   Test 2: TEST OK [0.000 secs, 3988 KB]
   Test 3: TEST OK [0.005 secs, 3988 KB]
   Test 4: TEST OK [0.005 secs, 3988 KB]
   Test 5: TEST OK [0.005 secs, 3988 KB]
   Test 6: TEST OK [0.014 secs, 3988 KB]
   Test 7: TEST OK [0.038 secs, 3988 KB]

All tests OK.
*/

#include <fstream>
#include <string>

using namespace std;

#define min(_A_, _B_) ( ((_A_) < (_B_)) ? (_A_) : (_B_) )

static ifstream fin("range.in", ios::in);
static ofstream fout("range.out", ios::out);

const int MAX_N = 250;

static int N;
static int mat[MAX_N + 1][MAX_N + 1] = { { 0 } };   // Matrix data
static int dp[MAX_N + 1][MAX_N + 1] = { { 0 } };    // For dynamic programming
static int tubeCounter[MAX_N + 1] = { 0 };          // Result
static int i, j, k;                                 // For loop
static char char_in;                                // For char reading

int main(int argc, char* argv[])
{
	fin >> N;

	/*
	*  Read the matrix.
	*/
	for (i = 1; i <= N; ++i) {
		for (j = 1; j <= N; ++j) {
			fin >> char_in;
			if (char_in == '1') {
				mat[i][j] = 1;
			}
			else {
				mat[i][j] = 0;
			}
		}
	}

	/*
	* 算法的具体内容：dp[i][j]为以(i, j)为左上角顶点的正方形的最大边长。
	* 然后检查左方、上方、左上方的情况。动态规划。
	*/
	for (i = 1; i <= N; ++i) {
		for (j = 1; j <= N; ++j) {
			if (mat[i][j] == 1) {
				dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
			}
		}
	}

	for (i = 1; i <= N; ++i) {
		for (j = 1; j <= N; ++j) {
			for (k = 2; k <= dp[i][j]; ++k) {
				tubeCounter[k] += 1;
			}
		}
	}

	for (k = 2; k <= N; ++k) {
		if (tubeCounter[k] != 0) {
			fout << k << ' ' << tubeCounter[k] << endl;
		}
	}

	fin.close();
	fout.close();
	return 0;
}