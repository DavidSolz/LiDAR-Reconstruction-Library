#include <LRE/linalg/matrix4.hpp>

Matrix4::Matrix4(const Matrix4 &other)
{
    std::memcpy(data_, other.data_, sizeof(data_));
}

Matrix4::Matrix4()
{
    std::memset(data_, 0.0f, sizeof(data_));
}

float &Matrix4::operator[](const int32_t &index)
{
    int32_t clamped_index = std::max(0, std::min(index, 15));
    return data_[clamped_index];
}

const float &Matrix4::operator[](const int32_t &index) const
{
    int32_t clamped_index = std::max(0, std::min(index, 15));
    return data_[clamped_index];
}

void Matrix4::identity()
{
    std::memset(data_, 0.0f, sizeof(data_));
    data_[0] = 1.0f;
    data_[5] = 1.0f;
    data_[10] = 1.0f;
    data_[15] = 1.0f;
}

void Matrix4::transpose()
{
    std::swap(data_[1], data_[4]);
    std::swap(data_[2], data_[8]);
    std::swap(data_[3], data_[12]);
    std::swap(data_[6], data_[9]);
    std::swap(data_[7], data_[13]);
    std::swap(data_[11], data_[14]);
}

float Matrix4::determinant() const
{
     float det = 0.0f;

    det += data_[0] * (data_[5] * (data_[10] * data_[15] - data_[11] * data_[14]) -
                       data_[6] * (data_[9] * data_[15] - data_[11] * data_[13]) +
                       data_[7] * (data_[9] * data_[14] - data_[10] * data_[13]));

    det -= data_[1] * (data_[4] * (data_[10] * data_[15] - data_[11] * data_[14]) -
                       data_[6] * (data_[8] * data_[15] - data_[11] * data_[12]) +
                       data_[7] * (data_[8] * data_[14] - data_[10] * data_[12]));

    det += data_[2] * (data_[4] * (data_[9] * data_[15] - data_[11] * data_[13]) -
                       data_[5] * (data_[8] * data_[15] - data_[11] * data_[12]) +
                       data_[7] * (data_[8] * data_[13] - data_[9] * data_[12]));

    det -= data_[3] * (data_[4] * (data_[9] * data_[14] - data_[10] * data_[13]) -
                       data_[5] * (data_[8] * data_[14] - data_[10] * data_[12]) +
                       data_[6] * (data_[8] * data_[13] - data_[9] * data_[12]));

    return det;
}

Matrix4 Matrix4::operator+(const Matrix4 &other) const
{
    Matrix4 result;

#ifdef __AVX__

    for (int32_t i = 0; i < 16; i += 4)
    {
        __m128 reg_a = _mm_loadu_ps(&data_[i]);
        __m128 reg_b = _mm_loadu_ps(&other.data_[i]);
        __m128 reg_c = _mm_add_ps(reg_a, reg_b);
        _mm_storeu_ps(&result.data_[i], reg_c);
    }

#else

    for (int32_t i = 0; i < 16; i++)
    {
        result.data_[i] = data_[i] + other.data_[i];
    }

#endif

    return result;
}

Matrix4 Matrix4::operator-(const Matrix4 &other) const
{
    Matrix4 result;

#ifdef __AVX__

    for (int32_t i = 0; i < 16; i += 4)
    {
        __m128 reg_a = _mm_loadu_ps(&data_[i]);
        __m128 reg_b = _mm_loadu_ps(&other.data_[i]);
        __m128 reg_c = _mm_sub_ps(reg_a, reg_b);
        _mm_storeu_ps(&result.data_[i], reg_c);
    }

#else

    for (int32_t i = 0; i < 16; i++)
    {
        result.data_[i] = data_[i] - other.data_[i];
    }

#endif

    return result;
}

Matrix4 Matrix4::operator*(const Matrix4 &other) const
{

    Matrix4 result;

    for (int32_t y = 0; y < 4; y++)
    {
        for (int32_t x = 0; x < 4; x++)
        {
            float sum = 0.0f;

            for (int32_t k = 0; k < 4; k++)
            {
                sum += data_[y * 4 + k] * other.data_[k * 4 + x];
            }

            result.data_[y * 4 + x] = sum;
        }
    }

    return result;
}

Matrix4 Matrix4::operator*(const float &scalar) const
{

    Matrix4 result;

#ifdef __AVX__

    __m128 constant = _mm_load1_ps(&scalar);

    for (int32_t i = 0; i < 16; i += 4)
    {
        __m128 reg_a = _mm_loadu_ps(&data_[i]);
        __m128 reg_b = _mm_mul_ps(reg_a, constant);
        _mm_storeu_ps(&result.data_[i], reg_b);
    }

#else

    for (int32_t i = 0; i < 16; i++)
    {
        result.data_[i] = data_[i] * scalar;
    }

#endif

    return result;
}

Matrix4 &Matrix4::operator=(const Matrix4 &other)
{
    std::memcpy(data_, other.data_, sizeof(data_));
    return *this;
}