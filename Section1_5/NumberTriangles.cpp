/*
ID: joshoy71
PROG: numtri
LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

//define
#define max(_A_, _B_) ((_A_ > _B_) ? _A_ : _B_)

// static or const vars
static int R = 0;
static int numtri[1001][1001] = { { 0 } };
static int f[1001][1001] = { { 0 } };

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);
	ifstream fin("numtri.in");
	ofstream fout("numtri.out");

	int tmp;

	fin >> R;
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j <= i; ++j) {
			fin >> numtri[i][j];
		}
	}

	for (int i = R - 1; i >= 0; --i)
		for (int j = 0; j < R; ++j)
			f[i][j] = numtri[i][j] + max(f[i + 1][j], f[i + 1][j + 1]);

	int result = f[0][0];
	fout << result << endl;

	return 0;
}