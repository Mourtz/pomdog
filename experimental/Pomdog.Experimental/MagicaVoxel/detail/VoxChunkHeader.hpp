// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#ifndef POMDOG_VOXCHUNKHEADER_6CE19808_HPP
#define POMDOG_VOXCHUNKHEADER_6CE19808_HPP

#include <cstdint>

namespace Pomdog {
namespace MagicaVoxel {

struct VoxChunkHeader {
    std::int32_t ID;
    std::int32_t ContentSize;
    std::int32_t ChildrenSize;
};

} // namespace MagicaVoxel
} // namespace Pomdog

#endif // POMDOG_VOXCHUNKHEADER_6CE19808_HPP
