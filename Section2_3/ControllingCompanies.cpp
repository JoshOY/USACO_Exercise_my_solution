/*
ID: joshoy71
PROG: concom
LANG: C++11
*/

#include <fstream>

using namespace std;

const int COMPANY_MAX_NUM = 100;

static ifstream fin("concom.in");
static ofstream fout("concom.out");

static bool control[COMPANY_MAX_NUM + 1][COMPANY_MAX_NUM + 1] = { { false } };	//record relations
static int m[COMPANY_MAX_NUM + 1][COMPANY_MAX_NUM + 1] = { { 0 } };	//record input data
static int indirectm[COMPANY_MAX_NUM + 1][COMPANY_MAX_NUM + 1] = { { 0 } };	//record indirect control percent
static int N;

void checkIndirectControl(int controller, int actualController)
{
	for (int j = 1; j <= COMPANY_MAX_NUM; ++j) {
		indirectm[actualController][j] += m[controller][j];
		if ((indirectm[actualController][j] > 50) && (control[actualController][j] == false) && (actualController != j)) {
			control[actualController][j] = true;
			checkIndirectControl(j, actualController);
		}
	}
}

void directCheck(int controller)
{
	for (int j = 1; j <= COMPANY_MAX_NUM; ++j) {
		if ((m[controller][j] > 50) && (controller != j)) {
			control[controller][j] = true;
		}
	}
}


int main(int argc, char* argv[])
{
	fin >> N;

	int inputI, inputJ, inputP;
	for (int n = 0; n < N; ++n) {
		fin >> inputI >> inputJ >> inputP;
		m[inputI][inputJ] = inputP;
		indirectm[inputI][inputJ] = inputP;		//A company also controls itself as one of C[k]
	}

	for (int h = 1; h <= COMPANY_MAX_NUM; ++h) {
		directCheck(h);
	}

	for (int h = 1; h <= COMPANY_MAX_NUM; ++h) {
		for (int k = 1; k <= COMPANY_MAX_NUM; ++k) {
			if (control[h][k] == true) {
				checkIndirectControl(k, h);
			}
		}
	}

	for (int h = 1; h <= COMPANY_MAX_NUM; ++h) {
		for (int k = 1; k <= COMPANY_MAX_NUM; ++k) {
			if ((control[h][k] == true) && (h != k)) {
				fout << h << ' ' << k << endl;
			}
		}
	}

	return 0;
}