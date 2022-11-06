#include <iostream>
#include <cassert>
#include <cmath>
#include "Matrix.hpp"

Matrix::Matrix(int rows, int cols)
{
    assert(rows > 0);
    assert(cols > 0);
    mNumRows = rows;
    mNumCols = cols;
    mData = new double *[mNumRows];
    for (int i{0}; i < mNumCols; i++)
    {
        mData[i] = new double[mNumCols];
    }
    for (int i = 0; i < mNumRows; i++)
    {
        for (int j = 0; j < mNumCols; j++)
        {
            mData[i][j] = 0.0;
        }
    }
}

Matrix::Matrix(const Matrix &otherMatrix)
{
    mNumRows = otherMatrix.mNumRows;
    mNumCols = otherMatrix.mNumCols;
    mData = new double *[mNumRows];
    for (int i{0}; i < mNumRows; i++)
    {
        mData[i] = new double[mNumCols];
    }
    for (int i{0}; i < mNumRows; i++)
    {
        for (int j{0}; j < mNumCols; j++)
        {
            mData[i][j] = otherMatrix.mData[i][j];
        }
    }
}

// Overriden destructor
Matrix::~Matrix()
{
    for (int i{0}; i < mNumRows; i++)
    {
        delete[] mData[i];
    }
    delete[] mData;
}

int Matrix::GetNumRows() const
{
    return mNumRows;
}

int Matrix::GetNumCols() const
{
    return mNumCols;
}

double &Matrix::operator()(int i, int j)
{
    assert((i > 0) && (i < mNumRows + 1));
    assert((j > 0) && (j < mNumCols + 1));
    return mData[i - 1][j - 1];
}

Matrix &Matrix::operator=(const Matrix &otherMatrix)
{
    assert(mNumRows == otherMatrix.mNumRows);
    assert(mNumCols == otherMatrix.mNumCols);
    for (int i{0}; i < mNumRows; i++)
    {
        for (int j{0}; j < mNumCols; j++)
        {
            mData[i][j] = otherMatrix.mData[i][j];
        }
    }
    return *this;
}

Matrix &Matrix::operator+() const
{
    Matrix mat(mNumRows, mNumCols);
    for (int i{0}; i < mNumRows; i++)
    {
        for (int j{0}; j < mNumCols; j++)
        {
            mat.mData[i][j] = mData[i][j];
        }
    }
    return mat;
}

Matrix &Matrix::operator-() const
{
    Matrix mat(mNumRows, mNumCols);
    for (int i{0}; i < mNumRows; i++)
    {
        for (int j{0}; j < mNumCols; j++)
        {
            mat.mData[i][j] = -mData[i][j];
        }
    }
    return mat;
}

Matrix Matrix::operator+(const Matrix &otherMatrix) const
{
    assert(mNumRows == otherMatrix.mNumRows);
    assert(mNumCols == otherMatrix.mNumCols);
    Matrix sumMat(mNumRows, mNumCols);
    for (int i{0}; i < mNumRows; i++)
    {
        for (int j{0}; j < mNumCols; j++)
        {
            sumMat.mData[i][j] = mData[i][j] + otherMatrix.mData[i][j];
        }
    }
    return sumMat;
}

Matrix Matrix::operator-(const Matrix &otherMatrix) const
{
    assert(mNumRows == otherMatrix.mNumRows);
    assert(mNumCols == otherMatrix.mNumCols);
    Matrix sumMat(mNumRows, mNumCols);
    for (int i{0}; i < mNumRows; i++)
    {
        for (int j{0}; j < mNumCols; j++)
        {
            sumMat.mData[i][j] = mData[i][j] - otherMatrix.mData[i][j];
        }
    }
    return sumMat;
}

Matrix Matrix::operator*(double n) const
{
    Matrix multMat(mNumRows, mNumCols);
    for (int i{0}; i < mNumRows; i++)
    {
        for (int j{0}; j < mNumCols; j++)
        {
            multMat.mData[i][j] = mData[i][j] * n;
        }
    }
    return multMat;
}

Vector operator*(const Matrix &mat, const Vector &vec)
{
    int original_vector_size {vec.GetSize( )};
    assert(mat.GetNumCols() == vec.GetSize());
    int new_vector_length {mat.GetNumRows( )};
    Vector new_vec(new_vector_length);

    for (int i{0}; i < new_vector_length; i++)
    {
        for (int j{0}; j < original_vector_size; j++)
        {
            new_vec[i] += mat.mData[i][j] * vec.Read(j);
        }
    }
    return new_vec;
}

Vector operator*(const Vector &vec, const Matrix &mat)
{   
   int original_vector_size {vec.GetSize()};
   assert(mat.GetNumRows() == original_vector_size);
   int new_vector_length {mat.GetNumCols()};
   Vector new_vector(new_vector_length);

   for (int i{0}; i<new_vector_length; i++)
   {
      for (int j{0}; j<original_vector_size; j++)
      {
         new_vector[i] += vec.Read(j)*mat.mData[j][i];
      }
   }

   return new_vector;
}

// Output operator
std::ostream& operator<< (std::ostream& output, const Matrix& mat)
{
    for (int i{0}; i<mat.GetNumRows(); i++)
    {
        for (int j{0}; j<mat.GetNumCols(); j++)
        {
            output << mat.mData[i][j] << " ";
        }
        if (i != mat.GetNumRows()-1) {output << std::endl;}        
    }
    return output;
}

// Determinant of matrix (recursion)
double Matrix::CalculateDeterminant() const
{
    assert(mNumRows == mNumCols);
    double determinant {0.0};

    if (mNumRows == 1)
    {
        determinant = mData[0][0];
    }
    else
    {
        // More than one entry of matrix
        for (int i_outer{0}; i_outer<mNumRows; i_outer++)
        {
            Matrix sub_matrix(mNumRows-1, mNumCols-1);
            for (int i{0}; i<mNumRows-1; i++)
            {
                for (int j{0}; j<i_outer; j++)
                {
                    sub_matrix(i+1, j+1) = mData[i+1][j];
                }
                for (int j{i_outer}; j<mNumRows -1; j++)
                {
                    sub_matrix(i+1, j+1) = mData[i+1][j+1];
                }  
            }
            double sub_matrix_determinant = sub_matrix.CalculateDeterminant();
            determinant += pow(-1.0, i_outer) *
                                mData[0][i_outer]*sub_matrix_determinant;
        }
    }
    return determinant;
}