/*
ID: joshoy71
PROG: prefix
LANG: C++11
*/

#include <fstream>
#include <vector>
#include <string>
using namespace std;

const int P_MAX = 200;
const int S_LENGTH_MAX = 200000;

static vector<string> P;
static int PCounter = 0;
static int SCounter = 0;
static char S[S_LENGTH_MAX + 1] = { '\0' };
static bool dp[S_LENGTH_MAX + 1] = { false };

int main(int argc, char* argv[])
{
	ifstream fin("prefix.in");
	ofstream fout("prefix.out");

	//INPUT PART
	string tmp;
	fin >> tmp;
	while (tmp != ".") {
		++PCounter;
		P.push_back(tmp);
		fin >> tmp;
	}

	int l = 0;
	fin >> tmp;
	while (!fin.eof()) {
		l = tmp.length();
		for (int i = 0; i < l; ++i) {
			S[SCounter + i] = tmp[i];
		}
		SCounter += l;
		fin >> tmp;
	}
	PCounter = P.size();

	//SOLVE PART
	dp[0] = true;
	for (int i = 1; i <= SCounter; ++i) {
		for (int j = 0; j < PCounter; ++j) {
			if (i == P[j].length() && (string(S, i) == P[j])) {
				dp[i] = true;
				break;
			}
			if ((i > P[j].length()) && (dp[i - P[j].length()] == true)) {
				bool strEqual = true;
				for (int k = 0; k < P[j].length(); ++k) {
					if (S[k + i - P[j].length()] != P[j][k]) {
						strEqual = false;
						break;
					}
				}
				if (strEqual) {
					dp[i] = true;
					break;
				}
			}
		}
	}

	for (int i = SCounter; i >= 0; --i) {
		if (dp[i] == true) {
			fout << i << endl;
			return 0;
		}
	}

	return 0;
}