#ifndef MATRIX4_HPP
#define MATRIX4_HPP

#include <cstring>
#include <cstdint>
#include <algorithm>
#include <cmath>

#ifdef __AVX__
#include <immintrin.h>
#endif

class Matrix4
{
 private:

    float data_[16];

 public:

    Matrix4(const Matrix4 & other);

    Matrix4();

    float &operator[](const int32_t & index);

    const float &operator[](const int32_t & index) const;

    void identity();

    float determinant() const;

    Matrix4 transposed();

    Matrix4 cofactor() const;

    Matrix4 inverted() const;

    Matrix4 operator*(const Matrix4& other) const;

    Matrix4 operator*(const float& scalar) const;

    Matrix4 operator+(const Matrix4& other) const;

    Matrix4 operator-(const Matrix4& other) const;

    Matrix4& operator=(const Matrix4& other);

};

#endif