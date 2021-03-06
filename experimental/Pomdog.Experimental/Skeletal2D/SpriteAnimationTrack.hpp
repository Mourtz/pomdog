// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#ifndef POMDOG_SPRITEANIMATIONTRACK_FC96976A_HPP
#define POMDOG_SPRITEANIMATIONTRACK_FC96976A_HPP

#include "AnimationTimeInterval.hpp"
#include "Skin.hpp"
#include "Pomdog/Utility/Optional.hpp"
#include "Pomdog/Math/Rectangle.hpp"
#include "Pomdog/Math/Vector2.hpp"
#include <cstdint>
#include <vector>

namespace Pomdog {
namespace Detail {
namespace Skeletal2D {

class SpriteKeyframe {
public:
    Rectangle Subrect;
    Vector2 Origin;
    AnimationTimeInterval Time;
    std::int16_t TexturePage;
    bool TextureRotate;
};

class SpriteAnimationTrack final {
public:
    SpriteAnimationTrack() = default;
    SpriteAnimationTrack(std::vector<SpriteKeyframe> && keys, std::uint32_t slotHashId);

    void Apply(Skin & skin, AnimationTimeInterval const& time);

    AnimationTimeInterval Length() const;

private:
    std::vector<SpriteKeyframe> keys;
    std::uint32_t slotHashId;
    Optional<std::uint16_t> slotIndex;
};

}// namespace Skeletal2D
}// namespace Detail
}// namespace Pomdog

#endif // POMDOG_SPRITEANIMATIONTRACK_FC96976A_HPP
