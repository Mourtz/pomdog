// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#ifndef POMDOG_SPRITEANIMATIONLOADER_C360BEBA_HPP
#define POMDOG_SPRITEANIMATIONLOADER_C360BEBA_HPP

#include "Pomdog.Experimental/TexturePacker/TextureAtlas.hpp"
#include <vector>

namespace Pomdog {
namespace Detail {
namespace Skeletal2D {

class SpriteAnimationTrack;

}// namespace Skeletal2D
}// namespace Detail
namespace Spine {

class SkeletonDesc;

std::vector<Detail::Skeletal2D::SpriteAnimationTrack> CreateSpriteAnimationTrack(
    SkeletonDesc const& desc,
    TexturePacker::TextureAtlas const& textureAtlas,
    char const* name);

}// namespace Spine
}// namespace Pomdog

#endif // POMDOG_SPRITEANIMATIONLOADER_C360BEBA_HPP
