# pragma once

#include "Vector.hpp"
#include "Matrix.hpp"

class LinearSystem
{
private:
    int mSize; // size of the linear system
    Matrix* mpA; // matrix of coefficients
    Vector* mpb; // vector of knwon elements

    // Only allow constructor that specifies matrix and vector to be used
    // Copy constructor is private
    LinearSystem(const LinearSystem& otherLinearSystem) {};

public:
    LinearSystem(const Matrix& A, const Vector& b);
    ~LinearSystem();
    // Solve
    virtual Vector Solve();

};