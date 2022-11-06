#include <cmath>
#include <iostream>
#include <cassert>
#include "Vector.hpp"

// Constructor
Vector::Vector(int size)
{
    assert(size > 0 );
    mSize = size;
    mData = new double [mSize];
    for (int i{0}; i<mSize; i++)
    {
        mData[i] = 0.0;
    }
}

// Copy constructor
Vector::Vector(const Vector& otherVector)
{
    mSize = otherVector.GetSize();
    mData = new double [mSize];
    for (int i{0}; i<mSize; i++)
    {
        mData[i] = otherVector.mData[i];
    }
}

// Destructor
Vector::~Vector()
{
    delete[] mData;
}

// Get size of a vector
int Vector::GetSize() const
{
    return mSize;
}

// Overloading square bracket operator
double& Vector::operator[](int i)
{
    assert(i > -1);
    assert(i < mSize);
    return mData[i];
} 

// Overloading square bracket operator
double& Vector::operator()(int i)
{
    assert(i > 0);
    assert(i < mSize+1);
    return mData[i-1];
}

double Vector::Read(int i) const
{
    assert(i > -1);
    assert(i < mSize);
    return mData[i];
}

Vector& Vector::operator=(const Vector& otherVector)
{
    assert(mSize == otherVector.mSize);
    for (int i{0}; i<mSize; i++)
    {
        mData[i] = otherVector.mData[i];
    }
    return *this;
}

Vector Vector::operator+() const
{
    Vector v(mSize);
    for (int i{0}; i<mSize; i++)
    {
        v[i] = mData[i];
    }
    return v;
}

Vector Vector::operator-() const
{
    Vector v(mSize);
    for (int i{0}; i<mSize; i++)
    {
        v[i] = -mData[i];
    }
    return v;
}

Vector Vector::operator+(const Vector& otherVector) const
{
    assert(mSize == otherVector.mSize);
    Vector v(mSize);
    for (int i{0}; i<mSize; i++)
    {
        v[i] = mData[i] + otherVector.mData[i];
    }
    return v;
}

Vector Vector::operator-(const Vector& otherVector) const
{
    assert(mSize == otherVector.mSize);
    Vector v(mSize);
    for (int i{0}; i<mSize; i++)
    {
        v[i] = mData[i] - otherVector.mData[i];
    }
    return v;
}

Vector Vector::operator*(double n) const
{
    Vector v(mSize);
    for (int i{0}; i<mSize; i++)
    {
        v[i] = mData[i] * n;
    }
    return v;
}

std::ostream& operator<<(std::ostream& output, const Vector& v)
{
    // Format se element separeted with " " and std::endl at the end
    for (int i{0}; i<v.mSize; i++)
    {
        output << v.mData[i] << " ";
    }
    return output;
}

double Vector::CalculateNorm(int p) const
{
    double norm, sum {0.0};
    for (int i{0}; i<mSize; i++)
    {
        sum += pow(fabs(mData[i]), p);
    } 
    norm = pow(sum, 1.0/((static_cast<double>(p))));
    return norm;
}

int length(const Vector& v)
{
    return v.mSize;
}

double ScalarProduct(const Vector& v1, const Vector& v2)
{
    assert(v1.mSize == v2.mSize);
    double res{0.0};
    for (int i{0}; i<v1.mSize; i++)
    {
        res += v1.mData[i] * v2.mData[i];
    }
    return res;
}