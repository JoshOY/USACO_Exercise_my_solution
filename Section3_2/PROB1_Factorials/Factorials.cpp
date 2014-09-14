/*
ID: joshoy71
PROG: fact4
LANG: C++11
*/

/*
TEST RESULT:
   Test 1: TEST OK [0.005 secs, 3496 KB]
   Test 2: TEST OK [0.008 secs, 3496 KB]
   Test 3: TEST OK [0.008 secs, 3496 KB]
   Test 4: TEST OK [0.008 secs, 3496 KB]
   Test 5: TEST OK [0.005 secs, 3496 KB]
   Test 6: TEST OK [0.003 secs, 3496 KB]
   Test 7: TEST OK [0.003 secs, 3496 KB]
   Test 8: TEST OK [0.003 secs, 3496 KB]
   Test 9: TEST OK [0.005 secs, 3496 KB]
   Test 10: TEST OK [0.008 secs, 3496 KB]

   Really simple and stupid...
*/
   
#include <fstream>

using namespace std;

static ifstream fin("fact4.in");
static ofstream fout("fact4.out");

static int N;

int main(int argc, char* argv[])
{
	fin >> N;
	int result = 1;
	for (int i = 2; i <= N; ++i) {
		result = (result * i) % 100000;
		while (result % 10 == 0) {
			result /= 10;
		}
	}

	fout << result % 10 << endl;

	return 0;
}