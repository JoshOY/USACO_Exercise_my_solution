/*
ID: joshoy71
PROG: castle
LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const int MAX_ROWS_COLS = 50;
const int northWall = 0x0002;
const int southWall = 0x0008;
const int eastWall = 0x0004;
const int westWall = 0x0001;
const bool NORTH = false;
const bool EAST = true;

typedef struct {
	int area;
	int color;
} RoomInfo;

static int M, N;
static int gridColored[MAX_ROWS_COLS][MAX_ROWS_COLS] = { { 0 } };
static int gridWalls[MAX_ROWS_COLS][MAX_ROWS_COLS] = { { 0 } };
static int areaCounter = 0;
static vector<RoomInfo> roomInfoVec;
static int wallBreakRow, wallBreakCol;
static bool direction;

int sortRoomInfoVec(const RoomInfo& A, const RoomInfo& B) {
	if (A.area > B.area)
		return 1;
	else {
		if((A.area == B.area) && (A.color < B.color))
			return 1;
		return 0;
	}
}


void dfs(int color, int row, int col)
{
	gridColored[row][col] = color;
	++areaCounter;
	if (!(gridWalls[row][col] & northWall) && (gridColored[row - 1][col] == 0))
		dfs(color, row - 1, col);
	if (!(gridWalls[row][col] & eastWall) && (gridColored[row][col + 1] == 0))
		dfs(color, row, col + 1);
	if (!(gridWalls[row][col] & southWall) && (gridColored[row + 1][col] == 0))
		dfs(color, row + 1, col);
	if (!(gridWalls[row][col] & westWall) && (gridColored[row][col - 1] == 0))
		dfs(color, row, col - 1);
	return;
}

bool findLinked(int colorA, int colorB)
{
	for (wallBreakCol = 0; wallBreakCol < M; ++wallBreakCol) {
		for (wallBreakRow = N - 1; wallBreakRow >= 0; --wallBreakRow) {
			//travel all the walls!
			if ((gridWalls[wallBreakRow][wallBreakCol] & northWall) && (wallBreakRow != 0)) {
				if (((gridColored[wallBreakRow][wallBreakCol] == colorA) && (gridColored[wallBreakRow - 1][wallBreakCol] == colorB))
					|| ((gridColored[wallBreakRow][wallBreakCol] == colorB) && (gridColored[wallBreakRow - 1][wallBreakCol] == colorA))) {
					direction = NORTH;
					return true;
				}
			}
			if ((gridWalls[wallBreakRow][wallBreakCol] & eastWall) && (wallBreakCol != M - 1)) {
				if (((gridColored[wallBreakRow][wallBreakCol] == colorA) && (gridColored[wallBreakRow][wallBreakCol + 1] == colorB))
					|| ((gridColored[wallBreakRow][wallBreakCol] == colorB) && (gridColored[wallBreakRow][wallBreakCol + 1] == colorA))) {
					direction = EAST;
					return true;
				}
			}
		}
	}
	return false;
}


int main(int argc, char* argv[])
{
	ifstream fin("castle.in");
	ofstream fout("castle.out");

	//N rows, M columns
	fin >> M >> N;

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			fin >> gridWalls[i][j];
		}
	}

	int currentColor = 0;
	for (int j = 0; j < M; ++j) {
		for (int i = N - 1; i >= 0; --i) {
			if (gridColored[i][j] == 0) {
				areaCounter = 0;
				currentColor += 1;
				dfs(currentColor, i, j);
				roomInfoVec.push_back({ areaCounter , currentColor});
			}
		}
	}

	fout << currentColor << endl;

	std::sort(roomInfoVec.begin(), roomInfoVec.end(), sortRoomInfoVec);

	fout << roomInfoVec[0].area << endl;
	
	bool shouldContinue = true;
	for (int i = 0; i < roomInfoVec.size() - 1; ++i) {
		if (!shouldContinue)
			break;
		for (int j = i + 1; j < roomInfoVec.size(); ++j) {
			if ((i + 2 < roomInfoVec.size()) 
				&& ((roomInfoVec[i].area + roomInfoVec[j].area) < (roomInfoVec[i + 1].area + roomInfoVec[i + 2].area))) {
				break;
			}
			if (findLinked(roomInfoVec[i].color, roomInfoVec[j].color)) {
				fout << roomInfoVec[i].area + roomInfoVec[j].area << endl;
				fout << wallBreakRow + 1 << " " << wallBreakCol + 1 << " ";
				if (direction == NORTH) {
					fout << "N" << endl;
				}
				else {
					fout << "E" << endl;
				}
				shouldContinue = false;
				break;
			}
		}
	}
	

	return 0;
}