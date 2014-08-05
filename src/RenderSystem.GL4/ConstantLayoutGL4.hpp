﻿//
//  Copyright (C) 2013-2014 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#ifndef POMDOG_CONSTANTLAYOUTGL4_25949458_085E_49FD_91A9_EFF89B064B88_HPP
#define POMDOG_CONSTANTLAYOUTGL4_25949458_085E_49FD_91A9_EFF89B064B88_HPP

#if (_MSC_VER > 1000)
#	pragma once
#endif

#include "../RenderSystem/NativeConstantLayout.hpp"
#include <cstdint>
#include <vector>

namespace Pomdog {
namespace Details {
namespace RenderSystem {
namespace GL4 {

class ConstantBufferGL4;

struct ConstantBufferBindingGL4 {
	std::shared_ptr<ConstantBufferGL4> ConstantBuffer;
	std::string Name;
	std::uint16_t SlotIndex;
};

class ConstantLayoutGL4 final: public NativeConstantLayout {
public:
	ConstantLayoutGL4() = delete;

	explicit ConstantLayoutGL4(std::vector<ConstantBufferBindingGL4> && bindings);

	void SetConstantBuffer(std::string const& constantName, std::shared_ptr<NativeConstantBuffer> const& constantBuffer) override;
	
	void SetConstantBuffer(std::string const& constantName) override;
	
	void Apply();

private:
	std::vector<ConstantBufferBindingGL4> bindings;
};

}// namespace GL4
}// namespace RenderSystem
}// namespace Details
}// namespace Pomdog

#endif // !defined(POMDOG_CONSTANTLAYOUTGL4_25949458_085E_49FD_91A9_EFF89B064B88_HPP)