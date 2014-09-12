/*
ID: joshoy71
PROG: contact
LANG: C++11
*/

/*
TEST RESULT:
	Test 1: TEST OK [0.003 secs, 3508 KB]
	Test 2: TEST OK [0.008 secs, 3508 KB]
	Test 3: TEST OK [0.014 secs, 3508 KB]
	Test 4: TEST OK [0.038 secs, 3508 KB]
	Test 5: TEST OK [0.113 secs, 3508 KB]
	Test 6: TEST OK [0.146 secs, 3524 KB]
	Test 7: TEST OK [0.200 secs, 3524 KB]
*/

#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

const int INPUT_MAX = 200000;
const int LINE_OUTPUT_MAX_NUM = 6;

typedef struct _Data
{
	int times;
	string signal;
} Data;

int sortData(const Data& A, const Data& B)
{
	if (A.times > B.times) {
		return 1;
	}
	else if (A.times == B.times) {
		if (A.signal.length() < B.signal.length()) {
			return 1;
		}
		else if (A.signal.length() == B.signal.length()) {
			for (int i = 0; i < A.signal.length(); ++i) {
				if (A.signal[i] < B.signal[i]) {
					return 1;
				}
				else if (A.signal[i] > B.signal[i]) {
					return 0;
				}
			}
			return 0;
		}
		else {
			return 0;
		}
	}
	else {
		return 0;
	}
}

static ifstream fin("contact.in");
static ofstream fout("contact.out");

static int A, B, N;
static string str;
static vector<Data> result;
static map<string, int> signalTimesMap;

void input()
{
	string tmp = "";
	fin >> A >> B >> N;
	while (!fin.eof()) {
		tmp = "";
		fin >> tmp;
		str += tmp;
	}
	return;
}

void solve()
{
	int strLength = str.length();
	for (int signalLength = A; signalLength <= B; ++signalLength) {
		for (int i = 0; i + signalLength - 1 < strLength; ++i) {
			signalTimesMap[str.substr(i, signalLength)] += 1;
		}
	}

	//then trans the map into a vector and sort it
	for (auto iter = signalTimesMap.begin(); iter != signalTimesMap.end(); ++iter) {
		result.push_back({ iter->second, iter->first });
	}

	std::sort(result.begin(), result.end(), sortData);
	return;
}

void output()
{
	int counter = 0;
	int index = 0;
	while (counter != N) {
		++counter;
		if (index >= result.size()) {
			break;
		}
		int t = result[index].times;
		fout << t << endl;
		int lineCounter = 1;
		while (true) {
			fout << result[index].signal;
			if ((index + 1 < result.size()) && (result[index + 1].times == t)) {
				++index;
				if (lineCounter != LINE_OUTPUT_MAX_NUM) {
					fout << " ";
					++lineCounter;
				}
				else {
					fout << endl;
					lineCounter = 1;
				}
				continue;
			} else {
				++index;
				fout << endl;
				break;
			}
		}
	}
}

int main(int argc, char* argv[])
{
	input();
	solve();
	output();

	return 0;
}