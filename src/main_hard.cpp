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

	// inits the matrix heights and widths
	int const a_height = 3;
	int const a_width = 3;

	// inits the first and second matrix
	string a[a_width][a_height] = {
		{"1/21", "5", "0"},
		{"2/7", "  1/4", "0"},
		{"0", "  8", "1"}
	};

	// parse vectors
	vector<vector <Fraction>> parsedFractions(a_width, vector<Fraction>(a_height));
	string delimiter = "/";
	string token;
	int bottom;
	int top;
	for (int i = 0; i < a_width; i++) {
		for (int j = 0; j < a_height; j++){
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

	// solve
	

	// output answer
	puts("The answer is: ");
	for (int i = 0; i < a_width; i++) {
		for (int j = 0; j < a_height; j++)
			cout << "\t" <<  parsedFractions[i][j];
		puts("\n");
	}


	return 0;

}
