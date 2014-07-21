/*
ID: joshoy71
PROG: ride
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
	char cometName[7];
	char groupName[7];

	ofstream fout("ride.out");
	ifstream fin("ride.in");

	fin >> cometName >> groupName;

	int i = 0; int j = 0;
	char ccomet = '\0';
	char cgroup = '\0';

	unsigned int cometNum = 1;
	unsigned int groupNum = 1;

	while(true) {
		ccomet = cometName[i];
		if(ccomet != '\0') {
			cometNum *= (int(ccomet) - 64);
			cometNum %= 47;
			i++;
		} else {
			break;
		}
	}

	while(true) {
		cgroup = groupName[j];
		if(cgroup != '\0') {
			groupNum *= (int(cgroup) - 64);
			groupNum %= 47;
			j++;
		} else {
			break;
		}
	}

	if(groupNum == cometNum) {
		fout << "GO" << endl;
	} else {
		fout << "STAY" << endl;
	}

	return 0;
}