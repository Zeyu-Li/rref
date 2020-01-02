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
	puts("\nFirst matrix input (put the elements of row seperated by spaces or linebreaks): ");
	cout << "* Remeber, this must be a " << A_width << "*" << A_height << " matrix\n\n";
	for (int i = 0; i < A_height; i++) {
		cout << "Line " << i + 1 << ": ";
		for (int j = 0; j < A_width; ++j) {
			cin >> a[i][j];
		}
		cout << "\n";
	}

	// solve rref
	for (int i = 0; i < A_width; i++) {
		for (int j = 0; j < B_height; j++) {
			a[i][j] = 0;
			for (int k = 0; k < A_height; k++) {
				c[i][j] += a[i][k] * b[k][j];
			}
		}
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
