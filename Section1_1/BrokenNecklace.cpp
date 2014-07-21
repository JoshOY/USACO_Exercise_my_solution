/*
ID: joshoy71
PROG: beads
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

const char redBead = 'r';
const char blueBead = 'b';
const char whiteBead = 'w';
const bool RED_COMBO = true;
const bool BLUE_COMBO = false;

void solveNecklace(unsigned int& max_num, string& necklace)
{
	unsigned int currentCombo = 0;
	unsigned int lastCombo = 0;
	unsigned int startPoint = 0;
	bool status;

	if (necklace[0] == blueBead) {
		status = BLUE_COMBO;
	}
	else if (necklace[0] == redBead) {
		status = RED_COMBO;
	}
	else {
		for (startPoint = 0; true; startPoint++) {
			if (necklace[startPoint] == whiteBead) {
				currentCombo++;
			}
			else {
				if (necklace[startPoint] == blueBead) {
					status = BLUE_COMBO;
					break;
				}
				else {
					status = RED_COMBO;
					break;
				}
			}
		}
	}

	for (int i = startPoint; i < necklace.length(); i++) {
		if ((necklace[i] == redBead) && (status == RED_COMBO)) {
			currentCombo++;
		}
		else if ((necklace[i] == blueBead) && (status == BLUE_COMBO)) {
			currentCombo++;
		}
		else if (necklace[i] == whiteBead) {
			currentCombo++;
		}
		else {
			if (max_num < (currentCombo + lastCombo)) {
				max_num = (currentCombo + lastCombo);
			}
			lastCombo = currentCombo;
			currentCombo = 1;
			status = (!status);

			int j = i - 1;
			while (j >= 0) {
				if (necklace[j] == whiteBead) {
					currentCombo++;
					lastCombo--;
					j--;
				}
				else {
					break;
				}
			}
		}
	}

	if (max_num < (currentCombo + lastCombo)) {
		max_num = (currentCombo + lastCombo);
	}
}


int main(int argc, char* argv[])
{
	ifstream fin("beads.in");
	ofstream fout("beads.out");

	int beadNum;
	fin >> beadNum;

	string necklace;
	//cin >> necklace;
	fin >> necklace;
	necklace = necklace + necklace;

	unsigned int max_num = 0;
	bool one_colored = false;

	for (int i = 0; i < necklace.length(); i++) {
		if (necklace[i] != necklace[0]) {
			break;
		}
		if (i == necklace.length() - 1) {
			one_colored = true;
		}
	}

	if (one_colored == false) {
		solveNecklace(max_num, necklace);
		reverse(necklace.begin(), necklace.end());
		solveNecklace(max_num, necklace);
	}
	else {
		max_num = necklace.length() / 2;
	}

	if (max_num > beadNum) {
		max_num = beadNum;
	}

	fout << max_num << endl;

	//system("pause");
	return 0;
}