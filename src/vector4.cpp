#include <LRE/linalg/vector4.hpp>

Vector4::Vector4(const Vector4 &other)
{
    std::memcpy(data_, other.data_, sizeof(data_));
}

Vector4::Vector4(const float &x, const float &y, const float &z, const float &w)
{
    data_[0] = x;
    data_[1] = y;
    data_[2] = z;
    data_[3] = w;
}

Vector4::Vector4(const float &x, const float &y, const float &z)
{
    data_[0] = x;
    data_[1] = y;
    data_[2] = z;
    data_[3] = 0.0f;
}

Vector4::Vector4(const float &x, const float &y)
{
    data_[0] = x;
    data_[1] = y;
    data_[2] = 0.0f;
    data_[3] = 0.0f;
}

Vector4::Vector4(const float &x)
{
    data_[0] = x;
    data_[1] = 0.0f;
    data_[2] = 0.0f;
    data_[3] = 0.0f;
}

Vector4::Vector4()
{
    std::memset(data_, 0, sizeof(data_));
}

float Vector4::magnitude() const
{
    float sqr_length = sqr_magnitude();
    return std::sqrt(sqr_length);
}

Vector4 Vector4::normalized() const
{
    float length = magnitude();

    if (length <= 1e-6f)
    {
        length = 1.0f;
    }

    return Vector4(data_[0], data_[1], data_[2], data_[3])/length;
}

float Vector4::sqr_magnitude() const
{
    return data_[0] * data_[0] + data_[1] * data_[1] + data_[2] * data_[2] + data_[3] * data_[3];
}

bool Vector4::operator==(const Vector4 &other) const
{
    return std::memcmp(data_, other.data_, sizeof(data_)) == 0;
}

Vector4 &Vector4::operator=(const Vector4 &other)
{
    std::memcpy(data_, other.data_, sizeof(data_));
    return *this;
}

Vector4 Vector4::operator+(const Vector4 &other) const
{
    Vector4 result;

#ifdef __AVX__

    __m128 reg_a = _mm_loadu_ps(data_);
    __m128 reg_b = _mm_loadu_ps(other.data_);
    __m128 reg_c = _mm_add_ps(reg_a, reg_b);

    _mm_storeu_ps(result.data_, reg_c);

#else

    result.data_[0] = data_[0] + other.data_[0];
    result.data_[1] = data_[1] + other.data_[1];
    result.data_[2] = data_[2] + other.data_[2];
    result.data_[3] = data_[3] + other.data_[3];

#endif

    return result;
}

Vector4 Vector4::operator-(const Vector4 &other) const
{
    Vector4 result;

#ifdef __AVX__

    __m128 reg_a = _mm_loadu_ps(data_);
    __m128 reg_b = _mm_loadu_ps(other.data_);
    __m128 reg_c = _mm_sub_ps(reg_a, reg_b);
    
    _mm_storeu_ps(result.data_, reg_c);

#else

    result.data_[0] = data_[0] - other.data_[0];
    result.data_[1] = data_[1] - other.data_[1];
    result.data_[2] = data_[2] - other.data_[2];
    result.data_[3] = data_[3] - other.data_[3];

#endif

    return result;
}

Vector4 Vector4::operator*(const float &scalar) const
{
    Vector4 result;

#ifdef __AVX__

    __m128 reg_a = _mm_loadu_ps(data_);
    __m128 reg_b = _mm_set_ps1(scalar);
    __m128 reg_c = _mm_mul_ps(reg_a, reg_b);
    
    _mm_storeu_ps(result.data_, reg_c);

#else

    result.data_[0] = data_[0] * scalar;
    result.data_[1] = data_[1] * scalar;
    result.data_[2] = data_[2] * scalar;
    result.data_[3] = data_[3] * scalar;

#endif

    return result;
}

Vector4 Vector4::operator/(const float &scalar) const
{
    Vector4 result;
    float scalar_in_range = scalar;

    if (std::abs(scalar_in_range) < 1e-6f)
    {
        scalar_in_range = 1.0f;
    }

#ifdef __AVX__

    __m128 reg_a = _mm_loadu_ps(data_);
    __m128 reg_b = _mm_set_ps1( 1.0f/scalar_in_range );
    __m128 reg_c = _mm_mul_ps(reg_a, reg_b);
    
    _mm_storeu_ps(result.data_, reg_c);

#else

    result.data_[0] = data_[0] / scalar_in_range;
    result.data_[1] = data_[1] / scalar_in_range;
    result.data_[2] = data_[2] / scalar_in_range;
    result.data_[3] = data_[3] / scalar_in_range;

#endif

    return result;
}

Vector4 &Vector4::normalize()
{
    float length = magnitude();
    *this = this->operator/(length);
    return *this;
}

float &Vector4::x()
{
    return data_[0];
}

float &Vector4::y()
{
    return data_[1];
}

float &Vector4::z()
{
    return data_[2];
}

float &Vector4::w()
{
    return data_[3];
}

float Vector4::distance(const Vector4 &a, const Vector4 &b)
{
    Vector4 difference = a - b;
    return difference.magnitude();
}

float Vector4::dot(const Vector4 &a, const Vector4 &b)
{
    
#ifdef __AVX__

    __m128 reg_a = _mm_loadu_ps(a.data_);
    __m128 reg_b = _mm_loadu_ps(b.data_);

    __m128 reg_mul = _mm_mul_ps(reg_a, reg_b);

    __m128 shuf = _mm_movehdup_ps(reg_mul);
    __m128 sums = _mm_add_ps(reg_mul, shuf);
    shuf = _mm_movehl_ps(shuf, sums);
    sums = _mm_add_ss(sums, shuf);

    return _mm_cvtss_f32(sums);
#else
    return a.data_[0] * b.data_[0] + a.data_[1] * b.data_[1] +
           a.data_[2] * b.data_[2] + a.data_[3] * b.data_[3];
#endif

}

Vector4 Vector4::lerp(const Vector4 &a, const Vector4 &b, float t)
{
    t = std::max(0.0f, std::min(t, 1.0f));
    return a + (b - a) * t;
}

Vector4 Vector4::lerp_unclamped(const Vector4 &a, const Vector4 &b, const float &t)
{
    return a + (b - a) * t;
}

Vector4 Vector4::max(const Vector4 &a, const Vector4 &b)
{
    float x = std::max(a.data_[0], b.data_[0]);
    float y = std::max(a.data_[1], b.data_[1]);
    float z = std::max(a.data_[2], b.data_[2]);
    float w = std::max(a.data_[3], b.data_[3]);

    return Vector4(x, y, z, w);
}

Vector4 Vector4::min(const Vector4 &a, const Vector4 &b)
{
    float x = std::min(a.data_[0], b.data_[0]);
    float y = std::min(a.data_[1], b.data_[1]);
    float z = std::min(a.data_[2], b.data_[2]);
    float w = std::min(a.data_[3], b.data_[3]);

    return Vector4(x, y, z, w);
}

Vector4 Vector4::project(const Vector4 &a, const Vector4 &b)
{
    float dot_product = Vector4::dot(a, b);
    float b_sqr_magnitude = b.sqr_magnitude();

    if (b_sqr_magnitude < 1e-6f)
    {
        b_sqr_magnitude = 1.0f;
    }

    float ratio = dot_product / b_sqr_magnitude;

    return b * ratio;
}