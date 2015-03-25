﻿// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#ifndef POMDOG_MATH_DETAIL_FLOATINGPOINTVECTOR4_46E21CD7_0D28_4BFF_B38D_EAC35762288B_HPP
#define POMDOG_MATH_DETAIL_FLOATINGPOINTVECTOR4_46E21CD7_0D28_4BFF_B38D_EAC35762288B_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "ForwardDeclarations.hpp"
#include "Pomdog/Basic/Export.hpp"
#include <cstddef>
#include <cstdint>
#include <cfloat>
#include <type_traits>

namespace Pomdog {
namespace Detail {

///@brief vector in four-dimensional space.
template <typename T>
class POMDOG_EXPORT FloatingPointVector4 {
public:
	static_assert(std::is_floating_point<T>::value, "T is floating point.");
	typedef T value_type;

	T X, Y, Z, W;

public:
	// Constructors:
	FloatingPointVector4() = default;

	///@brief Copy constructor.
	FloatingPointVector4(FloatingPointVector4 const&) = default;

	///@brief Move constructor.
	FloatingPointVector4(FloatingPointVector4 &&) = default;

	///@brief Construct from floating-point values.
	FloatingPointVector4(T x, T y, T z, T w);
	FloatingPointVector4(FloatingPointVector3<T> const& xyz, T w);

	// Assignment operators:
	FloatingPointVector4 & operator=(FloatingPointVector4 const& other) = default;
	FloatingPointVector4 & operator=(FloatingPointVector4 && other) = default;

	FloatingPointVector4 & operator+=(FloatingPointVector4 const& other);
	FloatingPointVector4 & operator-=(FloatingPointVector4 const& other);
	FloatingPointVector4 & operator*=(T scaleFactor);
	FloatingPointVector4 & operator/=(T scaleFactor);

	// Unary operators:
	FloatingPointVector4 operator+() const;
	FloatingPointVector4 operator-() const;

	// Binary operators:
	FloatingPointVector4 operator+(FloatingPointVector4 const& other) const;
	FloatingPointVector4 operator-(FloatingPointVector4 const& other) const;
	FloatingPointVector4 operator*(FloatingPointVector4 const& other) const;
	FloatingPointVector4 operator/(FloatingPointVector4 const& other) const;
	FloatingPointVector4 operator*(T scaleFactor) const;
	FloatingPointVector4 operator/(T scaleFactor) const;

	bool operator == (FloatingPointVector4 const& other) const;
	bool operator != (FloatingPointVector4 const& other) const;

	T Length() const;

	T LengthSquared() const;

	static T Distance(FloatingPointVector4 const& a, FloatingPointVector4 const& b);

	static T DistanceSquared(FloatingPointVector4 const& a, FloatingPointVector4 const& b);

	static T Dot(FloatingPointVector4 const& a, FloatingPointVector4 const& b);

	void Normalize();

	static FloatingPointVector4 Normalize(FloatingPointVector4 const& source);

	static void Normalize(FloatingPointVector4 const& source, FloatingPointVector4 & result);

	///@brief Returns pointer to the first element.
	T const* Data() const;

	///@brief Returns pointer to the first element.
	T* Data();
};

template <typename T>
FloatingPointVector4<T> POMDOG_EXPORT
operator*(T scaleFactor, FloatingPointVector4<T> const& vector);

}// namespace Detail
}// namespace Pomdog

#endif // !defined(POMDOG_MATH_DETAIL_FLOATINGPOINTVECTOR4_46E21CD7_0D28_4BFF_B38D_EAC35762288B_HPP)
