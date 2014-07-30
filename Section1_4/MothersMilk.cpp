/*
ID: joshoy71
PROG: milk3
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
using namespace std;

#define max(_A_,_B_) (_A_ > _B_) ? _A_ : _B_

typedef enum
{
	a_to_b = 0,
	a_to_c = 1,
	b_to_a = 3,
	b_to_c = 2,
	c_to_a = 4,
	c_to_b = 5
} Trans;

typedef struct 
{
	int cap;	/* Bucket capacity */
	int v;	/* Current milk volumn */
} Bucket;

typedef struct
{
	int av;
	int bv;
	int cv;
	Trans trans;
	int count;
} step;

const int MAX_CAP = 20;
static bool possibility[MAX_CAP + 1] = { false };
static Bucket A, B, C;
static deque<step> stepsQueue;

bool canPour(const Bucket& from, const Bucket& to)
{
	if (to.v == to.cap || from.v == 0) { return false; }
	return true;
}

bool checkNotRedo(const Trans& goingToDo)
{
	auto tmpA = A;
	auto tmpB = B;
	auto tmpC = C;
	switch (goingToDo)
	{
	case a_to_b:
		if (tmpB.v + tmpA.v <= tmpB.cap) { tmpB.v += tmpA.v; tmpA.v = 0; }
		else { tmpA.v -= (tmpB.cap - tmpB.v); tmpB.v = tmpB.cap; }
		break;
	case a_to_c:
		if (tmpC.v + tmpA.v <= tmpC.cap) { tmpC.v += tmpA.v; tmpA.v = 0; }
		else { tmpA.v -= (tmpC.cap - tmpC.v); tmpC.v = tmpC.cap; }
		break;
	case b_to_a:
		if (tmpA.v + tmpB.v <= tmpA.cap) { tmpA.v += tmpB.v; tmpB.v = 0; }
		else { tmpB.v -= (tmpA.cap - tmpA.v); tmpA.v = tmpA.cap; }
		break;
	case b_to_c:
		if (tmpC.v + tmpB.v <= tmpC.cap) { tmpC.v += tmpB.v; tmpB.v = 0; }
		else { tmpB.v -= (tmpC.cap - tmpC.v); tmpC.v = tmpC.cap; }
		break;
	case c_to_a:
		if (tmpA.v + tmpC.v <= tmpA.cap) { tmpA.v += tmpC.v; tmpC.v = 0; }
		else { tmpC.v -= (tmpA.cap - tmpA.v); tmpA.v = tmpA.cap; }
		break;
	case c_to_b:
		if (tmpB.v + tmpC.v <= tmpB.cap) { tmpB.v += tmpC.v; tmpC.v = 0; }
		else { tmpC.v -= (tmpB.cap - tmpB.v); tmpB.v = tmpB.cap; }
		break;
	}
	
	if (tmpA.v == 0) {
		possibility[tmpC.v] = true;
	}

	switch ((goingToDo + 3) % 6)
	{
	case a_to_b:
		if (tmpB.v + tmpA.v <= tmpB.cap) { tmpB.v += tmpA.v; tmpA.v = 0; }
		else { tmpA.v -= (tmpB.cap - tmpB.v); tmpB.v = tmpB.cap; }
		break;
	case a_to_c:
		if (tmpC.v + tmpA.v <= tmpC.cap) { tmpC.v += tmpA.v; tmpA.v = 0; }
		else { tmpA.v -= (tmpC.cap - tmpC.v); tmpC.v = tmpC.cap; }
		break;
	case b_to_a:
		if (tmpA.v + tmpB.v <= tmpA.cap) { tmpA.v += tmpB.v; tmpB.v = 0; }
		else { tmpB.v -= (tmpA.cap - tmpA.v); tmpA.v = tmpA.cap; }
		break;
	case b_to_c:
		if (tmpC.v + tmpB.v <= tmpC.cap) { tmpC.v += tmpB.v; tmpB.v = 0; }
		else { tmpB.v -= (tmpC.cap - tmpC.v); tmpC.v = tmpC.cap; }
		break;
	case c_to_a:
		if (tmpA.v + tmpC.v <= tmpA.cap) { tmpA.v += tmpC.v; tmpC.v = 0; }
		else { tmpC.v -= (tmpA.cap - tmpA.v); tmpA.v = tmpA.cap; }
		break;
	case c_to_b:
		if (tmpB.v + tmpC.v <= tmpB.cap) { tmpB.v += tmpC.v; tmpC.v = 0; }
		else { tmpC.v -= (tmpB.cap - tmpB.v); tmpB.v = tmpB.cap; }
		break;
	}

	if (tmpA.v == A.v && tmpB.v == B.v && tmpC.v == C.v) {
		return false;
	}

	return true;
}

void pour()
{
	auto st = stepsQueue.front();
	A.v = st.av;
	B.v = st.bv;
	C.v = st.cv;

	switch (st.trans)
	{
	case a_to_b:
		if (B.v + A.v <= B.cap) { B.v += A.v; A.v = 0; }
		else { A.v -= (B.cap - B.v); B.v = B.cap; }
		break;
	case a_to_c:
		if (C.v + A.v <= C.cap) { C.v += A.v; A.v = 0; }
		else { A.v -= (C.cap - C.v); C.v = C.cap; }
		break;
	case b_to_a:
		if (A.v + B.v <= A.cap) { A.v += B.v; B.v = 0; }
		else { B.v -= (A.cap - A.v); A.v = A.cap; }
		break;
	case b_to_c:
		if (C.v + B.v <= C.cap) { C.v += B.v; B.v = 0; }
		else { B.v -= (C.cap - C.v); C.v = C.cap; }
		break;
	case c_to_a:
		if (A.v + C.v <= A.cap) { A.v += C.v; C.v = 0; }
		else { C.v -= (A.cap - A.v); A.v = A.cap; }
		break;
	case c_to_b:
		if (B.v + C.v <= B.cap) { B.v += C.v; C.v = 0; }
		else { C.v -= (B.cap - B.v); B.v = B.cap; }
		break;
	}

	if (A.v == 0)
		possibility[C.v] = true;

	if (C.v != C.cap && st.count < 14) {
		//push next steps
		if (canPour(A, B) && (st.trans != b_to_a || checkNotRedo(a_to_b)))
			stepsQueue.push_back({ A.v, B.v, C.v, a_to_b , st.count+1 });
		if (canPour(A, C) && (st.trans != c_to_a || checkNotRedo(a_to_c)))
			stepsQueue.push_back({ A.v, B.v, C.v, a_to_c, st.count + 1 });
		if (canPour(B, A) && (st.trans != a_to_b || checkNotRedo(b_to_a)))
			stepsQueue.push_back({ A.v, B.v, C.v, b_to_a, st.count + 1 });
		if (canPour(B, C) && (st.trans != c_to_b || checkNotRedo(b_to_c)))
			stepsQueue.push_back({ A.v, B.v, C.v, b_to_c, st.count + 1 });
		if (canPour(C, A) && (st.trans != a_to_c || checkNotRedo(c_to_a)))
			stepsQueue.push_back({ A.v, B.v, C.v, c_to_a, st.count + 1 });
		if (canPour(C, B) && (st.trans != b_to_c || checkNotRedo(c_to_b)))
			stepsQueue.push_back({ A.v, B.v, C.v, c_to_b, st.count + 1 });
	}

	stepsQueue.pop_front();
	return;
}

int main(int argc, char* argv[])
{
	ifstream fin("milk3.in");
	ofstream fout("milk3.out");
	int a_max, b_max, c_max;
	fin >> a_max >> b_max >> c_max;

	A = { a_max, 0 };
	B = { b_max, 0 };
	C = { c_max, c_max };
	possibility[c_max] = true;

	stepsQueue.push_back({ A.v, B.v, C.v, c_to_a , 0});
	stepsQueue.push_back({ A.v, B.v, C.v, c_to_b , 0});
	while (stepsQueue.size() != 0){
		pour();
	}

	vector<int> possibilityVec;
	for (int i = 0; i <= MAX_CAP; ++i) {
		if (possibility[i] == true) {
			possibilityVec.push_back(i);
		}
	}
	for (int i = 0; i < possibilityVec.size(); ++i) {
		fout << possibilityVec[i] ;
		if(i != possibilityVec.size() - 1)
			fout << " ";
		else
			fout << endl;
	}

	return 0;
}