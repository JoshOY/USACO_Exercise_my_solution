/*
ID: joshoy71
PROG: fracdec
LANG: C++11
*/

/*
TEST RESULT
Executing...
   Test 1: TEST OK [0.003 secs, 8380 KB]
   Test 2: TEST OK [0.003 secs, 8380 KB]
   Test 3: TEST OK [0.003 secs, 8380 KB]
   Test 4: TEST OK [0.003 secs, 8380 KB]
   Test 5: TEST OK [0.003 secs, 8380 KB]
   Test 6: TEST OK [0.003 secs, 8380 KB]
   Test 7: TEST OK [0.008 secs, 8380 KB]
   Test 8: TEST OK [0.035 secs, 8380 KB]
   Test 9: TEST OK [0.003 secs, 8380 KB]

	Here are the test data inputs:

	------- test 1 ----
	22 5
	------- test 2 ----
	1 7
	------- test 3 ----
	100000 59
	------- test 4 ----
	1 100000
	------- test 5 ----
	3 3
	------- test 6 ----
	59 330
	------- test 7 ----
	100000 9817
	------- test 8 ----
	1 99991
	------- test 9 ----
	982 4885
	
All tests OK.
*/
#include <fstream>
#include <string>
#include <sstream>
#include <memory.h>

using namespace std;

const int N_AND_D_MAX = 100000;
const int OUTPUT_MAX_CHAR_PER_LINE = 76;

// N, D <= 100000
static int N, D;
static string result = "";
static string repeatPart("(");
static int  lastDividend[N_AND_D_MAX * 10 + 1] = { -1 };
static bool traversed[N_AND_D_MAX * 10 + 1] = { false };

static ifstream fin("fracdec.in");
static ofstream fout("fracdec.out");


void initAndInput()
{
	memset(lastDividend, -1, N_AND_D_MAX + 1);
	fin >> N >> D;
	return;
}

void solve()
{
	int tmpN = N;
	stringstream ss;
	int counter = 0;
	int lootStartPoint;
	bool isFinite = false;

	//for example: 8 / 7 = 1.xxxx
	ss << (N / D) << '.';
	ss >> result;
	//then (8 - 1 * 7) / 7 = 1 / 7, solve it...
	tmpN -= (N / D) * D;
	
	while (true) {
		++counter;
		tmpN *= 10;
		if (traversed[tmpN] == false) {
			traversed[tmpN] = true;
			lastDividend[tmpN] = counter;
			tmpN -= (tmpN / D) * D;
		}
		else if (tmpN == 0) {
			isFinite = true;
			break;
		} else {
			lootStartPoint = lastDividend[tmpN];
			break;
		}
	}

	if (!isFinite) {
		tmpN = N - ((N / D) * D);
		int i = 1;
		while (i < lootStartPoint) {
			tmpN *= 10;
			result.push_back((tmpN / D) + '0');
			tmpN -= (tmpN / D) * D;
			++i;
		}
		for (i = 1; i <= counter - lootStartPoint; ++i) {
			tmpN *= 10;
			repeatPart.push_back((tmpN / D) + '0');
			tmpN -= (tmpN / D) * D;
		}
		repeatPart.push_back(')');
		result += repeatPart;
	}
	else {
		tmpN = N - ((N / D) * D);
		while (tmpN != 0) {
			tmpN *= 10;
			result.push_back((tmpN / D) + '0');
			tmpN -= (tmpN / D) * D;
		}
	}

	return;
}

int main(int argc, char* argv[])
{
	initAndInput();

	// when N = n * D
	if ((N / D) * D == N) {
		fout << N / D << ".0" << endl;
		return 0;
	}

	// else
	solve();

	int i = 0;
	int j = 1;
	while (i < result.size()) {
		if (j == 0) {
			fout << endl;
		}
		fout << result[i];
		++i;
		j = (i % OUTPUT_MAX_CHAR_PER_LINE);
	}
	fout << endl;

	return 0;
}