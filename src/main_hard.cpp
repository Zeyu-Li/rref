#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm> // for sort() 
#include "../libs/Fraction.h"
#include "../libs/Fraction.cpp"
using namespace std;

// damn whitespaces and string lib not included
// from https://www.techiedelight.com/trim-string-cpp-remove-leading-trailing-spaces/
const string WHITESPACE = " \n\r\t\f\v";
// I know bad pratice, but I'm still learning
int col_ptr = 0;

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

string trim(const string& s) {
	// trims right and left for whitespace chars
	return rtrim(ltrim(s));
}

bool sortcol(vector<Fraction>& v1, vector<Fraction>& v2) {
	return v1[col_ptr] < v2[col_ptr];
}

bool col_zeros(vector<vector <Fraction>>& matrix, const int col) {
	// counts zeros in col
	int zeros = 0;
	for (int i = 0; i < matrix.size(); i++) {
		if (matrix[i][col] == Fraction(0,1)) {
			zeros++;
		}
	}
	if (matrix.size() == zeros) {
		return true;
	}
	return false;
}

int main() {

	// inits the matrix heights and widths
	Fraction one = Fraction(1, 1);
	int const a_height = 3;
	int const a_width = 4;

	// inits the first and second matrix
	string a[a_height][a_width] = {
		{"1/21", "5", "0", "12/3"},
		{"2/7", "  1/4", "90", "0"},
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

	// inits; end is when to stop, zero counter is how many zero rows
	int end = a_height;
	int zero_counter = 0;
	int row_ptr, pivot;
	Fraction pivot_factor, factor;
	// init zeros
	vector<Fraction> zero;
	for (int t = 0; t < a_width; t++)
		zero.push_back(Fraction(0,1));

	vector<vector <Fraction>> finalFrac(a_height, vector<Fraction>(a_width));
	while (end >= 1) {
		pivot = end;
		// sort by x (lead) element in row https://www.geeksforgeeks.org/sorting-2d-vector-in-c-set-1-by-row-and-column/
		sort(parsedFractions.begin(), parsedFractions.end(), sortcol);

		// if col is not all zero get leading number that is not 0
		if (!col_zeros(parsedFractions, col_ptr)) {
			while (parsedFractions[0][col_ptr] == 0) {
				// if the row is all zero, erase and add to 0 counter and delete from end ptr
				if (equal(parsedFractions[0].begin() + 1, parsedFractions[0].end(), parsedFractions[0].begin())) {
					parsedFractions.erase(parsedFractions.begin());
					zero_counter++;
					end--;
					pivot--;
					// if matrix is all zero, break from checks
					if (end == 0) {
						break;
					}
				} else {
					// push to end
					vector<Fraction> temp = parsedFractions[0];
					parsedFractions.erase(parsedFractions.begin());
					parsedFractions.push_back(temp);
					pivot--;
				}
			}
		} else {
			// if col is all zeros, go to next column
			col_ptr++;
			continue;
		}

		// turn first element into 1 if not so already and cancel out (pivot) the others
		if (parsedFractions[0][col_ptr] != one) {
			factor = one / parsedFractions[0][col_ptr];
			parsedFractions[0][col_ptr] = one;
			for (int tmp_col_ptr = col_ptr + 1; tmp_col_ptr < parsedFractions[0].size(); tmp_col_ptr++) {
				parsedFractions[0][tmp_col_ptr] = parsedFractions[0][tmp_col_ptr] * factor;
			}
			
			// push to final matrix once it is a one
			finalFrac[col_ptr] = parsedFractions[0];
		} else {
			finalFrac[col_ptr] = parsedFractions[0];
		}
		// if matrix remaining is 1, then done
		if (parsedFractions.size() == 1) {
			break;
		}

		// row pointer always starts at the 1
		row_ptr = 1;
		// zero out others by pivot
		while (row_ptr < pivot) {
			// for each row
			pivot_factor = parsedFractions[row_ptr][col_ptr];
			parsedFractions[row_ptr][col_ptr] = Fraction(0, 1);
			for (int col_s = col_ptr + 1; col_s < a_width; col_s++) {
				parsedFractions[row_ptr][col_s] = parsedFractions[row_ptr][col_s] - (pivot_factor * parsedFractions[0][col_s]);
			}
			row_ptr++;
		}

		// ease first matrix, it's in the final matrix
		parsedFractions.erase(parsedFractions.begin());
		end--;
		col_ptr++;
	}

	// fully rref by:
	// starting from the back and work up
	int start, pivoter;
	Fraction pivot_factor_;
	for (int back = finalFrac.size() - 1; back > 0; back--) {
		for (int starter = 0; ; starter++){
			if (finalFrac[back][starter] == 1) {
				start = starter;
				break;
			}
		}
		// inits pivotor as the row minus 1 (row before the one minused)
		pivoter = back - 1;

		pivot_factor_ = finalFrac[pivoter][start];
		finalFrac[pivoter][start] = Fraction(0, 1);
		for (int col_s = start + 1; col_s < a_width; col_s++) {
			finalFrac[pivoter][col_s] = finalFrac[pivoter][col_s] - (pivot_factor_ * finalFrac[back][col_s]);
		}
	}

	// add 0s back
	for (int j = 0; j < zero_counter; j++)
		finalFrac.push_back(zero);

	// output answer
	cout << "The answer is: " << endl;
	for (int i = 0; i < a_height; i++) {
		for (int j = 0; j < a_width; j++)
			cout << "\t" <<  finalFrac[i][j];
		cout << "\n";
	}

	return 0;
}
