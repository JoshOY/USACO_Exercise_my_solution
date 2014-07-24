/*
ID: joshoy71
PROG: crypt1
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main(int argc, char* argv[])
{
	ifstream fin("crypt1.in");
	ofstream fout("crypt1.out");
	int n;

	int numberAvailable[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	vector<int> legitimateThreeDigits;
	vector<int> firstLineList;

	
	fin >> n;
	if (n == 0) {
		fout << 0 << endl;
		return 0;
	}
	

	for (int i = 0; i < n; i++) {
		int p;
		fin >> p;
		numberAvailable[p] = 1;
	}
	

	int CRYPTARITHM = 0;

	for (int i = 1; i <= 9; i++) {
		if (numberAvailable[i] == 1){

			for (int j = 1; j <= 9; j++) {
				if (numberAvailable[j] == 1){

					for (int k = 1; k <= 9; k++) {
						if (numberAvailable[k] == 1){
							//Now that i, j, k are available...
							for (int l = 1; l <= 9; l++) {
								if (numberAvailable[l] == 1) {
									int lineOne = i * 100 + j * 10 + k;
									int lineTwo = l;
									if ((lineOne * lineTwo) < 1000) {
										int lineThreeAndFour = (lineOne * lineTwo);
										int cen = lineThreeAndFour - (lineThreeAndFour % 100);
										int dec = (lineThreeAndFour - cen) - ((lineThreeAndFour - cen) % 10);
										int per = lineThreeAndFour - cen - dec;
										if ((numberAvailable[cen / 100]) && (numberAvailable[dec / 10]) && (numberAvailable[per])) {
											legitimateThreeDigits.push_back(lineThreeAndFour);
											firstLineList.push_back(i * 100 + j * 10 + k);
										}
									}

								}  //l
							}

						}  //k
					}


				} //j
			}


		} //i
	}

	for (int i = 0; i < legitimateThreeDigits.size(); i++) {
		for (int j = 0; j < legitimateThreeDigits.size(); j++) {
			int resultLine = ((legitimateThreeDigits[i] * 10) + legitimateThreeDigits[j]);
			if ((resultLine < 10000) && (firstLineList[i] == firstLineList[j])) {
				int kil = resultLine - (resultLine % 1000);
				int cen = (resultLine - kil) - ((resultLine - kil) % 100);
				int dec = (resultLine - kil - cen) - ((resultLine - kil - cen) % 10);
				int per = resultLine - kil - cen - dec;
				if ((numberAvailable[kil / 1000]) && (numberAvailable[cen / 100]) && (numberAvailable[dec / 10]) && (numberAvailable[per])) {
					CRYPTARITHM++;
				}
			}
		}
	}

	fout << CRYPTARITHM << endl;
	return 0;
}