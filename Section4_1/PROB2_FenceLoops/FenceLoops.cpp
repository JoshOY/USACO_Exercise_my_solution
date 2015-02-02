/*
ID: joshoy71
PROG: fence6
LANG: C++11
*/

/*
解法：略有点恶心的一题。
开始总是找错最小环，后来搜了一下最小环的正确找法orz。
主要过程分两步：先构建出图，然后找最小环。

Executing...
   Test 1: TEST OK [0.003 secs, 3576 KB]
   Test 2: TEST OK [0.005 secs, 3576 KB]
   Test 3: TEST OK [0.003 secs, 3576 KB]
   Test 4: TEST OK [0.005 secs, 3576 KB]
   Test 5: TEST OK [0.005 secs, 3576 KB]
   Test 6: TEST OK [0.005 secs, 3576 KB]
   Test 7: TEST OK [0.005 secs, 3576 KB]
   Test 8: TEST OK [0.014 secs, 3576 KB]
   Test 9: TEST OK [0.008 secs, 3576 KB]

All tests OK.
*/

#include <fstream>

using namespace std;

const int N_MAX = 100;
const int INFI = 0x7fff;

struct Edge
{
	Edge() { len = 0; vertex1 = 0; vertex2 = 0; };

	int len = 0;
	int vertex1 = 0;
	int vertex2 = 0;
};

static ifstream fin("fence6.in", ios::in);
static ofstream fout("fence6.out", ios::out);
static int graph[N_MAX + 1][N_MAX + 1] = { { 0 } };
static int min_dist[N_MAX + 1][N_MAX + 1] = { { 0 } };
static int N;
static int edge_vertex_found[N_MAX + 1] = { 0 };
static int vertex_num = 0;
static int result = INFI;
static Edge edges[N_MAX + 1] = { Edge() };


inline int getLinkVertex(int edge1, int edge2) {
	if (edges[edge1].vertex1 == edges[edge2].vertex1) {
		return edges[edge1].vertex1;
	}
	else if (edges[edge1].vertex2 == edges[edge2].vertex1){
		return edges[edge1].vertex2;
	}
	else if (edges[edge1].vertex1 == edges[edge2].vertex2) {
		return edges[edge1].vertex1;
	}
	else if (edges[edge1].vertex2 == edges[edge2].vertex2) {
		return edges[edge1].vertex2;
	}
	else {
		return 0;
	}
}

void init()
{
	for (int i = 0; i <= N_MAX; ++i) {
		for (int j = 0; j <= N_MAX; ++j) {
			graph[i][j] = INFI;
		}
	}

	fin >> N;
	int s, ls, n1s, n2s, tmp;

	for (int i = 1; i <= N; ++i) {
		fin >> s >> ls >> n1s >> n2s;

		// When this edge links some new edges...
		if (edge_vertex_found[s] == 0) {
			vertex_num += 2;
			edge_vertex_found[s] = 2;
			edges[s].len = ls;
			edges[s].vertex1 = vertex_num - 1;
			edges[s].vertex2 = vertex_num;
			graph[vertex_num - 1][vertex_num] = ls;
			graph[vertex_num][vertex_num - 1] = ls;

			for (int j = 1; j <= n1s; ++j) {
				fin >> tmp;
				edge_vertex_found[tmp] += 1;
				if (edges[tmp].vertex1 == 0)
					edges[tmp].vertex1 = vertex_num - 1;
				else
					edges[tmp].vertex2 = vertex_num - 1;
			}
			for (int j = 1; j <= n2s; ++j) {
				fin >> tmp;
				edge_vertex_found[tmp] += 1;
				if (edges[tmp].vertex1 == 0)
					edges[tmp].vertex1 = vertex_num;
				else
					edges[tmp].vertex2 = vertex_num;
			}
		}
		// If we have known this edge before...
		else if (edge_vertex_found[s] == 1) {
			vertex_num += 1;
			edge_vertex_found[s] = 2;
			edges[s].len = ls;
			edges[s].vertex2 = vertex_num;
			graph[edges[s].vertex1][edges[s].vertex2] = ls;
			graph[edges[s].vertex2][edges[s].vertex1] = ls;

			for (int j = 1; j <= n1s; ++j) {
				fin >> tmp;
				if (edge_vertex_found[tmp] == 2) {
					continue;
				}
				else if (edge_vertex_found[tmp] == 1) {
					int vertex_linked = getLinkVertex(s, tmp);
					if (vertex_linked == 0) {
						edge_vertex_found[tmp] = 2;
						edges[tmp].vertex2 = vertex_num;
					}
				}
				else /* edge_vertex_found[tmp] == 0 */ {
					edge_vertex_found[tmp] += 1;
					if (edges[tmp].vertex1 == 0)
						edges[tmp].vertex1 = vertex_num;
					else
						edges[tmp].vertex2 = vertex_num;
				}
			}
			for (int j = 1; j <= n2s; ++j) {
				fin >> tmp;
				if (edge_vertex_found[tmp] == 2) {
					continue;
				}
				else if (edge_vertex_found[tmp] == 1) {
					int vertex_linked = getLinkVertex(s, tmp);
					if (vertex_linked == 0) {
						edge_vertex_found[tmp] = 2;
						edges[tmp].vertex2 = vertex_num;
					}
				}
				else /* edge_vertex_found[tmp] == 0 */ {
					edge_vertex_found[tmp] += 1;
					if (edges[tmp].vertex1 == 0)
						edges[tmp].vertex1 = vertex_num;
					else
						edges[tmp].vertex2 = vertex_num;
				}
			}
		}
		// if we have already ack 2 vertex of this edge
		else {
			edges[s].len = ls;
			graph[edges[s].vertex1][edges[s].vertex2] = ls;
			graph[edges[s].vertex2][edges[s].vertex1] = ls;
			for (int j = 1; j <= n1s; ++j) {
				fin >> tmp;
			}
			for (int j = 1; j <= n2s; ++j) {
				fin >> tmp;
			}
		}
	}

	return;
}

void solve()
{
	// 用Floyd-Warshall算法的同时算出最小环
	int i, j, k;
	for (i = 0; i <= vertex_num; ++i) {
		for (j = 0; j <= vertex_num; ++j) {
			min_dist[i][j] = graph[i][j];
		}
	}

	for (k = 1; k <= vertex_num; ++k) {
		for (i = 1; i <= k - 1; ++i) {
			for (j = i + 1; j <= k - 1; ++j) {
				if (result > min_dist[i][j] + graph[i][k] + graph[k][j]) {
					result = min_dist[i][j] + graph[i][k] + graph[k][j];
				}
			}
		}
		for (i = 1; i <= vertex_num; ++i) {
			for (j = 1; j <= vertex_num; ++j) {
				if (min_dist[i][j] > min_dist[i][k] + min_dist[k][j]) {
					min_dist[i][j] = min_dist[i][k] + min_dist[k][j];
				}
			}
		}
	}
	return;
}

int main(int argc, char *argv[])
{
	init();
	solve();

	fout << result << endl;

	return 0;
}