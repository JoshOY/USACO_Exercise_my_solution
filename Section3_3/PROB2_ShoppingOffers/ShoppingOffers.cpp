/*
ID: joshoy71
PROG: shopping
LANG: C++11
*/

/*
TEST RESULT:
Executing...
   Test 1: TEST OK [0.003 secs, 3536 KB]
   Test 2: TEST OK [0.003 secs, 3536 KB]
   Test 3: TEST OK [0.003 secs, 3536 KB]
   Test 4: TEST OK [0.003 secs, 3536 KB]
   Test 5: TEST OK [0.003 secs, 3536 KB]
   Test 6: TEST OK [0.003 secs, 3536 KB]
   Test 7: TEST OK [0.003 secs, 3536 KB]
   Test 8: TEST OK [0.003 secs, 3536 KB]
   Test 9: TEST OK [0.003 secs, 3536 KB]
   Test 10: TEST OK [0.003 secs, 3536 KB]
   Test 11: TEST OK [0.003 secs, 3536 KB]
   Test 12: TEST OK [0.003 secs, 3536 KB]

All tests OK.
Your program ('shopping') produced all correct answers!  This is your
submission #2 for this problem.  Congratulations!
*/

#include <fstream>
#include <set>
#include <vector>

using namespace std;

#define min(_A_, _B_) ( ((_A_) < (_B_)) ? (_A_) : (_B_) )

typedef struct _Offer
{
	_Offer()
	{
		for (int i = 0; i < 5; ++i) {
			numsNeed[i] = 0;
		}
		costReduce = 0;
	}
	int numsNeed[5];
	int costReduce;
} Offer;

static ifstream fin("shopping.in");
static ofstream fout("shopping.out");
static int productKind = 0;
static int productCodeIndex[5];
static int codeProductIndex[1000];
static vector<Offer> offerList;
static int price[5] = { 0 };
static int itemsNeed[5] = { 0 };
static int leastCost[6][6][6][6][6] = { { { { { 0 } } } } };
static int result;

void input()
{
	for (int i = 0; i <= 999; ++i) {
		codeProductIndex[i] = -1;
	}

	int s;
	fin >> s;
	int n, c, k;
	for (int i = 0; i < s; ++i) {
		Offer newoffer;
		fin >> n;
		for (int j = 0; j < n; ++j) {
			fin >> c >> k;
			if (codeProductIndex[c] == -1) {
				productCodeIndex[productKind] = c;
				codeProductIndex[c] = productKind;
				productKind++;
			}
			newoffer.numsNeed[codeProductIndex[c]] = k;
		}
		fin >> newoffer.costReduce;
		offerList.push_back(newoffer);
	}

	int b;
	fin >> b;
	for (int i = 0; i < b; ++i) {
		fin >> c;
		
		/*Forgot this at submission#1 =.= */
		if (codeProductIndex[c] == -1) {
			productCodeIndex[productKind] = c;
			codeProductIndex[c] = productKind;
			productKind++;
		}

		fin >> itemsNeed[codeProductIndex[c]] >> price[codeProductIndex[c]];
	}
	return;
}

void solve()
{
	for (int a = 0; a <= 5; ++a) {
		for (int b = 0; b <= 5; ++b) {
			for (int c = 0; c <= 5; ++c) {
				for (int d = 0; d <= 5; ++d) {
					for (int e = 0; e <= 5; ++e) {
						leastCost[a][b][c][d][e] = price[0] * a + price[1] * b + price[2] * c + price[3] * d + price[4] * e;
					}
				}
			}
		}
	}

	leastCost[0][0][0][0][0] = 0;
	int purchaseNum0, purchaseNum1, purchaseNum2, purchaseNum3, purchaseNum4, offerCost;
	for (int offerIndex = 0; offerIndex < offerList.size(); ++offerIndex) {
		purchaseNum0 = offerList[offerIndex].numsNeed[0];
		purchaseNum1 = offerList[offerIndex].numsNeed[1];
		purchaseNum2 = offerList[offerIndex].numsNeed[2];
		purchaseNum3 = offerList[offerIndex].numsNeed[3];
		purchaseNum4 = offerList[offerIndex].numsNeed[4];
		offerCost = offerList[offerIndex].costReduce;
		for (int a = purchaseNum0; a <= 5; ++a) {
			for (int b = purchaseNum1; b <= 5; ++b) {
				for (int c = purchaseNum2; c <= 5; ++c) {
					for (int d = purchaseNum3; d <= 5; ++d) {
						for (int e = purchaseNum4; e <= 5; ++e) {
							leastCost[a][b][c][d][e] = min(leastCost[a][b][c][d][e], leastCost[a- purchaseNum0][b - purchaseNum1][c - purchaseNum2][d - purchaseNum3][e - purchaseNum4] + offerCost);
						}
					}
				}
			}
		}
	}
	result = leastCost[itemsNeed[0]][itemsNeed[1]][itemsNeed[2]][itemsNeed[3]][itemsNeed[4]];
}

int main(int argc, char* argv[])
{
	input();
	solve();
	fout << result << endl;
	return 0;
}