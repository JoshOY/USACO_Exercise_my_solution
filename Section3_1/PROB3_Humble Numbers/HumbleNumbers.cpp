/*
ID: joshoy71
PROG: humble
LANG: C++11
*/

/*
TEST RESULT:
Executing...
   Test 1: TEST OK [0.005 secs, 4276 KB]
   Test 2: TEST OK [0.005 secs, 4276 KB]
   Test 3: TEST OK [0.003 secs, 4276 KB]
   Test 4: TEST OK [0.005 secs, 4276 KB]
   Test 5: TEST OK [0.008 secs, 4276 KB]
   Test 6: TEST OK [0.038 secs, 4276 KB]
   Test 7: TEST OK [0.014 secs, 4276 KB]
   Test 8: TEST OK [0.011 secs, 4276 KB]
   Test 9: TEST OK [0.003 secs, 4276 KB]
   Test 10: TEST OK [0.003 secs, 4276 KB]
   Test 11: TEST OK [0.005 secs, 4276 KB]
   Test 12: TEST OK [0.140 secs, 4276 KB]

All tests OK.
*/

#include <fstream>

using namespace std;

#define min(A, B) ( ((A) < (B)) ? (A) : (B) )

const int K_MAX = 100;
const int N_MAX = 100000;

static ifstream fin("humble.in");
static ofstream fout("humble.out");

static int N, K;
static long long S[K_MAX + 1] = { 1 };
static int indexMultied[K_MAX + 1] = { 0 };
static int humsize = 0;
static long long hum[N_MAX + 1] = { 1 };

void input()
{
	fin >> K >> N;
	for(int i = 1; i <= K; ++i) {
		fin >> S[i];
	}
	return;
}

void solve()
{	
	long long nextHum = 0xffffffff;
	while(humsize != N) {
		nextHum = 0xffffffff; 
		for(int i = 1; i <= K; ++i) {
			for(int j = indexMultied[i]; j <= humsize; ++j) {
				if(S[i] * hum[j] > hum[humsize]) {
					nextHum = min(nextHum, S[i] * hum[j]);
					indexMultied[i] = j;
					break;
				}
			}
		}
		++humsize;
		hum[humsize] = nextHum;
	}

	return;
}

int main(int argc, char* argv[])
{
	input();
	solve();
	fout << hum[N] << endl;

	return 0;
}