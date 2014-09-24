/*
ID: joshoy71
PROG: msquare
LANG: C++11
*/

/*
TEST RESULT:
   Test 1: TEST OK [0.011 secs, 3508 KB]
   Test 2: TEST OK [0.008 secs, 3508 KB]
   Test 3: TEST OK [0.005 secs, 3508 KB]
   Test 4: TEST OK [0.008 secs, 3508 KB]
   Test 5: TEST OK [0.070 secs, 4432 KB]
   Test 6: TEST OK [0.111 secs, 5224 KB]
   Test 7: TEST OK [0.176 secs, 3524 KB]
   Test 8: TEST OK [0.232 secs, 6148 KB]
*/

#include <fstream>
#include <string>
#include <set>
#include <queue>

using namespace std;

typedef struct _step {
	string steps;
	string order;
	int stepNum;
} Step;

static ifstream fin("msquare.in");
static ofstream fout("msquare.out");

const int SQUARE_SIZE = 8;

static string targetOrder;
static queue<Step> q;
static set<string> orderRecord;
static int resultStepNum;
static string resultStepsOrder;

void swapChar(char& A, char& B) 
{
	A = A ^ B;
	B = A ^ B;
	A = A ^ B;
	return;
}

void inputAndInit()
{
	//input
	char ch;
	for (int i = 1; i <= SQUARE_SIZE; ++i) {
		fin >> ch;
		targetOrder.push_back(ch);
	}

	//init
	q.push({"", "12345678", 0});
	orderRecord.insert("12345678");
	return;
}

void bfs()
{
	Step currentStep;
	string shiftedOrder;
	char tmpCh;
	while (q.size() != 0) {
		currentStep = q.front();
		q.pop();
		
		//check
		if (currentStep.order == targetOrder) {
			resultStepNum = currentStep.stepNum;
			resultStepsOrder = currentStep.steps;
			break;
		}

		
		//selection A:
		shiftedOrder = currentStep.order;
		swapChar(shiftedOrder[0], shiftedOrder[7]);
		swapChar(shiftedOrder[1], shiftedOrder[6]);
		swapChar(shiftedOrder[2], shiftedOrder[5]);
		swapChar(shiftedOrder[3], shiftedOrder[4]);
		if (!orderRecord.count(shiftedOrder)) {
			orderRecord.insert(shiftedOrder);
			q.push({currentStep.steps + 'A', shiftedOrder, currentStep.stepNum + 1});
		}

		//Selection B:
		shiftedOrder[0] = currentStep.order[3];
		shiftedOrder[1] = currentStep.order[0];
		shiftedOrder[2] = currentStep.order[1];
		shiftedOrder[3] = currentStep.order[2];
		shiftedOrder[4] = currentStep.order[5];
		shiftedOrder[5] = currentStep.order[6];
		shiftedOrder[6] = currentStep.order[7];
		shiftedOrder[7] = currentStep.order[4];
		if (!orderRecord.count(shiftedOrder)) {
			orderRecord.insert(shiftedOrder);
			q.push({ currentStep.steps + 'B', shiftedOrder, currentStep.stepNum + 1 });
		}

		//Selection C:
		shiftedOrder[0] = currentStep.order[0];
		shiftedOrder[1] = currentStep.order[6];
		shiftedOrder[2] = currentStep.order[1];
		shiftedOrder[3] = currentStep.order[3];
		shiftedOrder[4] = currentStep.order[4];
		shiftedOrder[5] = currentStep.order[2];
		shiftedOrder[6] = currentStep.order[5];
		shiftedOrder[7] = currentStep.order[7];
		if (!orderRecord.count(shiftedOrder)) {
			orderRecord.insert(shiftedOrder);
			q.push({ currentStep.steps + 'C', shiftedOrder, currentStep.stepNum + 1 });
		}

	}
	return;
}

int main(int argc, char* argv[])
{
	inputAndInit();
	bfs();
	
	fout << resultStepNum << endl;
	for (int i = 0; i < resultStepsOrder.size(); ++i) {
		fout << resultStepsOrder[i];
		if ((i != 0) && (i % 60 == 0))
			fout << endl;
	}
	fout << endl;

	return 0;
}