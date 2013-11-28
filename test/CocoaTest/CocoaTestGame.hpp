﻿//
//  Copyright (C) 2013 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#ifndef POMDOG_COCOATESTGAME_HPP
#define POMDOG_COCOATESTGAME_HPP

#if (_MSC_VER > 1000)
#	pragma once
#endif

#include <Pomdog/Application/GameSystem.hpp>
#include <Pomdog/Graphics/GraphicsContext.hpp>

namespace Pomdog {

class CocoaTestGame
{
public:
	explicit CocoaTestGame(GameSystem & rootSystem);

	void Initialize();
	
	void Update();
	
	void Draw();
	
private:
	std::shared_ptr<GameSystem> gameSystem;
	std::shared_ptr<GraphicsContext> graphicsContext;
};

}// namespace Pomdog

#endif // !defined(POMDOG_COCOATESTGAME_HPP)