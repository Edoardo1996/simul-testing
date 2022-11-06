#pragma once

#include <iostream>
#include "Vector.hpp"  

class Matrix
{
private:
    double** mData; 
    int mNumRows;
    int mNumCols;
public:
    Matrix(int rows, int cols); // Constructor
    Matrix(const Matrix& otherMatrix); // Copy-constructor
    ~Matrix(); // Destructor
    int GetNumRows() const;
    int GetNumCols() const;
    double& operator()(int i, int j);
    Matrix& operator=(const Matrix& otherMatrix);
    Matrix& operator+() const;
    Matrix& operator-() const;
    Matrix operator+(const Matrix& otherMatrix) const;
    Matrix operator-(const Matrix& otherMatrix) const;
    // scalar multiplication
    Matrix operator* (double n) const;
    // Determinant calculation (recursively)
    double CalculateDeterminant() const;
    // insertion operator
    friend std::ostream& operator<< (std::ostream& output, const Matrix& mat);
    // declare vector multiplication friendship
    friend Vector operator*(const Matrix& mat, const Vector& vec);
    friend Vector operator*(const Vector& vec, const Matrix& mat);
};
// prototype signatures for friend operators
Vector operator*(const Matrix& mat, const Vector& vec);
Vector operator*(const Vector& vec, const Matrix& mat);