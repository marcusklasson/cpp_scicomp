#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h> 

#include "matrix.hpp"
#include "myMatrixExponential.hpp"

using namespace std;

#include "r8lib.h" // has to be included after namespace std
#include "r8mat_expm1.h" 

double* createMatrixAsArray(const string& filename) {
	ifstream infile(filename);
	double* array;

	if (infile.good()) {
		string line;
		double value;
		vector<vector<double>> v;

		while (getline(infile, line)) {
			v.push_back(vector<double>());
			stringstream split(line);

			while (split >> value) {
				v.back().push_back(value);
			}	
		}

		int nRows = v.size();
		int nCols = v[0].size(); 
		array = new double[nRows*nCols];
		// The array is represented as a matrix by going through the column values first.
		//	For example, if we have a 2x2 matrix, the first two values will be the first column
		//	and the final two values will be the second column. So when we read the matrix from file
		//	by inserting it row by row, the array will understand each row as its column. Therefore,
		//	we have to loop through the matrix first over the columns and insert them into the array. 
		
		int count = 0;
		for (int j = 0; j < nCols; ++j) {
			for (int i = 0; i < nRows; ++i) {
				array[count] = v[i][j];
				++count;
			}
		}

	} else {
		cout << "Error! Could not read file. Exiting..." << endl;
		exit(EXIT_FAILURE);
	}

	return array;
}

int main(int argc, char* argv[]) {

	if (argc < 2) {
		cout << "Error! Argument with file containing matrix is missing. Exiting...\n" << endl;;
		exit(EXIT_FAILURE);
	}

	double* array;
	double* result;
	int m;

	cout << "\n" << argv[1] << "\n";
	Matrix A(argv[1]);
	A.printMatrix();
	Matrix expA = myMatrixExponential(A);
	cout << "Matrix exponential " << endl;
	expA.printMatrix();

	m = A.getRows();
	array = createMatrixAsArray(argv[1]);
	result = r8mat_expm1(m, array);
	r8mat_print(m, m, result, "r8mat matrix exponential: ");

	delete [] array; 
	delete [] result; 

	return 0;

}