// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#ifndef POMDOG_SHADERCOMPILING_C56F5C9E_HPP
#define POMDOG_SHADERCOMPILING_C56F5C9E_HPP

#include <wrl/client.h>
#if defined(_XBOX_ONE) && defined(_TITLE)
#include <d3dcompiler_x.h>
#else
#include <d3dcompiler.h>
#include <d3dcommon.h>
#endif
#include <cstdint>

namespace Pomdog {
namespace Detail {
namespace RenderSystem {

class ShaderBytecode;
class ShaderCompileOptions;

namespace Direct3D {

struct HLSLCompiling {
    static Microsoft::WRL::ComPtr<ID3DBlob> CompileShader(
        ShaderBytecode const& shaderBytecode,
        ShaderCompileOptions const& compileOptions);
};

} // namespace Direct3D
} // namespace RenderSystem
} // namespace Detail
} // namespace Pomdog

#endif // POMDOG_SHADERCOMPILING_C56F5C9E_HPP