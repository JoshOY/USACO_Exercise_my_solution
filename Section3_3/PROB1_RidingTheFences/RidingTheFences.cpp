/*
ID: joshoy71
PROG: fence
LANG: C++11
*/

/*
TEST RESULT:
   Test 1: TEST OK [0.005 secs, 4484 KB]
   Test 2: TEST OK [0.005 secs, 4484 KB]
   Test 3: TEST OK [0.003 secs, 4484 KB]
   Test 4: TEST OK [0.003 secs, 4484 KB]
   Test 5: TEST OK [0.005 secs, 4484 KB]
   Test 6: TEST OK [0.005 secs, 4484 KB]
   Test 7: TEST OK [0.019 secs, 4484 KB]
   Test 8: TEST OK [0.035 secs, 4484 KB]
*/

#include <fstream>
#include <vector>

using namespace std;

const int FARM_MAX = 500;

static ifstream fin("fence.in");
static ofstream fout("fence.out");

static int F;
static int graph[FARM_MAX + 1][FARM_MAX + 1] = { { 0 } };
static int fenceNumOfFarm[FARM_MAX + 1] = { 0 };
static int remainFenceNumOfFarm[FARM_MAX + 1] = { 0 };
static vector<int> result;


void input()
{
	fin >> F;
	int from, to;
	for (int i = 1; i <= F; ++i) {
		fin >> from >> to;
		graph[from][to] += 1;
		graph[to][from] += 1;
		fenceNumOfFarm[from] += 1;
		fenceNumOfFarm[to] += 1;
		remainFenceNumOfFarm[from] += 1;
		remainFenceNumOfFarm[to] += 1;
	}
}

void dfs(int currentNode)
{
	if (remainFenceNumOfFarm == 0) {
		result.push_back(currentNode);
		return;
	} else {
	while (remainFenceNumOfFarm[currentNode] != 0) {
		for (int i = 1; i <= FARM_MAX; ++i) {
			if (graph[currentNode][i]) {
				--graph[currentNode][i];
				--graph[i][currentNode];
				--remainFenceNumOfFarm[currentNode];
				--remainFenceNumOfFarm[i];
				dfs(i);
				}
			}
		}
		result.push_back(currentNode);
	}
	return;
}

void solve()
{
	int start = 1;
	bool findOddStartPoint = false;
	for (start = 1; start <= FARM_MAX; ++start) {
		if (fenceNumOfFarm[start] & 0x0001) {
			findOddStartPoint = true;
			break;
		}
	}

	if (findOddStartPoint == false) {
		for (start = 1; start <= FARM_MAX; ++start) {
			if (fenceNumOfFarm[start] != 0) {
				break;
			}
		}
	}

	dfs(start);
	
	return;
}

void output()
{
	for (int i = result.size() - 1; i >= 0; --i) {
		fout << result[i] << endl;
	}
	return;
}

int main(int argc, char* argv[])
{
	input();
	solve();
	output();

	return 0;
}