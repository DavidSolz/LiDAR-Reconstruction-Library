#include <matrix4.hpp>

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

Matrix4 &Matrix4::operator=(const Matrix4 &other)
{
    std::memcpy(data_, other.data_, sizeof(data_));
    return *this;
}