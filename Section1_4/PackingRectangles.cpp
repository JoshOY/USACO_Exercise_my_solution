/*
ID: joshoy71
PROG: packrec
LANG: C++11
*/


#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;




int max(int a, int b)
{
	return std::max(a, b);
}

int max(int a, int b, int c)
{
	return max(max(a, b), c);
}

int max(int a, int b, int c, int d)
{
	return max(max(a, b, c), d);
}


class Rect
{
public:
	Rect(int _x = 0, int _y = 0)
	{
		if (_y < _x) {
			x = _y;
			y = _x;
		}
		else {
			x = _x;
			y = _y;
		}
		S = _x * _y;
	}

	int x;
	int y;
	int S;

	static int sortbyS(const Rect& A, const Rect& B) {
		if (A.S < B.S) {
			return 1;
		}
		else if (A.S == B.S) {
			return A.x < B.x;
		} 
		return 0;
	}
};


static int minArea = 20000;
static vector<Rect> resultSet;
static map<int, Rect> r;

vector<vector<int> > perm(vector<int> vec)
{
	if (vec.size() == 1) {
		vector<vector<int> > resultVec;
		resultVec.push_back(vec);
		return resultVec;
	}
	else {
		auto vec_next = vec;
		vec_next.erase(vec_next.begin());
		vector<vector<int> > resultVec;
		vector<vector<int> > givingVec = perm(vec_next);

		for (vector<int> each_perm : givingVec) {
			for (int x = 0; x < each_perm.size(); x++) {
				auto tmp = each_perm;
				auto iter = tmp.begin();
				iter += x;
				tmp.insert(iter, vec[0]);
				resultVec.push_back(tmp);
			}
			each_perm.push_back(vec[0]);
			resultVec.push_back(each_perm);
		}
		return resultVec;
	}
}



void test(int w, int h)
{
	if (w * h <= minArea) {
		minArea = w * h;
		resultSet.push_back(Rect(w, h));
	}
}


void tryRect(map<int, Rect> rectMap, vector<int> order, vector<int> rotation) {
	for (int i = 0; i < 4; ++i) {
		if (rotation[i] == 1) {
			auto tmp = rectMap[order[i]].y;
			rectMap[order[i]].y = rectMap[order[i]].x;
			rectMap[order[i]].x = tmp;
		}
	}
	Rect a = rectMap[order[0]];
	Rect b = rectMap[order[1]];
	Rect c = rectMap[order[2]];
	Rect d = rectMap[order[3]];

	//Situation 1
	test(a.x + b.x + c.x + d.x
		, max(a.y, b.y, c.y, d.y));

	//Situation 2
	test(max(a.x, b.x + c.x + d.x)
		, max(b.y, c.y, d.y) + a.y);

	//Situation 3
	test(max(a.x + b.x, c.x) + d.x
		, max(d.y, c.y + max(a.y, b.y)));

	//Situation 4
	test(a.x + max(b.x, c.x) + d.x
		, max(a.y, b.y + c.y, d.y));

	//Situation 5
	test(max(a.x, b.x) + c.x + d.x
		, max((a.y + b.y), c.y, d.y));

	//Situation 6
	if ((a.x <= b.x) && (d.y >= b.y)) {
		test(max(a.x + c.x, b.x + d.x), max(a.y + b.y, c.y + d.y));
	}
}


int main(int argc, char* argv[])
{
	ifstream fin("packrec.in");
	ofstream fout("packrec.out");

	//fstream fin("E:\\usaco.txt", ios::in);
	//fstream fout("E:\\usacoOut.txt", ios::out);

	for (int x = 0; x < 4; x++){
		int a, b;
		fin >> a >> b;
		r[x] = Rect(a, b);
	}

	vector<int> numvec = { 0, 1, 2, 3 };
	vector<vector<int> > permedVec = perm(numvec);

	vector<vector<int> > rotation;
	rotation.push_back(vector<int>({ 0, 0, 0, 0 }));
	rotation.push_back(vector<int>({ 1, 0, 0, 0 }));
	rotation.push_back(vector<int>({ 0, 1, 0, 0 }));
	rotation.push_back(vector<int>({ 0, 0, 1, 0 }));
	rotation.push_back(vector<int>({ 0, 0, 0, 1 }));
	rotation.push_back(vector<int>({ 1, 1, 0, 0 }));
	rotation.push_back(vector<int>({ 1, 0, 1, 0 }));
	rotation.push_back(vector<int>({ 1, 0, 0, 1 }));
	rotation.push_back(vector<int>({ 0, 1, 1, 0 }));
	rotation.push_back(vector<int>({ 0, 1, 0, 1 }));
	rotation.push_back(vector<int>({ 0, 0, 1, 1 }));
	rotation.push_back(vector<int>({ 1, 1, 1, 0 }));
	rotation.push_back(vector<int>({ 1, 1, 0, 1 }));
	rotation.push_back(vector<int>({ 1, 0, 1, 1 }));
	rotation.push_back(vector<int>({ 0, 1, 1, 1 }));
	rotation.push_back(vector<int>({ 1, 1, 1, 1 }));

	for (int i = 0; i < permedVec.size(); ++i) {
		for (int j = 0; j < rotation.size(); ++j) {
			tryRect(r, permedVec[i], rotation[j]);
		}
	}


	sort(resultSet.begin(), resultSet.end(), Rect::sortbyS);
	
	fout << minArea << endl;
	bool shouldOutput = true;
	for (int i = 0; i < resultSet.size(); ++i) {
		if (shouldOutput)
			fout << resultSet[i].x << " " << resultSet[i].y << endl;
		auto j = i + 1;
		if ((j < resultSet.size()) && (resultSet[i].S == resultSet[j].S)) {
			shouldOutput = true;
			if (resultSet[i].x == resultSet[j].x)
				shouldOutput = false;
		}
		else {
			break;
		}
	}

	return 0;
}