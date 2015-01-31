/*
ID: joshoy71
PROG: rockers
LANG: C++11
*/

/*
解法：因为也不过20首可曲，深搜即可。应该不会爆栈。
Executing...
   Test 1: TEST OK [0.003 secs, 3496 KB]
   Test 2: TEST OK [0.003 secs, 3496 KB]
   Test 3: TEST OK [0.003 secs, 3496 KB]
   Test 4: TEST OK [0.003 secs, 3496 KB]
   Test 5: TEST OK [0.003 secs, 3496 KB]
   Test 6: TEST OK [0.003 secs, 3496 KB]
   Test 7: TEST OK [0.003 secs, 3496 KB]
   Test 8: TEST OK [0.019 secs, 3496 KB]
   Test 9: TEST OK [0.005 secs, 3496 KB]
   Test 10: TEST OK [0.003 secs, 3496 KB]
   Test 11: TEST OK [0.011 secs, 3496 KB]
   Test 12: TEST OK [0.016 secs, 3496 KB]

All tests OK.
YOUR PROGRAM ('rockers') WORKED FIRST TIME!  That's fantastic
-- and a rare thing.  Please accept these special automated
congratulations.
*/

#include <fstream>
#include <vector>

using namespace std;

static ifstream fin("rockers.in", ios::in);
static ofstream fout("rockers.out", ios::out);

/*
N: numbers of songs
T: available time for each disk
M: number of released disks
*/
static int N, T, M;
static vector<int> songLen;
static int result = 0;

void dfs(int song_index, int using_disk, int remain_time, int songs_recorded)
{
	if (using_disk > M) {
		if (songs_recorded - 1 > result) {
			result = songs_recorded - 1;
		}
		return;
	}

	if (song_index == N) {
		if (songs_recorded > result) {
			result = songs_recorded;
		}
		return;
	}

	// If we record this song.
	if (songLen[song_index] <= remain_time) {
		dfs(song_index + 1, using_disk, remain_time - songLen[song_index], songs_recorded + 1);
	}
	else if (songLen[song_index] > T) {
		// This song is too long to record, abandon it.
	}
	else { // If we have no more space in current disk?
		dfs(song_index + 1, using_disk + 1, T - songLen[song_index], songs_recorded + 1);
	}

	// If we ignore this song.
	dfs(song_index + 1, using_disk, remain_time, songs_recorded);
	return;
}

int main(int argc, char* argv[])
{
	// Input
	fin >> N >> T >> M;
	int tmp;
	for (int i = 0; i < N; ++i) {
		fin >> tmp;
		songLen.push_back(tmp);
	}

	// Solve
	dfs(0, 1, T, 0);

	// Output
	fout << result << endl;

	return 0;
}