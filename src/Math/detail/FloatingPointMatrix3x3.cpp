// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#include "Pomdog/Math/detail/FloatingPointMatrix3x3.hpp"
#include "Pomdog/Math/detail/FloatingPointMatrix2x2.hpp"
#include "Pomdog/Math/detail/FloatingPointQuaternion.hpp"
#include "Pomdog/Math/detail/FloatingPointVector2.hpp"
#include "Pomdog/Math/detail/FloatingPointVector3.hpp"
#include "Pomdog/Math/Radian.hpp"
#include "Pomdog/Utility/Assert.hpp"
#include <cmath>
#include <limits>
#include <utility>

namespace Pomdog {
namespace Detail {

template <typename T>
FloatingPointMatrix3x3<T> const FloatingPointMatrix3x3<T>::Identity = {
    1, 0, 0,
    0, 1, 0,
    0, 0, 1};
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix3x3<T>::FloatingPointMatrix3x3(
    T m00, T m01, T m02,
    T m10, T m11, T m12,
    T m20, T m21, T m22) noexcept
{
    m[0][0] = m00;
    m[0][1] = m01;
    m[0][2] = m02;
    m[1][0] = m10;
    m[1][1] = m11;
    m[1][2] = m12;
    m[2][0] = m20;
    m[2][1] = m21;
    m[2][2] = m22;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix3x3<T> & FloatingPointMatrix3x3<T>::operator*=(FloatingPointMatrix3x3 const& other)
{
    return *this = this->Concatenate(other);
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix3x3<T> & FloatingPointMatrix3x3<T>::operator+=(FloatingPointMatrix3x3 const& other)
{
    m[0][0] += other.m[0][0];
    m[0][1] += other.m[0][1];
    m[0][2] += other.m[0][2];
    m[1][0] += other.m[1][0];
    m[1][1] += other.m[1][1];
    m[1][2] += other.m[1][2];
    m[2][0] += other.m[2][0];
    m[2][1] += other.m[2][1];
    m[2][2] += other.m[2][2];
    return *this;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix3x3<T> & FloatingPointMatrix3x3<T>::operator-=(FloatingPointMatrix3x3 const& other)
{
    m[0][0] -= other.m[0][0];
    m[0][1] -= other.m[0][1];
    m[0][2] -= other.m[0][2];
    m[1][0] -= other.m[1][0];
    m[1][1] -= other.m[1][1];
    m[1][2] -= other.m[1][2];
    m[2][0] -= other.m[2][0];
    m[2][1] -= other.m[2][1];
    m[2][2] -= other.m[2][2];
    return *this;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix3x3<T> & FloatingPointMatrix3x3<T>::operator*=(T scaleFactor)
{
    m[0][0] *= scaleFactor;
    m[0][1] *= scaleFactor;
    m[0][2] *= scaleFactor;
    m[1][0] *= scaleFactor;
    m[1][1] *= scaleFactor;
    m[1][2] *= scaleFactor;
    m[2][0] *= scaleFactor;
    m[2][1] *= scaleFactor;
    m[2][2] *= scaleFactor;
    return *this;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix3x3<T> & FloatingPointMatrix3x3<T>::operator/=(T scaleFactor)
{
    auto const inverseDivider = T{1} / scaleFactor;
    m[0][0] *= inverseDivider;
    m[0][1] *= inverseDivider;
    m[0][2] *= inverseDivider;
    m[1][0] *= inverseDivider;
    m[1][1] *= inverseDivider;
    m[1][2] *= inverseDivider;
    m[2][0] *= inverseDivider;
    m[2][1] *= inverseDivider;
    m[2][2] *= inverseDivider;
    return *this;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix3x3<T> FloatingPointMatrix3x3<T>::operator+() const
{
    return *this;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix3x3<T> FloatingPointMatrix3x3<T>::operator-() const
{
    return this->Concatenate(T{-1});
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix3x3<T> FloatingPointMatrix3x3<T>::operator+(FloatingPointMatrix3x3 const& other) const
{
    return {
        m[0][0] + other.m[0][0],
        m[0][1] + other.m[0][1],
        m[0][2] + other.m[0][2],
        m[1][0] + other.m[1][0],
        m[1][1] + other.m[1][1],
        m[1][2] + other.m[1][2],
        m[2][0] + other.m[2][0],
        m[2][1] + other.m[2][1],
        m[2][2] + other.m[2][2]};
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix3x3<T> FloatingPointMatrix3x3<T>::operator-(FloatingPointMatrix3x3 const& other) const
{
    return {
        m[0][0] - other.m[0][0],
        m[0][1] - other.m[0][1],
        m[0][2] - other.m[0][2],
        m[1][0] - other.m[1][0],
        m[1][1] - other.m[1][1],
        m[1][2] - other.m[1][2],
        m[2][0] - other.m[2][0],
        m[2][1] - other.m[2][1],
        m[2][2] - other.m[2][2]};
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix3x3<T> FloatingPointMatrix3x3<T>::operator*(FloatingPointMatrix3x3 const& other) const
{
    return this->Concatenate(other);
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix3x3<T> FloatingPointMatrix3x3<T>::operator*(T scaleFactor) const
{
    return this->Concatenate(scaleFactor);
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix3x3<T> FloatingPointMatrix3x3<T>::operator/(T scaleFactor) const
{
    POMDOG_ASSERT(scaleFactor != T{0});
    auto const inverseDivider = T{1} / scaleFactor;
    return {
        m[0][0] * inverseDivider,
        m[0][1] * inverseDivider,
        m[0][2] * inverseDivider,
        m[1][0] * inverseDivider,
        m[1][1] * inverseDivider,
        m[1][2] * inverseDivider,
        m[2][0] * inverseDivider,
        m[2][1] * inverseDivider,
        m[2][2] * inverseDivider};
}
//-----------------------------------------------------------------------
template <typename T>
bool FloatingPointMatrix3x3<T>::operator==(FloatingPointMatrix3x3 const& other) const
{
    return m[0][0] == other.m[0][0] && m[0][1] == other.m[0][1] && m[0][2] == other.m[0][2]
        && m[1][0] == other.m[1][0] && m[1][1] == other.m[1][1] && m[1][2] == other.m[1][2]
        && m[2][0] == other.m[2][0] && m[2][1] == other.m[2][1] && m[2][2] == other.m[2][2];
}
//-----------------------------------------------------------------------
template <typename T>
bool FloatingPointMatrix3x3<T>::operator!=(FloatingPointMatrix3x3 const& other) const
{
    return m[0][0] != other.m[0][0] || m[0][1] != other.m[0][1] || m[0][2] != other.m[0][2]
        || m[1][0] != other.m[1][0] || m[1][1] != other.m[1][1] || m[1][2] != other.m[1][2]
        || m[2][0] != other.m[2][0] || m[2][1] != other.m[2][1] || m[2][2] != other.m[2][2];
}
//-----------------------------------------------------------------------
template <typename T>
T & FloatingPointMatrix3x3<T>::operator()(std::size_t row, std::size_t column)
{
    POMDOG_ASSERT_MESSAGE(row < RowSize, "row: out of range");
    POMDOG_ASSERT_MESSAGE(column < ColumnSize, "column: out of range");
    return m[row][column];
}
//-----------------------------------------------------------------------
template <typename T>
T const& FloatingPointMatrix3x3<T>::operator()(std::size_t row, std::size_t column) const
{
    POMDOG_ASSERT_MESSAGE(row < RowSize, "row: out of range");
    POMDOG_ASSERT_MESSAGE(column < ColumnSize, "column: out of range");
    return m[row][column];
}
//-----------------------------------------------------------------------
//template <typename T>
//std::array<T, 3> const& FloatingPointMatrix3x3<T>::operator[](std::size_t row) const
//{
//    POMDOG_ASSERT_MESSAGE(row < RowSize, "FloatingPointMatrix3x3, subscript out of range");
//    return m[row];
//}
//-----------------------------------------------------------------------
//template <typename T>
//std::array<T, 3> & FloatingPointMatrix3x3<T>::operator[](std::size_t row)
//{
//    POMDOG_ASSERT_MESSAGE(row < RowSize, "FloatingPointMatrix3x3, subscript out of range");
//    return m[row];
//}
//-----------------------------------------------------------------------
template <typename T>
void FloatingPointMatrix3x3<T>::SetScale(FloatingPointVector3<T> const& scale)
{
    m[0][0] = scale.X;
    m[1][1] = scale.Y;
    m[2][2] = scale.Z;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointVector3<T> FloatingPointMatrix3x3<T>::GetScale() const
{
    return {m[0][0], m[1][1], m[2][2]};
}
//-----------------------------------------------------------------------
template <typename T>
T FloatingPointMatrix3x3<T>::Determinant() const
{
    // | m00 m01 m02 | determinant =
    // | m10 m11 m12 |   (m00 * m11 * m22) +(m10 * m21 * m02) +(m20 *01 * m12)
    // | m20 m21 m22 |  -(m02 * m11 * m20) -(m12 * m21 * m00) -(m22 *01 * m10)
    //
    //   cofactor00    cofactor01     cofactor02
    //    |m11 m12|     |m10 m12|      |m10 m11|
    // m00|m21 m22|  m01|m20 m22|   m02|m20 m21|

    auto const cofactor00 = m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]);
    auto const cofactor10 = m[0][1] * (m[1][2] * m[2][0] - m[1][0] * m[2][2]);
    auto const cofactor20 = m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);

    return cofactor00 + cofactor10 + cofactor20;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix3x3<T>
FloatingPointMatrix3x3<T>::Adjoint(FloatingPointMatrix3x3 const& matrix)
{
    return {
         matrix.Minor2x2(0, 0).Determinant(),
        -matrix.Minor2x2(1, 0).Determinant(),
         matrix.Minor2x2(2, 0).Determinant(),
        -matrix.Minor2x2(0, 1).Determinant(),
         matrix.Minor2x2(1, 1).Determinant(),
        -matrix.Minor2x2(2, 1).Determinant(),
         matrix.Minor2x2(0, 2).Determinant(),
        -matrix.Minor2x2(1, 2).Determinant(),
         matrix.Minor2x2(2, 2).Determinant()};
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix3x3<T> FloatingPointMatrix3x3<T>::Concatenate(FloatingPointMatrix3x3 const& other) const
{
    return {
        m[0][0] * other.m[0][0] + m[0][1] * other.m[1][0] + m[0][2] * other.m[2][0],
        m[0][0] * other.m[0][1] + m[0][1] * other.m[1][1] + m[0][2] * other.m[2][1],
        m[0][0] * other.m[0][2] + m[0][1] * other.m[1][2] + m[0][2] * other.m[2][2],
        m[1][0] * other.m[0][0] + m[1][1] * other.m[1][0] + m[1][2] * other.m[2][0],
        m[1][0] * other.m[0][1] + m[1][1] * other.m[1][1] + m[1][2] * other.m[2][1],
        m[1][0] * other.m[0][2] + m[1][1] * other.m[1][2] + m[1][2] * other.m[2][2],
        m[2][0] * other.m[0][0] + m[2][1] * other.m[1][0] + m[2][2] * other.m[2][0],
        m[2][0] * other.m[0][1] + m[2][1] * other.m[1][1] + m[2][2] * other.m[2][1],
        m[2][0] * other.m[0][2] + m[2][1] * other.m[1][2] + m[2][2] * other.m[2][2]};
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix3x3<T> FloatingPointMatrix3x3<T>::Concatenate(T scaleFactor) const
{
    return {
        m[0][0] * scaleFactor,
        m[0][1] * scaleFactor,
        m[0][2] * scaleFactor,
        m[1][0] * scaleFactor,
        m[1][1] * scaleFactor,
        m[1][2] * scaleFactor,
        m[2][0] * scaleFactor,
        m[2][1] * scaleFactor,
        m[2][2] * scaleFactor};
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix2x2<T> FloatingPointMatrix3x3<T>::Minor2x2(std::size_t row, std::size_t column) const
{
    //   Matrix3x3 mat                     Matrix2x2 minor
    //     c0  c1  c2
    // r0 |11, 12, 13|                       |11, 13, x|
    // r1 |21, 22, 23| Minor2x2(mat, r2, c1) |21, 23. x|
    // r2 |31, 32, 33| --------------------> | x,  x, x|

    FloatingPointMatrix2x2<T> minor;
    for (std::size_t i = 0, s = 0; i < RowSize; ++i)
    {
        if (row == i) {
            continue;
        }

        for (std::size_t j = 0, t = 0; j < ColumnSize; ++j)
        {
            if (column == j) {
                continue;
            }

            POMDOG_ASSERT(s < 2);
            POMDOG_ASSERT(t < 2);
            minor(s, t) = m[i][j];
            ++t;
        }
        ++s;
    }
    return std::move(minor);
}
//-----------------------------------------------------------------------
template <typename T>
void
FloatingPointMatrix3x3<T>::Transpose(FloatingPointMatrix3x3 const& matrix, FloatingPointMatrix3x3 & result)
{
    result = {
        matrix.m[0][0], matrix.m[1][0], matrix.m[2][0],
        matrix.m[0][1], matrix.m[1][1], matrix.m[2][1],
        matrix.m[0][2], matrix.m[1][2], matrix.m[2][2]};
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix3x3<T>
FloatingPointMatrix3x3<T>::Transpose(FloatingPointMatrix3x3 const& matrix)
{
    return {
        matrix.m[0][0], matrix.m[1][0], matrix.m[2][0],
        matrix.m[0][1], matrix.m[1][1], matrix.m[2][1],
        matrix.m[0][2], matrix.m[1][2], matrix.m[2][2]};
}
//-----------------------------------------------------------------------
template <typename T>
void
FloatingPointMatrix3x3<T>::Invert(FloatingPointMatrix3x3 const& matrix, FloatingPointMatrix3x3 & result)
{
    result = Invert(matrix);
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix3x3<T>
FloatingPointMatrix3x3<T>::Invert(FloatingPointMatrix3x3 const& matrix)
{
    auto const determinant = matrix.Determinant();
    static_assert(std::is_same<decltype(matrix.Determinant()), T>::value, "determinant is T");
    POMDOG_ASSERT_MESSAGE(T{0} != determinant, "This is singular matrix");

    return Adjoint(matrix) / determinant;
}
//-----------------------------------------------------------------------
template <typename T>
void
FloatingPointMatrix3x3<T>::CreateTranslation(FloatingPointVector2<T> const& position, FloatingPointMatrix3x3 & result)
{
    result = Identity;
    result(2, 0) = position.X;
    result(2, 1) = position.Y;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix3x3<T>
FloatingPointMatrix3x3<T>::CreateTranslation(FloatingPointVector2<T> const& position)
{
    FloatingPointMatrix3x3 result;
    CreateTranslation(position, result);
    return std::move(result);
}
//-----------------------------------------------------------------------
template <typename T>
void
FloatingPointMatrix3x3<T>::CreateScale(T scale, FloatingPointMatrix3x3 & result)
{
    result.m[0][0] = scale;
    result.m[0][1] = 0;
    result.m[0][2] = 0;
    result.m[1][0] = 0;
    result.m[1][1] = scale;
    result.m[1][2] = 0;
    result.m[2][0] = 0;
    result.m[2][1] = 0;
    result.m[2][2] = scale;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix3x3<T>
FloatingPointMatrix3x3<T>::CreateScale(T scale)
{
    FloatingPointMatrix3x3 result;
    CreateScale(scale, result);
    return std::move(result);
}
//-----------------------------------------------------------------------
template <typename T>
void
FloatingPointMatrix3x3<T>::CreateScale(FloatingPointVector3<T> const& scale, FloatingPointMatrix3x3 & result)
{
    static_assert(std::is_same<T, decltype(scale.X)>::value, "scale is T");
    static_assert(std::is_same<T, decltype(scale.Y)>::value, "scale is T");
    static_assert(std::is_same<T, decltype(scale.Z)>::value, "scale is T");

    result.m[0][0] = scale.X;
    result.m[0][1] = 0;
    result.m[0][2] = 0;
    result.m[1][0] = 0;
    result.m[1][1] = scale.Y;
    result.m[1][2] = 0;
    result.m[2][0] = 0;
    result.m[2][1] = 0;
    result.m[2][2] = scale.Z;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix3x3<T>
FloatingPointMatrix3x3<T>::CreateScale(FloatingPointVector3<T> const& scale)
{
    FloatingPointMatrix3x3 result;
    CreateScale(scale, result);
    return std::move(result);
}
//-----------------------------------------------------------------------
template <typename T>
void
FloatingPointMatrix3x3<T>::CreateRotationX(Radian<T> const& angle, FloatingPointMatrix3x3 & result)
{
    static_assert(std::is_same<T, decltype(angle.value)>::value, "The angle value is T");
    auto const sinAngle = std::sin(angle.value);
    auto const cosAngle = std::cos(angle.value);

    result.m[0][0] = 1;
    result.m[0][1] = 0;
    result.m[0][2] = 0;
    result.m[1][0] = 0;
    result.m[1][1] = cosAngle;
    result.m[1][2] = sinAngle;
    result.m[2][0] = 0;
    result.m[2][1] = -sinAngle;
    result.m[2][2] = cosAngle;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix3x3<T>
FloatingPointMatrix3x3<T>::CreateRotationX(Radian<T> const& angle)
{
    FloatingPointMatrix3x3 result;
    CreateRotationX(angle, result);
    return std::move(result);
}
//-----------------------------------------------------------------------
template <typename T>
void
FloatingPointMatrix3x3<T>::CreateRotationY(Radian<T> const& angle, FloatingPointMatrix3x3 & result)
{
    static_assert(std::is_same<T, decltype(angle.value)>::value, "The angle value is T");
    auto const sinAngle = std::sin(angle.value);
    auto const cosAngle = std::cos(angle.value);

    result.m[0][0] = cosAngle;
    result.m[0][1] = 0;
    result.m[0][2] = -sinAngle;
    result.m[1][0] = 0;
    result.m[1][1] = 1;
    result.m[1][2] = 0;
    result.m[2][0] = sinAngle;
    result.m[2][1] = 0;
    result.m[2][2] = cosAngle;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix3x3<T>
FloatingPointMatrix3x3<T>::CreateRotationY(Radian<T> const& angle)
{
    FloatingPointMatrix3x3 result;
    CreateRotationY(angle, result);
    return std::move(result);
}
//-----------------------------------------------------------------------
template <typename T>
void
FloatingPointMatrix3x3<T>::CreateRotationZ(Radian<T> const& angle, FloatingPointMatrix3x3 & result)
{
    static_assert(std::is_same<T, decltype(angle.value)>::value, "angle is T");
    auto const sinAngle = std::sin(angle.value);
    auto const cosAngle = std::cos(angle.value);

    result.m[0][0] = cosAngle;
    result.m[0][1] = sinAngle;
    result.m[0][2] = 0;
    result.m[1][0] = -sinAngle;
    result.m[1][1] = cosAngle;
    result.m[1][2] = 0;
    result.m[2][0] = 0;
    result.m[2][1] = 0;
    result.m[2][2] = 1;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix3x3<T>
FloatingPointMatrix3x3<T>::CreateRotationZ(Radian<T> const& angle)
{
    FloatingPointMatrix3x3 result;
    CreateRotationZ(angle, result);
    return std::move(result);
}
//-----------------------------------------------------------------------
template <typename T>
void
FloatingPointMatrix3x3<T>::CreateFromQuaternion(FloatingPointQuaternion<T> const& quaternion, FloatingPointMatrix3x3 & result)
{
    auto const xx = quaternion.X * quaternion.X;
    auto const yy = quaternion.Y * quaternion.Y;
    auto const zz = quaternion.Z * quaternion.Z;
    auto const xy = quaternion.X * quaternion.Y;
    auto const zw = quaternion.Z * quaternion.W;
    auto const zx = quaternion.Z * quaternion.X;
    auto const yw = quaternion.Y * quaternion.W;
    auto const yz = quaternion.Y * quaternion.Z;
    auto const xw = quaternion.X * quaternion.W;

    result.m[0][0] = 1 - (2 * (yy + zz));
    result.m[0][1] = 2 * (xy + zw);
    result.m[0][2] = 2 * (zx - yw);
    result.m[1][0] = 2 * (xy - zw);
    result.m[1][1] = 1 - (2 * (zz + xx));
    result.m[1][2] = 2 * (yz + xw);
    result.m[2][0] = 2 * (zx + yw);
    result.m[2][1] = 2 * (yz - xw);
    result.m[2][2] = 1 - (2 * (yy + xx));
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix3x3<T>
FloatingPointMatrix3x3<T>::CreateFromQuaternion(FloatingPointQuaternion<T> const& quaternion)
{
    FloatingPointMatrix3x3 result;
    CreateFromQuaternion(quaternion, result);
    return std::move(result);
}
//-----------------------------------------------------------------------
template <typename T>
void
FloatingPointMatrix3x3<T>::CreateLerp(FloatingPointMatrix3x3 const& source1,
    FloatingPointMatrix3x3 const& source2, T amount, FloatingPointMatrix3x3 & result)
{
    result.m[0][0] = source1.m[0][0] + ((source2.m[0][0] - source1.m[0][0]) * amount);
    result.m[0][1] = source1.m[0][1] + ((source2.m[0][1] - source1.m[0][1]) * amount);
    result.m[0][2] = source1.m[0][2] + ((source2.m[0][2] - source1.m[0][2]) * amount);
    result.m[1][0] = source1.m[1][0] + ((source2.m[1][0] - source1.m[1][0]) * amount);
    result.m[1][1] = source1.m[1][1] + ((source2.m[1][1] - source1.m[1][1]) * amount);
    result.m[1][2] = source1.m[1][2] + ((source2.m[1][2] - source1.m[1][2]) * amount);
    result.m[2][0] = source1.m[2][0] + ((source2.m[2][0] - source1.m[2][0]) * amount);
    result.m[2][1] = source1.m[2][1] + ((source2.m[2][1] - source1.m[2][1]) * amount);
    result.m[2][2] = source1.m[2][2] + ((source2.m[2][2] - source1.m[2][2]) * amount);
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix3x3<T>
FloatingPointMatrix3x3<T>::CreateLerp(FloatingPointMatrix3x3 const& source1,
    FloatingPointMatrix3x3 const& source2, T amount)
{
    FloatingPointMatrix3x3 result;
    CreateLerp(source1, source2, amount, result);
    return std::move(result);
}
//-----------------------------------------------------------------------
template <typename T>
void
FloatingPointMatrix3x3<T>::CreateFromAxisAngle(FloatingPointVector3<T> const& axis,
    Radian<T> const& angle, FloatingPointMatrix3x3 & result)
{
    auto const sinAngle = std::sin(angle.value);
    auto const cosAngle = std::cos(angle.value);

    auto const t  = T{1} - cosAngle;
    auto const xx = axis.X * axis.X;
    auto const yy = axis.Y * axis.Y;
    auto const zz = axis.Z * axis.Z;
    auto const xy = axis.X * axis.Y;
    auto const xz = axis.X * axis.Z;
    auto const yz = axis.Y * axis.Z;

    //axis.Normalize();

    result.m[0][0] = t * xx + cosAngle;
    result.m[0][1] = t * xy + sinAngle * axis.Z;
    result.m[0][2] = t * xz - sinAngle * axis.Y;
    result.m[1][0] = t * xy - sinAngle * axis.Z;
    result.m[1][1] = t * yy + cosAngle;
    result.m[1][2] = t * yz + sinAngle * axis.X;
    result.m[2][0] = t * xz + sinAngle * axis.Y;
    result.m[2][1] = t * yz - sinAngle * axis.X;
    result.m[2][2] = t * zz + cosAngle;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix3x3<T>
FloatingPointMatrix3x3<T>::CreateFromAxisAngle(FloatingPointVector3<T> const& axis, Radian<T> const& angle)
{
    FloatingPointMatrix3x3 result;
    CreateFromAxisAngle(axis, angle, result);
    return std::move(result);
}
//-----------------------------------------------------------------------
template <typename T>
T const* FloatingPointMatrix3x3<T>::Data() const noexcept
{
    static_assert(std::is_floating_point<T>::value, "T is floating point number");
    return m[0].data();
}
//-----------------------------------------------------------------------
template <typename T>
T* FloatingPointMatrix3x3<T>::Data() noexcept
{
    static_assert(std::is_floating_point<T>::value, "T is floating point number");
    return m[0].data();
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix3x3<T> operator*(T scaleFactor, FloatingPointMatrix3x3<T> const& matrix)
{
    return matrix.Concatenate(scaleFactor);
}
//-----------------------------------------------------------------------
// explicit instantiations
template class FloatingPointMatrix3x3<float>;
template FloatingPointMatrix3x3<float> operator*<float>(float, FloatingPointMatrix3x3<float> const&);

#if defined(DBL_MANT_DIG)
template class FloatingPointMatrix3x3<double>;
template FloatingPointMatrix3x3<double> operator*<double>(double, FloatingPointMatrix3x3<double> const&);
#endif

#if defined(LDBL_MANT_DIG)
template class FloatingPointMatrix3x3<long double>;
template FloatingPointMatrix3x3<long double> operator*<long double>(long double, FloatingPointMatrix3x3<long double> const&);
#endif

} // namespace Detail
} // namespace Pomdog
