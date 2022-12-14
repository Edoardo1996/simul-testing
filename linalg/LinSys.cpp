#include <cmath>
#include <cassert>
#include "LinSys.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"   

LinearSystem::LinearSystem(const Matrix& A, const Vector& b)
{
    // Check compatibility
    int local_size = A.GetNumRows();
    assert(A.GetNumCols() == local_size);
    assert(b.GetSize() == local_size);

    // Set variables for the linear system
    mSize = local_size;
    mpA = new Matrix(A);
    mpb = new Vector(b);
}

// Destructor to free memory
LinearSystem::~LinearSystem()
{
   delete mpA;
   delete mpb;
}

// Solve the linear system with Gaussian elimination with pivoting
Vector LinearSystem::Solve()
{
    Vector m(mSize);
    Vector solution(mSize);

    // Introducing some references to make the syntax readable
    Matrix& rA = *mpA;
    Vector& rb = *mpb;

    // forward sweep of Gaussian elimination
    for (int k{0}; k<mSize-1; k++)
    {
        // see if pivoting is necessary
        double max {0.0};
        int row {-1};
        for (int i{k}; i<mSize; i++)
        {
            if (fabs(rA(i+1, k+1)) > max)
            {
                row = i;
                max = fabs(rA(i+1, k+1));
            }
        }
        assert(row >= 0);

        // pivot is necessary
        if (row != k)
        {
            // swap matrix rows k+1 with row+1
            for (int i{0}; i<mSize; i++)
            {
                double temp {rA(k+1, i+1)};
                rA(k+1, i+1) = rA(row+1, i+1);
                rA(row+1, i+1) = temp;
            }
            // swap vector entries k+1 with row+1    
            double temp {rb(k+1)};
            rb(k+1) = rb(row+1);
            rb(row+1) = temp;
        }

        // create zeros in the lower part of column k
        for (int i{k+1}; i<mSize; i++)
        {
            m(i+1) = rA(i+1, k+1) / rA(k+1, k+1);
            for (int j{k}; j<mSize; j++)
            {
                rA(i+1, j+1) -= rA(k+1, j+1) * m(i+1);
            }
            rb(i+1) -= rb(k+1) * m(i+1);
        }
    }

        
    // back substitution
    for (int i{mSize-1}; i>-1; i--)
    {
        solution(i+1) = rb(i+1);
        for (int j{i+1}; j<mSize; j++)
        {
            solution(i+1) -= rA(i+1, j+1) * solution(j+1);
        }
        solution(i+1) /= rA(i+1, i);
    }

    return solution;   
}