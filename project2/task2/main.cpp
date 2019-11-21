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

double* createMatrixAsArray(const char* filename) {
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

int main() {
	cout << "Create matrix from own class" << endl;
	unsigned int m = 2;
	Matrix A(m);
	A.fillMatrix(1);

	Matrix expA = myMatrixExponential(A, 1.0);
	expA.printMatrix();
	//A.identity();
	//A = A*(2);
	
	Matrix B(m);
	B.fillMatrix(3);
	A.printMatrix();
	B.printMatrix();
	cout << "matrix multiplication" << endl;
	A *= B;
	A.printMatrix();
	//A.printMatrix();

	Matrix D("matrix_files/matrix2.txt");
	D.printMatrix();
	Matrix expD = myMatrixExponential(D);
	expD.printMatrix();	

	int n = D.getRows();
	double* array = createMatrixAsArray("matrix_files/matrix2.txt");

	cout << "L2-Norm of matrix: " << r8mat_norm_l2(n, n, array) << "\n";

	double* result = r8mat_expm1(n, array);
	r8mat_print(n, n, result, "Cool matrix");

	//Matrix expA = A.matrixExponential();
	//expA.printMatrix();

	//expA = myMatrixExponential(A, 1.0);
	//expA.printMatrix();

	//cout << "Frobenius norm: \n";
	//double norm = I.normFrobenius();

	delete [] array; 
	return 0;
}