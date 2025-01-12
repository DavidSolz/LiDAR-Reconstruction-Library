#include <catch2/catch_all.hpp>
#include <LRE/linalg/matrix4.hpp>
#include <cstdint>

TEST_CASE("Matrix4: Default Constructor")
{
    Matrix4 mat;

    SECTION("All elements should be initialized to 0")
    {
        for (int32_t i = 0; i < 16; ++i)
        {
            REQUIRE(mat[i] == 0.0f);
        }
    }
}

TEST_CASE("Matrix4: Copy Constructor")
{
    Matrix4 mat1;
    for (int32_t i = 0; i < 16; ++i)
    {
        mat1[i] = static_cast<float>(i);
    }

    Matrix4 mat2(mat1);

    SECTION("Copied matrix should match the original")
    {
        for (int32_t i = 0; i < 16; ++i)
        {
            REQUIRE(mat2[i] == mat1[i]);
        }
    }
}

TEST_CASE("Matrix4: Index Operator")
{
    Matrix4 mat;
    for (int32_t i = 0; i < 16; ++i)
    {
        mat[i] = static_cast<float>(i * 2);
    }

    SECTION("Values should match the assigned ones")
    {
        for (int32_t i = 0; i < 16; ++i)
        {
            REQUIRE(mat[i] == i * 2.0f);
        }
    }

    SECTION("Const index operator should return correct values")
    {
        const Matrix4 constMat = mat;
        for (int32_t i = 0; i < 16; ++i)
        {
            REQUIRE(constMat[i] == i * 2.0f);
        }
    }
}

TEST_CASE("Matrix4: Multiplication Operator")
{
    Matrix4 mat1, mat2;
    for (int32_t i = 0; i < 16; ++i)
    {
        mat1[i] = static_cast<float>(i + 1);
    }

    Matrix4 result = mat1 * mat2;

    SECTION("Matrix multiplication should yield correct results")
    {
        for (int32_t i = 0; i < 16; ++i)
        {
            REQUIRE(result[i] == 0.0f);
        }
    }
}

TEST_CASE("Matrix4: Multiplication by scalar Operator")
{
    Matrix4 mat;
    const float scalar = 5.5f;

    for (int32_t i = 0; i < 16; ++i)
    {
        mat[i] = static_cast<float>(1.0f);
    }

    Matrix4 result = mat * scalar;

    SECTION("Matrix by scalar multiplication should yield correct results")
    {
        for (int32_t i = 0; i < 16; ++i)
        {
            REQUIRE(result[i] == (mat[i] * scalar));
        }
    }
}

TEST_CASE("Matrix4: Addition Operator")
{
    Matrix4 mat1, mat2;
    for (int32_t i = 0; i < 16; ++i)
    {
        mat1[i] = static_cast<float>(i);
        mat2[i] = static_cast<float>(i * 2);
    }

    Matrix4 result = mat1 + mat2;

    SECTION("Matrix addition should yield correct results")
    {
        for (int32_t i = 0; i < 16; ++i)
        {
            REQUIRE(result[i] == mat1[i] + mat2[i]);
        }
    }
}

TEST_CASE("Matrix4: Transpose")
{
    Matrix4 mat;

    for (int32_t i = 0; i < 16; ++i)
    {
        mat[i] = static_cast<float>(i + 1);
    }

    Matrix4 transposed_mat = mat.transposed();

    SECTION("Transpose of the matrix should swap rows with columns")
    {
        for (int32_t row = 0; row < 4; ++row)
        {
            for (int32_t col = 0; col < 4; ++col)
            {
                REQUIRE(mat[row * 4 + col] == transposed_mat[col * 4 + row]);
            }
        }
    }
}

TEST_CASE("Matrix4: Determinant")
{
    Matrix4 mat;

    SECTION("Determinant of the default matrix (zero matrix) should be 0")
    {
        float det = mat.determinant();
        REQUIRE(det == 0.0f);
    }

    SECTION("Determinant of an identity matrix should be 1")
    {
        mat.identity();
        float det = mat.determinant();
        REQUIRE(det == 1.0f);
    }

    SECTION("Determinant of a non-zero matrix should be calculated correctly")
    {
        for (int32_t i = 0; i < 16; ++i)
        {
            mat[i] = static_cast<float>(i + 1);
        }

        float det = mat.determinant();
        REQUIRE(det == 0.0f);
    }
}

TEST_CASE("Matrix4: Cofactor Matrix")
{
    Matrix4 mat;
    Matrix4 result;

    SECTION("Cofactor matrix should yield correct results")
    {

        for (int32_t i = 0; i < 16; ++i)
        {
            mat[i] = static_cast<float>(i + 1);
        }

        Matrix4 cofactor = mat.cofactor();

        for (int32_t i = 0; i < 16; ++i)
        {
            REQUIRE(cofactor[i] == result[i]);
        }
    }
}

TEST_CASE("Matrix4: Subtraction Operator")
{
    Matrix4 mat1, mat2;
    for (int32_t i = 0; i < 16; ++i)
    {
        mat1[i] = static_cast<float>(i * 2);
        mat2[i] = static_cast<float>(i);
    }

    Matrix4 result = mat1 - mat2;

    SECTION("Matrix subtraction should yield correct results")
    {
        for (int32_t i = 0; i < 16; ++i)
        {
            REQUIRE(result[i] == (mat1[i] - mat2[i]));
        }
    }
}

TEST_CASE("Matrix4: Assignment Operator")
{
    Matrix4 mat1;
    for (int32_t i = 0; i < 16; ++i)
    {
        mat1[i] = static_cast<float>(i);
    }

    Matrix4 mat2;
    mat2 = mat1;

    SECTION("Assigned matrix should match the original")
    {
        for (int32_t i = 0; i < 16; ++i)
        {
            REQUIRE(mat2[i] == mat1[i]);
        }
    }
}