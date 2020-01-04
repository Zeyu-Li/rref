#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

int main() {

	// asks user for width and height of matrix
	int A_width, A_height;

	cout << "Matrix: \nWidth: ";
	cin >> A_width;
	cout << "Height: ";
	cin >> A_height;

	// inits matrices
	vector<vector<int> > a(A_width, vector<int>(A_height));

	// inits the first and second matrix
	puts("\nFirst matrix input (put the elements (must be integers) of row seperated by spaces or linebreaks): ");
	cout << "* Remeber, this must be a " << A_width << "*" << A_height << " matrix\n\n";
	for (int i = 0; i < A_height; i++) {
		cout << "Line " << i + 1 << ": ";
		for (int j = 0; j < A_width; ++j) {
			cin >> a[i][j];
		}
		cout << "\n";
	}

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

	}

	// output answer
	puts("The answer is: ");
	for (int i = 0; i < A_height; i++) {
		for (int j = 0; j < A_height; j++)
			printf("%i\t", a[i][j]);
		puts("\n");
	}


	return 0;

}
