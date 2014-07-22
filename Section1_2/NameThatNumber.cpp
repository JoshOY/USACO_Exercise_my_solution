/*
ID: joshoy71
PROG: namenum
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

using namespace std;


/*
string translator(string cowName)
{
	string number = "";
	for (int i = 0; i < cowName.length(); i++) {
		if ((cowName[i] == 'A') || (cowName[i] == 'B') || (cowName[i] == 'C')) {
			number += '2';
		}
		else if ((cowName[i] == 'D') || (cowName[i] == 'E') || (cowName[i] == 'F')) {
			number += '3';
		}
		else if ((cowName[i] == 'G') || (cowName[i] == 'H') || (cowName[i] == 'I')) {
			number += '4';
		}
		else if ((cowName[i] == 'J') || (cowName[i] == 'K') || (cowName[i] == 'L')) {
			number += '5';
		}
		else if ((cowName[i] == 'M') || (cowName[i] == 'N') || (cowName[i] == 'O')) {
			number += '6';
		}
		else if ((cowName[i] == 'P') || (cowName[i] == 'R') || (cowName[i] == 'S')) {
			number += '7';
		}
		else if ((cowName[i] == 'T') || (cowName[i] == 'U') || (cowName[i] == 'V')) {
			number += '8';
		}
		else if ((cowName[i] == 'W') || (cowName[i] == 'X') || (cowName[i] == 'Y')) {
			number += '9';
		}
	}
	return number;
}*/

int main(int argc, char* argv[])
{
	map<char, char> char_dict;
	char_dict['A'] = '2';
	char_dict['B'] = '2';
	char_dict['C'] = '2';
	char_dict['D'] = '3';
	char_dict['E'] = '3';
	char_dict['F'] = '3';
	char_dict['G'] = '4';
	char_dict['H'] = '4';
	char_dict['I'] = '4';
	char_dict['J'] = '5';
	char_dict['K'] = '5';
	char_dict['L'] = '5';
	char_dict['M'] = '6';
	char_dict['N'] = '6';
	char_dict['O'] = '6';
	char_dict['P'] = '7';
	char_dict['R'] = '7';
	char_dict['S'] = '7';
	char_dict['T'] = '8';
	char_dict['U'] = '8';
	char_dict['V'] = '8';
	char_dict['W'] = '9';
	char_dict['X'] = '9';
	char_dict['Y'] = '9';

	ifstream fin("namenum.in");
	ifstream dictIn("dict.txt");
	ofstream fout("namenum.out");
	
	map<string, string> dictionary;
	vector<string> nameList;

	string code;
	fin >> code;

	string name;
	bool found = false;

	while (dictIn >> name) {
		if (name.length() == code.length()) {
			string tmpNameCode;
			for (int i = 0; i < name.length(); i++) {
				tmpNameCode.push_back(char_dict[name[i]]);
			}
			if (tmpNameCode == code) {
				fout << name << endl;
				found = true;
			}
		}
	}

	if (!found)
		fout << "NONE" << endl;

	return 0;
}