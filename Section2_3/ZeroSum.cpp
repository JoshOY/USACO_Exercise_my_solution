/*
ID: joshoy71
PROG: zerosum
LANG: C++11
*/

#include <fstream>
#include <string>

using namespace std;

static ifstream fin("zerosum.in");
static ofstream fout("zerosum.out");
static int N;

void dfs(string steps, int lastSum, int save)
{
	if (steps.length() == N - 1) {
		if (lastSum + save == 0){
			for (int i = 1; i <= N; ++i) {
				fout << i;
				if (i == N) {
					fout << endl;
				}
				else {
					fout << steps[i - 1];
				}
			}
		}
		return;
	}
	if (save > 0) {
		dfs(steps + ' ', lastSum, (save * 10) + steps.length() + 2);
	}
	else {
		dfs(steps + ' ', lastSum, (save * 10) - steps.length() - 2);
	}
	dfs(steps + '+', lastSum + save, steps.length() + 2);
	dfs(steps + '-', lastSum + save, -(steps.length() + 2));
}

int main(int argc, char* argv[])
{
	fin >> N;
	if (N == 1)
		return 0;

	dfs("", 0, 1);

	return 0;
}