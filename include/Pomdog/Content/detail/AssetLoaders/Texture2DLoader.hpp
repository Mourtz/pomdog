﻿//
//  Copyright (C) 2013-2015 mogemimi.
//  Distributed under the MIT License. See LICENSE.md or
//  http://enginetrouble.net/pomdog/license for details.
//

#ifndef POMDOG_TEXTURE2DLOADER_84BCFDDA_4E0C_4783_B628_2D48B5008588_HPP
#define POMDOG_TEXTURE2DLOADER_84BCFDDA_4E0C_4783_B628_2D48B5008588_HPP

#if (_MSC_VER > 1000)
#pragma once
#endif

#include "Pomdog/Content/detail/AssetLoader.hpp"
#include "Pomdog/Basic/Export.hpp"
#include <string>
#include <memory>

namespace Pomdog {

class Texture2D;

namespace Details {

class AssetLoaderContext;

template <>
struct POMDOG_EXPORT AssetLoader<Texture2D> final {
	std::shared_ptr<Texture2D> operator()(
		AssetLoaderContext const& loaderContext,
		std::string const& assetName);
};

}// namespace Details
}// namespace Pomdog

#endif // !defined(POMDOG_TEXTURE2DLOADER_84BCFDDA_4E0C_4783_B628_2D48B5008588_HPP)