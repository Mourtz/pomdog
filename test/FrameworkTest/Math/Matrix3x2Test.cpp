﻿//
//  Copyright (C) 2013-2014 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#include <gtest/iutest_switch.hpp>
#include <Pomdog/Math/Matrix3x2.hpp>
#include <Pomdog/Math/Vector2.hpp>
#include <Pomdog/Math/Vector3.hpp>
#include <Pomdog/Math/Radian.hpp>

using Pomdog::Matrix3x2;
using Pomdog::Vector2;

namespace {

static constexpr auto Epsilon = std::numeric_limits<float>::epsilon();

}// unused namespace

TEST(Matrix3x2, FirstTestCase)
{
	Matrix3x2 matrix {
		1.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
	};
	EXPECT_EQ(1.0f, matrix(0, 0));
	EXPECT_EQ(1.0f, matrix(0, 1));
	EXPECT_EQ(1.0f, matrix(1, 0));
	EXPECT_EQ(1.0f, matrix(1, 1));
	EXPECT_EQ(1.0f, matrix(2, 0));
	EXPECT_EQ(1.0f, matrix(2, 1));
	
	matrix = Matrix3x2 {
		0.0f, 1.0f,
		3.0f, 4.0f,
		6.0f, 7.0f,
	};
	EXPECT_EQ(0.0f, matrix(0, 0));
	EXPECT_EQ(1.0f, matrix(0, 1));
	EXPECT_EQ(3.0f, matrix(1, 0));
	EXPECT_EQ(4.0f, matrix(1, 1));
	EXPECT_EQ(6.0f, matrix(2, 0));
	EXPECT_EQ(7.0f, matrix(2, 1));
}

TEST(Matrix3x2, Identity)
{
	EXPECT_EQ(1.0f, Matrix3x2::Identity(0, 0));
	EXPECT_EQ(0.0f, Matrix3x2::Identity(0, 1));
	EXPECT_EQ(0.0f, Matrix3x2::Identity(1, 0));
	EXPECT_EQ(1.0f, Matrix3x2::Identity(1, 1));
	EXPECT_EQ(0.0f, Matrix3x2::Identity(2, 0));
	EXPECT_EQ(0.0f, Matrix3x2::Identity(2, 1));
	
	Matrix3x2 matrix = Matrix3x2::Identity;
	EXPECT_EQ(1.0f, matrix(0, 0));
	EXPECT_EQ(0.0f, matrix(0, 1));
	EXPECT_EQ(0.0f, matrix(1, 0));
	EXPECT_EQ(1.0f, matrix(1, 1));
	EXPECT_EQ(0.0f, matrix(2, 0));
	EXPECT_EQ(0.0f, matrix(2, 1));
}

TEST(Matrix3x2, Add)
{
	auto matrix1 = Matrix3x2::CreateTranslation({3.0f, 4.0f});
	auto matrix2 = Matrix3x2::CreateTranslation({5.0f, 2.0f});
	
	auto matrix = matrix1 + matrix2;
	EXPECT_EQ(2.0f, matrix(0, 0));
	EXPECT_EQ(0.0f, matrix(0, 1));
	EXPECT_EQ(0.0f, matrix(1, 0));
	EXPECT_EQ(2.0f, matrix(1, 1));
	EXPECT_EQ(8.0f, matrix(2, 0));
	EXPECT_EQ(6.0f, matrix(2, 1));
}

TEST(Matrix3x2, Subtract)
{
	auto matrix1 = Matrix3x2::CreateTranslation({5.0f, 4.0f});
	auto matrix2 = Matrix3x2::CreateTranslation({2.0f, 3.0f});
	
	auto matrix = matrix1 - matrix2;
	EXPECT_EQ(0.0f, matrix(0, 0));
	EXPECT_EQ(0.0f, matrix(0, 1));
	EXPECT_EQ(0.0f, matrix(1, 0));
	EXPECT_EQ(0.0f, matrix(1, 1));
	EXPECT_EQ(3.0f, matrix(2, 0));
	EXPECT_EQ(1.0f, matrix(2, 1));
}

TEST(Matrix3x2, CreateTranslation)
{
	auto matrix = Matrix3x2::CreateTranslation({3.0f, 4.0f});
	EXPECT_EQ(1.0f, matrix(0, 0));
	EXPECT_EQ(0.0f, matrix(0, 1));
	EXPECT_EQ(0.0f, matrix(1, 0));
	EXPECT_EQ(1.0f, matrix(1, 1));
	EXPECT_EQ(3.0f, matrix(2, 0));
	EXPECT_EQ(4.0f, matrix(2, 1));
}

TEST(Matrix3x2, CreateScale)
{
	auto matrix = Matrix3x2::CreateScale({3.0f, 4.0f});
	EXPECT_EQ(3.0f, matrix(0, 0));
	EXPECT_EQ(0.0f, matrix(0, 1));
	EXPECT_EQ(0.0f, matrix(1, 0));
	EXPECT_EQ(4.0f, matrix(1, 1));
	EXPECT_EQ(0.0f, matrix(2, 0));
	EXPECT_EQ(0.0f, matrix(2, 1));
	
	matrix = Matrix3x2::CreateScale(7.0f);
	EXPECT_EQ(7.0f, matrix(0, 0));
	EXPECT_EQ(0.0f, matrix(0, 1));
	EXPECT_EQ(0.0f, matrix(1, 0));
	EXPECT_EQ(7.0f, matrix(1, 1));
	EXPECT_EQ(0.0f, matrix(2, 0));
	EXPECT_EQ(0.0f, matrix(2, 1));
}

TEST(Matrix3x2, CreateRotation)
{
	auto matrix = Matrix3x2::CreateRotation(3.0f);
	EXPECT_NEAR(std::cos(3.0f), matrix(0, 0), Epsilon);
	EXPECT_NEAR(std::sin(3.0f), matrix(0, 1), Epsilon);
	EXPECT_NEAR(-std::sin(3.0f), matrix(1, 0), Epsilon);
	EXPECT_NEAR(std::cos(3.0f), matrix(1, 1), Epsilon);
	EXPECT_EQ(0.0f, matrix(2, 0));
	EXPECT_EQ(0.0f, matrix(2, 1));
}

TEST(Matrix3x2, CreateSkew)
{
	auto matrix = Matrix3x2::CreateSkew({3.0f, 4.0f});
	EXPECT_EQ(1.0f, matrix(0, 0));
	EXPECT_EQ(1.0f, matrix(1, 1));
	EXPECT_NEAR(std::tan(4.0f), matrix(0, 1), Epsilon);
	EXPECT_NEAR(std::tan(3.0f), matrix(1, 0), Epsilon);
	EXPECT_EQ(0.0f, matrix(2, 0));
	EXPECT_EQ(0.0f, matrix(2, 1));
}