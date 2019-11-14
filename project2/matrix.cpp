#include "matrix.hpp"

using namespace std;

Matrix::Matrix(unsigned m) {
	mRows = m;
	mCols = m;
	//double matrix[m][m] = {0};
	matrix.reserve(mRows);
	for (unsigned i = 0; i != mRows; ++i) {
		vector<double> col(mCols, 0.0);
		matrix.push_back(col);
	}
}

void Matrix::printMatrix() const {
	for (unsigned i = 0; i != mRows; ++i) {
		for (unsigned j = 0; j != mCols; ++j) {
			cout << matrix[i][j] << " ";
		}
		cout << "\n";
	}	
}


int main() {
	cout << "Create matrix from own class" << endl;
	unsigned m = 5;
	Matrix matrix(m);
	matrix.printMatrix();

	return 0;
}