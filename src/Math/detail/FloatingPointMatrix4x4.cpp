﻿//
//  Copyright (C) 2013 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#include <pomdog/Math/detail/FloatingPointMatrix4x4.hpp>
#include <pomdog/Utility/Assert.hpp>
#include <cmath>
#include <limits>
#include <pomdog/Math/detail/FloatingPointMatrix3x3.hpp>
#include <pomdog/Math/detail/FloatingPointQuaternion.hpp>
#include <pomdog/Math/detail/FloatingPointVector3.hpp>

namespace Pomdog {
namespace Details {

//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix4x4<T>::FloatingPointMatrix4x4(
	T m00, T m01, T m02, T m03,
	T m10, T m11, T m12, T m13,
	T m20, T m21, T m22, T m23,
	T m30, T m31, T m32, T m33)
{
	m[0][0] = m00;
	m[0][1] = m01;
	m[0][2] = m02;
	m[0][3] = m03;
	m[1][0] = m10;
	m[1][1] = m11;
	m[1][2] = m12;
	m[1][3] = m13;
	m[2][0] = m20;
	m[2][1] = m21;
	m[2][2] = m22;
	m[2][3] = m23;
	m[3][0] = m30;
	m[3][1] = m31;
	m[3][2] = m32;
	m[3][3] = m33;
}
//-----------------------------------------------------------------------
template <typename T>
T const& FloatingPointMatrix4x4<T>::operator()(std::size_t row, std::size_t column) const
{
	POMDOG_ASSERT_MESSAGE(row < RowSize(), "row: out of range");
	POMDOG_ASSERT_MESSAGE(column < ColumnSize(), "column: out of range");
	return m[row][column];
}
//-----------------------------------------------------------------------
template <typename T>
T & FloatingPointMatrix4x4<T>::operator()(std::size_t row, std::size_t column)
{
	POMDOG_ASSERT_MESSAGE(row < RowSize(), "row: out of range");
	POMDOG_ASSERT_MESSAGE(column < ColumnSize(), "column: out of range");
	return m[row][column];
}
//-----------------------------------------------------------------------
template <typename T>
std::array<T, 4> const& FloatingPointMatrix4x4<T>::operator[](std::size_t row) const
{
	POMDOG_ASSERT_MESSAGE(row < RowSize(), "FloatingPointMatrix4x4, subscript out of range");
	return m[row];
}
//-----------------------------------------------------------------------
template <typename T>
std::array<T, 4> & FloatingPointMatrix4x4<T>::operator[](std::size_t row)
{
	POMDOG_ASSERT_MESSAGE(row < RowSize(), "FloatingPointMatrix4x4, subscript out of range");
	return m[row];
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix4x4<T> & FloatingPointMatrix4x4<T>::operator*=(FloatingPointMatrix4x4 const& other)
{
	return *this = this->Concatenate(other);
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix4x4<T> & FloatingPointMatrix4x4<T>::operator+=(FloatingPointMatrix4x4 const& other)
{
	m[0][0] += other.m[0][0];
	m[0][1] += other.m[0][1];
	m[0][2] += other.m[0][2];
	m[0][3] += other.m[0][3];
	m[1][0] += other.m[1][0];
	m[1][1] += other.m[1][1];
	m[1][2] += other.m[1][2];
	m[1][3] += other.m[1][3];
	m[2][0] += other.m[2][0];
	m[2][1] += other.m[2][1];
	m[2][2] += other.m[2][2];
	m[2][3] += other.m[2][3];
	m[3][0] += other.m[3][0];
	m[3][1] += other.m[3][1];
	m[3][2] += other.m[3][2];
	m[3][3] += other.m[3][3];
	return *this;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix4x4<T> & FloatingPointMatrix4x4<T>::operator-=(FloatingPointMatrix4x4 const& other)
{
	m[0][0] -= other.m[0][0];
	m[0][1] -= other.m[0][1];
	m[0][2] -= other.m[0][2];
	m[0][3] -= other.m[0][3];
	m[1][0] -= other.m[1][0];
	m[1][1] -= other.m[1][1];
	m[1][2] -= other.m[1][2];
	m[1][3] -= other.m[1][3];
	m[2][0] -= other.m[2][0];
	m[2][1] -= other.m[2][1];
	m[2][2] -= other.m[2][2];
	m[2][3] -= other.m[2][3];
	m[3][0] -= other.m[3][0];
	m[3][1] -= other.m[3][1];
	m[3][2] -= other.m[3][2];
	m[3][3] -= other.m[3][3];
	return *this;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix4x4<T> & FloatingPointMatrix4x4<T>::operator*=(T scaleFactor)
{
	return *this = this->Concatenate(scaleFactor);
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix4x4<T> & FloatingPointMatrix4x4<T>::operator/=(T scaleFactor)
{
	auto const inverseDivider = 1 / scaleFactor;
	m[0][0] *= inverseDivider;
	m[0][1] *= inverseDivider;
	m[0][2] *= inverseDivider;
	m[0][3] *= inverseDivider;
	m[1][0] *= inverseDivider;
	m[1][1] *= inverseDivider;
	m[1][2] *= inverseDivider;
	m[1][3] *= inverseDivider;
	m[2][0] *= inverseDivider;
	m[2][1] *= inverseDivider;
	m[2][2] *= inverseDivider;
	m[2][3] *= inverseDivider;
	m[3][0] *= inverseDivider;
	m[3][1] *= inverseDivider;
	m[3][2] *= inverseDivider;
	m[3][3] *= inverseDivider;
	return *this;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix4x4<T> FloatingPointMatrix4x4<T>::operator+() const
{
	return *this;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix4x4<T> FloatingPointMatrix4x4<T>::operator-() const
{
	return this->Concatenate(-1);
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix4x4<T> FloatingPointMatrix4x4<T>::operator+(FloatingPointMatrix4x4 const& other) const
{
	return FloatingPointMatrix4x4
		( m[0][0] + other.m[0][0]
		, m[0][1] + other.m[0][1]
		, m[0][2] + other.m[0][2]
		, m[0][3] + other.m[0][3]
		
		, m[1][0] + other.m[1][0]
		, m[1][1] + other.m[1][1]
		, m[1][2] + other.m[1][2]
		, m[1][3] + other.m[1][3]
		
		, m[2][0] + other.m[2][0]
		, m[2][1] + other.m[2][1]
		, m[2][2] + other.m[2][2]
		, m[2][3] + other.m[2][3]
		
		, m[3][0] + other.m[3][0]
		, m[3][1] + other.m[3][1]
		, m[3][2] + other.m[3][2]
		, m[3][3] + other.m[3][3]
		);
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix4x4<T> FloatingPointMatrix4x4<T>::operator-(FloatingPointMatrix4x4 const& other) const
{
	return FloatingPointMatrix4x4
		( m[0][0] - other.m[0][0]
		, m[0][1] - other.m[0][1]
		, m[0][2] - other.m[0][2]
		, m[0][3] - other.m[0][3]
		
		, m[1][0] - other.m[1][0]
		, m[1][1] - other.m[1][1]
		, m[1][2] - other.m[1][2]	
		, m[1][3] - other.m[1][3]
		
		, m[2][0] - other.m[2][0]
		, m[2][1] - other.m[2][1]
		, m[2][2] - other.m[2][2]
		, m[2][3] - other.m[2][3]
		
		, m[3][0] - other.m[3][0]
		, m[3][1] - other.m[3][1]
		, m[3][2] - other.m[3][2]
		, m[3][3] - other.m[3][3]
		);
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix4x4<T> FloatingPointMatrix4x4<T>::operator*(FloatingPointMatrix4x4 const& other) const
{
	return this->Concatenate(other);
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix4x4<T> FloatingPointMatrix4x4<T>::operator*(T scaleFactor) const
{
	return this->Concatenate(scaleFactor);
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix4x4<T> FloatingPointMatrix4x4<T>::operator/(T scaleFactor) const
{
	auto const inverseDivider = 1 / scaleFactor;
	return FloatingPointMatrix4x4
		( m[0][0] * inverseDivider
		, m[0][1] * inverseDivider
		, m[0][2] * inverseDivider
		, m[0][3] * inverseDivider
		, m[1][0] * inverseDivider
		, m[1][1] * inverseDivider
		, m[1][2] * inverseDivider
		, m[1][3] * inverseDivider
		, m[2][0] * inverseDivider
		, m[2][1] * inverseDivider
		, m[2][2] * inverseDivider
		, m[2][3] * inverseDivider
		, m[3][0] * inverseDivider
		, m[3][1] * inverseDivider
		, m[3][2] * inverseDivider
		, m[3][3] * inverseDivider
		);
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix4x4<T> operator*(T scaleFactor, FloatingPointMatrix4x4<T> const& matrix)
{
	return matrix.Concatenate(scaleFactor);
}
//-----------------------------------------------------------------------
template <typename T>
bool FloatingPointMatrix4x4<T>::operator==(FloatingPointMatrix4x4 const& other) const
{
	return (
		m[0][0] == other.m[0][0] && m[0][1] == other.m[0][1] && m[0][2] == other.m[0][2] && m[0][3] == other.m[0][3] &&
		m[1][0] == other.m[1][0] && m[1][1] == other.m[1][1] && m[1][2] == other.m[1][2] && m[1][3] == other.m[1][3] &&
		m[2][0] == other.m[2][0] && m[2][1] == other.m[2][1] && m[2][2] == other.m[2][2] && m[2][3] == other.m[2][3] &&
		m[3][0] == other.m[3][0] && m[3][1] == other.m[3][1] && m[3][2] == other.m[3][2] && m[3][3] == other.m[3][3]
	);
}
//-----------------------------------------------------------------------
template <typename T>
bool FloatingPointMatrix4x4<T>::operator!=(FloatingPointMatrix4x4 const& other) const
{
	return (
		m[0][0] != other.m[0][0] || m[0][1] != other.m[0][1] || m[0][2] != other.m[0][2] || m[0][3] != other.m[0][3] ||
		m[1][0] != other.m[1][0] || m[1][1] != other.m[1][1] || m[1][2] != other.m[1][2] || m[1][3] != other.m[1][3] ||
		m[2][0] != other.m[2][0] || m[2][1] != other.m[2][1] || m[2][2] != other.m[2][2] || m[2][3] != other.m[2][3] ||
		m[3][0] != other.m[3][0] || m[3][1] != other.m[3][1] || m[3][2] != other.m[3][2] || m[3][3] != other.m[3][3]
	);
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix4x4<T> FloatingPointMatrix4x4<T>::Concatenate(FloatingPointMatrix4x4 const& rhs) const
{
	FloatingPointMatrix4x4 const& lhs(*this);
	return FloatingPointMatrix4x4
		( lhs.m[0][0] * rhs.m[0][0] + lhs.m[0][1] * rhs.m[1][0] + lhs.m[0][2] * rhs.m[2][0] + lhs.m[0][3] * rhs.m[3][0]
		, lhs.m[0][0] * rhs.m[0][1] + lhs.m[0][1] * rhs.m[1][1] + lhs.m[0][2] * rhs.m[2][1] + lhs.m[0][3] * rhs.m[3][1]
		, lhs.m[0][0] * rhs.m[0][2] + lhs.m[0][1] * rhs.m[1][2] + lhs.m[0][2] * rhs.m[2][2] + lhs.m[0][3] * rhs.m[3][2]
		, lhs.m[0][0] * rhs.m[0][3] + lhs.m[0][1] * rhs.m[1][3] + lhs.m[0][2] * rhs.m[2][3] + lhs.m[0][3] * rhs.m[3][3]

		, lhs.m[1][0] * rhs.m[0][0] + lhs.m[1][1] * rhs.m[1][0] + lhs.m[1][2] * rhs.m[2][0] + lhs.m[1][3] * rhs.m[3][0]
		, lhs.m[1][0] * rhs.m[0][1] + lhs.m[1][1] * rhs.m[1][1] + lhs.m[1][2] * rhs.m[2][1] + lhs.m[1][3] * rhs.m[3][1]
		, lhs.m[1][0] * rhs.m[0][2] + lhs.m[1][1] * rhs.m[1][2] + lhs.m[1][2] * rhs.m[2][2] + lhs.m[1][3] * rhs.m[3][2]
		, lhs.m[1][0] * rhs.m[0][3] + lhs.m[1][1] * rhs.m[1][3] + lhs.m[1][2] * rhs.m[2][3] + lhs.m[1][3] * rhs.m[3][3]

		, lhs.m[2][0] * rhs.m[0][0] + lhs.m[2][1] * rhs.m[1][0] + lhs.m[2][2] * rhs.m[2][0] + lhs.m[2][3] * rhs.m[3][0]
		, lhs.m[2][0] * rhs.m[0][1] + lhs.m[2][1] * rhs.m[1][1] + lhs.m[2][2] * rhs.m[2][1] + lhs.m[2][3] * rhs.m[3][1]
		, lhs.m[2][0] * rhs.m[0][2] + lhs.m[2][1] * rhs.m[1][2] + lhs.m[2][2] * rhs.m[2][2] + lhs.m[2][3] * rhs.m[3][2]
		, lhs.m[2][0] * rhs.m[0][3] + lhs.m[2][1] * rhs.m[1][3] + lhs.m[2][2] * rhs.m[2][3] + lhs.m[2][3] * rhs.m[3][3]

		, lhs.m[3][0] * rhs.m[0][0] + lhs.m[3][1] * rhs.m[1][0] + lhs.m[3][2] * rhs.m[2][0] + lhs.m[3][3] * rhs.m[3][0]
		, lhs.m[3][0] * rhs.m[0][1] + lhs.m[3][1] * rhs.m[1][1] + lhs.m[3][2] * rhs.m[2][1] + lhs.m[3][3] * rhs.m[3][1]
		, lhs.m[3][0] * rhs.m[0][2] + lhs.m[3][1] * rhs.m[1][2] + lhs.m[3][2] * rhs.m[2][2] + lhs.m[3][3] * rhs.m[3][2]
		, lhs.m[3][0] * rhs.m[0][3] + lhs.m[3][1] * rhs.m[1][3] + lhs.m[3][2] * rhs.m[2][3] + lhs.m[3][3] * rhs.m[3][3] 
		);
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix4x4<T> FloatingPointMatrix4x4<T>::Concatenate(T scaleFactor) const
{
	return FloatingPointMatrix4x4
		( m[0][0] * scaleFactor
		, m[0][1] * scaleFactor
		, m[0][2] * scaleFactor
		, m[0][3] * scaleFactor

		, m[1][0] * scaleFactor
		, m[1][1] * scaleFactor
		, m[1][2] * scaleFactor
		, m[1][3] * scaleFactor

		, m[2][0] * scaleFactor
		, m[2][1] * scaleFactor
		, m[2][2] * scaleFactor
		, m[2][3] * scaleFactor

		, m[3][0] * scaleFactor
		, m[3][1] * scaleFactor
		, m[3][2] * scaleFactor
		, m[3][3] * scaleFactor
		);
}
//-----------------------------------------------------------------------
template <typename T>
void FloatingPointMatrix4x4<T>::SetTranslation(FloatingPointVector3<T> const& position)
{
	m[3][0] = position.x;
	m[3][1] = position.y;
	m[3][2] = position.z;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointVector3<T> FloatingPointMatrix4x4<T>::GetTranslation() const
{
	return FloatingPointVector3<T>(m[3][0], m[3][1], m[3][2]);
}
//-----------------------------------------------------------------------
template <typename T>
void FloatingPointMatrix4x4<T>::SetScale(FloatingPointVector3<T> const& scale)
{
	m[0][0] = scale.x;
	m[1][1] = scale.y;
	m[2][2] = scale.z;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointVector3<T> FloatingPointMatrix4x4<T>::GetScale() const
{
	return FloatingPointVector3<T>(m[0][0], m[1][1], m[2][2]);
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix4x4<T> FloatingPointMatrix4x4<T>::Transpose() const
{
	return FloatingPointMatrix4x4(
		m[0][0], m[1][0], m[2][0], m[3][0],
		m[0][1], m[1][1], m[2][1], m[3][1],
		m[0][2], m[1][2], m[2][2], m[3][2],
		m[0][3], m[1][3], m[2][3], m[3][3]
	);
}
//-----------------------------------------------------------------------
template <typename T>
T FloatingPointMatrix4x4<T>::Determinant() const
{
	///@todo 余因子(cofactor)を出したほうがたぶん速い。
	/// See FloatingPointMatrix3x3::Determinant implementation
	return
	+ m[0][0] * m[1][1] * m[2][2] * m[3][3] + m[0][0] * m[1][2] * m[2][3] * m[3][1] + m[0][0] * m[1][3] * m[2][1] * m[3][2]
	+ m[0][1] * m[1][0] * m[2][3] * m[3][2] + m[0][1] * m[1][2] * m[2][0] * m[3][3] + m[0][1] * m[1][3] * m[2][2] * m[3][0]
	+ m[0][2] * m[1][0] * m[2][1] * m[3][3] + m[0][2] * m[1][1] * m[2][3] * m[3][0] + m[0][2] * m[1][3] * m[2][0] * m[3][1]
	+ m[0][3] * m[1][0] * m[2][2] * m[3][1] + m[0][3] * m[1][1] * m[2][0] * m[3][2] + m[0][3] * m[1][2] * m[2][1] * m[3][0]
	- m[0][0] * m[1][1] * m[2][3] * m[3][2] - m[0][0] * m[1][2] * m[2][1] * m[3][3] - m[0][0] * m[1][3] * m[2][2] * m[3][1]
	- m[0][1] * m[1][0] * m[2][2] * m[3][3] - m[0][1] * m[1][2] * m[2][3] * m[3][0] - m[0][1] * m[1][3] * m[2][0] * m[3][2]
	- m[0][2] * m[1][0] * m[2][3] * m[3][1] - m[0][2] * m[1][1] * m[2][0] * m[3][3] - m[0][2] * m[1][3] * m[2][1] * m[3][0]
	- m[0][3] * m[1][0] * m[2][1] * m[3][2] - m[0][3] * m[1][1] * m[2][2] * m[3][0] - m[0][3] * m[1][2] * m[2][0] * m[3][1];
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix3x3<T> FloatingPointMatrix4x4<T>::Minor3x3(std::size_t row, std::size_t column) const
{
	POMDOG_ASSERT_MESSAGE(row < RowSize(), "row: out of range");
	POMDOG_ASSERT_MESSAGE(column < ColumnSize(), "column: out of range");

	//      4x4 matrix                              3x3 minor
	//     c0  c1  c2  c3
	// r0 |11, 12, 13, 14|                       |11, 12, 13, x| 
	// r1 |21, 22, 23, 24| Minor3x3(mat, r2, c3) |21, 22. 23, x|
	// r2 |31, 32, 33, 34| --------------------> |41, 42, 43, x|
	// r3 |41, 42, 43, 44|                       | x,  x,  x, x|

	FloatingPointMatrix3x3<T> minor;
	for (std::size_t i = 0, s = 0; i < 4; ++i)
	{
		if (row == i)
			continue;

		for (std::size_t j = 0, t = 0; j < 4; ++j)
		{
			if (column == j)
				continue;

			minor[s][t] = this->m[i][j];
			++t;
		}
		++s;
	}
	return minor;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix4x4<T> FloatingPointMatrix4x4<T>::Adjoint() const
{
	return FloatingPointMatrix4x4
		(  this->Minor3x3(0, 0).Determinant()
		, -this->Minor3x3(1, 0).Determinant()
		,  this->Minor3x3(2, 0).Determinant()
		, -this->Minor3x3(3, 0).Determinant()
		
		, -this->Minor3x3(0, 1).Determinant()
		,  this->Minor3x3(1, 1).Determinant()
		, -this->Minor3x3(2, 1).Determinant()
		,  this->Minor3x3(3, 1).Determinant()
		 
		,  this->Minor3x3(0, 2).Determinant()
		, -this->Minor3x3(1, 2).Determinant()
		,  this->Minor3x3(2, 2).Determinant()
		, -this->Minor3x3(3, 2).Determinant()
		  
		, -this->Minor3x3(0, 3).Determinant()
		,  this->Minor3x3(1, 3).Determinant()
		, -this->Minor3x3(2, 3).Determinant()
		,  this->Minor3x3(3, 3).Determinant()
		);
}
//-----------------------------------------------------------------------
template <typename T>
void
FloatingPointMatrix4x4<T>::Invert(FloatingPointMatrix4x4 const& source, FloatingPointMatrix4x4 & result)
{
	auto const determinant = source.Determinant();
	POMDOG_ASSERT_MESSAGE(0 != determinant, "This is singular matrix");
	result = source.Adjoint() / determinant;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix4x4<T>
FloatingPointMatrix4x4<T>::Invert(FloatingPointMatrix4x4 const& source)
{
	FloatingPointMatrix4x4 result;
	Invert(source, result);
	return result;
}
//-----------------------------------------------------------------------
template <typename T>
void
FloatingPointMatrix4x4<T>::CreateIdentity(FloatingPointMatrix4x4 & result)
{
	result.m[0][0] = 1;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;
	
	result.m[1][0] = 0;
	result.m[1][1] = 1;
	result.m[1][2] = 0;
	result.m[1][3] = 0;
	
	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = 1;
	result.m[2][3] = 0;
	
	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix4x4<T>
FloatingPointMatrix4x4<T>::CreateIdentity()
{
	FloatingPointMatrix4x4 result;
	CreateIdentity(result);
	return result;
}
//-----------------------------------------------------------------------
template <typename T>
void
FloatingPointMatrix4x4<T>::CreateTranslation(FloatingPointVector3<T> const& position, FloatingPointMatrix4x4 & result)
{
	CreateIdentity(result);
	result.m[3][0] = position.x;
	result.m[3][1] = position.y;
	result.m[3][2] = position.z;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix4x4<T>
FloatingPointMatrix4x4<T>::CreateTranslation(FloatingPointVector3<T> const& position)
{
	FloatingPointMatrix4x4 result;
	CreateTranslation(position, result);
	return result;
}
//-----------------------------------------------------------------------
template <typename T>
void
FloatingPointMatrix4x4<T>::CreateScale(FloatingPointVector3<T> const& scale, FloatingPointMatrix4x4 & result)
{
	CreateIdentity(result);
	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = scale.z;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix4x4<T>
FloatingPointMatrix4x4<T>::CreateScale(FloatingPointVector3<T> const& scale)
{
	FloatingPointMatrix4x4 result;
	CreateScale(scale, result);
	return result;
}
//-----------------------------------------------------------------------
template <typename T>
void
FloatingPointMatrix4x4<T>::CreateRotationX(Radian<T> const& angle, FloatingPointMatrix4x4 & result)
{
	CreateIdentity(result);
	auto const sin_angle = std::sin(angle.value);
	auto const cos_angle = std::cos(angle.value);

	result.m[1][1] = cos_angle;
	result.m[1][2] = sin_angle;
	result.m[2][1] = -sin_angle;
	result.m[2][2] = cos_angle;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix4x4<T>
FloatingPointMatrix4x4<T>::CreateRotationX(Radian<T> const& angle)
{
	FloatingPointMatrix4x4 result;
	CreateRotationX(angle, result);
	return result;
}
//-----------------------------------------------------------------------
template <typename T>
void
FloatingPointMatrix4x4<T>::CreateRotationY(Radian<T> const& angle, FloatingPointMatrix4x4 & result)
{
	CreateIdentity(result);
	auto const sin_angle = std::sin(angle.value);
	auto const cos_angle = std::cos(angle.value);
	
	result.m[0][0] = cos_angle;
	result.m[0][2] = -sin_angle;
	result.m[2][0] = sin_angle;
	result.m[2][2] = cos_angle;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix4x4<T>
FloatingPointMatrix4x4<T>::CreateRotationY(Radian<T> const& angle)
{
	FloatingPointMatrix4x4 result;
	CreateRotationY(angle, result);
	return result;
}
//-----------------------------------------------------------------------
template <typename T>
void
FloatingPointMatrix4x4<T>::CreateRotationZ(Radian<T> const& angle, FloatingPointMatrix4x4 & result)
{
	CreateIdentity(result);
	auto const sin_angle = std::sin(angle.value);
	auto const cos_angle = std::cos(angle.value);

	result.m[0][0] = cos_angle;
	result.m[0][1] = sin_angle;
	result.m[1][0] = -sin_angle;
	result.m[1][1] = cos_angle;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix4x4<T>
FloatingPointMatrix4x4<T>::CreateRotationZ(Radian<T> const& angle)
{
	FloatingPointMatrix4x4 result;
	CreateRotationZ(angle, result);
	return result;
}
//-----------------------------------------------------------------------
template <typename T>
void
FloatingPointMatrix4x4<T>::CreateFromQuaternion(FloatingPointQuaternion<T> const& quaternion, FloatingPointMatrix4x4 & result)
{
	auto const xx = quaternion.x * quaternion.x;
	auto const yy = quaternion.y * quaternion.y;
	auto const zz = quaternion.z * quaternion.z;
	auto const xy = quaternion.x * quaternion.y;
	auto const zw = quaternion.z * quaternion.w;
	auto const zx = quaternion.z * quaternion.x;
	auto const yw = quaternion.y * quaternion.w;
	auto const yz = quaternion.y * quaternion.z;
	auto const xw = quaternion.x * quaternion.w;

	result.m[0][0] = 1 - (2 * (yy + zz));
	result.m[0][1] = 2 * (xy + zw);
	result.m[0][2] = 2 * (zx - yw);
	result.m[0][3] = 0;

	result.m[1][0] = 2 * (xy - zw);
	result.m[1][1] = 1 - (2 * (zz + xx));
	result.m[1][2] = 2 * (yz + xw);
	result.m[1][3] = 0;

	result.m[2][0] = 2 * (zx + yw);
	result.m[2][1] = 2 * (yz - xw);
	result.m[2][2] = 1 - (2 * (yy + xx));
	result.m[2][3] = 0;

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix4x4<T>
FloatingPointMatrix4x4<T>::CreateFromQuaternion(FloatingPointQuaternion<T> const& quaternion)
{
	FloatingPointMatrix4x4 result;
	CreateFromQuaternion(quaternion, result);
	return result;
}
//-----------------------------------------------------------------------
template <typename T>
void
FloatingPointMatrix4x4<T>::CreateLookAtLH(FloatingPointVector3<T> const & eye, FloatingPointVector3<T> const & at,
	FloatingPointVector3<T> const & up, FloatingPointMatrix4x4 & result)
{
	// zaxis = normal(At - Eye)
	// xaxis = normal(cross(Up, zaxis))
	// yaxis = cross(zaxis, xaxis)
	// 
	//  xaxis.x           yaxis.x           zaxis.x          0
	//  xaxis.y           yaxis.y           zaxis.y          0
	//  xaxis.z           yaxis.z           zaxis.z          0
	// -dot(xaxis, eye)  -dot(yaxis, eye)  -dot(zaxis, eye)  1

	typedef FloatingPointVector3<T> Vector3;
	auto const zaxis = Vector3::Normalize(at - eye);// RH: eye - at
	auto const xaxis = Vector3::Normalize(FloatingPointVector3<T>::Cross(up, zaxis));
	auto const yaxis = Vector3::Cross(zaxis, xaxis);

	result.m[0][0] = xaxis.x;
	result.m[0][1] = yaxis.x;
	result.m[0][2] = zaxis.x;
	result.m[0][3] = 0;
	
	result.m[1][0] = xaxis.y;
	result.m[1][1] = yaxis.y;
	result.m[1][2] = zaxis.y;
	result.m[1][3] = 0;
	
	result.m[2][0] = xaxis.z;
	result.m[2][1] = yaxis.z;
	result.m[2][2] = zaxis.z;
	result.m[2][3] = 0;

	result.m[3][0] = -Vector3::Dot(xaxis, eye);
	result.m[3][1] = -Vector3::Dot(yaxis, eye);
	result.m[3][2] = -Vector3::Dot(zaxis, eye);
	result.m[3][3] = 1;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix4x4<T>
FloatingPointMatrix4x4<T>::CreateLookAtLH(FloatingPointVector3<T> const& eye, FloatingPointVector3<T> const& at,
	FloatingPointVector3<T> const& up)
{// Left-handed Cartesian Coordinates
	FloatingPointMatrix4x4 result;
	CreateLookAtLH(eye, at, up, result);
	return result;
}
//-----------------------------------------------------------------------
template <typename T>
void
FloatingPointMatrix4x4<T>::CreateLookAtRH(FloatingPointVector3<T> const& eye, FloatingPointVector3<T> const& at,
	FloatingPointVector3<T> const& up, FloatingPointMatrix4x4 & result)
{
	// zaxis = normal(Eye - At)
	// xaxis = normal(cross(Up, zaxis))
	// yaxis = cross(zaxis, xaxis)
	// 
	//  xaxis.x           yaxis.x           zaxis.x          0
	//  xaxis.y           yaxis.y           zaxis.y          0
	//  xaxis.z           yaxis.z           zaxis.z          0
	// -dot(xaxis, eye)  -dot(yaxis, eye)  -dot(zaxis, eye)  1

	typedef FloatingPointVector3<T> Vector3;
	auto const zaxis = Vector3::Normalize(eye - at);// LH: at - eye
	auto const xaxis = Vector3::Normalize(FloatingPointVector3<T>::Cross(up, zaxis));
	auto const yaxis = Vector3::Cross(zaxis, xaxis);

	result.m[0][0] = xaxis.x;
	result.m[0][1] = yaxis.x;
	result.m[0][2] = zaxis.x;
	result.m[0][3] = 0;
	
	result.m[1][0] = xaxis.y;
	result.m[1][1] = yaxis.y;
	result.m[1][2] = zaxis.y;
	result.m[1][3] = 0;
	
	result.m[2][0] = xaxis.z;
	result.m[2][1] = yaxis.z;
	result.m[2][2] = zaxis.z;
	result.m[2][3] = 0;

	result.m[3][0] = -Vector3::Dot(xaxis, eye);
	result.m[3][1] = -Vector3::Dot(yaxis, eye);
	result.m[3][2] = -Vector3::Dot(zaxis, eye);
	result.m[3][3] = 1;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix4x4<T>
FloatingPointMatrix4x4<T>::CreateLookAtRH(FloatingPointVector3<T> const& eye, FloatingPointVector3<T> const& at,
	FloatingPointVector3<T> const& up)
{// Right-handed Cartesian Coordinates
	FloatingPointMatrix4x4 result;
	FloatingPointMatrix4x4::CreateLookAtRH(eye, at, up, result);
	return result;
}
//-----------------------------------------------------------------------
template <typename T>
void
FloatingPointMatrix4x4<T>::CreatePerspectiveLH(T width, T height, T zNear, T zFar, FloatingPointMatrix4x4 & result)
{
	POMDOG_ASSERT_MESSAGE(width > 0,   "width: out of range");
	POMDOG_ASSERT_MESSAGE(height > 0,  "height: out of range");
	POMDOG_ASSERT_MESSAGE(zNear >= 0,  "zNear: out of range");
	POMDOG_ASSERT_MESSAGE(zFar > 0,    "zFar: out of range");
	POMDOG_ASSERT_MESSAGE(zNear < zFar,"zNear: out of range");

	// 2*zn/w  0       0              0
	// 0       2*zn/h  0              0
	// 0       0       zf/(zf-zn)     1
	// 0       0       zn*zf/(zn-zf)  0

	T const a = 2 * zNear / width;
	T const b = 2 * zNear / height;
	T const c = zFar / (zFar - zNear);// RH: c = zFar / (zNear - zFar);
	T const d = zNear * zFar / (zNear - zFar);

	result.m[0][0] = a;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;
	
	result.m[1][0] = 0;
	result.m[1][1] = b;
	result.m[1][2] = 0;
	result.m[1][3] = 0;
	
	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = c;
	result.m[2][3] = 1;// RH: -1
	
	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = d;
	result.m[3][3] = 0;
}
//-----------------------------------------------------------------------
template <typename T>
void
FloatingPointMatrix4x4<T>::CreatePerspectiveRH(T width, T height, T zNear, T zFar, FloatingPointMatrix4x4 & result)
{
	POMDOG_ASSERT_MESSAGE(width > 0,  "width: out of range");
	POMDOG_ASSERT_MESSAGE(height > 0, "height: out of range");
	POMDOG_ASSERT_MESSAGE(zNear >= 0, "zNear: out of range");
	POMDOG_ASSERT_MESSAGE(zFar > 0,     "zFar: out of range");
	POMDOG_ASSERT_MESSAGE(zNear < zFar, "zNear: out of range");

	// 2*zn/w  0       0              0
	// 0       2*zn/h  0              0
	// 0       0       zf/(zn-zf)    -1
	// 0       0       zn*zf/(zn-zf)  0

	T const a = 2.0f * zNear / width;
	T const b = 2.0f * zNear / height;
	T const c = zFar / (zNear - zFar);//LH: c = zFar / (zFar - zNear);
	T const d = zNear * zFar / (zNear - zFar);

	result.m[0][0] = a;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;
	
	result.m[1][0] = 0;
	result.m[1][1] = b;
	result.m[1][2] = 0;
	result.m[1][3] = 0;
	
	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = c;
	result.m[2][3] = -1;// LH: +1
	
	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = d;
	result.m[3][3] = 0;
}
//-----------------------------------------------------------------------
template <typename T>
void
FloatingPointMatrix4x4<T>::CreatePerspectiveFieldOfViewLH(Radian<T> const& fovy, T aspect, T zNear, T zFar,
	FloatingPointMatrix4x4 & result)
{
	POMDOG_ASSERT_MESSAGE(fovy > 0, "fovy: out of range");
	POMDOG_ASSERT_MESSAGE(aspect > 0, "aspect: out of range");
	POMDOG_ASSERT_MESSAGE(zNear >= 0,  "zNear: out of range");
	POMDOG_ASSERT_MESSAGE(zFar > 0,  "zFar: out of range");
	POMDOG_ASSERT_MESSAGE(zNear < zFar, "zNear: out of range");

	// h = cot(fovY/2): ビュー空間の高さ
	// w = h / Aspect : ビュー空間の幅
	// cot(fovY/2) = 1/tan(fovY/2)
	// 
	// w   0   0              0
	// 0   h   0              0
	// 0   0   zf/(zf-zn)     1
	// 0   0   zn*zf/(zn-zf)  0

	T const h = 1 / std::tan(fovy.value/2);
	T const w = h / aspect;
	T const c = zFar / (zFar - zNear);// RH: c = zFar / (zNear - zFar);
	T const d = (zNear * zFar) / (zNear - zFar);

	result.m[0][0] = w;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;
	
	result.m[1][0] = 0;
	result.m[1][1] = h;
	result.m[1][2] = 0;
	result.m[1][3] = 0;
	
	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = c;
	result.m[2][3] = 1;// RH: -1

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = d;
	result.m[3][3] = 0;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix4x4<T>
FloatingPointMatrix4x4<T>::CreatePerspectiveFieldOfViewLH(Radian<T> const& fovy, T aspect, T zNear, T zFar)
{// Left-handed Cartesian Coordinates
	FloatingPointMatrix4x4 result;
	CreatePerspectiveFieldOfViewLH(fovy, aspect, zNear, zFar, result);
	return result;
}
//-----------------------------------------------------------------------
template <typename T>
void
FloatingPointMatrix4x4<T>::CreatePerspectiveFieldOfViewRH(Radian<T> const& fovy, T aspect, T zNear, T zFar,
	FloatingPointMatrix4x4 & result)
{
	POMDOG_ASSERT_MESSAGE(fovy > 0, "fovy: out of range");
	POMDOG_ASSERT_MESSAGE(aspect > 0, "aspect: out of range");
	POMDOG_ASSERT_MESSAGE(zNear >= 0,  "zNear: out of range");
	POMDOG_ASSERT_MESSAGE(zFar > 0,    "zFar: out of range");
	POMDOG_ASSERT_MESSAGE(zNear < zFar, "zNear: out of range");

	// h = cot(fovY/2): ビュー空間の高さ
	// w = h / Aspect : ビュー空間の幅
	// cot(fovY/2) == 1/tan(fovY/2)
	//
	// w   0   0              0
	// 0   h   0              0
	// 0   0   zf/(zn-zf)    -1
	// 0   0   zn*zf/(zn-zf)  0

	T const h = 1 / std::tan(fovy.value/2);
	T const w = h / aspect;
	T const c = zFar / (zNear - zFar);// LH: c = zFar / (zFar - zNear);
	T const d = (zNear * zFar) / (zNear - zFar);

	result.m[0][0] = w;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;
	
	result.m[1][0] = 0;
	result.m[1][1] = h;
	result.m[1][2] = 0;
	result.m[1][3] = 0;
	
	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = c;
	result.m[2][3] = -1;// LH: +1
	
	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = d;
	result.m[3][3] = 0;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix4x4<T>
FloatingPointMatrix4x4<T>::CreatePerspectiveFieldOfViewRH(Radian<T> const& fovy, T aspect, T zNear, T zFar)
{// Right-handed Cartesian Coordinates
	FloatingPointMatrix4x4 result;
	CreatePerspectiveFieldOfViewRH(fovy, aspect, zNear, zFar, result);
	return result;
}
//-----------------------------------------------------------------------
template <typename T>
void
FloatingPointMatrix4x4<T>::CreatePerspectiveOffCenterLH(T left, T right, T bottom, T top, T zNear, T zFar,
	FloatingPointMatrix4x4 & result)
{
	POMDOG_ASSERT_MESSAGE(zNear >= 0, "zNear: out of range");
	POMDOG_ASSERT_MESSAGE(zFar > 0, "zFar: out of range");
	POMDOG_ASSERT_MESSAGE(zNear < zFar, "zNear: out of range");

	// 2*zn/(r-l)   0            0              0
	// 0            2*zn/(t-b)   0              0
	// (l+r)/(l-r)  (t+b)/(b-t)  zf/(zf-zn)     1
	// 0            0            zn*zf/(zn-zf)  0

	T const x = 2 * zNear / (right - left);
	T const y = 2 * zNear / (top - bottom);
	T const a = (left + right) / (left - right);// RH: (left + right) / (right - left)
	T const b = (top + bottom) / (bottom - top);// RH: (top + bottom) / (top - bottom)
	T const c = zFar / (zFar - zNear);// RH: zFar / (zNear - zFar)
	T const d = zNear * zFar / (zNear - zFar);

	result.m[0][0] = x;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;
	
	result.m[1][0] = 0;
	result.m[1][1] = y;
	result.m[1][2] = 0;
	result.m[1][3] = 0;
	
	result.m[2][0] = a;
	result.m[2][1] = b;
	result.m[2][2] = c;
	result.m[2][3] = 1;// RH: -1
	
	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = d;
	result.m[3][3] = 0;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix4x4<T>
FloatingPointMatrix4x4<T>::CreatePerspectiveOffCenterLH(T left, T right, T bottom, T top, T zNear, T zFar)
{// Left-handed Cartesian Coordinates
	FloatingPointMatrix4x4 result;
	CreatePerspectiveOffCenterLH(left, right, bottom, top, zNear, zFar, result);
	return result;
}
//-----------------------------------------------------------------------
template <typename T>
void
FloatingPointMatrix4x4<T>::CreatePerspectiveOffCenterRH(T left, T right, T bottom, T top, T zNear, T zFar,
	FloatingPointMatrix4x4 & result)
{
	POMDOG_ASSERT_MESSAGE(zNear >= 0, "zNear: out of range");
	POMDOG_ASSERT_MESSAGE(zFar > 0, "zFar: out of range");
	POMDOG_ASSERT_MESSAGE(zNear < zFar, "zNear: out of range");

	// 2*zn/(r-l)   0            0              0
	// 0            2*zn/(t-b)   0              0
	// (l+r)/(r-l)  (t+b)/(t-b)  zf/(zn-zf)    -1
	// 0            0            zn*zf/(zn-zf)  0

	T const x = 2 * zNear / (right - left);
	T const y = 2 * zNear / (top - bottom);
	T const a = (left + right) / (right - left);// LH: (left + right) / (left - right)
	T const b = (top + bottom) / (top - bottom);// LH: (top + bottom) / (bottom - top)
	T const c = zFar / (zNear - zFar);// LH: zFar / (zFar - zNear)
	T const d = zNear * zFar / (zNear - zFar);

	result.m[0][0] = x;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;
	
	result.m[1][0] = 0;
	result.m[1][1] = y;
	result.m[1][2] = 0;
	result.m[1][3] = 0;
	
	result.m[2][0] = a;
	result.m[2][1] = b;
	result.m[2][2] = c;
	result.m[2][3] = -1; // LH: +1
	
	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = d;
	result.m[3][3] = 0;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix4x4<T>
FloatingPointMatrix4x4<T>::CreatePerspectiveOffCenterRH(T left, T right, T bottom, T top, T zNear, T zFar)
{// Right-handed Cartesian Coordinates
	FloatingPointMatrix4x4 result;
	CreatePerspectiveOffCenterRH(left, right, bottom, top, zNear, zFar, result);
	return result;
}
//-----------------------------------------------------------------------
template <typename T>
void
FloatingPointMatrix4x4<T>::CreateOrthographicOffCenterLH(T left, T right, T bottom, T top, T zNearPlane, T zFarPlane,
	FloatingPointMatrix4x4 & result)
{
	// 2/(r-l)      0            0           0
	// 0            2/(t-b)      0           0
	// 0            0            1/(zf-zn)   0
	// (l+r)/(l-r)  (t+b)/(b-t)  zn/(zn-zf)  1

	T const inverseRightLeft = 1 / (right - left);
	T const inverseTopBottom = 1 / (top - bottom);
	T const inverseFarNear   = 1 / (zFarPlane - zNearPlane);// RH: 1 / (zNearPlane - zFarPlane)

	T const x = 2 * inverseRightLeft;
	T const y = 2 * inverseTopBottom;
	T const z = inverseFarNear;
	T const a = (left + right) * (-inverseRightLeft);
	T const b = (top + bottom) * (-inverseTopBottom);
	T const c = zNearPlane * (-inverseFarNear);//RH: zNearPlane * inverseFarNear

	result.m[0][0] = x;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;
	
	result.m[1][0] = 0;
	result.m[1][1] = y;
	result.m[1][2] = 0;
	result.m[1][3] = 0;
	
	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = z;
	result.m[2][3] = 0;
	
	result.m[3][0] = a;
	result.m[3][1] = b;
	result.m[3][2] = c;
	result.m[3][3] = 1;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix4x4<T>
FloatingPointMatrix4x4<T>::CreateOrthographicOffCenterLH(T left, T right, T bottom, T top, T zNearPlane, T zFarPlane)
{// Left-handed Cartesian Coordinates
	FloatingPointMatrix4x4 result;
	CreateOrthographicOffCenterLH(left, right, bottom, top, zNearPlane, zFarPlane, result);
	return result;
}
//-----------------------------------------------------------------------
template <typename T>
void
FloatingPointMatrix4x4<T>::CreateOrthographicOffCenterRH(T left, T right, T bottom, T top, T zNearPlane, T zFarPlane,
	FloatingPointMatrix4x4 & result)
{
	// 2/(r-l)      0            0           0
	// 0            2/(t-b)      0           0
	// 0            0            1/(zn-zf)   0
	// (l+r)/(l-r)  (t+b)/(b-t)  zn/(zn-zf)  1

	T const inverseRightLeft = 1 / (right - left);
	T const inverseTopBottom = 1 / (top - bottom);
	T const inverseFarNear   = 1 / (zNearPlane - zFarPlane);// LH: 1 / (zFarPlane - zNearPlane)

	T const x = 2 * inverseRightLeft;
	T const y = 2 * inverseTopBottom;
	T const z = inverseFarNear;
	T const a = (left + right) * (-inverseRightLeft);
	T const b = (top + bottom) * (-inverseTopBottom);
	T const c = zNearPlane * inverseFarNear;// LH: zNearPlane * (-inverseFarNear)

	result.m[0][0] = x;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;
	
	result.m[1][0] = 0;
	result.m[1][1] = y;
	result.m[1][2] = 0;
	result.m[1][3] = 0;
	
	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = z;
	result.m[2][3] = 0;
	
	result.m[3][0] = a;
	result.m[3][1] = b;
	result.m[3][2] = c;
	result.m[3][3] = 1;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix4x4<T>
FloatingPointMatrix4x4<T>::CreateOrthographicOffCenterRH(T left, T right, T bottom, T top, T zNearPlane, T zFarPlane)
{// Right-handed Cartesian Coordinates
	FloatingPointMatrix4x4 result;
	CreateOrthographicOffCenterRH(left, right, bottom, top, zNearPlane, zFarPlane, result);
	return result;
}
//-----------------------------------------------------------------------
template <typename T>
void
FloatingPointMatrix4x4<T>::CreateOrthographicLH(T width, T height, T zNearPlane, T zFarPlane, FloatingPointMatrix4x4 & result)
{
	CreateOrthographicOffCenterLH(
		-width / 2, width / 2, -height / 2, height / 2, zNearPlane, zFarPlane, result);
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix4x4<T>
FloatingPointMatrix4x4<T>::CreateOrthographicLH(T width, T height, T zNearPlane, T zFarPlane)
{// Left-handed Cartesian Coordinates
	FloatingPointMatrix4x4 result;
	CreateOrthographicLH(width, height, zNearPlane, zFarPlane, result);
	return result;
}
//-----------------------------------------------------------------------
template <typename T>
void
FloatingPointMatrix4x4<T>::CreateOrthographicRH(T width, T height, T zNearPlane, T zFarPlane, FloatingPointMatrix4x4 & result)
{
	CreateOrthographicOffCenterRH(
		-width / 2, width / 2, -height / 2, height / 2, zNearPlane, zFarPlane, result);
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix4x4<T>
FloatingPointMatrix4x4<T>::CreateOrthographicRH(T width, T height, T zNearPlane, T zFarPlane)
{// Right-handed Cartesian Coordinates
	FloatingPointMatrix4x4 result;
	CreateOrthographicRH(width, height, zNearPlane, zFarPlane, result);
	return result;
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix4x4<T>
FloatingPointMatrix4x4<T>::CreateLerp(FloatingPointMatrix4x4 const& source1, FloatingPointMatrix4x4 const& source2, T amount)
{
	return FloatingPointMatrix4x4
		( source1.m[0][0] + ((source2.m[0][0] - source1.m[0][0]) * amount)
		, source1.m[0][1] + ((source2.m[0][1] - source1.m[0][1]) * amount)
		, source1.m[0][2] + ((source2.m[0][2] - source1.m[0][2]) * amount)
		, source1.m[0][3] + ((source2.m[0][3] - source1.m[0][3]) * amount)

		, source1.m[1][0] + ((source2.m[1][0] - source1.m[1][0]) * amount)
		, source1.m[1][1] + ((source2.m[1][1] - source1.m[1][1]) * amount)
		, source1.m[1][2] + ((source2.m[1][2] - source1.m[1][2]) * amount)
		, source1.m[1][3] + ((source2.m[1][3] - source1.m[1][3]) * amount)

		, source1.m[2][0] + ((source2.m[2][0] - source1.m[2][0]) * amount)
		, source1.m[2][1] + ((source2.m[2][1] - source1.m[2][1]) * amount)
		, source1.m[2][2] + ((source2.m[2][2] - source1.m[2][2]) * amount)
		, source1.m[2][3] + ((source2.m[2][3] - source1.m[2][3]) * amount)

		, source1.m[3][0] + ((source2.m[3][0] - source1.m[3][0]) * amount)
		, source1.m[3][1] + ((source2.m[3][1] - source1.m[3][1]) * amount)
		, source1.m[3][2] + ((source2.m[3][2] - source1.m[3][2]) * amount)
		, source1.m[3][3] + ((source2.m[3][3] - source1.m[3][3]) * amount)
		);
}
//-----------------------------------------------------------------------
template <typename T>
FloatingPointMatrix4x4<T>
FloatingPointMatrix4x4<T>::CreateFromAxisAngle(FloatingPointVector3<T> const& axis, Radian<T> const& angle)
{
	auto const sin_angle = std::sin(angle.value);
	auto const cos_angle = std::cos(angle.value);
	auto const t         = 1 - cos_angle;
	auto const xx        = axis.x * axis.x;
	auto const yy        = axis.y * axis.y;
	auto const zz        = axis.z * axis.z;
	auto const xy        = axis.x * axis.y;
	auto const xz        = axis.x * axis.z;
	auto const yz        = axis.y * axis.z;

	return FloatingPointMatrix4x4
		( t * xx + cos_angle
		, t * xy + sin_angle * axis.z
		, t * xz - sin_angle * axis.y
		, 0

		, t * xy - sin_angle * axis.z
		, t * yy + cos_angle
		, t * yz + sin_angle * axis.x
		, 0

		, t * xz + sin_angle * axis.y
		, t * yz - sin_angle * axis.x
		, t * zz + cos_angle
		, 0

		, 0, 0, 0, 1
		);
}
//-----------------------------------------------------------------------
template <typename T>
T const* FloatingPointMatrix4x4<T>::Data() const
{
	static_assert(std::is_floating_point<T>::value, "T is floating point number");
	return m[0].data();
}
//-----------------------------------------------------------------------
template <typename T>
T* FloatingPointMatrix4x4<T>::Data()
{
	static_assert(std::is_floating_point<T>::value, "T is floating point number");
	return m[0].data();
}
//-----------------------------------------------------------------------
// explicit instantiations
template class FloatingPointMatrix4x4<float>;

#if defined(DBL_MANT_DIG)
template class FloatingPointMatrix4x4<double>;
#endif

#if defined(LDBL_MANT_DIG)
template class FloatingPointMatrix4x4<long double>;
#endif

}// namespace Details
}// namespace Pomdog