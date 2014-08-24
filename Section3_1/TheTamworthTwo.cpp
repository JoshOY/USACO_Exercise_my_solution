/*
ID: joshoy71
PROG: ttwo
LANG: C++11
*/

#include <fstream>
#include <vector>
using namespace std;

const int MAX_BORDER = 10;
const int NORTH = 0x0001;
const int EAST = 0x0002;
const int SOUTH = 0x0004;
const int WEST = 0x0008;
const int MAX_STEPS = 160000;

typedef struct _Position
{
	int x;
	int y;
} Position;

/********************
	Notice that the position is like this:
	+------> y
	|
	|
	V
	x
********************/

static ifstream fin("ttwo.in");
static ofstream fout("ttwo.out");
static char mapRead[MAX_BORDER + 2][MAX_BORDER + 2];
static Position farmerPositions;
static Position cowsPositions;
static int steps = 1;
static int farmerDirection = NORTH;
static int cowsDirection = NORTH;

void init()
{
	for (int i = 1; i <= MAX_BORDER; ++i) {
		for (int j = 1; j <= MAX_BORDER; ++j) {
			fin >> mapRead[i][j];
		}
	}

	for (int i = 0; i <= MAX_BORDER + 1; ++i) {
		mapRead[0][i] = '*';
		mapRead[i][0] = '*';
		mapRead[MAX_BORDER + 1][i] = '*';
		mapRead[i][MAX_BORDER + 1] = '*';
	}

	for (int i = 1; i <= MAX_BORDER; ++i) {
		for (int j = 1; j <= MAX_BORDER; ++j) {
			if (mapRead[i][j] == 'F') {
				farmerPositions = { i, j };
			}
			else if (mapRead[i][j] == 'C') {
				cowsPositions = { i, j };
			}
			else {
				continue;
			}
		}
	}

	return;
}

void rotateFarmer()
{
	farmerDirection <<= 1;
	if (farmerDirection & 0x0010)
		farmerDirection >>= 4;
	return;
}

void rotateCows()
{
	cowsDirection <<= 1;
	if (cowsDirection & 0x0010)
		cowsDirection >>= 4;
	return;
}

int solve()
{
	for (steps = 1; steps <= MAX_STEPS; ++steps) {

		//move farmer John
		switch (farmerDirection)
		{
		case NORTH:
			if (mapRead[farmerPositions.x - 1][farmerPositions.y] == '*') {
				rotateFarmer();
			} else {
				farmerPositions = { farmerPositions.x - 1, farmerPositions.y };
			}
			break;
		case EAST:
			if (mapRead[farmerPositions.x][farmerPositions.y + 1] == '*') {
				rotateFarmer();
			}
			else {
				farmerPositions = { farmerPositions.x, farmerPositions.y + 1 };
			}
			break;
		case SOUTH:
			if (mapRead[farmerPositions.x + 1][farmerPositions.y] == '*') {
				rotateFarmer();
			}
			else {
				farmerPositions = { farmerPositions.x + 1, farmerPositions.y };
			}
			break;
		case WEST:
			if (mapRead[farmerPositions.x][farmerPositions.y - 1] == '*') {
				rotateFarmer();
			}
			else {
				farmerPositions = { farmerPositions.x, farmerPositions.y - 1};
			}
			break;
		}

		//move two cows
		switch (cowsDirection)
		{
		case NORTH:
			if (mapRead[cowsPositions.x - 1][cowsPositions.y] == '*') {
				rotateCows();
			}
			else {
				cowsPositions = { cowsPositions.x - 1, cowsPositions.y };
			}
			break;
		case EAST:
			if (mapRead[cowsPositions.x][cowsPositions.y + 1] == '*') {
				rotateCows();
			}
			else {
				cowsPositions = { cowsPositions.x, cowsPositions.y + 1 };
			}
			break;
		case SOUTH:
			if (mapRead[cowsPositions.x + 1][cowsPositions.y] == '*') {
				rotateCows();
			}
			else {
				cowsPositions = { cowsPositions.x + 1, cowsPositions.y };
			}
			break;
		case WEST:
			if (mapRead[cowsPositions.x][cowsPositions.y - 1] == '*') {
				rotateCows();
			}
			else {
				cowsPositions = { cowsPositions.x, cowsPositions.y - 1 };
			}
			break;
		}

		//check
		if ((farmerPositions.x == cowsPositions.x) && (farmerPositions.y == cowsPositions.y)) {
			return steps;
		}
	}

	return 0;
}

int main(int argc, char* argv[])
{
	init();

	fout << solve() << endl;

	return 0;
}