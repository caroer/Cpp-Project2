#include "Matrix.h"
#include <iostream>
#include "r8lib.h"
#include <vector>
#include "r8mat_expm1.cpp"
#include "r8mat_expm1.h"
#include "r8lib.cpp"
#include <cmath>
#include <math.h>
using namespace std;

// Reference:
// https://codereview.stackexchange.com/questions/149669/c-operator-overloading-for-matrix-operations-follow-up


Matrix::Matrix(int s)	// Constructor of class Matrix.
{
	m = s;
	Mat = new double* [m];

	for (int i = 0; i < m; i++)
	{
		Mat[i] = new double[m]();		// For each row i every column value shall be set to 0.
	}
}

Matrix::Matrix(const Matrix &q)			// Copy constructor. 
{
	m = q.m;
	Mat = new double* [q.m];
	for (int i = 0; i < q.m; i++)
	{
		Mat[i] = new double[q.m];
	}
	for (int i = 0; i < q.m; i++) {
		for (int j = 0; j < q.m; j++) {
			Mat[i][j] = q.Mat[i][j];
		}
	}
}


Matrix::~Matrix()		// Destructor. 
{
	for (int i = 0; i < m; i++){
		delete[] Mat[i];
	}
	delete[] Mat;
}


Matrix& Matrix::operator=(const Matrix& q)		// Overload operator. 
{
	if (this == &q)
		return(*this);
	delete[] Mat;
	this->m = q.m;
	this->Mat = new double* [m];
	int ol = 0;
	
	for (int i = 0; i < m; i++)
	{
		this->Mat[i] = new double[m];	
		ol++;
		for (int j = 0; j < m; j++)
		{
			this->Mat[i][j] = q.Mat[i][j];
		}		
	}
	return(*this);
}

Matrix& Matrix::operator+=(const Matrix& Q)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			this->Mat[i][j] += Q.Mat[i][j];

		}
	}
	return (*this);
}


Matrix& Matrix::operator*=(const Matrix& Q)
{
	Matrix temp(Q.m);
	for (int i = 0; i < temp.m; ++i) {
		for (int j = 0; j < temp.m; ++j) {
			for (int k = 0; k < m; ++k) {
				temp.Mat[i][j] += (Mat[i][k] * Q.Mat[k][j]);
			}
		}
	}
	return (*this = temp);
}

Matrix& Matrix::operator*=(const double num)
{
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < m; ++j) {
			this->Mat[i][j] *= num;
		}
	}
	return *this;
}


Matrix Matrix::operator*(const double& num)const {
	Matrix temp(m);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			temp.Mat[i][j] = Mat[i][j] * num;
		}
	}
	return temp;
}

double norm(const Matrix& Q)			// Computes the norm of the matrices. 
{
	double *K = new double[Q.m]();		// Creating the vector K which will consist of each sum of the values in each row.
	double max;
	
	for (int i = 0; i < Q.m; i++) {	
		for (int j = 0; j < Q.m; j++) {
			K[i] += Q.Mat[i][j];
		}
	}
	for (int i = 0; i < Q.m; i++) {			// Determining the maximum value in the vector K.
		if (K[0] < K[i]) {
			K[0] = K[i];
		}
	}

	return K[0];
}

void printMatrix(const Matrix& Q) {
	cout << "\nThe entered matrix is: " << endl;
	for (int i = 0; i < Q.m; i++) {
		for (int j = 0; j < Q.m; j++) {
			cout << Q.Mat[i][j] << ' ';
		}
		cout << ' ' << endl;
	}
	//cout << "\n" << endl;
}

void fillMatrix(const int m, const Matrix& Q) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			cout << "Enter matrix value for row number " << i << " and column number " << j << ": ";
			cin >> Q.Mat[i][j];
		}
	}
}


int main()	
{
	int m = 2;
	double tol = 1e-10;
	Matrix M(m);
	fillMatrix(m, M);
	printMatrix(M);

	// Creating the identity matrix.
	Matrix s(m);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			if (j == i) {
				s.Mat[i][j] = 1;
			}
		}
	}

	//  Creating the vector to be used as input in the r8mat_expm1 function.
	int asize = m * m;
	double* a;
	a = new double[asize];
	int aelement = 0;

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			a[aelement] = M.Mat[j][i];
			aelement += 1;
		}
	}

	// Creating a matrix out of the result vector.
	double* result = r8mat_expm1(m, a);
	Matrix R(m);
	int relement = 0;

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			R.Mat[j][i] = result[relement];
			relement += 1;
		}
	}

	// Calculation of the matrix exponential.
	Matrix t = M;

	for (double i = 1.0; i < 1000; i++) {
		s += t;
		double c = 1.0 / (i + 1.0);
		t *= (M * c);
		if (norm(t) < tol) {
			cout << "\nThe number of terms required in the sum are: " << endl;
			cout << i + 1 << endl;
			cout << "\nThe norm of the error term is: " << endl;
			cout << norm(t) << endl;
			cout << "\nThe difference between the norm of the approximation and the norm of the given routine is: " << endl;
			cout << abs(norm(s) - norm(R)) << endl;
			break;
		}
	}
	
	return 0;
}