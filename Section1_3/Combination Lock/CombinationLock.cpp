/*
ID: joshoy71
PROG: combo
LANG: C++11
*/

/*
TEST RESULT:
   Test 1: TEST OK [0.005 secs, 3500 KB]
   Test 2: TEST OK [0.003 secs, 3500 KB]
   Test 3: TEST OK [0.008 secs, 3500 KB]
   Test 4: TEST OK [0.008 secs, 3500 KB]
   Test 5: TEST OK [0.005 secs, 3500 KB]
   Test 6: TEST OK [0.005 secs, 3500 KB]
   Test 7: TEST OK [0.005 secs, 3500 KB]
   Test 8: TEST OK [0.008 secs, 3500 KB]
   Test 9: TEST OK [0.008 secs, 3500 KB]
   Test 10: TEST OK [0.005 secs, 3500 KB]
*/

#include <fstream>
#include <set>
#include <string>

using namespace std;

static ifstream fin("combo.in");
static ofstream fout("combo.out");

static int N;
static int x1, x2, x3;
static int y1, y2, y3;
static set<string> resultSet;

int movePos(int x, int movPos)
{
	if(movPos == 0) {
		return x;
	} else if (movPos > 0) {
		return movePos(((x == N) ? 1 : x + 1), movPos - 1);
	} else {
		return movePos(((x == 1) ? N : x - 1), movPos + 1);
	}
}

int main(int argc, char* argv[])
{
	fin >> N
		>> x1 >> x2 >> x3
		>> y1 >> y2 >> y3;

	string valid = "";

	for (int a = -2; a <= 2; ++a) {
		for (int b = -2; b <= 2; ++b) {
			for (int c = -2; c <= 2; ++c) {
				valid.push_back(movePos(x1, a));
				valid.push_back(movePos(x2, b));
				valid.push_back(movePos(x3, c));
				resultSet.insert(valid);
				valid = "";

				valid.push_back(movePos(y1, a));
				valid.push_back(movePos(y2, b));
				valid.push_back(movePos(y3, c));
				resultSet.insert(valid);
				valid = "";
			}
		}
	}

	fout << (resultSet.size()) << endl;

	return 0;
}