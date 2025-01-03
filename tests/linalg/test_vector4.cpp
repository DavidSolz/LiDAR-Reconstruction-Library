#include <catch2/catch_all.hpp>
#include <LRE/linalg/vector4.hpp>
#include <cstdint>

TEST_CASE("Vector4: Constructors")
{
    SECTION("Default Constructor")
    {
        Vector4 vec;
        REQUIRE(vec.x() == 0.0f);
        REQUIRE(vec.y() == 0.0f);
        REQUIRE(vec.z() == 0.0f);
        REQUIRE(vec.w() == 0.0f);
    }

    SECTION("Single-Value Constructor")
    {
        Vector4 vec(5.0f);
        REQUIRE(vec.x() == 5.0f);
        REQUIRE(vec.y() == 0.0f);
        REQUIRE(vec.z() == 0.0f);
        REQUIRE(vec.w() == 0.0f);
    }

    SECTION("Two-Value Constructor")
    {
        Vector4 vec(3.0f, 4.0f);
        REQUIRE(vec.x() == 3.0f);
        REQUIRE(vec.y() == 4.0f);
        REQUIRE(vec.z() == 0.0f);
        REQUIRE(vec.w() == 0.0f);
    }

    SECTION("Three-Value Constructor")
    {
        Vector4 vec(1.0f, 2.0f, 3.0f);
        REQUIRE(vec.x() == 1.0f);
        REQUIRE(vec.y() == 2.0f);
        REQUIRE(vec.z() == 3.0f);
        REQUIRE(vec.w() == 0.0f);
    }

    SECTION("Four-Value Constructor")
    {
        Vector4 vec(1.0f, 2.0f, 3.0f, 4.0f);
        REQUIRE(vec.x() == 1.0f);
        REQUIRE(vec.y() == 2.0f);
        REQUIRE(vec.z() == 3.0f);
        REQUIRE(vec.w() == 4.0f);
    }

    SECTION("Copy Constructor")
    {
        Vector4 original(1.0f, 2.0f, 3.0f, 4.0f);
        Vector4 copy(original);
        REQUIRE(copy.x() == original.x());
        REQUIRE(copy.y() == original.y());
        REQUIRE(copy.z() == original.z());
        REQUIRE(copy.w() == original.w());
    }
}

TEST_CASE("Vector4: Magnitude and Normalization")
{
    Vector4 vec(3.0f, 4.0f, 0.0f, 0.0f);

    SECTION("Magnitude")
    {
        REQUIRE(vec.magnitude() == 5.0f);
    }

    SECTION("Squared Magnitude")
    {
        REQUIRE(vec.sqr_magnitude() == 25.0f);
    }

    SECTION("Normalization")
    {
        Vector4 norm = vec.normalized();
        REQUIRE(norm.magnitude() == 1.0f);
        REQUIRE(norm.x() == (3.0f / 5.0f));
        REQUIRE(norm.y() == (4.0f / 5.0f));
    }
}

TEST_CASE("Vector4: Arithmetic Operators")
{
    Vector4 vec1(1.0f, 2.0f, 3.0f, 4.0f);
    Vector4 vec2(4.0f, 3.0f, 2.0f, 1.0f);

    SECTION("Addition")
    {
        Vector4 result = vec1 + vec2;
        REQUIRE(result.x() == 5.0f);
        REQUIRE(result.y() == 5.0f);
        REQUIRE(result.z() == 5.0f);
        REQUIRE(result.w() == 5.0f);
    }

    SECTION("Subtraction")
    {
        Vector4 result = vec1 - vec2;
        REQUIRE(result.x() == -3.0f);
        REQUIRE(result.y() == -1.0f);
        REQUIRE(result.z() == 1.0f);
        REQUIRE(result.w() == 3.0f);
    }

    SECTION("Hadamard product")
    {
        Vector4 result = vec1 * vec2;
        for (int32_t i = 0; i < 4; i++)
        {
            REQUIRE(result[i] == vec1[i] * vec2[i]);
        }
    }

    SECTION("Multiplication by Scalar")
    {
        Vector4 result = vec1 * 2.0f;
        REQUIRE(result.x() == 2.0f);
        REQUIRE(result.y() == 4.0f);
        REQUIRE(result.z() == 6.0f);
        REQUIRE(result.w() == 8.0f);
    }

    SECTION("Division by Scalar")
    {
        Vector4 result = vec1 / 2.0f;
        REQUIRE(result.x() == 0.5f);
        REQUIRE(result.y() == 1.0f);
        REQUIRE(result.z() == 1.5f);
        REQUIRE(result.w() == 2.0f);
    }
}

TEST_CASE("Vector4: Comparison Operator")
{
    Vector4 vec1(1.0f, 2.0f, 3.0f, 4.0f);
    Vector4 vec2(1.0f, 2.0f, 3.0f, 4.0f);
    Vector4 vec3(4.0f, 3.0f, 2.0f, 1.0f);

    SECTION("Equality")
    {
        REQUIRE(vec1 == vec2);
        REQUIRE_FALSE(vec1 == vec3);
    }
}

TEST_CASE("Vector4: Static Functions")
{
    Vector4 a(1.0f, 0.0f, 0.0f, 0.0f);
    Vector4 b(0.0f, 1.0f, 0.0f, 0.0f);

    SECTION("Dot Product")
    {
        REQUIRE(Vector4::dot(a, b) == 0.0f);
        REQUIRE(Vector4::dot(a, a) == 1.0f);
    }

    SECTION("Distance")
    {
        REQUIRE(std::abs(Vector4::distance(a, b) - sqrtf(2.0f)) < 1e-6f);
    }

    SECTION("Lerp")
    {
        Vector4 result = Vector4::lerp(a, b, 0.5f);
        REQUIRE(result.x() == 0.5f);
        REQUIRE(result.y() == 0.5f);
        REQUIRE(result.z() == 0.0f);
        REQUIRE(result.w() == 0.0f);
    }

    SECTION("Lerp Unclamped")
    {
        Vector4 result = Vector4::lerp_unclamped(a, b, 1.5f);
        REQUIRE(result.x() == -0.5f);
        REQUIRE(result.y() == 1.5f);
    }

    SECTION("Max")
    {
        Vector4 result = Vector4::max(a, b);
        REQUIRE(result.x() == 1.0f);
        REQUIRE(result.y() == 1.0f);
    }

    SECTION("Min")
    {
        Vector4 result = Vector4::min(a, b);
        REQUIRE(result.x() == 0.0f);
        REQUIRE(result.y() == 0.0f);
    }

    SECTION("Project")
    {
        Vector4 result = Vector4::project(a, b);
        REQUIRE(result.x() == 0.0f);
        REQUIRE(result.y() == 0.0f);
    }
}
