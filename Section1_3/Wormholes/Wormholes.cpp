/*
ID: joshoy71
PROG: wormhole
LANG: C++11
*/

/*
TEST RESULT:
Executing...
   Test 1: TEST OK [0.003 secs, 3500 KB]
   Test 2: TEST OK [0.003 secs, 3500 KB]
   Test 3: TEST OK [0.005 secs, 3500 KB]
   Test 4: TEST OK [0.005 secs, 3500 KB]
   Test 5: TEST OK [0.005 secs, 3500 KB]
   Test 6: TEST OK [0.005 secs, 3500 KB]
   Test 7: TEST OK [0.022 secs, 3500 KB]
   Test 8: TEST OK [0.022 secs, 3500 KB]
   Test 9: TEST OK [0.022 secs, 3500 KB]
   Test 10: TEST OK [0.027 secs, 3500 KB]

All tests OK.
YOUR PROGRAM ('wormhole') WORKED FIRST TIME!  That's fantastic
-- and a rare thing.  Please accept these special automated
congratulations.
*/

#include <fstream>
#include <vector>

using namespace std;

static ifstream fin("wormhole.in");
static ofstream fout("wormhole.out");

const int N_MAX = 12;
const long long X_MAX = 1000000000;
typedef struct _Pos
{
	long long x;
	long long y;
} Pos;

static int N;
static int result;
static vector<Pos> points = { {-1, -1} };
static int goDirectlyNextPoint[N_MAX + 1] = { 0 };

bool hasStuck(vector<int> linkWith) //linkWith[i] = j means wormhole i links with wormhole j
{
	int stepsCounter, transToPoint;
	for (int start = 1; start <= N; ++start) {
		transToPoint = start;
		stepsCounter = 0;
		while (goDirectlyNextPoint[transToPoint] != 0) {
			transToPoint = linkWith[goDirectlyNextPoint[transToPoint]];
			stepsCounter++;
			if (stepsCounter > N + 1) {
				return true;
			}
		}
	}
	return false;
}

void findStuck(int currentPoint, vector<int> linkWith)
{
	if (currentPoint > N) {
		if (hasStuck(linkWith)) {
			result += 1;
			return;
		}
	}

	for (int i = currentPoint + 1; i <= N; ++i) {
		if (linkWith[i] != 0) {
			continue;
		} else {
			vector<int> nextLinkWith = linkWith;
			nextLinkWith[i] = currentPoint;
			nextLinkWith[currentPoint] = i;
			int nextPoint = currentPoint + 1;
			while ((nextPoint <= N) && (nextLinkWith[nextPoint] != 0)) {
				++nextPoint;
			}
			findStuck(nextPoint, nextLinkWith);
		}
	}
	return;
}

int main(int argc, char* argv[])
{
	fin >> N;
	long long tmpX, tmpY;
	for (int i = 1; i <= N; ++i) {
		fin >> tmpX >> tmpY;
		points.push_back({ tmpX, tmpY });
	}

	//get the right pos
	long long rightPointMinXPos[N_MAX + 1] = { X_MAX + 1 };
	for (int i = 1; i <= N; ++i) {
		rightPointMinXPos[i] = X_MAX + 1;
		for (int j = 1; j <= N; ++j) {
			if ((points[i].y == points[j].y) && (points[i].x < points[j].x) && (points[j].x < rightPointMinXPos[i])) {
				rightPointMinXPos[i] = points[j].x;
				goDirectlyNextPoint[i] = j;
			}
		}
	}

	vector<int> initialLink = { 0 };
	for (int i = 1; i <= N; ++i) {
		initialLink.push_back(0);
	}

	findStuck(1, initialLink);

	fout << result << endl;

	return 0;
}