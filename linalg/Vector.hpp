#include <ostream>
#pragma once

class Vector {
private:
    double* mData; // Data of vector
    int mSize; // Size of vector
public:

    Vector(int size); // Constructor
    Vector(const Vector& otherVector); // Copy Constructor
    ~Vector(); // Destructor

    int GetSize() const;
    double Read(int i) const;
    double CalculateNorm(int p=2) const;  // p-norm
    void CheckIndex(int i); // Error handling
    
    double& operator[](int i); // Zero-based indexing
    double& operator()(int i); // One-based indexing
    Vector& operator=(const Vector& otherVector);
    Vector operator+() const;
    Vector operator-() const;
    Vector operator+(const Vector& otherVector) const;
    Vector operator-(const Vector& otherVector) const;
    // Scalar multiplication
    Vector operator*(double n) const;
    // insetion operator
    friend std::ostream& operator<<(std::ostream& output, const Vector &v);
   
    // length function
    friend int length(const Vector& v);
    friend double ScalarProduct(const Vector& v1, const Vector& v2);
    

};