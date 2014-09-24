/*
ID: joshoy71
PROG: ratios
LANG: C++11
*/

/*
TEST RESULT:
   Test 1: TEST OK [0.005 secs, 3500 KB]
   Test 2: TEST OK [0.008 secs, 3500 KB]
   Test 3: TEST OK [0.008 secs, 3500 KB]
   Test 4: TEST OK [0.005 secs, 3500 KB]
   Test 5: TEST OK [0.005 secs, 3500 KB]
   Test 6: TEST OK [0.005 secs, 3500 KB]
*/

#include <fstream>

static std::ifstream fin("ratios.in");
static std::ofstream fout("ratios.out");

static int a1, a2, a3, b1, b2, b3, c1, c2, c3, x1, x2, x3;
static int Y1, Y2, Y3, n;
static int D, D1, D2, D3;

int gcd(int a, int b)
{
	if (a < b) {
		int tmp = a;
		a = b;
		b = tmp;
	}

	if (b == 0)
		return a;
	else
		return gcd(b, a%b);
}

void input()
{
	fin >> Y1 >> Y2 >> Y3
		>> a1 >> b1 >> c1
		>> a2 >> b2 >> c2
		>> a3 >> b3 >> c3;
	return;
}

bool solve()
{
	// use Cramer's rule to solve
	D = (a1 * b2 * c3 + b1 * c2 * a3 + c1 * a2 * b3 - a1 * b3 * c2 - a2 * b1 * c3 - a3 * b2 * c1);
	if (D == 0) {
		return false;
	}

	D1 = ((Y1 * b2 * c3) + (Y2 * c2 * a3) + (Y3 * a2 * b3) - (Y1 * b3 * c2) - (a2 * Y2 * c3) - (a3 * b2 *  Y3));
	D2 = ((a1 * Y2 * c3) + (b1 * Y3 * a3) + (c1 * Y1 * b3) - (a1 * b3 * Y3) - (Y1 * b1 * c3) - (a3 * Y2 * c1));
	D3 = ((a1 * b2 * Y3) + (b1 * c2 * Y1) + (c1 * a2 * Y2) - (a1 * Y2 * c2) - (a2 * b1 * Y3) - (Y1 * b2 * c1));

	if (D < 0) {
		D = -D;
		D1 = -D1;
		D2 = -D2;
		D3 = -D3;
		if ((D1 < 0) || (D2 < 0) || (D3 < 0)) {
			return false;
		}
	}
	else if (D > 0) {
		if ((D1 < 0) || (D2 < 0) || (D3 < 0)) {
			return false;
		}
	}

	int g = gcd(D1, gcd(D2, gcd(D3, D)));

	x1 = D1 / g;
	x2 = D2 / g;
	x3 = D3 / g;
	n = D / g;

	return true;
}

int main(int argc, char* argv[])
{
	input();
	if (solve()) {
		fout << x1 << " " << x2  << " " << x3  << " " << n << std::endl;
	}
	else {
		fout << "NONE" << std::endl;
	}

	return 0;
}