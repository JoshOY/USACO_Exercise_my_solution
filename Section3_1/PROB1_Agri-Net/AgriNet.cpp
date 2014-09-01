/*
ID: joshoy71
PROG: agrinet
LANG: C++11
*/

/*
TEST RESULT:
   Test 1: TEST OK [0.011 secs, 3536 KB]
   Test 2: TEST OK [0.008 secs, 3536 KB]
   Test 3: TEST OK [0.008 secs, 3536 KB]
   Test 4: TEST OK [0.005 secs, 3536 KB]
   Test 5: TEST OK [0.003 secs, 3536 KB]
   Test 6: TEST OK [0.008 secs, 3536 KB]
   Test 7: TEST OK [0.005 secs, 3536 KB]
   Test 8: TEST OK [0.008 secs, 3536 KB]
   Test 9: TEST OK [0.011 secs, 3536 KB]
   Test 10: TEST OK [0.014 secs, 3536 KB]
*/

#include <fstream>

using namespace std;

const int N_MAX = 100;
const int infinite = 0xfffff;

static int N;
static int graph[N_MAX + 1][N_MAX + 1] = { { 0 } };
static int shortestRouteLength[N_MAX] = { infinite };
static bool nodeTravelled[N_MAX + 1] = { false };
static int result = 0;

static ifstream fin("agrinet.in");
static ofstream fout("agrinet.out");

void initAndInput()
{
	// init
	for(int i = 0; i <= N_MAX; ++i) {
		shortestRouteLength[i] = infinite;
	}

	//input
	fin >> N;
	for(int i = 1; i <= N; ++i) {
		for(int j = 1; j <= N; ++j) {
			fin >> graph[i][j];
		}
	}

	return;
}

void primAlgorithm(int targetNode)
{
	int tmpMinLength = infinite;
	int nextNode = 0;

	nodeTravelled[targetNode] = true;

	for (int i = 1; i <= N; ++i) {
		if (i == targetNode) {
			continue;
		}
		if ((nodeTravelled[i] == false) && (shortestRouteLength[i] > graph[targetNode][i])) {
			shortestRouteLength[i] = graph[targetNode][i];
		}

	}

	for (int i = 1; i <= N; ++i) {
		if (i == targetNode) {
			continue;
		}
		if ((nodeTravelled[i] == false) && (tmpMinLength > shortestRouteLength[i])) {
			nextNode = i;
			tmpMinLength = shortestRouteLength[i];
		}
	}

	if (nextNode != 0) {
		result += tmpMinLength;
		primAlgorithm(nextNode);
	}

	return;

}

void output()
{
	fout << result << endl;
	return;
}

int main(int argc, char* argv[])
{
	initAndInput();
	primAlgorithm(1);
	output();
	
	return 0;
}