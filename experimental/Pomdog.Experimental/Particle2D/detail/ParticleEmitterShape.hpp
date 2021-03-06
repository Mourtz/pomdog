// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#ifndef POMDOG_PARTICLEEMITTERSHAPE_DCE4AD88_HPP
#define POMDOG_PARTICLEEMITTERSHAPE_DCE4AD88_HPP

#include "Pomdog/Math/Vector2.hpp"
#include "Pomdog/Math/Radian.hpp"
#include <random>

namespace Pomdog {
namespace Detail {
namespace Particles {

class ParticleEmitterShape {
public:
    virtual ~ParticleEmitterShape() = default;

    virtual void Compute(std::mt19937 & random, Vector2 & emitPosition, Radian<float> & emitAngle) const = 0;
};

}// namespace Particles
}// namespace Detail
}// namespace Pomdog

#endif // POMDOG_PARTICLEEMITTERSHAPE_DCE4AD88_HPP
