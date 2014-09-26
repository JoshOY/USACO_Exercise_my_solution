/*
ID: joshoy71
PROG: butter
LANG: C++11
*/

/*
TEST RESULT:
   Test 1: TEST OK [0.008 secs, 9912 KB]
   Test 2: TEST OK [0.005 secs, 9912 KB]
   Test 3: TEST OK [0.016 secs, 9912 KB]
   Test 4: TEST OK [0.014 secs, 9912 KB]
   Test 5: TEST OK [0.019 secs, 9912 KB]
   Test 6: TEST OK [0.035 secs, 9912 KB]
   Test 7: TEST OK [0.121 secs, 9912 KB]
   Test 8: TEST OK [0.381 secs, 9912 KB]
   Test 9: TEST OK [0.705 secs, 9912 KB]
   Test 10: TEST OK [0.724 secs, 9912 KB]
*/

#include <fstream>

using namespace std;

const int P_MAX = 800;
const int N_MAX = 500;
const int C_MAX = 1450;
const int INFI = 0x7ffff;

int N;	//number of cows
int P;	//number of pastures
int C;	//number of paths

ifstream fin("butter.in");
ofstream fout("butter.out");


int graph[P_MAX + 1][P_MAX + 1];
int cowNumOfPastures[P_MAX + 1];
bool pastureInQueue[P_MAX + 1] = { false };
int q[1000001] = { 0 };
int frontIndex, backIndex;

void initAndInput()
{
	for (int i = 0; i <= P_MAX; ++i) {
		for (int j = 0; j <= P_MAX; ++j) {
			graph[i][j] = INFI;
		}
	}

	fin >> N >> P >> C;
	int tmp;
	for (int i = 1; i <= N; ++i) {
		fin >> tmp;
		++cowNumOfPastures[tmp];
	}
	int pasA, pasB;
	for (int i = 1; i <= C; ++i) {
		fin >> pasA >> pasB >> tmp;
		graph[pasA][pasB] = tmp;
		graph[pasB][pasA] = tmp;
	}
}

//SPFA, Shortest Path Faster Algorithm, recommending to use~
void spfa()
{
	//Using a queue q to record
	int frontElement;
	int linking;

	frontIndex = backIndex = 0;

	for (int sugarPlace = 1; sugarPlace <= P; ++sugarPlace) {
		//At first we get the directly linked pastures into the queue q...
		for (linking = 1; linking <= P; ++linking) {
			if (graph[sugarPlace][linking] != INFI) {
				q[backIndex + 1] = linking;
				backIndex += 1;
			}
		}

		//So here we go with it...
		while (frontIndex != backIndex) {
			frontElement = q[frontIndex];
			frontIndex += 1;
			pastureInQueue[frontElement] = false;
			for (linking = sugarPlace + 1; linking <= P; ++linking) {
				if (graph[sugarPlace][frontElement] + graph[frontElement][linking] < graph[sugarPlace][linking]) {
					graph[sugarPlace][linking] = graph[sugarPlace][frontElement] + graph[frontElement][linking];
					if (!pastureInQueue[linking]) {
						q[backIndex + 1] = linking;
						backIndex += 1;
						pastureInQueue[linking] = true;
					}
				}
			}
		}
		for (linking = sugarPlace + 1; linking <= P; ++linking) {
			graph[linking][sugarPlace] = graph[sugarPlace][linking];
		}
	}
	for (int pasture = 1; pasture <= P; ++pasture) {
		graph[pasture][pasture] = 0;
	}
}

int getResult()
{
	int minDistance = INFI;
	int currentPastureDistanceCount;
	int sugarPlace, fromPasture;
	for (sugarPlace = 1; sugarPlace <= P; ++sugarPlace) {
		currentPastureDistanceCount = 0;
		for (fromPasture = 1; fromPasture <= P; ++fromPasture) {
			currentPastureDistanceCount += graph[sugarPlace][fromPasture] * cowNumOfPastures[fromPasture];
		}
		if (currentPastureDistanceCount < minDistance) {
			minDistance = currentPastureDistanceCount;
		}
	}
	return minDistance;
}

int main(int argc, char* argv[])
{
	initAndInput();
	spfa();
	fout << getResult() << endl;

	return 0;
}