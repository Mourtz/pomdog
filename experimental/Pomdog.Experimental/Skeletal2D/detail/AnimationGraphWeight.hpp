// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#ifndef POMDOG_ANIMATIONGRAPHWEIGHT_2B7D7365_HPP
#define POMDOG_ANIMATIONGRAPHWEIGHT_2B7D7365_HPP

#include "Pomdog.Experimental/Skeletal2D/AnimationBlendInputType.hpp"
#include <cstdint>

namespace Pomdog {
namespace Detail {
namespace Skeletal2D {

class AnimationGraphWeight {
public:
    explicit AnimationGraphWeight(float value);

    explicit AnimationGraphWeight(bool value);

    void SetValue(float value);
    void SetValue(bool value);

    float GetFloat() const;
    bool GetBool() const;

private:
    float weight;
    AnimationBlendInputType type;
};

}// namespace Skeletal2D
}// namespace Detail
}// namespace Pomdog

#endif // POMDOG_ANIMATIONGRAPHWEIGHT_2B7D7365_HPP
