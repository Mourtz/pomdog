// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#include <Pomdog/Math/Matrix3x3.hpp>
#include <Pomdog/Math/Vector2.hpp>
#include <Pomdog/Math/Vector3.hpp>
#include <Pomdog/Math/Radian.hpp>
#include <gtest/iutest_switch.hpp>

using Pomdog::Matrix3x3;
using Pomdog::Vector2;
using Pomdog::Vector3;

namespace {

static constexpr auto Epsilon = std::numeric_limits<float>::epsilon();

}// unused namespace

TEST(Matrix3x3, FirstTestCase)
{
    Matrix3x3 matrix {
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f
    };
    EXPECT_EQ(1.0f, matrix(0, 0));
    EXPECT_EQ(1.0f, matrix(0, 1));
    EXPECT_EQ(1.0f, matrix(0, 2));
    EXPECT_EQ(1.0f, matrix(1, 0));
    EXPECT_EQ(1.0f, matrix(1, 1));
    EXPECT_EQ(1.0f, matrix(1, 2));
    EXPECT_EQ(1.0f, matrix(2, 0));
    EXPECT_EQ(1.0f, matrix(2, 1));
    EXPECT_EQ(1.0f, matrix(2, 2));

    matrix = Matrix3x3 {
        0.0f, 1.0f, 2.0f,
        3.0f, 4.0f, 5.0f,
        6.0f, 7.0f, 8.0f
    };
    EXPECT_EQ(0.0f, matrix(0, 0));
    EXPECT_EQ(1.0f, matrix(0, 1));
    EXPECT_EQ(2.0f, matrix(0, 2));
    EXPECT_EQ(3.0f, matrix(1, 0));
    EXPECT_EQ(4.0f, matrix(1, 1));
    EXPECT_EQ(5.0f, matrix(1, 2));
    EXPECT_EQ(6.0f, matrix(2, 0));
    EXPECT_EQ(7.0f, matrix(2, 1));
    EXPECT_EQ(8.0f, matrix(2, 2));
}

TEST(Matrix3x3, Identity)
{
    EXPECT_EQ(1.0f, Matrix3x3::Identity(0, 0));
    EXPECT_EQ(0.0f, Matrix3x3::Identity(0, 1));
    EXPECT_EQ(0.0f, Matrix3x3::Identity(0, 2));
    EXPECT_EQ(0.0f, Matrix3x3::Identity(1, 0));
    EXPECT_EQ(1.0f, Matrix3x3::Identity(1, 1));
    EXPECT_EQ(0.0f, Matrix3x3::Identity(1, 2));
    EXPECT_EQ(0.0f, Matrix3x3::Identity(2, 0));
    EXPECT_EQ(0.0f, Matrix3x3::Identity(2, 1));
    EXPECT_EQ(1.0f, Matrix3x3::Identity(2, 2));

    Matrix3x3 matrix = Matrix3x3::Identity;
    EXPECT_EQ(1.0f, matrix(0, 0));
    EXPECT_EQ(0.0f, matrix(0, 1));
    EXPECT_EQ(0.0f, matrix(0, 2));
    EXPECT_EQ(0.0f, matrix(1, 0));
    EXPECT_EQ(1.0f, matrix(1, 1));
    EXPECT_EQ(0.0f, matrix(1, 2));
    EXPECT_EQ(0.0f, matrix(2, 0));
    EXPECT_EQ(0.0f, matrix(2, 1));
    EXPECT_EQ(1.0f, matrix(2, 2));
}

TEST(Matrix3x3, CreateTranslation)
{
    auto matrix = Matrix3x3::CreateTranslation({3.0f, 4.0f});
    EXPECT_EQ(1.0f, matrix(0, 0));
    EXPECT_EQ(0.0f, matrix(0, 1));
    EXPECT_EQ(0.0f, matrix(0, 2));
    EXPECT_EQ(0.0f, matrix(1, 0));
    EXPECT_EQ(1.0f, matrix(1, 1));
    EXPECT_EQ(0.0f, matrix(1, 2));
    EXPECT_EQ(3.0f, matrix(2, 0));
    EXPECT_EQ(4.0f, matrix(2, 1));
    EXPECT_EQ(1.0f, matrix(2, 2));
}

TEST(Matrix3x3, CreateScale)
{
    auto matrix = Matrix3x3::CreateScale({3.0f, 4.0f, 5.0f});
    EXPECT_EQ(3.0f, matrix(0, 0));
    EXPECT_EQ(0.0f, matrix(0, 1));
    EXPECT_EQ(0.0f, matrix(0, 2));
    EXPECT_EQ(0.0f, matrix(1, 0));
    EXPECT_EQ(4.0f, matrix(1, 1));
    EXPECT_EQ(0.0f, matrix(1, 2));
    EXPECT_EQ(0.0f, matrix(2, 0));
    EXPECT_EQ(0.0f, matrix(2, 1));
    EXPECT_EQ(5.0f, matrix(2, 2));

    matrix = Matrix3x3::CreateScale(7.0f);
    EXPECT_EQ(7.0f, matrix(0, 0));
    EXPECT_EQ(0.0f, matrix(0, 1));
    EXPECT_EQ(0.0f, matrix(0, 2));
    EXPECT_EQ(0.0f, matrix(1, 0));
    EXPECT_EQ(7.0f, matrix(1, 1));
    EXPECT_EQ(0.0f, matrix(1, 2));
    EXPECT_EQ(0.0f, matrix(2, 0));
    EXPECT_EQ(0.0f, matrix(2, 1));
    EXPECT_EQ(7.0f, matrix(2, 2));
}

TEST(Matrix3x3, CreateRotationX)
{
    auto matrix = Matrix3x3::CreateRotationX(3.0f);
    EXPECT_NEAR(std::cos(3.0f), matrix(1, 1), Epsilon);
    EXPECT_NEAR(std::sin(3.0f), matrix(1, 2), Epsilon);
    EXPECT_NEAR(-std::sin(3.0f), matrix(2, 1), Epsilon);
    EXPECT_NEAR(std::cos(3.0f), matrix(2, 2), Epsilon);

    EXPECT_EQ(1.0f, matrix(0, 0));
    EXPECT_EQ(0.0f, matrix(0, 1));
    EXPECT_EQ(0.0f, matrix(0, 2));
    EXPECT_EQ(0.0f, matrix(1, 0));
    EXPECT_EQ(0.0f, matrix(2, 0));
}

TEST(Matrix3x3, CreateRotationY)
{
    auto matrix = Matrix3x3::CreateRotationY(3.0f);
    EXPECT_NEAR(std::cos(3.0f), matrix(0, 0), Epsilon);
    EXPECT_NEAR(-std::sin(3.0f), matrix(0, 2), Epsilon);
    EXPECT_NEAR(std::sin(3.0f), matrix(2, 0), Epsilon);
    EXPECT_NEAR(std::cos(3.0f), matrix(2, 2), Epsilon);

    EXPECT_EQ(0.0f, matrix(0, 1));
    EXPECT_EQ(0.0f, matrix(1, 0));
    EXPECT_EQ(1.0f, matrix(1, 1));
    EXPECT_EQ(0.0f, matrix(1, 2));
    EXPECT_EQ(0.0f, matrix(2, 1));
}

TEST(Matrix3x3, CreateRotationZ)
{
    auto matrix = Matrix3x3::CreateRotationZ(3.0f);
    EXPECT_NEAR(std::cos(3.0f), matrix(0, 0), Epsilon);
    EXPECT_NEAR(std::sin(3.0f), matrix(0, 1), Epsilon);
    EXPECT_NEAR(-std::sin(3.0f), matrix(1, 0), Epsilon);
    EXPECT_NEAR(std::cos(3.0f), matrix(1, 1), Epsilon);

    EXPECT_EQ(0.0f, matrix(0, 2));
    EXPECT_EQ(0.0f, matrix(1, 2));
    EXPECT_EQ(0.0f, matrix(2, 0));
    EXPECT_EQ(0.0f, matrix(2, 1));
    EXPECT_EQ(1.0f, matrix(2, 2));
}
