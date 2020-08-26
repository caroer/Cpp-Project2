#ifndef Matrix_h
#define Matrix_h
#include <iostream>

class Matrix {

public:
	int m;
	double** Mat;
	int* K;
	Matrix(int m);
	Matrix(const Matrix&);
	~Matrix();
	Matrix& operator=(const Matrix&);
	Matrix& operator+=(const Matrix&);
	Matrix& operator*=(const Matrix&);
	Matrix& operator*=(const double);
	Matrix operator*(const double&) const;
	double norm() const;			
	void printMatrix() const;
	void fillMatrix(const int, const Matrix& Q);

};

#endif
