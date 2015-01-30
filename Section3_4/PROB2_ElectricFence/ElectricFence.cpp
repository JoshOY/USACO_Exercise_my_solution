/*
ID: joshoy71
PROG: fence9
LANG: C++11
*/

/*
解法：三角形内一行一行扫过去即可。
Executing...
   Test 1: TEST OK [0.008 secs, 3492 KB]
   Test 2: TEST OK [0.005 secs, 3492 KB]
   Test 3: TEST OK [0.003 secs, 3492 KB]
   Test 4: TEST OK [0.003 secs, 3492 KB]
   Test 5: TEST OK [0.005 secs, 3492 KB]
   Test 6: TEST OK [0.005 secs, 3492 KB]
   Test 7: TEST OK [0.000 secs, 3492 KB]
   Test 8: TEST OK [0.008 secs, 3492 KB]
   Test 9: TEST OK [0.005 secs, 3492 KB]
   Test 10: TEST OK [0.005 secs, 3492 KB]
   Test 11: TEST OK [0.003 secs, 3492 KB]
   Test 12: TEST OK [0.005 secs, 3492 KB]

All tests OK.
*/
#include <fstream>


using namespace std;

static ifstream fin("fence9.in", ios::in);
static ofstream fout("fence9.out", ios::out);

static int n, m, p;

int main(int argc, char* argv[])
{
	fin >> n >> m >> p;
	int x1, x2, result;

	result = 0;

	for (int i = 1; i < m; i++) {
        x1 = n * i * (1.0 / double(m)) + 1;
        x2 = p - i * (p - n) * (1.0 / double(m));
        if ((p - n) * i % m == 0)
        	x2--;
        result += (x2 - x1 + 1);
    }
    fout << result << endl;

	return 0;
}