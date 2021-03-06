// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#ifndef POMDOG_SKINNEDMESHLOADER_0D066D10_HPP
#define POMDOG_SKINNEDMESHLOADER_0D066D10_HPP

#include "Pomdog.Experimental/TexturePacker/TextureAtlas.hpp"
#include "Pomdog/Graphics/GraphicsDevice.hpp"
#include "Pomdog/Math/Vector2.hpp"
#include <memory>

namespace Pomdog {

class SkinnedMesh;
class SkeletonPose;

namespace Spine {

class SkeletonDesc;

SkinnedMesh CreateSkinnedMesh(
    GraphicsDevice & graphicsDevice,
    std::vector<Matrix3x2> const& bindPosesInGlobal,
    SkeletonDesc const& skeletonDesc,
    TexturePacker::TextureAtlas const& textureAtlas,
    Vector2 const& textureSize,
    std::string const& skinName);

}// namespace Spine
}// namespace Pomdog

#endif // POMDOG_SKINNEDMESHLOADER_0D066D10_HPP
