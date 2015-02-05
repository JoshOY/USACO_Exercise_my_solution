/*
ID: joshoy71
PROG: ditch
LANG: C++11
*/

/*
解法：最大流问题。
以用Edmonds-Karp算法求最大流即可。

Executing...
   Test 1: TEST OK [0.003 secs, 3656 KB]
   Test 2: TEST OK [0.003 secs, 3656 KB]
   Test 3: TEST OK [0.003 secs, 3656 KB]
   Test 4: TEST OK [0.003 secs, 3656 KB]
   Test 5: TEST OK [0.003 secs, 3656 KB]
   Test 6: TEST OK [0.003 secs, 3656 KB]
   Test 7: TEST OK [0.003 secs, 3656 KB]
   Test 8: TEST OK [0.011 secs, 3656 KB]
   Test 9: TEST OK [0.003 secs, 3656 KB]
   Test 10: TEST OK [0.005 secs, 3656 KB]
   Test 11: TEST OK [0.003 secs, 3656 KB]
   Test 12: TEST OK [0.003 secs, 3656 KB]

All tests OK.
YOUR PROGRAM ('ditch') WORKED FIRST TIME!  That's fantastic
-- and a rare thing.  Please accept these special automated
congratulations.
*/

#include <fstream>
#include <queue>

using namespace std;

#define min(_A_, _B_) ( ((_A_) < (_B_)) ? (_A_) : (_B_) )
const int M_MAX = 200;
const int INFI = 0x7fff;

static ifstream fin("ditch.in", ios::in);
static ofstream fout("ditch.out", ios::out);
/*
N: number of edges
M: number of vertices
*/
static int N, M;
static int graph[M_MAX + 1][M_MAX + 1] = { { 0 } };
static int result;
static queue<int> q;
static int pre[M_MAX + 1] = { 0 };
static int flow[M_MAX + 1] = { 0 };

void init()
{
	fin >> N >> M;

	int from, to, cap;

	for (int i = 1; i <= N; ++i) {
		fin >> from >> to >> cap;
		// 注意用 += 而不是 = 以防有多条边
		graph[from][to] += cap;
	}

	return;
}

int BFS(int src, int des)
{
	while (q.empty() == false) {
		q.pop();
	}
	for (int i = 1; i <= M; ++i) {
		pre[i] = -1;
	}
	pre[src] = 0;
	flow[src] = INFI;
	q.push(src);

	while (q.empty() == false) {
		int index = q.front();
		q.pop();
		if (index == des) {
			break;
		}
		for (int i = 1; i <= M; ++i) {
			if ((i != src) && (graph[index][i] > 0) && (pre[i] == -1)) {
				pre[i] = index;
				flow[i] = min(graph[index][i], flow[index]);
				q.push(i);
			}
		}
	}

	if (pre[des] == -1) {
		return -1;
	}
	else {
		return flow[des];
	}
}

int maxFlow(int src, int des)
{
	int increasement = 0;
	int sumFLow = 0;
	
	while ((increasement = BFS(src, des)) != -1) {
		int k = des;
		while (k != src) {
			int last = pre[k];
			graph[last][k] -= increasement;
			graph[k][last] += increasement;
			k = last;
		}
		sumFLow += increasement;
	}
	return sumFLow;
}

void solve()
{
	result = maxFlow(1, M);
	return;
}

int main(int argc, char* argv[])
{
	init();
	solve();
	fout << result << endl;

	fin.close();
	fout.close();
	return 0;
}