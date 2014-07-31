/*
ID: joshoy71
PROG: sprime
LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

static int N;

static vector<int> numVec1 = {2, 3, 5, 7};
static vector<int> numVec2;
static vector<int> numVec3;
static vector<int> numVec4;
static vector<int> numVec5;
static vector<int> numVec6;
static vector<int> numVec7;
static vector<int> numVec8;

const int addnum[] = {1, 3, 7, 9};

bool isPrime(int a)
{
	for (int i = 3; (i * i ) <= a; i += 2)
		if (a % i == 0)
			return false;
	return true;
}

int main(int argc, char* argv[])
{

	ifstream fin("sprime.in");
	ofstream fout("sprime.out");

	fin >> N;
	//////////////////////////////
	//N = 1
	//////////////////////////////
	if (N == 1) {
		fout << 2 << endl
			<< 3 << endl
			<< 5 << endl
			<< 7 << endl;
		return 0;
	}
	
	int tmp = 0;

	//////////////////////////////
	//N = 2
	//////////////////////////////
	for (int i = 0; i < numVec1.size(); ++i) {
		for (int j = 0; j < 4; ++j) {
			tmp = numVec1[i] * 10 + addnum[j];
			if (isPrime(tmp)) {
				numVec2.push_back(tmp);
			}
		}
	}
	if (N == 2) {
		for (int i = 0; i < numVec2.size(); ++i) {
			fout << numVec2[i] << endl;
		}
		return 0;
	}

	//////////////////////////////
	//N = 3
	//////////////////////////////
	for (int i = 0; i < numVec2.size(); ++i) {
		for (int j = 0; j < 4; ++j) {
			tmp = numVec2[i] * 10 + addnum[j];
			if (isPrime(tmp)) {
				numVec3.push_back(tmp);
			}
		}
	}
	if (N == 3) {
		for (int i = 0; i < numVec3.size(); ++i) {
			fout << numVec3[i] << endl;
		}
		return 0;
	}

	//////////////////////////////
	//N = 4
	//////////////////////////////
	for (int i = 0; i < numVec3.size(); ++i) {
		for (int j = 0; j < 4; ++j) {
			tmp = numVec3[i] * 10 + addnum[j];
			if (isPrime(tmp)) {
				numVec4.push_back(tmp);
			}
		}
	}
	if (N == 4) {
		for (int i = 0; i < numVec4.size(); ++i) {
			fout << numVec4[i] << endl;
		}
		return 0;
	}

	//////////////////////////////
	//N = 4
	//////////////////////////////
	for (int i = 0; i < numVec4.size(); ++i) {
		for (int j = 0; j < 4; ++j) {
			tmp = numVec4[i] * 10 + addnum[j];
			if (isPrime(tmp)) {
				numVec5.push_back(tmp);
			}
		}
	}
	if (N == 5) {
		for (int i = 0; i < numVec5.size(); ++i) {
			fout << numVec5[i] << endl;
		}
		return 0;
	}

	//////////////////////////////
	//N = 6
	//////////////////////////////
	for (int i = 0; i < numVec5.size(); ++i) {
		for (int j = 0; j < 4; ++j) {
			tmp = numVec5[i] * 10 + addnum[j];
			if (isPrime(tmp)) {
				numVec6.push_back(tmp);
			}
		}
	}
	if (N == 6) {
		for (int i = 0; i < numVec6.size(); ++i) {
			fout << numVec6[i] << endl;
		}
		return 0;
	}

	//////////////////////////////
	//N = 7
	//////////////////////////////
	for (int i = 0; i < numVec6.size(); ++i) {
		for (int j = 0; j < 4; ++j) {
			tmp = numVec6[i] * 10 + addnum[j];
			if (isPrime(tmp)) {
				numVec7.push_back(tmp);
			}
		}
	}
	if (N == 7) {
		for (int i = 0; i < numVec7.size(); ++i) {
			fout << numVec7[i] << endl;
		}
		return 0;
	}
	
	//////////////////////////////
	//N = 8
	//////////////////////////////
	for (int i = 0; i < numVec7.size(); ++i) {
		for (int j = 0; j < 4; ++j) {
			tmp = numVec7[i] * 10 + addnum[j];
			if (isPrime(tmp)) {
				numVec8.push_back(tmp);
			}
		}
	}
	if (N == 8) {
		for (int i = 0; i < numVec8.size(); ++i) {
			fout << numVec8[i] << endl;
		}
	}

	return 0;
}