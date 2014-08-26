/*
ID: joshoy71
PROG: cowtour
LANG: C++11
*/

/*
Test Result:
   Test 1: TEST OK [0.005 secs, 3700 KB]
   Test 2: TEST OK [0.003 secs, 3700 KB]
   Test 3: TEST OK [0.008 secs, 3700 KB]
   Test 4: TEST OK [0.005 secs, 3700 KB]
   Test 5: TEST OK [0.030 secs, 3700 KB]
   Test 6: TEST OK [0.062 secs, 3700 KB]
   Test 7: TEST OK [0.016 secs, 3700 KB]
   Test 8: TEST OK [0.022 secs, 3700 KB]
   Test 9: TEST OK [0.022 secs, 3700 KB]
*/

#include <string>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

#define min(a, b) (((a) < (b)) ? (a) : (b) )
#define max(a, b) (((a) > (b)) ? (a) : (b) )
#define distance(X1, Y1, X2, Y2) ( sqrt ( (double)((X1) - (X2)) * ((X1) - (X2)) + (double)((Y1) - (Y2)) * ((Y1) - (Y2)) ) )
#define INT_MAX 2147483646    /* maximum (signed) int value */

typedef struct __Point
{
	int x;
	int y;
} Point;

const int N_MAX = 150;
const int infinite = 1000001;
static ifstream fin("cowtour.in");
static ofstream fout("cowtour.out");

static int N;	//the number of pastures
static bool chosen[N_MAX + 1] = { false };	//if we had put the pasture#i into a set, chosen[i] = true;
static bool fields[N_MAX + 1][N_MAX + 1] = { { false } };	//if pasture #j is in field #i, then fields[i][j] = true;
static int fieldsNum = 0;	//the number of pastures
static double fieldsDiameter[N_MAX + 1] = { 0 };	//record diameters of all fields;
static Point points[N_MAX + 1];	//record the x, y value of nodes;
static double dis[N_MAX + 1][N_MAX + 1] = { { 0 } };	//record shortest distance between these pastures;
static double result = infinite;

void input()
{
	fin >> N;
	for (int i = 1; i <= N; ++i) {
		fin >> points[i].x >> points[i].y;
	}
	string lineRead;
	for (int i = 1; i <= N; ++i) {
		fin >> lineRead;
		for (int j = 1; j <= N; ++j) {
			if (lineRead[j - 1] == '0') {
				if (i == j) {
					dis[i][j] = 0;
				}
				else {
					dis[i][j] = infinite;
				}
			}
			else {
				dis[i][j] = distance(points[i].x, points[i].y, points[j].x, points[j].y);
			}
		}
	}

	return;
}

void floydWarshallAlgorithm()
{
	for (int k = 1; k <= N; ++k) {
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= N; ++j) {
				if (dis[i][k] + dis[k][j] < dis[i][j]) {
					dis[i][j] = dis[i][k] + dis[k][j];
				}
			}
		}
	}
	return;
}

void getLongest()
{
	double longest = 0;
	for (int i = 1; i <= N; ++i) {
		longest = 0;
		for (int j = 1; j <= N; ++j) {
			if (dis[i][j] != infinite) {
				longest = max(longest, dis[i][j]);
			}
		}
		dis[i][0] = longest;
	}
	return;
}

void findPastures() {
	double currentDiameter = 0;
	for (int i = 1; i <= N; ++i) {
		if (chosen[i] == false) {
			++fieldsNum;
			fields[fieldsNum][i] = true;
			chosen[i] = true;
			currentDiameter = dis[i][0];
			for (int j = i + 1; j <= N; ++j) {
				if (dis[i][j] != infinite) {
					fields[fieldsNum][j] = true;
					chosen[j] = true;
					if (currentDiameter < dis[j][0])
						currentDiameter = dis[j][0];
				}
			}
			fieldsDiameter[fieldsNum] = currentDiameter;
		}
		else {
			continue;
		}
	}
	return;
}

void getResult()
{
	double minimumResult;
	// Firstly, get two fields #a and #b;
	for (int a = 1; a < fieldsNum; ++a) {
		for (int b = a + 1; b <= fieldsNum; ++b) {
			// Then link each two pastures #p and #q in two fields and check;
			for (int p = 1; p <= N; ++p) {
				if (fields[a][p] == true) {
					for (int q = 1; q <= N; ++q) {
						if (fields[b][q] == true) {
							// When linkable
							minimumResult = dis[p][0] + distance(points[p].x, points[p].y, points[q].x, points[q].y) + dis[q][0];
							for (int n = 1; n <= fieldsNum; ++n) {
								if (fieldsDiameter[n] > minimumResult) {
									minimumResult = fieldsDiameter[n];
								}
							}
							if (result > minimumResult) {
								result = minimumResult;
							}
						}
						else {
							continue;
						}
					}
				}
				else {
					continue;
				}
			}

		}
	}

	return;
}

int main(int argc, char* argv[])
{
	input();
	floydWarshallAlgorithm();
	getLongest();
	findPastures();
	getResult();
	fout << setiosflags(ios::fixed) << setprecision(6) << result << endl;

	return 0;
}