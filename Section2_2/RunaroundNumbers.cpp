/*
ID: joshoy71
PROG: runround
LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#define charNum2int(_CHARNUM_) ((int)_CHARNUM_ - 48)
#define bit(_N_) (1 << _N_)

static int M;
static stringstream ss;
static string mStr;
static bool solved = false;
static int recorder = 0;

bool check()
{
	if (mStr.length() == 1)
		return true;

	for (int i = 0; i < mStr.length(); ++i) {
		if (charNum2int(mStr[i]) == mStr.length())
			return false;

		if (!(bit(charNum2int(mStr[i])) & recorder))
			recorder |= bit(charNum2int(mStr[i]));
		else
			return false;
	}

	recorder = 0;
	int i = 0;
	int counter = 0;
	while (true) {
		if (!(bit(charNum2int( mStr[ ( i + charNum2int(mStr[i]) ) % mStr.length()])) & recorder)) {
			recorder |= bit(charNum2int(mStr[(i + charNum2int(mStr[i])) % mStr.length()]));
			i = (i + charNum2int(mStr[i])) % mStr.length();
			++counter;
		}
		else {
			return false;
		}

		if (i == 0) {
			if (counter != mStr.length())
				return false;
			break;
		}
	}

	return true;
}

int main(int argc, char* argv[])
{
	ifstream fin("runround.in");
	ofstream fout("runround.out");

	fin >> M;
	
	while (!solved) {
		++M;
		ss << M;
		ss >> mStr;
		ss.clear();
		recorder = 0;
		solved = check();
	}

	fout << M << endl;
	return 0;
}