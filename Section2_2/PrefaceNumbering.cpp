/*
ID: joshoy71
PROG: preface
LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

static int N;
static int mill, hund, tens, sing;
static map<char, int> result;
static ifstream fin("preface.in");
static ofstream fout("preface.out");

void init()
{
	mill = N / 1000;
	hund = (N / 100) - (mill * 10);
	tens = (N % 100) / 10;
	sing = N % 10;

	result['I'] = 0;	// 1
	result['V'] = 0;	// 5
	result['X'] = 0;	// 10
	result['L'] = 0;	// 50
	result['C'] = 0;	// 100
	result['D'] = 0;	// 500
	result['M'] = 0;	// 1000
	return;
}

void add_digit(int num, int digit, char A, char B, char C)
{
	if (num <= 0) {
		return;
	}
	switch (num) {
	case 1:
		result[A] += 1 * digit;
		break;
	case 2:
		result[A] += 3 * digit;
		break;
	case 3:
		result[A] += 6 * digit;
		break;
	case 4:
		result[A] += 7 * digit;
		result[B] += 1 * digit;
		break;
	case 5:
		result[A] += 7 * digit;
		result[B] += 2 * digit;
		break;
	case 6:
		result[A] += 8 * digit;
		result[B] += 3 * digit;
		break;
	case 7:
		result[A] += 10 * digit;
		result[B] += 4 * digit;
		break;
	case 8:
		result[A] += 13 * digit;
		result[B] += 5 * digit;
		break;
	case 9:
		result[A] += 14 * digit;
		result[B] += 5 * digit;
		result[C] += 1 * digit;
		break;
	}
	return;
}

void add_single(int num, int digit, char A, char B, char C)
{
	switch (num) {
	case 1:
		result[A] += 1 * digit;
		break;
	case 2:
		result[A] += 2 * digit;
		break;
	case 3:
		result[A] += 3 * digit;
		break;
	case 4:
		result[A] += 1 * digit;
		result[B] += 1 * digit;
		break;
	case 5:
		result[B] += 1 * digit;
		break;
	case 6:
		result[A] += 1 * digit;
		result[B] += 1 * digit;
		break;
	case 7:
		result[A] += 2 * digit;
		result[B] += 1 * digit;
		break;
	case 8:
		result[A] += 3 * digit;
		result[B] += 1 * digit;
		break;
	case 9:
		result[A] += 1 * digit;
		result[C] += 1 * digit;
		break;
	}
	return;
}

void convertSingleDigit()
{
	for (int i = 0; i <= sing; ++i) {

		switch (mill) {
		case 0:
			break;
		case 1:
			result['M'] += 1; break;
		case 2:
			result['M'] += 2; break;
		case 3:
			result['M'] += 3; break;
		}

		switch (hund) {
		case 0:
			break;
		case 1:
			result['C'] += 1; break;
		case 2:
			result['C'] += 2; break;
		case 3:
			result['C'] += 3; break;
		case 4:
			result['C'] += 1; result['D'] += 1; break;
		case 5:
			result['D'] += 1; break;
		case 6:
			result['C'] += 1; result['D'] += 1; break;
		case 7:
			result['C'] += 2; result['D'] += 1; break;
		case 8:
			result['C'] += 3; result['D'] += 1; break;
		case 9:
			result['C'] += 1; result['M'] += 1; break;
		}

		switch (tens) {
		case 0:
			break;
		case 1:
			result['X'] += 1; break;
		case 2:
			result['X'] += 2; break;
		case 3:
			result['X'] += 3; break;
		case 4:
			result['X'] += 1; result['L'] += 1; break;
		case 5:
			result['L'] += 1; break;
		case 6:
			result['X'] += 1; result['L'] += 1; break;
		case 7:
			result['X'] += 2; result['L'] += 1; break;
		case 8:
			result['X'] += 3; result['L'] += 1; break;
		case 9:
			result['X'] += 1; result['C'] += 1; break;
		}

	}
	add_digit(sing, 1, 'I', 'V', 'X');
}

void calculate(int num, int digit, char A, char B, char C)
{
	result[A] += (14 * num * digit);
	result[B] += (5 * num * digit);
	result[C] += (1 * num * digit);

	return;
}

void print()
{
	fout << "I " << result['I'] << endl;
	if (result['V'] != 0)
		fout << "V " << result['V'] << endl;
	if (result['X'] != 0)
		fout << "X " << result['X'] << endl;
	if (result['L'] != 0)
		fout << "L " << result['L'] << endl;
	if (result['C'] != 0)
		fout << "C " << result['C'] << endl;
	if (result['D'] != 0)
		fout << "D " << result['D'] << endl;
	if (result['M'] != 0)
		fout << "M " << result['M'] << endl;
	fout.close();
	return;
}

int main(int argc, char* argv[])
{
	fin >> N;
	fin.close();
	init();

	if (N < 10) {
		add_digit(N, 1, 'I', 'V', 'X');
		print();
		return 0;
	}

	if (N < 100) {
		calculate(tens, 1, 'I', 'V', 'X');

		add_digit(tens - 1, 10, 'X', 'L', 'C'); 
		convertSingleDigit();
		print();
		return 0;
	}

	if (N < 1000) {
		calculate(hund * 10 + tens, 1, 'I', 'V', 'X');
		calculate(hund, 10, 'X', 'L', 'C');

		add_digit(tens - 1, 10, 'X', 'L', 'C');

		add_digit(hund - 1, 100, 'C', 'D', 'M');
		add_single(hund, tens * 10, 'C', 'D', 'M');

		convertSingleDigit();
		print();
		return 0;
	}

	//else
	calculate(mill * 100 + hund * 10 + tens, 1, 'I', 'V', 'X');
	calculate(mill * 10 + hund, 10, 'X', 'L', 'C');
	calculate(mill, 100, 'C', 'D', 'M');

	add_digit(tens - 1, 10, 'X', 'L', 'C');

	add_digit(hund - 1, 100, 'C', 'D', 'M');
	add_single(hund, tens * 10, 'C', 'D', 'M');

	add_digit(mill - 1, 1000, 'M', '\0', '\0');
	add_single(mill, hund * 100 + tens * 10, 'M', '\0', '\0');
	convertSingleDigit();
	print();

	return 0;
}