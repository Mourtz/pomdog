// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#ifndef POMDOG_PARTICLERENDERABLE_1729BB9F_HPP
#define POMDOG_PARTICLERENDERABLE_1729BB9F_HPP

#include "Renderable.hpp"
#include "Pomdog.Experimental/Rendering/Commands/ParticleBatchCommand.hpp"
#include <Pomdog/Pomdog.hpp>
#include <memory>

namespace Pomdog {

class ParticleRenderable: public Renderable {
public:
    ParticleRenderable(std::shared_ptr<Texture2D> const& texture);
    //ParticleRenderable(std::shared_ptr<Texture2D> const& texture, TextureRegion const& textureRegion);

    void Visit(GameObject & gameObject, Renderer & renderer) override;

private:
    Detail::Rendering::ParticleBatchCommand command;
};

}// namespace Pomdog

#endif // POMDOG_PARTICLERENDERABLE_1729BB9F_HPP
