/*
ID: joshoy71
PROG: heritage
LANG: C++11
*/

/*
注：很水的一题。

Executing...
   Test 1: TEST OK [0.008 secs, 3500 KB]
   Test 2: TEST OK [0.008 secs, 3500 KB]
   Test 3: TEST OK [0.005 secs, 3500 KB]
   Test 4: TEST OK [0.005 secs, 3500 KB]
   Test 5: TEST OK [0.011 secs, 3500 KB]
   Test 6: TEST OK [0.008 secs, 3500 KB]
   Test 7: TEST OK [0.008 secs, 3500 KB]
   Test 8: TEST OK [0.005 secs, 3500 KB]
   Test 9: TEST OK [0.008 secs, 3500 KB]

All tests OK.
YOUR PROGRAM ('heritage') WORKED FIRST TIME!  That's fantastic
-- and a rare thing.  Please accept these special automated
congratulations.
*/

#include <fstream>
#include <string>
#include <map>

using namespace std;

static ifstream fin("heritage.in", ios::in);
static ofstream fout("heritage.out", ios::out);
static map<char, int> priority;

struct Node
{
	Node(char v)
	{
		left = nullptr;
		right = nullptr;
		value = v;
	}

	~Node()
	{
		if (left  != nullptr) left ->~Node();
		if (right != nullptr) right->~Node();
	}

	void insert(Node* newnode)
	{
		if (priority[newnode->value] < priority[this->value]) {
			if (this->left == nullptr) {
				this->left = newnode;
			}
			else {
				this->left->insert(newnode);
			}
		}
		else {  // priority[newnode->value] > priority[this->value]
			if (this->right == nullptr) {
				this->right = newnode;
			}
			else {
				this->right->insert(newnode);
			}
		}
		return;
	}

	char value;
	Node *left;
	Node *right;
};

void outputPostOrder(Node *treeroot)
{
	if (treeroot->left  != nullptr) outputPostOrder(treeroot->left);
	if (treeroot->right != nullptr) outputPostOrder(treeroot->right);
	fout << treeroot->value;
	return;
}


int main(int argc, char *argv[])
{
	string line1, line2;
	fin >> line1 >> line2;
	int totalLength = line1.length();

	// Record the priority
	for (int i = 1; i <= totalLength; ++i) {
		priority[line1[i - 1]] = i;
	}

	// Create the tree
	Node* root = new Node(line2[0]);
	for (int i = 1; i < totalLength; ++i) {
		Node *newnode = new Node(line2[i]);
		root->insert(newnode);
	}

	// Output
	outputPostOrder(root);
	fout << endl;

	delete root;
	return 0;
}

