/*
ID: joshoy71
PROG: stall4
LANG: C++11
*/

#include <fstream>
#include <vector>

/*
解法：匈牙利算法，推荐：https://www.byvoid.com/zhs/blog/hungary

Executing...
   Test 1: TEST OK [0.005 secs, 3536 KB]
   Test 2: TEST OK [0.005 secs, 3536 KB]
   Test 3: TEST OK [0.011 secs, 3536 KB]
   Test 4: TEST OK [0.005 secs, 3536 KB]
   Test 5: TEST OK [0.003 secs, 3536 KB]
   Test 6: TEST OK [0.005 secs, 3536 KB]
   Test 7: TEST OK [0.011 secs, 3536 KB]
   Test 8: TEST OK [0.008 secs, 3536 KB]
   Test 9: TEST OK [0.014 secs, 3536 KB]

All tests OK.
*/

using namespace std;

const int N_MAX = 200;
const int M_MAX = 200;

static ifstream fin("stall4.in", ios::in);
static ofstream fout("stall4.out", ios::out);
static int N, M;
static bool graph[N_MAX + 1][M_MAX + 1] = { { 0 } };
static bool visited[N_MAX + 1] = { 0 };
static int linkVertex[M_MAX + 1] = { 0 };

void init()
{
	fin >> N >> M;
	int tmp_num, tmp;
	for (int i = 1; i <= N; ++i) {
		fin >> tmp_num;
		for (int j = 1; j <= tmp_num; ++j) {
			fin >> tmp;
			graph[i][tmp] = true;
		}
	}
	return;
}

//对k寻找匹配，如果找到就记录匹配，并返回true,否则返回false
bool findAugmentingPath(int src)
{
	//对所有节点遍历一遍，寻找没有访问过并且与i连通的点
	for (int i = 1; i <= N; ++i) {
		if ((graph[src][i] == true) && (visited[i] == false)) {
			visited[i] = true;
			if ((linkVertex[i] == 0) || findAugmentingPath(linkVertex[i])) {
				linkVertex[i] = src;
				return true;
			}
		}
	}
	return false;
}

int HungaryAlgorithm() {
	int rtn = 0;
	for (int i = 1; i <= M; ++i) {
		for (int j = 0; j <= M_MAX; ++j) {
			visited[j] = false;
		}
		if (findAugmentingPath(i)) {
			rtn += 1;
		}
	}
	return rtn;
}

int main(int argc, char* argv[])
{
	init();
	fout << HungaryAlgorithm() << endl;

	fin.close();
	fout.close();
	return 0;
}