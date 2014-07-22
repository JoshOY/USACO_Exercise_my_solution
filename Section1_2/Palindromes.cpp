/*
ID: joshoy71
PROG: palsquare
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

using namespace std;

static map<int, char> numMap;

void initNumMap(map<int, char>& numMap)
{
	numMap[0] = '0';
	numMap[1] = '1';
	numMap[2] = '2';
	numMap[3] = '3';
	numMap[4] = '4';
	numMap[5] = '5';
	numMap[6] = '6';
	numMap[7] = '7';
	numMap[8] = '8';
	numMap[9] = '9';
	numMap[10] = 'A';
	numMap[11] = 'B';
	numMap[12] = 'C';
	numMap[13] = 'D';
	numMap[14] = 'E';
	numMap[15] = 'F';
	numMap[16] = 'G';
	numMap[17] = 'H';
	numMap[18] = 'I';
	numMap[19] = 'J';
}

int power(int a, int n)
{
	int result = 1;
	for (int i = 0; i < n; i++) {
		result *= a;
	}
	return result;
}

string convertDecToTargetAry(unsigned int number, unsigned int ary) {
	string targetAryNumber;
	int n = 0;
	while (number >= power(ary, n)){
		n++;
	}
	for (int i = n - 1; i >= 0; i--) {
		unsigned int current_weight = power(ary, i);
		int bitnum = 0;
		while (number - (bitnum * current_weight) >= current_weight) {
			bitnum++;
		}
		number -= (bitnum * current_weight);
		targetAryNumber.push_back(numMap[bitnum]);
	}
	return targetAryNumber;
}

bool isPalindromesNumber(const string& number)
{
	int i = 0;
	int j = number.length() - 1;
	for (int m = 0; m < int(number.length() / 2); m++) {
		if (number[i] != number[j]) {
			return false;
		}
		i++;
		j--;
	}
	return true;
}

int main(int argc, char* argv[])
{
	ifstream fin("palsquare.in");
	ofstream fout("palsquare.out");

	initNumMap(numMap);

	unsigned int B;
	fin >> B;

	for (unsigned int num = 1; num <= 300; num++) {
		string targetNum =  convertDecToTargetAry(num, B);
		string targetNumSquare = convertDecToTargetAry((num * num), B);
		if (isPalindromesNumber(targetNumSquare))
		{
			fout << targetNum << " " << targetNumSquare << endl;
		}
	}

	return 0;
}