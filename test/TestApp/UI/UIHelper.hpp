﻿//
//  Copyright (C) 2013-2014 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#ifndef POMDOG_UIHELPER_25E8AD61_F482_4291_B3E0_EA50C4CD3649_HPP
#define POMDOG_UIHELPER_25E8AD61_F482_4291_B3E0_EA50C4CD3649_HPP

#if (_MSC_VER > 1000)
#	pragma once
#endif

#include <Pomdog/Pomdog.hpp>

namespace Pomdog {
namespace UI {

struct UIHelper {
	static Vector2 ConvertToChildSpace(Vector2 const& position, Matrix3x2 const& transform)
	{
		return Vector2::Transform(position, Matrix3x2::Invert(transform));
	}
	
	static Point2D ConvertToChildSpace(Point2D const& position, Matrix3x2 const& transform)
	{
		auto positionInChild = ConvertToChildSpace(Vector2(position.X, position.Y), transform);
		return Point2D(positionInChild.X, positionInChild.Y);
	}
};

}// namespace UI
}// namespace Pomdog

#endif // !defined(POMDOG_UIHELPER_25E8AD61_F482_4291_B3E0_EA50C4CD3649_HPP)