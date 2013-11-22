//
//  Copyright (C) 2013 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#ifndef POMDOG_GL4_GRAPHICSCONTEXTGL4_HPP
#define POMDOG_GL4_GRAPHICSCONTEXTGL4_HPP

#if (_MSC_VER > 1000)
#	pragma once
#endif

#include "GL4Prerequisites.hpp"
#include "../RenderSystem/NativeGraphicsContext.hpp"
#include "GLContext.hpp"
#include <memory>

namespace Pomdog {
namespace Details {
namespace GL4 {

class GraphicsContextGL4 final: public RenderSystem::NativeGraphicsContext
{
public:
	~GraphicsContextGL4() = default;
	
	void Clear(Color const& color);
	
	void Present();
	
private:
	std::unique_ptr<GLContext> context;
};

}// namespace GL4
}// namespace Details
}// namespace Pomdog

#endif // !defined(POMDOG_GL4_GRAPHICSCONTEXTGL4_HPP)
