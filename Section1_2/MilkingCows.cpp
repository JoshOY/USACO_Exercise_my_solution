/*
ID: joshoy71
PROG: milk2
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

static int tmpStart;
static int tmpEnd;

class MilkTime
{
public:
	int start_time;
	int end_time;

	MilkTime(int startT, int endT)
	{
		start_time = startT;
		end_time = endT;
	}

	static int compareStartTime(const MilkTime& A, const MilkTime& B)
	{
		if (A.start_time < B.start_time){
			return 1;
		}
		else if (A.start_time == B.start_time){
			if (A.end_time < B.end_time) {
				return 1;
			} else { 
				return 0; 
			}
		}
		else {
			return 0;
		}
	}

};


int handleIter(vector<MilkTime>::iterator& iter
				, vector<MilkTime>::iterator& iterNext
				, const vector<MilkTime>::iterator& endIter)
{
	if(iterNext != endIter){
		if ((iter->end_time >= iterNext->start_time) && (iter->end_time < iterNext->end_time)) {
			tmpEnd = iterNext->end_time;
			iter = iterNext;
			return 1;
		}
		else if ((iter->end_time >= iterNext->start_time) && (iter->end_time >= iterNext->end_time)) {
			++iterNext;
			handleIter(iter, iterNext, endIter);
		}
		else {
			tmpEnd = iter->end_time;
			return 0;
		}
	}
	else {
		return 2;
	}
}

int main(int argc, char* argv[])
{
	ifstream fin("milk2.in");
	ofstream fout("milk2.out");

	int N;
	fin >> N;

	vector<MilkTime> timeChart;

	for (int i = 0; i < N; i++) {
		int time_start, time_end;
		fin >> time_start >> time_end;

		timeChart.push_back( MilkTime(time_start, time_end) );
	}

	sort(timeChart.begin(), timeChart.end(), MilkTime::compareStartTime);

	int longestMilkingTime = 0;
	int longestBreakingTime = 0;

	tmpStart = timeChart.begin()->start_time;
	tmpEnd = timeChart.begin()->end_time;
	auto iter = timeChart.begin();

	while (true) {

		auto iterNext = iter; ++iterNext;
		int result = handleIter(iter, iterNext, timeChart.end());

		if (result == 1) {
			continue;
		}
		else if (result == 0) {
			if (longestMilkingTime < (tmpEnd - tmpStart)) {
				longestMilkingTime = (tmpEnd - tmpStart);
			}
			if (longestBreakingTime < (iterNext->start_time - iter->end_time)) {
				longestBreakingTime = (iterNext->start_time - iter->end_time);
			}
			tmpStart = iterNext->start_time;
			tmpEnd = iterNext->end_time;
			iter = iterNext;
			continue;
		}
		else if (result == 2) {
			tmpEnd = iter->end_time;
			if (longestMilkingTime < (tmpEnd - tmpStart)) {
				longestMilkingTime = (tmpEnd - tmpStart);
			}
			break;
		}
	}

	fout << longestMilkingTime << " " << longestBreakingTime << endl;

	return 0;
}