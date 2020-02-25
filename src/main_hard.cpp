#include <cstdio>
#include <iostream>
#include <vector>
#include<algorithm> // for sort() 
#include "../libs/Fraction.h"
#include "../libs/Fraction.cpp"
using namespace std;

// damn whitespaces and string lib not included
// from https://www.techiedelight.com/trim-string-cpp-remove-leading-trailing-spaces/
const string WHITESPACE = " \n\r\t\f\v";
// I know bad pratice, but I'm still learning
int lead = 0;

string ltrim(const string& s)
{
	size_t start = s.find_first_not_of(WHITESPACE);
	return (start == string::npos) ? "" : s.substr(start);
}

string rtrim(const string& s)
{
	size_t end = s.find_last_not_of(WHITESPACE);
	return (end == string::npos) ? "" : s.substr(0, end + 1);
}

string trim(const string& s)
{
	return rtrim(ltrim(s));
}

bool sortcol(const vector<int>& v1, const vector<int>& v2) {
	return v1[lead] < v2[lead];
}

int main() {

	// inits the matrix heights and widths
	int const a_height = 3;
	int const a_width = 4;

	// inits the first and second matrix
	string a[a_height][a_width] = {
		{"1/21", "5", "0", "12/3"},
		{"2/7", "  1/4", "0", "0"},
		{"0", "  8", "1", "2/3"}
	};

	// parse vectors
	vector<vector <Fraction>> parsedFractions(a_height, vector<Fraction>(a_width));
	string delimiter = "/";
	string token;
	int bottom;
	int top;
	for (int i = 0; i < a_height; i++) {
		for (int j = 0; j < a_width; j++){
			string someString = trim(a[i][j]);
			bottom = 1;
			top = 0;

			// from https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
			size_t pos = 0;
			try {
				if ((pos = someString.find(delimiter)) != string::npos) {
					token = someString.substr(0, pos);
					top = stoi(token);
					someString.erase(0, pos + delimiter.length());
					bottom = stoi(someString);
				} else {
				top = stoi(someString);
				}
			} catch (...) {
				cout << "One of the input numbers is wrong" << endl;
				return 0;
			}
			Fraction frac(top, bottom);
			parsedFractions[i][j] = frac;
		}
	}

	int done_y = 0, done_x = 0;
	int end = a_height;
	int end_x = a_height;
	bool finished_push = false;
	while (lead < end) {
		// sort by x (lead) element in row https://www.geeksforgeeks.org/sorting-2d-vector-in-c-set-1-by-row-and-column/
		sort(parsedFractions.begin(), parsedFractions.end(),sortcol);

		while (true) {
			if (parsedFractions[done_y][0] == 0) {
				if (equal(parsedFractions[done_y].begin() + 1, parsedFractions[done_y].end(), parsedFractions[done_y].begin())) {
					vector<Fraction> temp = parsedFractions[done_y];
					parsedFractions.erase(parsedFractions.begin() + done_y);
					parsedFractions.push_back(temp);
					end--;
					if (end == lead) {
						break;
					}
				} else {
					break;
				}
			}
			// check if all zeros, if so, push back
			
		}
		
		// turn first element into 1 if not  so already and cancel out (pivot) the others
		if (parsedFractions[done_y][done_x] < 1) {
			;
		} else if (parsedFractions[done_y][done_x] == 1) {
			;
		} else {

		}
		for (int x = 0; x < end_x; x++) {
			Fraction tmp = parsedFractions[lead][lead];
			if (y == lead) {
				parsedFractions[y][x] = parsedFractions[y][x] / tmp;
			} else {
				parsedFractions[y][x] = parsedFractions[y][x] - (parsedFractions[lead][x] * (parsedFractions[y][lead] / tmp));
			}
			std::cout << parsedFractions[y][x]<<endl;
		}
		done_y++;
		done_x++;
		lead++;
	}

	// output answer
	cout << "The answer is: ";
	for (int i = 0; i < a_height; i++) {
		for (int j = 0; j < a_width; j++)
			cout << "\t" <<  parsedFractions[i][j];
		cout << "\n";
	}


	return 0;

}
