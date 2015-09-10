// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#ifndef POMDOG_FORWARDDECLARATIONS_2B34361D_HPP
#define POMDOG_FORWARDDECLARATIONS_2B34361D_HPP

#include "Pomdog/Basic/Export.hpp"
#include <cstdint>

// Forward declarations of Math

namespace Pomdog {
namespace Detail {

template <typename T>
class Coordinate2D;

template <typename T>
class Coordinate3D;

template <typename RealType>
class POMDOG_EXPORT FloatingPointMatrix2x2;

template <typename RealType>
class POMDOG_EXPORT FloatingPointMatrix3x2;

template <typename RealType>
class POMDOG_EXPORT FloatingPointMatrix3x3;

template <typename RealType>
class POMDOG_EXPORT FloatingPointMatrix4x4;

template <typename RealType>
class POMDOG_EXPORT FloatingPointQuaternion;

template <typename RealType>
class POMDOG_EXPORT FloatingPointVector2;

template <typename RealType>
class POMDOG_EXPORT FloatingPointVector3;

template <typename RealType>
class POMDOG_EXPORT FloatingPointVector4;

template <typename T, class PhantomType>
class TaggedArithmetic;

namespace Tags {

struct DegreeTag;
struct RadianTag;

} // namespace Tags
} // namespace Detail

using Matrix2x2 = Detail::FloatingPointMatrix2x2<float>;
using Matrix3x2 = Detail::FloatingPointMatrix3x2<float>;
using Matrix3x3 = Detail::FloatingPointMatrix3x3<float>;
using Matrix4x4 = Detail::FloatingPointMatrix4x4<float>;
using Point2D = Detail::Coordinate2D<std::int32_t>;
using Point3D = Detail::Coordinate3D<std::int32_t>;
using Quaternion = Detail::FloatingPointQuaternion<float>;
using Vector2 = Detail::FloatingPointVector2<float>;
using Vector3 = Detail::FloatingPointVector3<float>;
using Vector4 = Detail::FloatingPointVector4<float>;

template <typename T>
using Degree = Detail::TaggedArithmetic<T, Detail::Tags::DegreeTag>;

template <typename T>
using Radian = Detail::TaggedArithmetic<T, Detail::Tags::RadianTag>;

class BoundingBox;
class BoundingBox2D;
class BoundingCircle;
class BoundingSphere;
class Color;
class Ray;
class Rectangle;

// Enumerations:
enum class ContainmentType: std::uint8_t;

} // namespace Pomdog

#endif // POMDOG_FORWARDDECLARATIONS_2B34361D_HPP
