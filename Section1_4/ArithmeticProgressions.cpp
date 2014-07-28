/*
ID: joshoy71
PROG: ariprog
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int M, N;

int main(int argc, char* argv[])
{
	ifstream fin("ariprog.in");
	ofstream fout("ariprog.out");

	fin >> N >> M;

	bool* numSet = new bool[M * M * 2];

	for (int i = 0; i <= M; ++i) {
		for (int j = i; j <= M; ++j) {
			numSet[i*i + j*j] = true;
		}
	}

	std::vector<int> numVec;
	for (int i = 0; i <= 2 * M * M; ++i) {
		if (numSet[i] == true)
			numVec.push_back(i);
	}

	vector<pair<int, int> > result;
	int lastNum = numVec[numVec.size() - 1];
	int counter = 1;

	for (int b = 1; b * (N - 1) <= lastNum; ++b) {
		for (int a = 0; a < numVec.size(); ++a) {
			if (numVec[a] + b * (N - 1) > lastNum) {
				break;
			}
			counter = 1;
			while (numSet[numVec[a] + counter * b] == true) {
				counter++;
				if (counter == N) {
					result.push_back(pair<int, int>(numVec[a], b));
					break;
				}
			}
		}
	}

	delete numSet;

	if (result.size() == 0) {
		fout << "NONE" << endl;
		return 0;
	}


	for (int i = 0; i < result.size(); ++i) {
		fout << result[i].first << " " << result[i].second << endl;
	}

	return 0;
}