/*/*
ID: joshoy71
PROG: barn1
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Board
{
public:
	Board(int begin, int end) : beginPos(begin), endPos(end)
	{
		length = endPos - beginPos + 1;
	}

	static int compareLargerLength(const Board& A, const Board& B)
	{
		if (A.length > B.length) {
			return 1;
		}
		return 0;
	}

	int beginPos;
	int endPos;
	int length;
};

int main(int argc, char* argv[])
{
	ifstream fin("barn1.in");
	ofstream fout("barn1.out");

	// M: the maximum number of boards that can be purchased;
	// S: the total number of stalls;
	// C: the number of cows in the stalls
	int M, S, C;

	fin >> M >> S >> C;

	if (M >= C) {
		fout << C << endl;
		return 0;
	}

	vector<int> stallStatus;	// 1: has cow; 0: empty
	for (int i = 0; i < S; i++) {
		stallStatus.push_back(0);
	}

	int numOfStall;
	for (int i = 0; i < C; i++) {
		fin >> numOfStall;
		stallStatus[numOfStall - 1] = 1;
	}

	vector<Board> blankLineList;

	int counter = 0;
	int start = 0;
	int end = 0;
	bool continueing;

	if (stallStatus[0] == 0){
		continueing = true;
	}
	else {
		continueing = false;
	}

	for (int i = 0; i < S; i++) {
		if (continueing) {
			if (stallStatus[i] == 0) {
				end = i;
			}
			else {
				if (start != 0) {
					blankLineList.push_back(Board(start, end));
				}
				continueing = false;
			}
		} else {
			 if (stallStatus[i] == 0) {
				 start = i;
				 end = i;
				 continueing = true;
			 }
		}
}

// sort from long to short
sort(blankLineList.begin(), blankLineList.end(), Board::compareLargerLength);

int startPoint, endPoint;
for (int i = 0; i < S; i++) {
	if (stallStatus[i] == 1){
		startPoint = i;
		break;
	}
}

for (int i = S - 1; i >= 0; i--) {
	if (stallStatus[i] == 1){
		endPoint = i;
		break;
	}
}

int boardTotalLength = (endPoint - startPoint + 1);

if (blankLineList.size() == 0) {
	fout << boardTotalLength << endl;
	return 0;
}

auto iter = blankLineList.begin();
int currentBoardAmount = 1;
while (currentBoardAmount < M) {
	boardTotalLength -= iter->length;
	++iter;
	currentBoardAmount++;
}

fout << boardTotalLength << endl;

return 0;
}