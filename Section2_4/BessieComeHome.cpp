/*
ID: joshoy71
PROG: comehome
LANG: C++11
*/

/*
TEST RESULT
Executing...
   Test 1: TEST OK [0.011 secs, 3504 KB]
   Test 2: TEST OK [0.014 secs, 3504 KB]
   Test 3: TEST OK [0.008 secs, 3504 KB]
   Test 4: TEST OK [0.011 secs, 3504 KB]
   Test 5: TEST OK [0.005 secs, 3504 KB]
   Test 6: TEST OK [0.005 secs, 3504 KB]
   Test 7: TEST OK [0.008 secs, 3504 KB]
   Test 8: TEST OK [0.005 secs, 3504 KB]
   Test 9: TEST OK [0.008 secs, 3504 KB]
All tests OK.
*/

#include <fstream>

using namespace std;

#define min(a, b) ( ((a) < (b)) ? (a) : (b) )
#define max(a, b) ( ((a) > (b)) ? (a) : (b) )
#define charToOrder(ch) (int)( ((ch) <= 'Z') ? ((ch) - 'A' + 27) : ((ch - 'a' + 1)) )
#define orderToChar(n) (char) ( ((n) <= 26) ? ((n) - 1 + 'a') : ((n) - 27 + 'A') )

const int PASTURE_MAX = 52;
const int infinite = 0xfffff;

static ifstream fin("comehome.in");
static ofstream fout("comehome.out");

static int P;
static int chart[PASTURE_MAX + 1][PASTURE_MAX + 1] = { { false } };
static bool hasCow[PASTURE_MAX + 1] = { false };
static int shortestDistance = infinite;
static char shortestFrom;

void input()
{
	for (int i = 0; i <= PASTURE_MAX; ++i) {
		for (int j = 0; j <= PASTURE_MAX; ++j) {
			if (i == j) {
				chart[i][j] = 0;
			}
			else {
				chart[i][j] = infinite;
			}
		}
	}

	char node1, node2;
	int dis;
	fin >> P;
	for (int i = 1; i <= P; ++i) {
		fin >> node1 >> node2 >> dis;
		if (chart[charToOrder(node1)][charToOrder(node2)] == infinite){
			chart[charToOrder(node1)][charToOrder(node2)] = dis;
			chart[charToOrder(node2)][charToOrder(node1)] = dis;
			if ((node1 >= 'A') && (node1 <= 'Y')) {
				hasCow[charToOrder(node1)] = true;
			}
			if ((node2 >= 'A') && (node2 <= 'Y')) {
				hasCow[charToOrder(node2)] = true;
			}
		}
		else {
			if (chart[charToOrder(node1)][charToOrder(node2)] > dis) {
				chart[charToOrder(node1)][charToOrder(node2)] = dis;
				chart[charToOrder(node2)][charToOrder(node1)] = dis;
			}
		}
	}
	return;
}

void findShortest()
{
	// Floyd-Warshall algorithm
	for (int k = 1; k < PASTURE_MAX; ++k) {
		for (int i = 1; i <= PASTURE_MAX; ++i) {
			if (i == k) continue;
			for (int j = 1; j <= PASTURE_MAX; ++j) {
				if (j == k) continue;
				chart[i][j] = min(chart[i][j], chart[i][k] + chart[k][j]);
			}
		}
	}

	for (int i = 1; i < PASTURE_MAX; ++i) {
		if ((hasCow[i]) && (chart[PASTURE_MAX][i] < shortestDistance)) {
			shortestDistance = chart[PASTURE_MAX][i];
			shortestFrom = orderToChar(i);
		}	
	}
}

int main(int argc, char* argv[])
{
	input();
	findShortest();
	fout << shortestFrom << ' ' << shortestDistance << endl;
	return 0;
}
