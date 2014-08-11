/*
ID: joshoy71
PROG: hamming
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define bit(_N_) (1 << (_N_ - 1))

static int N, B, D;
static vector<int> result;

bool isHamming(unsigned int xor_code)
{
	unsigned int counter = 0;
	for (int i = 1; i <= B; ++i) {
		if (bit(i) & xor_code) {
			++counter;
		}
		if (counter == D) {
			return true;
		}
	}
	return false;
}

int main(int argc, char* argv[])
{
	ifstream fin("hamming.in");
	ofstream fout("hamming.out");

	fin >> N >> B >> D;
	result.push_back(0);

	unsigned int num = 0;
	bool isResult = false;
	while (result.size() < N) {
		isResult = true;
		++num;
		for (int i = 0; i < result.size(); ++i) {
			if (!isHamming(num ^ result[i])) {
				isResult = false;
				break;
			}
		}
		if (isResult) {
			result.push_back(num);
		}
	}

	for (int i = 1; i <= result.size(); ++i) {
		fout << result[i - 1];
		if (((i != 1) && (i % 10 == 0)) || (i == result.size())) {
			fout << endl;
		}
		else {
			fout << " ";
		}
	}
	
	return 0;
}