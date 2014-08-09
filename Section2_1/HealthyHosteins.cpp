/*
ID: joshoy71
PROG: holstein
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <deque>

using namespace std;

#define bit(_N_) (1 << (_N_ - 1))
#define INT_MAX 2147483647

static int V;	//vitamin numbers
static int G;	//types of feeds available
static vector<int> vitaminNeed;
static vector<vector<int> > feedsInfo;
static deque<int> feedsSelected;
static bool foundInThisLayer = false;
static int typesNeed = 0;
static vector<int> resultSet;

void bfs()
{
	vector<int> totalVitamins;
	for (int n = 0; n < V; ++n) {
		totalVitamins.push_back(0);
	}

	while (!foundInThisLayer) {
		++typesNeed;
		int findRange = feedsSelected.size();

		for (int i = 0; i < findRange; ++i) {

			bool isResult = true;
			for (int n = 0; n < V; ++n) {
				totalVitamins[n] = 0;
			}

			for (int n = 0; n < G; ++n) {
				if (bit(n + 1) & feedsSelected[0]) {
					for (int m = 0; m < V; ++m) {
						totalVitamins[m] += feedsInfo[n][m];
					}
				}
			}

			for (int j = 0; j < V; ++j) {
				if (totalVitamins[j] < vitaminNeed[j]) {
					for (int n = bit(G); n > 0; n >>= 1) {
						if (!(n & feedsSelected[0])) {
							feedsSelected.push_back(feedsSelected[0] | n);
						}
						else {
							break;
						}
					}
					isResult = false;
					break;
				}
			}

			if (isResult) {
				resultSet.push_back(feedsSelected[0]);
				foundInThisLayer = true;
			}
			feedsSelected.pop_front();
		}
	}

	return;
}

vector<int> getMinimumResult()
{
	int min = INT_MAX;
	int selection = 0;
	vector<int> finalResult;
	vector<int> currentResult;

	for (int i = 0; i < resultSet.size(); ++i) {
		int sum = 0;
		currentResult.clear();
		for (int n = 1; n <= G; ++n) {
			if (bit(n) & resultSet[selection]) {
				currentResult.push_back(n);
			}
		}

		for (int n = 0; n < currentResult.size(); ++n) {
			sum += feedsInfo[currentResult[n] - 1][n];
		}

		if (sum < min) {
			min = sum;
			selection = i;
		}
	}

	
	for (int n = 1; n <= G; ++n) {
		if (bit(n) & resultSet[selection]) {
			finalResult.push_back(n);
		}
	}
	return finalResult;
}


int main(int argc, char* argv[])
{
	ifstream fin("holstein.in");
	ofstream fout("holstein.out");

	fin >> V;

	int tmp;
	for (int i = 0; i < V; ++i) {
		fin >> tmp;
		vitaminNeed.push_back(tmp);
	}

	fin >> G;

	vector<int> tmpVec;
	for (int i = 0; i < G; ++i) {
		tmpVec.clear();
		for (int j = 0; j < V; ++j) {
			fin >> tmp;
			tmpVec.push_back(tmp);
		}
		feedsInfo.push_back(tmpVec);
	}

	//Inputs end

	for (int i = 1; i <= G; ++i) {
		feedsSelected.push_back(bit(i));
	}

	bfs();
	vector<int> finalResult = getMinimumResult();

	fout << typesNeed;
	for (int i = 0; i < typesNeed; ++i) {
		fout << " " << finalResult[i];
	}
	fout << endl;

	fin.close();
	fout.close();

	return 0;
}