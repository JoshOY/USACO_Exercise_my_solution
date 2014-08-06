/*
ID: joshoy71
PROG: sort3
LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

static int N;		// the number of records to be sorted
static std::vector<int> startOrder;
static std::vector<int> finalOrder;
static std::vector< std::pair<int, int> > cycles;
static int a, b, c;	// a < b < c
static bool travelled[1000] = { false };

using namespace std;

int main(int argc, char* argv[])
{
	ifstream fin("sort3.in");
	ofstream fout("sort3.out");

	fin >> N;
	int tmp;
	for (int i = 0; i < N; ++i) {
		fin >> tmp;
		startOrder.push_back(tmp);
	}

	finalOrder = startOrder;
	std::sort(finalOrder.begin(), finalOrder.end());
	
	a = finalOrder[0];
	c = finalOrder[N - 1];
	for (int i = 0; i < N; ++i) {
		if (a != finalOrder[i]) {
			b = finalOrder[i];
			break;
		}
	}

	for (int i = 0; i < N; ++i) {
		if (startOrder[i] != finalOrder[i])
			cycles.push_back(pair<int, int>(finalOrder[i], startOrder[i]));
	}

	int biChangeCounter = 0;
	for (int i = 0; i < cycles.size(); ++i) {
		if (!travelled[i]) {
			for (int j = i + 1; j < cycles.size(); ++j) {
				if ((travelled[j] == false) && (cycles[i].first == cycles[j].second) && (cycles[i].second == cycles[j].first)) {
					travelled[i] = true;
					travelled[j] = true;
					++biChangeCounter;
					break;
				}
			}
		}
	}

	int triChangeCounter = 0;
	for (int i = 0; i < cycles.size(); ++i) {
		if (travelled[i] == false)
			++triChangeCounter;
	}
	triChangeCounter /= 3;

	fout << cycles.size() - biChangeCounter - triChangeCounter << endl;

	return 0;
}