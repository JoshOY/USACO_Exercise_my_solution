/*
ID: joshoy71
PROG: clocks
LANG: C++11
*/


#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;

static vector<int> clocks;
static map<int, vector<int> > rotationMethodMap;



void initMap() {
	rotationMethodMap[1] = vector<int>({ 1, 1, 0, 1, 1 ,0, 0, 0, 0 });
	rotationMethodMap[2] = vector<int>({ 1, 1, 1, 0, 0, 0, 0, 0, 0 });
	rotationMethodMap[3] = vector<int>({ 0, 1, 1, 0, 1, 1, 0, 0, 0 });
	rotationMethodMap[4] = vector<int>({ 1, 0, 0, 1, 0, 0, 1, 0, 0 });
	rotationMethodMap[5] = vector<int>({ 0, 1, 0, 1, 1, 1, 0, 1, 0 });
	rotationMethodMap[6] = vector<int>({ 0, 0, 1, 0, 0, 1, 0, 0, 1 });
	rotationMethodMap[7] = vector<int>({ 0, 0, 0, 1, 1, 0, 1, 1, 0 });
	rotationMethodMap[8] = vector<int>({ 0, 0, 0, 0, 0, 0, 1, 1, 1 });
	rotationMethodMap[9] = vector<int>({ 0, 0, 0, 0, 1, 1, 0, 1, 1 });
}

vector<int> rotation(vector<int> clockList, vector<int> method)
{
	for (int which = 0; which < 9; ++which) {
		if (method[which] == 1) {
			clockList[which] += 3;
			if (clockList[which] == 15) {
				clockList[which] = 3;
			}
		}
	}
	return clockList;
}

typedef vector<int> Result;

vector<int> getClock(const vector<int>& travelled)
{
	vector<int> result_clock = clocks;
	for (int i = 0; i < travelled.size(); ++i) {
		result_clock = rotation(result_clock, rotationMethodMap[travelled[i]]);
	}
	return result_clock;
}

static queue<Result> q;

bool check(const vector<int>& clockList)
{
	for (int i = 0; i < 9; ++i) {
		if (clockList[i] != 12) {
			return false;
		}
	}
	return true;
}

bool checkQueue(const vector<int>& _queue, int x)
{
	int counter = 0;
	for (int i = 0; i < _queue.size(); i++) {
		if (_queue[i] == x) {
			++counter;
		}
		if (counter == 3) {
			return false;
		}
	}
	return true;
}

Result bfsTravel()
{
	if (q.size() == 0) {
		for (int i = 1; i <= 9; ++i) {
			Result initResult({ i });
			if (check(getClock(initResult))) {
				return initResult;
			}
			q.push(initResult);
		}
		return bfsTravel();
	}

	else {
		auto times = q.size();
		for (int i = 0; i < times; ++i) {
			for (int j = q.front()[q.front().size() - 1]; j <= 9; ++j) {
				if (checkQueue(q.front(), j)){
					auto rotatedClocks = rotation(getClock(q.front()), rotationMethodMap[j]);
					if (check(rotatedClocks)) {
						Result result = q.front();
						result.push_back(j);
						return result;
					}
					else {
						Result not_final_result = q.front();
						not_final_result.push_back(j);
						q.push(not_final_result);
					}
				}
			}
			q.pop();
		}


		return bfsTravel();
	}
}




int main(int argc, char* argv[])
{
	initMap();
	ifstream fin("clocks.in");
	ofstream fout("clocks.out");

	//fstream fin("E:\\usaco.txt", ios::in);
	//fstream fout("E:\\usacoOut.txt", ios::out);

	//input the status
	for (int i = 0; i < 9; ++i) {
		clocks.push_back(0);
		fin >> clocks[i];
	}

	Result result = bfsTravel();

	for (int i = 0; i < result.size(); ++i) {
		fout << result[i];
		if (i != result.size() - 1)
			fout << " ";
		else
			fout << endl;
	}

	return 0;
}