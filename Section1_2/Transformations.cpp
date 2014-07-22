/*
ID: joshoy71
PROG: transform
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

static int squareLength;

vector<vector<char> > case_one(const vector<vector<char> >& square)
{
	vector<vector<char> > finalSquare(square);
	for (int i = 0; i < squareLength; i++) {
		for (int j = 0; j < squareLength; j++) {
			finalSquare[j][squareLength - 1 - i] = square[i][j];
		}
	}
	return finalSquare;
}

vector<vector<char> > case_two(const vector<vector<char> >& square) {
	vector<vector<char> > finalSquare(square);
	for (int i = 0; i < squareLength; i++) {
		for (int j = 0; j < squareLength; j++) {
			finalSquare[squareLength - 1 - i][squareLength - 1 - j] = square[i][j];
		}
	}
	return finalSquare;
}

vector<vector<char> > case_three(const vector<vector<char> >& square)
{
	return (case_one(case_two(square)));
}

vector<vector<char> > case_four(const vector<vector<char> >& square)
{
	vector<vector<char> > finalSquare(square);
	for (int i = 0; i < squareLength; i++) {
		for (int j = 0; j < squareLength; j++) {
			finalSquare[i][squareLength - 1 - j] = square[i][j];
		}
	}
	return finalSquare;
}

int main(int argc, char* argv[])
{
	ifstream fin("transform.in");
	ofstream fout("transform.out");
	
	fin >> squareLength;

	vector<vector<char> > square;
	vector<vector<char> > targetSquare;

	for (int i = 0; i < squareLength; i++) {
		string line;
		fin >> line;
		vector<char> tmpvec;
		for (int j = 0; j < squareLength; j++) {
			tmpvec.push_back(line[j]);
		}
		square.push_back(tmpvec);
	}

	for (int i = 0; i < squareLength; i++) {
		string line;
		fin >> line;
		vector<char> tmpvec;
		for (int j = 0; j < squareLength; j++) {
			tmpvec.push_back(line[j]);
		}
		targetSquare.push_back(tmpvec);
	}

	if (case_one(square) == targetSquare) {
		fout << "1" << endl;
	}
	else if (case_two(square) == targetSquare) {
		fout << "2" << endl;
	}
	else if (case_three(square) == targetSquare) {
		fout << "3" << endl;
	}
	else if (case_four(square) == targetSquare) {
		fout << "4" << endl;
	}
	else if ( (case_one(case_four(square)) == targetSquare) 
		|| (case_two(case_four(square)) == targetSquare) 
		|| (case_three(case_four(square)) == targetSquare) ) {
		fout << "5" << endl;
	}
	else if (square == targetSquare) {
		fout << "6" << endl;
	}
	else { 
		fout << "7" << endl;
	}

	return 0;
}


