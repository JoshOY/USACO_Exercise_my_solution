/*
ID: joshoy71
PROG: lamps
LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define light(_N_) (0x0020 >> ((_N_) - 1))

// 11 1111, the first six lights are enough to show status of all the lights
static long sixLights = 0x003F;

// button[1]: 111111, button[2]: 101010, button[3]: 010101, button[4]: 100100
static const int button[5] = {0, 0x003F, 0x002A, 0x0015, 0x0024};

static int finalOn = 0;
static int finalOff = 0;
static int N;	//light num
static int C;	//counter
static vector<int> possibilities = { };
static vector<int> result = { };

void pushPossibilities()
{
	if (C == 0) {
		possibilities.push_back(sixLights);
		return;
	} else if (C == 1) {
		possibilities.push_back(sixLights ^ button[1]);
		possibilities.push_back(sixLights ^ button[2]);
		possibilities.push_back(sixLights ^ button[3]);
		possibilities.push_back(sixLights ^ button[4]);
		return;
	}
	else if (C == 2) {
		possibilities.push_back(sixLights);
		possibilities.push_back(sixLights ^ button[1]);
		possibilities.push_back(sixLights ^ button[2]);
		possibilities.push_back(sixLights ^ button[3]);
		possibilities.push_back(sixLights ^ button[1] ^ button[4]);
		possibilities.push_back(sixLights ^ button[2] ^ button[4]);
		possibilities.push_back(sixLights ^ button[3] ^ button[4]);
		return;
	}
	// if C >= 3, we always have these possibillities
	else {
		possibilities.push_back(sixLights);
		possibilities.push_back(sixLights ^ button[1]);
		possibilities.push_back(sixLights ^ button[2]);
		possibilities.push_back(sixLights ^ button[3]);
		possibilities.push_back(sixLights ^ button[4]);
		possibilities.push_back(sixLights ^ button[1] ^ button[4]);
		possibilities.push_back(sixLights ^ button[2] ^ button[4]);
		possibilities.push_back(sixLights ^ button[3] ^ button[4]);
		return;
	}
}

bool check()
{
	bool bRtn = true;
	for (int i = 0; i < possibilities.size(); ++i) {
		if ((finalOn == 0) && (finalOff == 0)) {
			result.push_back(possibilities[i]);
			bRtn = false;
		}
		else if ((finalOn != 0) && (finalOff == 0)) {
			if ((possibilities[i] & finalOn) == finalOn) {
				bRtn = false;
				result.push_back(possibilities[i]);
			}
		}
		else if ((finalOn == 0) && (finalOff != 0)) {
			if (!(possibilities[i] & finalOff)) {
				bRtn = false;
				result.push_back(possibilities[i]);
			}
		}
		else {
			if ( ((possibilities[i] & finalOn) == finalOn) && (!(possibilities[i] & finalOff))) {
				bRtn = false;
				result.push_back(possibilities[i]);
			}
		}
	}
	return bRtn;
}

int main(int argc, char* argv[])
{
	ifstream fin("lamps.in");
	ofstream fout("lamps.out");

	fin >> N >> C;
	int tmpInput;

	while (true) {
		fin >> tmpInput;
		if (tmpInput != -1) {
			tmpInput %= 6;
			if (tmpInput == 0)
				tmpInput = 6;
			finalOn |= light(tmpInput);
		} else {
			break;
		}
	}

	while (true) {
		fin >> tmpInput;
		if (tmpInput != -1) {
			tmpInput %= 6;
			if (tmpInput == 0)
				tmpInput = 6;
			finalOff |= light(tmpInput);
		} else {
			break;
		}
	}

	pushPossibilities();
	std::sort(possibilities.begin(), possibilities.end());
	bool impossible = check();

	if (impossible == true) {
		fout << "IMPOSSIBLE" << endl;
	}
	else {
		for (int i = 0; i < result.size(); ++i) {
			int c = 1;
			int pos = 1;
			while (c <= N) {
				pos = c % 6;
				if (pos == 0)
					pos = 6;
				if (result[i] & light(pos))
					fout << '1';
				else
					fout << '0';
				++c;
			}
			fout << endl;
		}
	}

	return 0;
}