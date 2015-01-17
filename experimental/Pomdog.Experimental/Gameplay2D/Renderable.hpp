﻿//
//  Copyright (C) 2013-2015 mogemimi.
//  Distributed under the MIT License. See LICENSE.md or
//  http://enginetrouble.net/pomdog/license for details.
//

#ifndef POMDOG_RENDERABLE_45A0A118_A075_4172_929C_05DF1A2E47FF_HPP
#define POMDOG_RENDERABLE_45A0A118_A075_4172_929C_05DF1A2E47FF_HPP

#if (_MSC_VER > 1000)
#pragma once
#endif

#include "Pomdog.Experimental/Gameplay/Component.hpp"
#include "Pomdog.Experimental/Gameplay/GameObject.hpp"
#include "Pomdog/Math/Color.hpp"
#include "Pomdog/Math/Matrix4x4.hpp"

namespace Pomdog {

class Renderer;

struct Material {
	Color Color = Color::White;
};

class Renderable: public Component<Renderable> {
public:
	virtual ~Renderable() = default;

	virtual void Visit(GameObject & gameObject, Renderer & renderer) = 0;

	Material Material;
	float DrawOrder = 0.0f;
	bool IsVisible = true;
};

}// namespace Pomdog

#endif // !defined(POMDOG_RENDERABLE_45A0A118_A075_4172_929C_05DF1A2E47FF_HPP)
