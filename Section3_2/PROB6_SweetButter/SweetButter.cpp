/*
ID: joshoy71
PROG: butter
LANG: C++11
*/

#include <fstream>
#include <queue>

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
queue<int> q;

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

	for (int sugarPlace = 1; sugarPlace <= P; ++sugarPlace) {
		//At first we get the directly linked pastures into the queue q...
		for (linking = 1; linking <= P; ++linking) {
			if (graph[sugarPlace][linking] != INFI) {
				q.push(linking);
			}
		}

		//So here we go with it...
		while (!q.empty()) {
			frontElement = q.front();
			q.pop();
			pastureInQueue[frontElement] = false;
			for (linking = sugarPlace + 1; linking <= P; ++linking) {
				if (graph[sugarPlace][frontElement] + graph[frontElement][linking] < graph[sugarPlace][linking]) {
					graph[sugarPlace][linking] = graph[sugarPlace][frontElement] + graph[frontElement][linking];
					if (!pastureInQueue[linking]) {
						q.push(linking);
						pastureInQueue[linking] = true;
					}
				}
			}
		}
		for(linking = sugarPlace + 1; linking <= P; ++linking) {
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