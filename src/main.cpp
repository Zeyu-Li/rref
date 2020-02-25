#include <cstdio>
#include <iostream>
#include <vector>
#include "../libs/Fraction.h"
#include "../libs/Fraction.cpp"
using namespace std;


// damn whitespaces and string lib not included
// from https://www.techiedelight.com/trim-string-cpp-remove-leading-trailing-spaces/
const string WHITESPACE = " \n\r\t\f\v";

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

int main() {

	// asks user for width and height of matrix
	int A_width, A_height;

	cout << "Matrix: \nWidth: ";
	cin >> A_width;
	cout << "Height: ";
	cin >> A_height;

	// inits matrices
	vector<vector <string>> a(A_height, vector<string>(A_width));
	vector<vector <Fraction>> parsedFractions(A_height, vector<Fraction>(A_width));

	// inits the first matrix
	puts("\nFirst matrix input (put the elements (must be integers) of row seperated by spaces or linebreaks): ");
	cout << "* Remember, this must be a " << A_width << "*" << A_height << " matrix\n\n";
	for (int i = 0; i < A_height; i++) {
		cout << "Line " << i + 1 << ": ";
		for (int j = 0; j < A_width; ++j) {
			cin >> a[i][j];
		}
		cout << "\n";
	}

	// parse vectors
	string delimiter = "/";
	string token;
	int bottom;
	int top;
	for (int i = 0; i < A_height; i++) {
		for (int j = 0; j < A_width; j++){
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

/*
	vector <bool> locked{false};
	vector <bool> flags;

	// solve rref
	for (int i = 0; i < A_width; i++) {

		// for each row, if the element is 0, move it to the end
		for (int j = 0; j < A_height; j++) {
			if (a[j][i] == 0 && !locked[j]) {
				flags.push_back(j);
			}
		}
		if (flags.size() == A_height) {
			continue;
		}
		else {
			locked[i] = true;
			for (auto i : flags) {
				auto tmp = a[i];
				a.erase(a.begin() + i);
				a.push_back(tmp);
			}
		}

		for (auto k = 0; k < flags.size(); k++) {
			auto element = a[k];
		}
		flags.clear();

	} */

	// output answer
	puts("The answer is: ");
	for (int i = 0; i < A_height; i++) {
		for (int j = 0; j < A_height; j++)
			cout << "\t" << parsedFractions[i][j];
		puts("\n");
	}

	return 0;
}
