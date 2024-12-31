#ifndef VECTOR4_HPP
#define VECTOR4_HPP

#include <cstring>
#include <cmath>

#ifdef __AVX__
#include <immintrin.h>
#endif

class Vector4
{
 private:

    float data_[4];

 public:

    Vector4(const float & x, const float & y, const float & z, const float & w);

    Vector4(const float & x, const float & y, const float & z);

    Vector4(const float & x, const float & y);

    Vector4(const float & x);

    Vector4(const Vector4 & other);

    Vector4();

    float magnitude() const;

    Vector4 normalized() const;

    float sqr_magnitude() const;

    float & x();

    float & y();

    float & z();

    float & w();

    bool operator==(const Vector4 & other) const;

    Vector4 operator+(const Vector4 & other) const;

    Vector4 operator-(const Vector4 & other) const;

    Vector4 operator*(const float & scalar) const;

    Vector4 operator/(const float & scalar) const;

    Vector4& operator=(const Vector4 & other);

    Vector4& normalize();

    static float distance(const Vector4 & a, const Vector4 & b);

    static float dot(const Vector4 & a, const Vector4 & b);

    static Vector4 lerp(const Vector4 & a, const Vector4 & b, float t);

    static Vector4 lerp_unclamped(const Vector4 & a, const Vector4 & b, const float & t);

    static Vector4 max(const Vector4 & a, const Vector4 & b);

    static Vector4 min(const Vector4 & a, const Vector4 & b);

    static Vector4 project(const Vector4 & a, const Vector4 & b);
};

#endif