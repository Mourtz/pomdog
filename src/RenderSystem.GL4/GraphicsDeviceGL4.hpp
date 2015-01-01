﻿//
//  Copyright (C) 2013-2015 mogemimi.
//  Distributed under the MIT License. See LICENSE.md or
//  http://enginetrouble.net/pomdog/license for details.
//

#ifndef POMDOG_SRC_GL4_GRAPHICSDEVICEGL4_74F5BC81_6BDB_4FDC_99F4_DF45CEC32B5F_HPP
#define POMDOG_SRC_GL4_GRAPHICSDEVICEGL4_74F5BC81_6BDB_4FDC_99F4_DF45CEC32B5F_HPP

#if (_MSC_VER > 1000)
#pragma once
#endif

#include "../RenderSystem/NativeGraphicsDevice.hpp"
#include <memory>

namespace Pomdog {
namespace Details {
namespace RenderSystem {
namespace GL4 {

class GraphicsDeviceGL4 final: public NativeGraphicsDevice {
public:
	///@copydoc NativeGraphicsDevice
	std::unique_ptr<NativeIndexBuffer>
	CreateIndexBuffer(std::uint32_t sizeInBytes, BufferUsage bufferUsage) override;
	
	///@copydoc NativeGraphicsDevice
	std::unique_ptr<NativeIndexBuffer>
	CreateIndexBuffer(void const* indices, std::uint32_t sizeInBytes,
		BufferUsage bufferUsage) override;
	
	///@copydoc NativeGraphicsDevice
	std::unique_ptr<NativeVertexBuffer>
	CreateVertexBuffer(std::uint32_t sizeInBytes, BufferUsage bufferUsage) override;
	
	///@copydoc NativeGraphicsDevice
	std::unique_ptr<NativeVertexBuffer>
	CreateVertexBuffer(void const* vertices, std::uint32_t sizeInBytes,
		BufferUsage bufferUsage) override;

	///@copydoc NativeGraphicsDevice
	std::unique_ptr<NativeBlendState>
	CreateBlendState(BlendDescription const& description) override;

	///@copydoc NativeGraphicsDevice
	std::unique_ptr<NativeDepthStencilState>
	CreateDepthStencilState(DepthStencilDescription const& description) override;

	///@copydoc NativeGraphicsDevice
	std::unique_ptr<NativeSamplerState>
	CreateSamplerState(SamplerDescription const& description) override;

	///@copydoc NativeGraphicsDevice
	std::unique_ptr<NativeRasterizerState>
	CreateRasterizerState(RasterizerDescription const& description) override;
	
	///@copydoc NativeGraphicsDevice
	std::unique_ptr<NativeEffectPass>
	CreateEffectPass(ShaderBytecode const& vertexShaderBytecode,
		ShaderBytecode const& pixelShaderBytecode) override;
	
	///@copydoc NativeGraphicsDevice
	std::unique_ptr<NativeConstantBuffer> CreateConstantBuffer(
		std::uint32_t byteConstants) override;
	
	///@copydoc NativeGraphicsDevice
	std::unique_ptr<NativeEffectReflection> CreateEffectReflection(
		NativeEffectPass & nativeEffectPass) override;
	
	///@copydoc NativeGraphicsDevice
	std::unique_ptr<NativeInputLayout>
	CreateInputLayout(NativeEffectPass & nativeEffectPass,
		std::vector<VertexBufferBinding> const& vertexBufferBindings) override;
	
	///@copydoc NativeGraphicsDevice
	std::unique_ptr<NativeTexture2D>
	CreateTexture2D(std::int32_t width, std::int32_t height,
		std::uint32_t mipmapLevels, SurfaceFormat format) override;
	
	///@copydoc NativeGraphicsDevice
	std::unique_ptr<NativeRenderTarget2D>
	CreateRenderTarget2D(std::int32_t width, std::int32_t height,
		std::uint32_t mipmapLevels, SurfaceFormat format, DepthFormat depthStencilFormat) override;
};

}// namespace GL4
}// namespace RenderSystem
}// namespace Details
}// namespace Pomdog

#endif // !defined(POMDOG_SRC_GL4_GRAPHICSDEVICEGL4_74F5BC81_6BDB_4FDC_99F4_DF45CEC32B5F_HPP)
