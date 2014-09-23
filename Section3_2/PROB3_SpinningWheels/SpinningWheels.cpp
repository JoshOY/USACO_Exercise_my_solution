/*
ID: joshoy71
PROG: spin
LANG: C++11
*/

/*
TEST RESULT:
   Test 1: TEST OK [0.005 secs, 3496 KB]
   Test 2: TEST OK [0.011 secs, 3496 KB]
   Test 3: TEST OK [0.011 secs, 3496 KB]
   Test 4: TEST OK [0.016 secs, 3496 KB]
   Test 5: TEST OK [0.011 secs, 3496 KB]
   Test 6: TEST OK [0.008 secs, 3496 KB]
   Test 7: TEST OK [0.011 secs, 3496 KB]
   Test 8: TEST OK [0.008 secs, 3496 KB]

All tests OK.
*/

#include <fstream>

using namespace std;

const int WHEEL_NUM = 5;
const int ANGLE_MAX = 360;
const int TIME_MAX = 360;

static ifstream fin("spin.in");
static ofstream fout("spin.out");

static int wheelWedgeAngle[WHEEL_NUM + 1][WHEEL_NUM + 1] = { { 0 } };	//wheelWedgeExtent[w][n]: The angle of wedge #n of wheel #w
static int speed[WHEEL_NUM + 1] = { 0 };
static int wedgeNum[WHEEL_NUM + 1] = { 0 };
static int wheelWedgeExtent[WHEEL_NUM + 1][WHEEL_NUM + 1] = { { 0 } };	//wheelWedgeExtent[w][n]: The extent length of wedge #n of wheel #w, values will be constant
static int resultTime = 0;
static int angleCounter[ANGLE_MAX] = { 0 }; 

void input()
{
	for(int w = 1; w <= WHEEL_NUM; ++w) {
		fin >> speed[w];
		fin >> wedgeNum[w];
		for (int n = 1; n <= wedgeNum[w]; ++n) {
			fin >> wheelWedgeAngle[w][n] >> wheelWedgeExtent[w][n];
		}
	}

	return;
}

bool check()
{
	int a, t, w, n;
	for (t = 0; t < TIME_MAX; ++t) {
		for (a = 0; a < ANGLE_MAX; ++a) {
			angleCounter[a] = 0;
		}
		for (w = 1; w <= WHEEL_NUM; ++w) {
			for (n = 1; n <= wedgeNum[w]; ++n) {
				for (a = wheelWedgeAngle[w][n]; a <= wheelWedgeAngle[w][n] + wheelWedgeExtent[w][n]; ++a) {
					++angleCounter[a % 360];
				}
			}
		}
		for (a = 0; a < ANGLE_MAX; ++a) {
			if (angleCounter[a] == WHEEL_NUM) {
				resultTime = t;
				return true;
			}
		}
		for (w = 1; w <= WHEEL_NUM; ++w) {
			for (n = 1; n <= wedgeNum[w]; ++n) {
				wheelWedgeAngle[w][n] = (wheelWedgeAngle[w][n] + speed[w]) % 360;
			}
		}
	}

	return false;
}

int main(int argc, char* argv[])
{
	input();
	if (check()) {
		fout << resultTime << endl;
	} else {
		fout << "none" << endl;
	}

	return 0;
}