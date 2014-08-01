/*
ID: joshoy71
PROG: checker
LANG: C++11
*/

#include <fstream>
#include <vector>

using namespace std;
#define MAX_BOARD_SIZE 13
#define bit(_N_) (1 << (_N_))  //return int with 1 on _N_ bit, for example: bit(3) is 0000 0000 0000 0100
#define getFirstOne(_POS_) ( (_POS_) & ((~(_POS_)) + 1) )		//return int with fisrt 1 count from right to left in _POS_, for example: getFirstOne(0x0038) is 0000 0000 0000 1000


static int counterFor3 = 0;
static vector<vector<int> > result;
static int counter = 0;
static int boardPlacement = 0x1FFF;
static int boardSize = 6;		//Well, set it to 6 is just for test, later we will have it changed.

void init()
{
	boardPlacement >>= (MAX_BOARD_SIZE - boardSize);
}


void solveSituationOneTwoThree(int row, int columnsPlacedQueen, int leftSlash, int rightSlash, vector<int> record) {
	if (counterFor3 > 3)
		return;
	if (row == 1) {
		for (int firstColNum = 1; firstColNum <= boardSize; ++firstColNum) {
			columnsPlacedQueen = (0x0001 << (firstColNum - 1));
			solveSituationOneTwoThree(2, columnsPlacedQueen, columnsPlacedQueen << 1, columnsPlacedQueen >> 1, { firstColNum });
		}
	}
	else {
		int canPlace = boardPlacement & (~(columnsPlacedQueen | leftSlash | rightSlash));
		while (canPlace != 0x0000) {
			int newQueen = getFirstOne(canPlace);
			int place = 1; int tmp = 1;
			while (tmp != newQueen) {
				++place;
				tmp <<= 1;
			}
			canPlace -= newQueen;
			if (row == boardSize) {
				++counterFor3;
				if (counterFor3 <= 3) {
					record.push_back(place);
					result.push_back(record);
				}
			}
			else {
				record.push_back(place);
				solveSituationOneTwoThree(row + 1, columnsPlacedQueen | newQueen, (leftSlash << 1) | (newQueen << 1), (rightSlash >> 1) | (newQueen >> 1), record);
				record.pop_back();
			}
		}
		return;
	}
}

void solve(int row, int columnsPlacedQueen, int leftSlash, int rightSlash)
{
	if (row == 1) {
		for (int firstColNum = 1; firstColNum <= boardSize; ++firstColNum) {
			columnsPlacedQueen = (0x0001 << (firstColNum - 1));
			solve(2, columnsPlacedQueen, columnsPlacedQueen << 1, columnsPlacedQueen >> 1);
		}
	}
	else {
		int saveQueenColumnState = columnsPlacedQueen;
		int canPlace = boardPlacement & (~(columnsPlacedQueen | leftSlash | rightSlash));
		while (canPlace != 0x0000) {
			int newQueen = getFirstOne(canPlace);
			canPlace -= newQueen;
			if (row == boardSize) {
				++counter;
			}
			else {
				solve(row + 1, columnsPlacedQueen | newQueen, (leftSlash << 1) | (newQueen << 1), (rightSlash >> 1) | ((newQueen >> 1)));
			}
		}
		return;
	}
}

int main(int argc, char* argv[])
{
	ifstream fin("checker.in");
	ofstream fout("checker.out");
	fin >> boardSize;
	
	init();
	solveSituationOneTwoThree(1, 0, 0, 0, {});
	solve(1, 0, 0, 0);

	for (int a = 0; a < result.size(); ++a) {
		for (int b = 0; b < result[a].size(); ++b) {
			fout << result[a][b];
			if (b != result[a].size() - 1)
				fout << " ";
		}
		fout << endl;
	}
	fout << counter << endl;
	return 0;
}
