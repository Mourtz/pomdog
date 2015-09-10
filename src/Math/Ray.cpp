// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#include "Pomdog/Math/Ray.hpp"
#include "Pomdog/Math/BoundingBox.hpp"
#include "Pomdog/Math/BoundingSphere.hpp"
#include <cmath>
#include <algorithm>

namespace Pomdog {
//-----------------------------------------------------------------------
Ray::Ray(Vector3 const& positionIn, Vector3 const& directionIn)
    : Position(positionIn)
    , Direction(directionIn)
{
}
//-----------------------------------------------------------------------
bool Ray::operator==(Ray const& ray) const noexcept
{
    return this->Position == ray.Position
        && this->Direction == ray.Direction;
}
//-----------------------------------------------------------------------
bool Ray::operator!=(Ray const& ray) const noexcept
{
    return this->Position != ray.Position
        || this->Direction != ray.Direction;
}
//-----------------------------------------------------------------------
Optional<float> Ray::Intersects(BoundingBox const& box) const
{
    typedef float T;

    constexpr auto PositiveInfinity = std::numeric_limits<T>::max();
    constexpr auto NegativeInfinity = std::numeric_limits<T>::lowest();
    constexpr auto Epsilon = std::numeric_limits<T>::epsilon();

    auto & ray = *this;

    auto tNear = NegativeInfinity;
    auto tFar = PositiveInfinity;

    if (std::abs(ray.Direction.X) < Epsilon) {
        if (ray.Position.X < box.Min.X || ray.Position.X > box.Max.X) {
            return Pomdog::NullOpt;
        }
    }
    else {
        POMDOG_ASSERT(ray.Direction.X != 0);
        auto t1 = (box.Min.X - ray.Position.X) / ray.Direction.X;
        auto t2 = (box.Max.X - ray.Position.X) / ray.Direction.X;

        if (t1 > t2) {
            std::swap(t1, t2);
        }

        POMDOG_ASSERT(tNear <= t1);
        POMDOG_ASSERT(tFar >= t2);
        tNear = t1;
        tFar = t2;

        if (tNear > tFar || tFar < 0) {
            return Pomdog::NullOpt;
        }
    }

    if (std::abs(ray.Direction.Y) < Epsilon) {
        if (ray.Position.Y < box.Min.Y || ray.Position.Y > box.Max.Y) {
            return Pomdog::NullOpt;
        }
    }
    else {
        POMDOG_ASSERT(ray.Direction.Y != 0);
        auto t1 = (box.Min.Y - ray.Position.Y) / ray.Direction.Y;
        auto t2 = (box.Max.Y - ray.Position.Y) / ray.Direction.Y;

        if (t1 > t2) {
            std::swap(t1, t2);
        }
        if (tNear < t1) {
            tNear = t1;
        }
        if (tFar > t2) {
            tFar = t2;
        }
        if (tNear > tFar || tFar < 0) {
            return Pomdog::NullOpt;
        }
    }

    if (std::abs(ray.Direction.Z) < Epsilon) {
        if (ray.Position.Z < box.Min.Z || ray.Position.Z > box.Max.Z) {
            return Pomdog::NullOpt;
        }
    }
    else {
        POMDOG_ASSERT(ray.Direction.Z != 0);
        auto t1 = (box.Min.Z - ray.Position.Z) / ray.Direction.Z;
        auto t2 = (box.Max.Z - ray.Position.Z) / ray.Direction.Z;

        if (t1 > t2) {
            std::swap(t1, t2);
        }
        if (tNear < t1) {
            tNear = t1;
        }
        if (tFar > t2) {
            tFar = t2;
        }
        if (tNear > tFar || tFar < 0) {
            return Pomdog::NullOpt;
        }
    }

    POMDOG_ASSERT(tNear <= tFar && tFar >= 0);
    return tFar;
}
//-----------------------------------------------------------------------
Optional<float> Ray::Intersects(BoundingSphere const& sphere) const
{
    const auto toSphere = sphere.Center - this->Position;
    const auto toSphereLengthSquared = toSphere.LengthSquared();
    const auto sphereRadiusSquared = sphere.Radius * sphere.Radius;

    if (toSphereLengthSquared < sphereRadiusSquared) {
        return 0;
    }

    const auto distance = Vector3::Dot(this->Direction, toSphere);
    if (distance < 0) {
        return Pomdog::NullOpt;
    }

    const auto discriminant = sphereRadiusSquared + distance * distance - toSphereLengthSquared;
    if (discriminant < 0) {
        return Pomdog::NullOpt;
    }
    return std::max(distance - std::sqrt(discriminant), 0.0f);
}
//-----------------------------------------------------------------------
} // namespace Pomdog
