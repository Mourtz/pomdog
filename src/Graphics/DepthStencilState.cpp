//
//  Copyright (C) 2013-2014 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#include <Pomdog/Graphics/DepthStencilState.hpp>
#include "../RenderSystem/NativeGraphicsDevice.hpp"
#include "../RenderSystem/NativeDepthStencilState.hpp"
#include <Pomdog/Graphics/GraphicsDevice.hpp>
#include <Pomdog/Utility/Assert.hpp>

namespace Pomdog {
//-----------------------------------------------------------------------
DepthStencilState::DepthStencilState(std::shared_ptr<GraphicsDevice> const& graphicsDevice,
	DepthStencilDescription const& descriptionIn)
	: nativeDepthStencilState(graphicsDevice->NativeGraphicsDevice()->CreateDepthStencilState(descriptionIn))
	, description(descriptionIn)
{
	POMDOG_ASSERT(nativeDepthStencilState);
}
//-----------------------------------------------------------------------
DepthStencilState::~DepthStencilState() = default;
//-----------------------------------------------------------------------
DepthStencilDescription DepthStencilState::Description() const
{
	return description;
}
//-----------------------------------------------------------------------
std::shared_ptr<DepthStencilState>
DepthStencilState::CreateReadWriteDepth(std::shared_ptr<GraphicsDevice> const& graphicsDevice)
{
	DepthStencilDescription desc;
	desc.DepthBufferEnable = true;
	desc.DepthBufferWriteEnable = true;
	POMDOG_ASSERT(desc.StencilEnable == false);
	
	return std::make_shared<DepthStencilState>(graphicsDevice, desc);
}
//-----------------------------------------------------------------------
std::shared_ptr<DepthStencilState>
DepthStencilState::CreateReadOnlyDepth(std::shared_ptr<GraphicsDevice> const& graphicsDevice)
{
	DepthStencilDescription desc;
	desc.DepthBufferEnable = true;
	desc.DepthBufferWriteEnable = false;
	POMDOG_ASSERT(desc.StencilEnable == false);
	
	return std::make_shared<DepthStencilState>(graphicsDevice, desc);
}
//-----------------------------------------------------------------------
std::shared_ptr<DepthStencilState>
DepthStencilState::CreateNone(std::shared_ptr<GraphicsDevice> const& graphicsDevice)
{
	DepthStencilDescription desc;
	desc.DepthBufferEnable = false;
	desc.DepthBufferWriteEnable = false;
	POMDOG_ASSERT(desc.StencilEnable == false);
	
	return std::make_shared<DepthStencilState>(graphicsDevice, desc);
}
//-----------------------------------------------------------------------
Details::RenderSystem::NativeDepthStencilState* DepthStencilState::NativeDepthStencilState()
{
	return nativeDepthStencilState.get();
}
//-----------------------------------------------------------------------
}// namespace Pomdog
