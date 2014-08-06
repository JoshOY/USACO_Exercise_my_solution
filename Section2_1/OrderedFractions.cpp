/*
ID: joshoy71
PROG: frac1
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct
{
      int a;
      int b;
} Num;

static int N;
static vector<Num> result;

bool check(int a, int b)      // Make sure that b > a
{
      if ( a == 1 )
            return true;
      else if ( a == 0) {
            return false;
      }
      else {
            if (b - a > a)
                  return check(a, b-a);
            else
                  return check(b-a, a);
      }

}

int sortResult(const Num& A, const Num& B)
{
      if ( (A.a * B.b) < (A.b * B.a) )	// (A.a / A.b) < (B.a / B.b), but not turning it to float
            return 1;
      else
            return 0;
}

int main(int argc, char* argv[])
{
    ifstream fin("frac1.in");
    ofstream fout("frac1.out");

      fin >> N;
      result.push_back({0, 1});

      for (int y = 1; y <= N; ++y) {
            for (int x = 1; x < y; ++x) {
                  if (check(x, y)) {
                        result.push_back({x, y});
                  }
            }
      }

      result.push_back({1, 1});
      std::sort(result.begin(), result.end(), sortResult);

      for (int i = 0; i < result.size(); ++i) {
            fout << result[i].a << "/" << result[i].b << endl;
      }

      return 0;
}
