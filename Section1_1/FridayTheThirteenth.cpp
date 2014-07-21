/*
ID: joshoy71
PROG: friday
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

static vector<unsigned int> outputVec;

unsigned int calculateDays(unsigned int year)
{
	unsigned int dayOfJanFirst;

	if(year == 1900) {
		dayOfJanFirst = 2;
	} else {
		dayOfJanFirst = calculateDays(year - 1);
	}

	//Leap year
	if( (year % 400 == 0) || ((year % 100 != 0) && (year % 4 == 0)) ) {
		unsigned int dayOfCurrentDate = dayOfJanFirst;
		//January
		dayOfCurrentDate = (dayOfCurrentDate + 12) % 7;
		++outputVec[dayOfCurrentDate];
		//Febuary
		dayOfCurrentDate = (dayOfCurrentDate + 31) % 7;
		++outputVec[dayOfCurrentDate];
		//March
		dayOfCurrentDate = (dayOfCurrentDate + 29) % 7;
		++outputVec[dayOfCurrentDate];
		//April
		dayOfCurrentDate = (dayOfCurrentDate + 31) % 7;
		++outputVec[dayOfCurrentDate];
		//May
		dayOfCurrentDate = (dayOfCurrentDate + 30) % 7;
		++outputVec[dayOfCurrentDate];
		//June
		dayOfCurrentDate = (dayOfCurrentDate + 31) % 7;
		++outputVec[dayOfCurrentDate];
		//July
		dayOfCurrentDate = (dayOfCurrentDate + 30) % 7;
		++outputVec[dayOfCurrentDate];
		//August
		dayOfCurrentDate = (dayOfCurrentDate + 31) % 7;
		++outputVec[dayOfCurrentDate];
		//September
		dayOfCurrentDate = (dayOfCurrentDate + 31) % 7;
		++outputVec[dayOfCurrentDate];
		//October
		dayOfCurrentDate = (dayOfCurrentDate + 30) % 7;
		++outputVec[dayOfCurrentDate];
		//November
		dayOfCurrentDate = (dayOfCurrentDate + 31) % 7;
		++outputVec[dayOfCurrentDate];
		//December
		dayOfCurrentDate = (dayOfCurrentDate + 30) % 7;
		++outputVec[dayOfCurrentDate];

		dayOfCurrentDate = (dayOfCurrentDate + 19) % 7;
		return dayOfCurrentDate;
	}
	//Not leap year
	else {
		unsigned int dayOfCurrentDate = dayOfJanFirst;
		//January
		dayOfCurrentDate = (dayOfCurrentDate + 12) % 7;
		++outputVec[dayOfCurrentDate];
		//Febuary
		dayOfCurrentDate = (dayOfCurrentDate + 31) % 7;
		++outputVec[dayOfCurrentDate];
		//March
		dayOfCurrentDate = (dayOfCurrentDate + 28) % 7;
		++outputVec[dayOfCurrentDate];
		//April
		dayOfCurrentDate = (dayOfCurrentDate + 31) % 7;
		++outputVec[dayOfCurrentDate];
		//May
		dayOfCurrentDate = (dayOfCurrentDate + 30) % 7;
		++outputVec[dayOfCurrentDate];
		//June
		dayOfCurrentDate = (dayOfCurrentDate + 31) % 7;
		++outputVec[dayOfCurrentDate];
		//July
		dayOfCurrentDate = (dayOfCurrentDate + 30) % 7;
		++outputVec[dayOfCurrentDate];
		//August
		dayOfCurrentDate = (dayOfCurrentDate + 31) % 7;
		++outputVec[dayOfCurrentDate];
		//September
		dayOfCurrentDate = (dayOfCurrentDate + 31) % 7;
		++outputVec[dayOfCurrentDate];
		//October
		dayOfCurrentDate = (dayOfCurrentDate + 30) % 7;
		++outputVec[dayOfCurrentDate];
		//November
		dayOfCurrentDate = (dayOfCurrentDate + 31) % 7;
		++outputVec[dayOfCurrentDate];
		//December
		dayOfCurrentDate = (dayOfCurrentDate + 30) % 7;
		++outputVec[dayOfCurrentDate];
	
		dayOfCurrentDate = (dayOfCurrentDate + 19) % 7;
		return dayOfCurrentDate;
	}
}

int main(int argc, char* argv[])
{
	ofstream fout("friday.out");
	ifstream fin("friday.in");

	for(int i = 0; i < 7; i++) {
		outputVec.push_back(0);
	}

	unsigned int N;
	fin >> N;

	calculateDays(1900 + N - 1);

	for(int i = 0; i < 7; i++) {
		fout << outputVec[i];
		if(i != 6) {
			fout << " ";
		} else {
			fout << endl;
		}
	}

	return 0;
}