/*/*
ID: joshoy71
PROG: milk
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Seller
{
public:
	int price;
	int amount;

	Seller(int _price, int _amount): price(_price), amount(_amount)
	{

	}

	static int comparePrice(const Seller& A, const Seller& B)
	{
		if(A.price < B.price) {
			return 1;
		}
		else {
			if((A.price == B.price) && (A.amount > B.amount))
				return 1;
			else
				return 0; 
		}
	}
};


int main(int argc, char* argv[])
{
	ifstream fin("milk.in");
	ofstream fout("milk.out");

	int N, M;	// N: Amount needing, M: Seller amount
	fin >> N >> M;

	if(N == 0) {
		fout << 0 << endl;
		return 0;
	}

	vector<Seller> peasantList;
	
	/* Input data */
	int price, amount;
	for(int i = 0; i < M; i++) {	
		fin >> price >> amount;
		peasantList.push_back(Seller(price, amount));
	}

	/* sort the list */
	sort(peasantList.begin(), peasantList.end(), Seller::comparePrice);

	int totalCost = 0;
	int currentAmount = 0;
	auto iter = peasantList.begin();

	while(true) {
		if(N > (currentAmount + iter->amount)) {
			currentAmount += iter->amount;
			totalCost += ( (iter->price) * (iter->amount) );
			++iter;
		} else {
			int remainNeeding = (N - currentAmount);
			totalCost += remainNeeding * (iter->price);
			break;
		}
	}

	fout << totalCost << endl;

	return 0;
}