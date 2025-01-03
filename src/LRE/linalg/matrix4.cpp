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

Matrix4 Matrix4::transposed()
{
    Matrix4 result;

    for (int32_t y = 0; y < 4; y++)
    {
        for (int32_t x = 0; x < 4; x++)
        {
            result[x * 4 + y] = data_[y * 4 + x];
        }
    }

    return result;
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
        __m128 reg_b = _mm_loadu_ps(&other[i]);
        __m128 reg_c = _mm_add_ps(reg_a, reg_b);
        _mm_storeu_ps(&result[i], reg_c);
    }

#else

    for (int32_t i = 0; i < 16; i++)
    {
        result[i] = data_[i] + other[i];
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
        __m128 reg_b = _mm_loadu_ps(&other[i]);
        __m128 reg_c = _mm_sub_ps(reg_a, reg_b);
        _mm_storeu_ps(&result[i], reg_c);
    }

#else

    for (int32_t i = 0; i < 16; i++)
    {
        result[i] = data_[i] - other[i];
    }

#endif

    return result;
}

Matrix4 Matrix4::cofactor() const
{
    Matrix4 result;

    float minor[9];

    for (int32_t row = 0; row < 4; ++row)
    {
        for (int32_t col = 0; col < 4; ++col)
        {

            int32_t minor_row = 0;
            for (int32_t i = 0; i < 4; ++i)
            {
                if (i == row)
                {
                    continue;
                }

                int32_t minor_col = 0;
                for (int32_t j = 0; j < 4; ++j)
                {
                    if (j == col)
                    {
                        continue;
                    }

                    minor[minor_row * 3 + minor_col] = data_[i * 4 + j];
                    ++minor_col;
                }
                ++minor_row;
            }

            float minor_determinant =
                minor[0] * (minor[4] * minor[8] - minor[5] * minor[7]) 
                - minor[1] * (minor[3] * minor[8] - minor[5] * minor[6]) 
                + minor[2] * (minor[3] * minor[7] - minor[4] * minor[6]);

            result[row * 4 + col] = ((row + col) % 2 == 0 ? 1.0f : -1.0f) * minor_determinant;
        }
    }

    return result;
}

Matrix4 Matrix4::inverted() const
{
    Matrix4 result;

    const float det = determinant();

    if (std::abs(det) < 1e-6f)
    {
        return *this;
    }

    Matrix4 cofactor_matrix = cofactor();

    Matrix4 transposed_cofactor_matrix = cofactor_matrix.transposed();

    result = transposed_cofactor_matrix * (1.0f / det);

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
                sum += data_[y * 4 + k] * other[k * 4 + x];
            }

            result[y * 4 + x] = sum;
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
        _mm_storeu_ps(&result[i], reg_b);
    }

#else

    for (int32_t i = 0; i < 16; i++)
    {
        result[i] = data_[i] * scalar;
    }

#endif

    return result;
}

Matrix4 &Matrix4::operator=(const Matrix4 &other)
{
    std::memcpy(data_, other.data_, sizeof(data_));
    return *this;
}