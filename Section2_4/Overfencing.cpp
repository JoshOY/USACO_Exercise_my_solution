/*
ID: joshoy71
PROG: maze1
LANG: C++11
*/

#include <fstream>
#include <string>

using namespace std;

#define min(_A_, _B_) (((_A_) < (_B_)) ? (_A_) : (_B_))
#define max(_A_, _B_) (((_A_) > (_B_)) ? (_A_) : (_B_))

const int W_MAX = 38;
const int H_MAX = 100;
const int northWall = 0x0001;
const int eastWall = 0x0002;
const int southWall = 0x0004;
const int westWall = 0x0008;

static ifstream fin("maze1.in");
static ofstream fout("maze1.out");
static int maze[H_MAX + 2][W_MAX + 2] = { { 0 } };
static int exit1_h, exit1_w, exit2_h, exit2_w;
static int exitSteps[H_MAX + 2][W_MAX + 2] = { { 0 } };
static int W, H;

void readFile()
{
	fin >> W >> H;
	string lineRead;

	for (int i = 1; i <= 2 * H + 1; ++i) {
		getline(fin, lineRead);

		//if can't read a whole line, then read again
		if (lineRead.length() == 0)
			getline(fin, lineRead);

		if ((i & 0x0001) == 1) {
			for (int j = 2; j <= 2 * W + 1; j += 2) {
				if (lineRead[j - 1] == '-') {
					maze[i / 2][j / 2] |= southWall;
					maze[i / 2 + 1][j / 2] |= northWall;
				}
			}
		}
		else {
			for (int j = 1; j <= 2 * W + 1; j += 2) {
				if (lineRead[j - 1] == '|') {
					maze[i / 2][j / 2] |= eastWall;
					maze[i / 2][j / 2 + 1] |= westWall;
				}
			}
		}
	}

	return;
}

void findExit() {
	bool foundOne = false;
	for (int j = 1; j <= W; ++j) {
		if (!(maze[0][j] & southWall)) {
			if (!foundOne) {
				exit1_h = 1;
				exit1_w = j;
				maze[1][j] |= northWall;
				foundOne = true;
			} else {
				exit2_h = 1;
				exit2_w = j;
				maze[1][j] |= northWall;
			}
		}
		if (!(maze[H + 1][j] & northWall)) {
			if (!foundOne) {
				exit1_h = H;
				exit1_w = j;
				maze[H][j] |= southWall;
				foundOne = true;
			}
			else {
				exit2_h = H;
				exit2_w = j;
				maze[H][j] |= southWall;
			}
		}
	}
	for (int i = 1; i <= H; ++i) {
		if ((maze[i][0] & eastWall) == 0) {
			if (!foundOne) {
				exit1_h = i;
				exit1_w = 1;
				maze[i][1] |= westWall;
				foundOne = true;
			}
			else {
				exit2_h = i;
				exit2_w = 1;
				maze[i][1] |= westWall;
			}
		}
		if ((maze[i][W + 1] & westWall) == 0) {
			if (!foundOne) {
				exit1_h = i;
				exit1_w = W;
				maze[i][W] |= eastWall;
				foundOne = true;
			}
			else {
				exit2_h = i;
				exit2_w = W;
				maze[i][W] |= eastWall;
			}
		}
	}
}

void dfsExit(int i, int j, int step, int from)
{
	if ((exitSteps[i][j] == 0) || (step < exitSteps[i][j]))
		exitSteps[i][j] = step;
	else
		return;

	if ( ((maze[i][j] & northWall) == 0) && ((from & northWall) == 0) ) {
		dfsExit(i - 1, j, step + 1, southWall);
	}
	if (((maze[i][j] & southWall) == 0) && ((from & southWall) == 0)) {
		dfsExit(i + 1, j, step + 1, northWall);
	}
	if (((maze[i][j] & westWall) == 0) && ((from & westWall) == 0)) {
		dfsExit(i, j - 1, step + 1, eastWall);
	}
	if (((maze[i][j] & eastWall) == 0) && ((from & eastWall) == 0)) {
		dfsExit(i, j + 1, step + 1, westWall);
	}
	return;
}

int longestStep()
{
	int result = 1;
	for (int i = 1; i <= H; ++i) {
		for (int j = 1; j <= W; ++j) {
			result = max(result, exitSteps[i][j]);
		}
	}
	return result;
}

int main(int argc, char* argv[])
{
	readFile();	
	if ((W == 1) && (H == 1)) {
		fout << 1 << endl;
		return 0;
	}
	
	findExit();

	dfsExit(exit1_h, exit1_w, 1, 0);
	dfsExit(exit2_h, exit2_w, 1, 0);

	fout << longestStep() << endl;

	return 0;
}