/*
ID: joshoy71
PROG: gift1
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
	ofstream fout("gift1.out");
	ifstream fin("gift1.in");

	unsigned int NP;
	int money_initial;
	int money_giving;
	int giving_people_num;
	vector<string> nameVector;
	
	fin >> NP;	

	map<string, int> moneyMap;
	string giverName;
	string tmpName;

	for (unsigned int i = 0; i < NP; i++) {
		fin >> tmpName;
		nameVector.push_back(tmpName);
		moneyMap[tmpName] = 0;
	}

	for (unsigned int i = 0; i < NP; i++) {
		fin >> giverName;
		fin >> money_initial >> giving_people_num;
		if ( (money_initial != 0) && (giving_people_num != 0) ) {
			moneyMap[giverName] -= (money_initial - (money_initial % giving_people_num));
			for (int j = 0; j < giving_people_num; j++) {
				fin >> tmpName;
				moneyMap[tmpName] += (money_initial / giving_people_num);
			}
		} else if ((money_initial == 0) && (giving_people_num != 0)) {
			for (int j = 0; j < giving_people_num; j++) {
				fin >> tmpName;
			}
		} else {}

	}

	for (int i = 0; i < NP; i++) {
		fout << nameVector[i] << " " << moneyMap[nameVector[i]] << endl;
	}

	return 0;
}