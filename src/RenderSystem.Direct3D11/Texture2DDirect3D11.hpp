// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#ifndef POMDOG_TEXTURE2DDIRECT3D11_BA251B9A_HPP
#define POMDOG_TEXTURE2DDIRECT3D11_BA251B9A_HPP

#include "PrerequisitesDirect3D11.hpp"
#include "../RenderSystem/NativeTexture2D.hpp"
#include "Pomdog/Graphics/detail/ForwardDeclarations.hpp"
#include <wrl/client.h>

namespace Pomdog {
namespace Detail {
namespace Direct3D11 {

class Texture2DDirect3D11 final: public NativeTexture2D {
public:
    Texture2DDirect3D11(
        ID3D11Device* nativeDevice,
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> const& deviceContext,
        std::int32_t pixelWidth,
        std::int32_t pixelHeight,
        std::int32_t levelCount,
        SurfaceFormat format);

    void SetData(
        std::int32_t pixelWidth,
        std::int32_t pixelHeight,
        std::int32_t levelCount,
        SurfaceFormat format,
        void const* pixelData) override;

    ID3D11ShaderResourceView* GetShaderResourceView() const;

private:
    Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2D;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
};

} // namespace Direct3D11
} // namespace Detail
} // namespace Pomdog

#endif // POMDOG_TEXTURE2DDIRECT3D11_BA251B9A_HPP
