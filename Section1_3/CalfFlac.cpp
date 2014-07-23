/*/*
ID: joshoy71
PROG: calfflac
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

#if 0
#define ITER_FORW(_ITER_, _TEXT_) ++_ITER_; while((!(((*_ITER_) >= 'a') && ((*_ITER_) <= 'z')) || (((*_ITER_) >= 'A') && ((*_ITER_) <= 'Z'))) && (_ITER_ != _TEXT_.end())) {++_ITER_;}
#define ITER_BACK(_ITER_, _TEXT_) --_ITER_; while((!(((*_ITER_) >= 'a') && ((*_ITER_) <= 'z')) || (((*_ITER_) >= 'A') && ((*_ITER_) <= 'Z'))) && (_ITER_ != _TEXT_.begin())) {--_ITER_;}
#endif

#define ITER_FORW(_ITER_, _TEXT_) ++_ITER_; while((!(((_TEXT_[_ITER_] >= 'a') && (_TEXT_[_ITER_] <= 'z')) || ((_TEXT_[_ITER_] >= 'A') && (_TEXT_[_ITER_] <= 'Z')))) && (_ITER_ != _TEXT_.length() )) ++_ITER_
#define ITER_BACK(_ITER_, _TEXT_) --_ITER_; while((!(((_TEXT_[_ITER_] >= 'a') && (_TEXT_[_ITER_] <= 'z')) || ((_TEXT_[_ITER_] >= 'A') && (_TEXT_[_ITER_] <= 'Z')))) && (_ITER_ != 0 )) --_ITER_

using namespace std;

class Flac
{
public:
	Flac(string _content, int _start, int _end)
	{
		reallength = getRealLength(_content);
		start = _start;
		endindex = _end;
	}
	static int getRealLength(string content)
	{
		int counter = 0;
		for (int i = 0; i < content.length(); i++) {
			if (((content[i] >= 'A') && (content[i] <= 'Z')) || ((content[i] >= 'a') && (content[i] <= 'z'))) {
				counter++;
			}
		}
		return counter;
	}

	int start;
	int endindex;
	int reallength;
};

int main(int argc, char* argv[])
{
	ifstream fin("calfflac.in");
	ofstream fout("calfflac.out");

	string text;
	char tmp[81] = "";
	while (fin.getline(tmp, 81)) {
		text.append(tmp);
		text += "\n";
	}

	vector<Flac> flacList;

	int firstLetterIndex = 0;
	int j;
	while ((!(((text[firstLetterIndex] >= 'a') && (text[firstLetterIndex] <= 'z')) || ((text[firstLetterIndex] >= 'A') && (text[firstLetterIndex] <= 'Z')))) && (firstLetterIndex != text.length())) {
		++firstLetterIndex;
	}

	for (int i = firstLetterIndex; i < text.length(); ++i) {
		if (i == text.length()) {
			break;
		}
		int back = i;
		int forward = i;
		ITER_FORW(forward, text);
		if ((forward != text.length()) && (back != 0)) {
			ITER_BACK(back, text);
			bool isFlac = false;
			bool hasIndexZero = false;
			while (true) {
				if (toupper(text[back]) == toupper(text[forward])) {
					isFlac = true;
					if (back == 0) {
						hasIndexZero = true;
						break;
					}
					ITER_BACK(back, text);
					ITER_FORW(forward, text);
				}
				else {
					break;
				}
			}

			if (isFlac && hasIndexZero) {
			}
			else if (isFlac) {
				ITER_BACK(forward, text);
				ITER_FORW(back, text);
			}

			if (isFlac){
				string content = text.substr(back, forward - back + 1);
				if (content.length() != 1) {
					flacList.push_back(Flac(content, back, forward));
				}
			}
		}
		else {
		}
	}

	for (int i = 0; i < text.length(); ++i) {
		while ((!(((text[i] >= 'a') && (text[i] <= 'z')) || ((text[i] >= 'A') && (text[i] <= 'Z')))) && (i != text.length())) {
			++i;
		}
		j = i;
		ITER_FORW(j, text);
		if (j == text.length()) {
			break;
		}
		bool isFlac = false;
		if (toupper(text[i]) == toupper(text[j])) {
			int forward = j;
			int backward = i;
			while (true) {
				if (toupper(text[backward]) == toupper(text[forward])) {
					if (backward == firstLetterIndex) {
						break;
					}
					ITER_FORW(forward, text);
					ITER_BACK(backward, text);
				}
				else {
					ITER_FORW(backward, text);
					ITER_BACK(forward, text);
					break;
				}
			}
			string content = text.substr(backward, forward - backward + 1);
			if (content.length() != 1) {
				flacList.push_back(Flac(content, backward, forward));
			}
		}

	}

	int greatest_length = 0;
	int greatest_index = 0;

	for (int i = 0; i < flacList.size(); i++) {
		if (flacList[i].reallength > greatest_length) {
			greatest_length = flacList[i].reallength;
			greatest_index = i;
		}
	}

	fout << greatest_length << endl;
	fout << text.substr(flacList[greatest_index].start, (flacList[greatest_index].endindex - flacList[greatest_index].start + 1)) << endl;

	//cout << greatest_length << endl;
	//cout << text.substr(flacList[greatest_index].start, (flacList[greatest_index].endindex - flacList[greatest_index].start + 1)) << endl;

	return 0;
}