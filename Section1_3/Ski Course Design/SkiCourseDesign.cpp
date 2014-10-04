/*
ID: joshoy71
PROG: skidesign
LANG: C++11
*/

/*
TEST RESULT:
Executing...
   Test 1: TEST OK [0.003 secs, 3496 KB]
   Test 2: TEST OK [0.003 secs, 3496 KB]
   Test 3: TEST OK [0.003 secs, 3496 KB]
   Test 4: TEST OK [0.003 secs, 3496 KB]
   Test 5: TEST OK [0.003 secs, 3496 KB]
   Test 6: TEST OK [0.003 secs, 3496 KB]
   Test 7: TEST OK [0.003 secs, 3496 KB]
   Test 8: TEST OK [0.003 secs, 3496 KB]
   Test 9: TEST OK [0.003 secs, 3496 KB]
   Test 10: TEST OK [0.003 secs, 3496 KB]

All tests OK.
YOUR PROGRAM ('skidesign') WORKED FIRST TIME!  That's fantastic
-- and a rare thing.  Please accept these special automated
congratulations.
*/

#include <fstream>
#include <vector>

using namespace std;

static ifstream fin("skidesign.in");
static ofstream fout("skidesign.out");

const long long COST_MAX = 100000000;
const int ELEVATION_MAX = 100;
const int DIFFERENCE_MAX = 17;

static int N;
static vector<int> hillElevation;

int main(int argc, char* argv[])
{
	fin >> N;
	int tmp;
	for (int i = 1; i <= N; ++i) {
		fin >> tmp;
		hillElevation.push_back(tmp);
	}

	long long minCost = COST_MAX;
	long long cost = 0;
	for (int h = 0; h <= ELEVATION_MAX; ++h) {
		cost = 0;
		for (int i = 0; i < N; ++i) {
			if (hillElevation[i] < h) {
				cost += (h - hillElevation[i]) * (h - hillElevation[i]);
			} else if (hillElevation[i] < h + DIFFERENCE_MAX) {
				continue;
			} else {
				cost += (hillElevation[i] - h - DIFFERENCE_MAX) * (hillElevation[i] - h - DIFFERENCE_MAX);
			}
		}
		if (cost < minCost) {
			minCost = cost;
		}
	}

	fout << minCost << endl;
	return 0;
}