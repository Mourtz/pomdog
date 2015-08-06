// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#include <Pomdog/Math/MathHelper.hpp>
#include <gtest/iutest_switch.hpp>

namespace MathHelper = Pomdog::MathHelper;

TEST(MathHelper, Constants)
{
    namespace Math = Pomdog::Math;
    EXPECT_EQ(Math::Pi<double>,         3.14159265358979323846);
    EXPECT_EQ(Math::TwoPi<double>,      6.28318530717958647692);
    EXPECT_EQ(Math::OneOverPi<double>,  0.31830988618379067154);
    EXPECT_EQ(Math::OneOver2Pi<double>, 0.15915494309189533576);
    EXPECT_EQ(Math::PiOver2<double>,    1.57079632679489661923);
    EXPECT_EQ(Math::PiOver4<double>,    0.78539816339744830962);
    EXPECT_EQ(Math::Pi<float>,         3.1415926535f);
    EXPECT_EQ(Math::TwoPi<float>,      6.2831853071f);
    EXPECT_EQ(Math::OneOverPi<float>,  0.3183098861f);
    EXPECT_EQ(Math::OneOver2Pi<float>, 0.1591549430f);
    EXPECT_EQ(Math::PiOver2<float>,    1.5707963267f);
    EXPECT_EQ(Math::PiOver4<float>,    0.7853981633f);
}

TEST(MathHelper, Clamp)
{
    EXPECT_EQ(0.0, MathHelper::Clamp(std::numeric_limits<double>::lowest(), 0.0, 1.0));
    EXPECT_EQ(0.0, MathHelper::Clamp(0.0, 0.0, 1.0));
    EXPECT_EQ(0.5, MathHelper::Clamp(0.5, 0.0, 1.0));
    EXPECT_EQ(1.0, MathHelper::Clamp(1.0, 0.0, 1.0));
    EXPECT_EQ(1.0, MathHelper::Clamp(std::numeric_limits<double>::max(), 0.0, 1.0));

    EXPECT_EQ(0.0f, MathHelper::Clamp(std::numeric_limits<float>::lowest(), 0.0f, 1.0f));
    EXPECT_EQ(0.0f, MathHelper::Clamp(0.0f, 0.0f, 1.0f));
    EXPECT_EQ(0.5f, MathHelper::Clamp(0.5f, 0.0f, 1.0f));
    EXPECT_EQ(1.0f, MathHelper::Clamp(1.0f, 0.0f, 1.0f));
    EXPECT_EQ(1.0f, MathHelper::Clamp(std::numeric_limits<float>::max(), 0.0f, 1.0f));

    EXPECT_EQ(-4.0f, MathHelper::Clamp(-4.3f, -4.0f, 5.0f));
    EXPECT_EQ(-2.5f, MathHelper::Clamp(-2.5f, -4.0f, 5.0f));
    EXPECT_EQ(0.0f, MathHelper::Clamp(0.0f, -4.0f, 5.0f));
    EXPECT_EQ(3.5f, MathHelper::Clamp(3.5f, -4.0f, 5.0f));
    EXPECT_EQ(5.0f, MathHelper::Clamp(5.7f, -4.0f, 5.0f));
}

TEST(MathHelper, Saturate)
{
    EXPECT_EQ(0.0, MathHelper::Saturate(std::numeric_limits<double>::lowest()));
    EXPECT_EQ(0.0, MathHelper::Saturate(-0.1));
    EXPECT_EQ(0.0, MathHelper::Saturate(0.0));
    EXPECT_EQ(0.1, MathHelper::Saturate(0.1));
    EXPECT_EQ(0.5, MathHelper::Saturate(0.5));
    EXPECT_EQ(0.9, MathHelper::Saturate(0.9));
    EXPECT_EQ(1.0, MathHelper::Saturate(1.0));
    EXPECT_EQ(1.0, MathHelper::Saturate(1.1));
    EXPECT_EQ(1.0, MathHelper::Saturate(std::numeric_limits<double>::max()));

    EXPECT_EQ(0.0f, MathHelper::Saturate(std::numeric_limits<float>::lowest()));
    EXPECT_EQ(0.0f, MathHelper::Saturate(-0.1f));
    EXPECT_EQ(0.0f, MathHelper::Saturate(0.0f));
    EXPECT_EQ(0.1f, MathHelper::Saturate(0.1f));
    EXPECT_EQ(0.5f, MathHelper::Saturate(0.5f));
    EXPECT_EQ(0.9f, MathHelper::Saturate(0.9f));
    EXPECT_EQ(1.0f, MathHelper::Saturate(1.0f));
    EXPECT_EQ(1.0f, MathHelper::Saturate(1.1f));
    EXPECT_EQ(1.0f, MathHelper::Saturate(std::numeric_limits<float>::max()));
}

TEST(MathHelper, Lerp)
{
    constexpr auto epsilon = std::numeric_limits<float>::epsilon();

    EXPECT_NEAR(0.0f, MathHelper::Lerp(0.0f, 1.0f, 0.0f), epsilon);
    EXPECT_NEAR(0.2f, MathHelper::Lerp(0.0f, 1.0f, 0.2f), epsilon);
    EXPECT_NEAR(0.5f, MathHelper::Lerp(0.0f, 1.0f, 0.5f), epsilon);
    EXPECT_NEAR(0.8f, MathHelper::Lerp(0.0f, 1.0f, 0.8f), epsilon);
    EXPECT_NEAR(1.0f, MathHelper::Lerp(0.0f, 1.0f, 1.0f), epsilon);

    EXPECT_NEAR(-1.0f, MathHelper::Lerp(-1.0f, 1.0f, 0.0f), epsilon);
    EXPECT_NEAR(-0.6f, MathHelper::Lerp(-1.0f, 1.0f, 0.2f), epsilon);
    EXPECT_NEAR(0.0f, MathHelper::Lerp(-1.0f, 1.0f, 0.5f), epsilon);
    EXPECT_NEAR(0.6f, MathHelper::Lerp(-1.0f, 1.0f, 0.8f), epsilon);
    EXPECT_NEAR(1.0f, MathHelper::Lerp(-1.0f, 1.0f, 1.0f), epsilon);

    EXPECT_NEAR(-0.5f, MathHelper::Lerp(-0.5f, 0.5f, 0.0f), epsilon);
    EXPECT_NEAR(-0.3f, MathHelper::Lerp(-0.5f, 0.5f, 0.2f), epsilon);
    EXPECT_NEAR(0.0f, MathHelper::Lerp(-0.5f, 0.5f, 0.5f), epsilon);
    EXPECT_NEAR(0.3f, MathHelper::Lerp(-0.5f, 0.5f, 0.8f), epsilon);
    EXPECT_NEAR(0.5f, MathHelper::Lerp(-0.5f, 0.5f, 1.0f), epsilon);

    EXPECT_LT(MathHelper::Lerp(0.0f, 1.0f, 0.0f), MathHelper::Lerp(0.0f, 1.0f, 0.1f));
    EXPECT_LT(MathHelper::Lerp(0.0f, 1.0f, 0.1f), MathHelper::Lerp(0.0f, 1.0f, 0.2f));
    EXPECT_LT(MathHelper::Lerp(0.0f, 1.0f, 0.2f), MathHelper::Lerp(0.0f, 1.0f, 0.3f));
    EXPECT_LT(MathHelper::Lerp(0.0f, 1.0f, 0.3f), MathHelper::Lerp(0.0f, 1.0f, 0.4f));
    EXPECT_LT(MathHelper::Lerp(0.0f, 1.0f, 0.4f), MathHelper::Lerp(0.0f, 1.0f, 0.5f));
    EXPECT_LT(MathHelper::Lerp(0.0f, 1.0f, 0.5f), MathHelper::Lerp(0.0f, 1.0f, 0.6f));
    EXPECT_LT(MathHelper::Lerp(0.0f, 1.0f, 0.6f), MathHelper::Lerp(0.0f, 1.0f, 0.7f));
    EXPECT_LT(MathHelper::Lerp(0.0f, 1.0f, 0.7f), MathHelper::Lerp(0.0f, 1.0f, 0.8f));
    EXPECT_LT(MathHelper::Lerp(0.0f, 1.0f, 0.8f), MathHelper::Lerp(0.0f, 1.0f, 0.9f));
    EXPECT_LT(MathHelper::Lerp(0.0f, 1.0f, 0.9f), MathHelper::Lerp(0.0f, 1.0f, 1.0f));
}

TEST(MathHelper, SmoothStep)
{
    constexpr auto epsilon = std::numeric_limits<float>::epsilon();

    EXPECT_NEAR(0.0f, MathHelper::SmoothStep(0.0f, 1.0f, 0.0f), epsilon);
    EXPECT_NEAR(0.5f, MathHelper::SmoothStep(0.0f, 1.0f, 0.5f), epsilon);
    EXPECT_NEAR(1.0f, MathHelper::SmoothStep(0.0f, 1.0f, 1.0f), epsilon);

    EXPECT_NEAR(-1.0f, MathHelper::SmoothStep(-1.0f, 1.0f, 0.0f), epsilon);
    EXPECT_NEAR(0.0f, MathHelper::SmoothStep(-1.0f, 1.0f, 0.5f), epsilon);
    EXPECT_NEAR(1.0f, MathHelper::SmoothStep(-1.0f, 1.0f, 1.0f), epsilon);

    EXPECT_NEAR(-0.5f, MathHelper::SmoothStep(-0.5f, 0.5f, 0.0f), epsilon);
    EXPECT_NEAR(0.0f, MathHelper::SmoothStep(-0.5f, 0.5f, 0.5f), epsilon);
    EXPECT_NEAR(0.5f, MathHelper::SmoothStep(-0.5f, 0.5f, 1.0f), epsilon);

    EXPECT_LT(MathHelper::SmoothStep(0.0f, 1.0f, 0.0f), MathHelper::SmoothStep(0.0f, 1.0f, 0.1f));
    EXPECT_LT(MathHelper::SmoothStep(0.0f, 1.0f, 0.1f), MathHelper::SmoothStep(0.0f, 1.0f, 0.2f));
    EXPECT_LT(MathHelper::SmoothStep(0.0f, 1.0f, 0.2f), MathHelper::SmoothStep(0.0f, 1.0f, 0.3f));
    EXPECT_LT(MathHelper::SmoothStep(0.0f, 1.0f, 0.3f), MathHelper::SmoothStep(0.0f, 1.0f, 0.4f));
    EXPECT_LT(MathHelper::SmoothStep(0.0f, 1.0f, 0.4f), MathHelper::SmoothStep(0.0f, 1.0f, 0.5f));
    EXPECT_LT(MathHelper::SmoothStep(0.0f, 1.0f, 0.5f), MathHelper::SmoothStep(0.0f, 1.0f, 0.6f));
    EXPECT_LT(MathHelper::SmoothStep(0.0f, 1.0f, 0.6f), MathHelper::SmoothStep(0.0f, 1.0f, 0.7f));
    EXPECT_LT(MathHelper::SmoothStep(0.0f, 1.0f, 0.7f), MathHelper::SmoothStep(0.0f, 1.0f, 0.8f));
    EXPECT_LT(MathHelper::SmoothStep(0.0f, 1.0f, 0.8f), MathHelper::SmoothStep(0.0f, 1.0f, 0.9f));
    EXPECT_LT(MathHelper::SmoothStep(0.0f, 1.0f, 0.9f), MathHelper::SmoothStep(0.0f, 1.0f, 1.0f));
}
