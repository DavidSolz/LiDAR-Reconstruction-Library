#ifndef MATRIX4_HPP
#define MATRIX4_HPP

#include <cstring>
#include <cstdint>
#include <cmath>

class Matrix4
{
 private:

    float data_[16];

 public:

    Matrix4(const Matrix4 & other);

    Matrix4();

    float &operator[](const int32_t & index);

    const float &operator[](const int32_t & index) const;

    Matrix4 operator*(const Matrix4& other) const;

    Matrix4& operator=(const Matrix4& other);


};

#endif