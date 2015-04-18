// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#include "HLSLCompiling.hpp"
#include "../RenderSystem/ShaderBytecode.hpp"
#include "../RenderSystem/ShaderCompileOptions.hpp"
#include "../Utility/PathHelper.hpp"
#include "Pomdog/Platform/Win32/PrerequisitesWin32.hpp"
#include "Pomdog/Logging/Log.hpp"
#include "Pomdog/Utility/StringFormat.hpp"
#include "Pomdog/Utility/Assert.hpp"
#include "Pomdog/Utility/Exception.hpp"
#include <utility>
#include <vector>
#include <string>
#include <fstream>

namespace Pomdog {
namespace Detail {
namespace RenderSystem {
namespace Direct3D {
namespace {

static std::string ToString(ShaderProfile const& profile)
{
    std::string output;

    switch (profile.PipelineStage) {
    case ShaderPipelineStage::VertexShader:
        output += "vs_";
        break;
    case ShaderPipelineStage::PixelShader:
        output += "ps_";
        break;
    //case ShaderPipelineStage::GeometryShader:
    //    output += "gs_";
    //    break;
    //case ShaderPipelineStage::DomainShader:
    //    output += "ds_";
    //    break;
    //case ShaderPipelineStage::ComputeShader:
    //    output += "cs_";
    //    break;
    //case ShaderPipelineStage::HullShader:
    //    output += "hs_";
    //    break;
    }

    output += std::to_string(profile.ShaderModel.Major);
    output += '_';
    output += std::to_string(profile.ShaderModel.Minor);

    return std::move(output);
}
//-----------------------------------------------------------------------
static std::vector<std::uint8_t> ReadBinaryFile(std::ifstream && streamIn)
{
    std::ifstream stream = std::move(streamIn);
    POMDOG_ASSERT(stream);

    stream.seekg(0, stream.end);
    auto const length = static_cast<std::size_t>(stream.tellg());
    stream.seekg(0, stream.beg);

    std::vector<std::uint8_t> result(length + 1, 0);
    stream.read(reinterpret_cast<char*>(result.data()), result.size());
    return std::move(result);
}
//-----------------------------------------------------------------------
class HLSLCodeInclude : public ID3DInclude {
private:
    std::string currentDirectory;
    std::vector<std::uint8_t> outputSource;

public:
    explicit HLSLCodeInclude(std::string const& curentDirectoryIn)
        : currentDirectory(curentDirectoryIn)
    {}

    HRESULT __stdcall Open(D3D_INCLUDE_TYPE includeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID* ppData, UINT* pBytes)
    {
        UNREFERENCED_PARAMETER(pParentData);

        //if (D3D10_INCLUDE_FORCE_DWORD == includeType) {
        //    return E_FAIL;
        //}

        std::string includePath;
        if (D3D_INCLUDE_LOCAL == includeType) {
            includePath = PathHelper::Join(currentDirectory, pFileName);
        }
        else {
            includePath = pFileName;
        }

        if (D3D_INCLUDE_LOCAL != includeType
            && D3D_INCLUDE_SYSTEM != includeType) {
            return E_FAIL;
        }

#if defined(DEBUG) && !defined(NDEBUG)
        if (D3D_INCLUDE_LOCAL == includeType) {
            Log::Internal("ShaderInclude: Local");
        }
        else if (D3D_INCLUDE_SYSTEM == includeType) {
            Log::Internal("ShaderInclude: System");
        }
        Log::Internal(StringFormat("include shader file : %s", includePath.c_str()));
#endif

        std::ifstream stream(includePath);

        if (stream) {
            Log::Internal(StringFormat("Could not find a shader source file %s", includePath.c_str()));
            return E_FAIL;
        }

        outputSource = ReadBinaryFile(std::move(stream));

        *ppData = outputSource.data();
        *pBytes = static_cast<UINT>(outputSource.size());

        return S_OK;
    }

    HRESULT __stdcall Close(LPCVOID pData)
    {
        UNREFERENCED_PARAMETER(pData);
        outputSource.clear();
        return S_OK;
    }
};
//-----------------------------------------------------------------------
static void CompileFromShaderFile(ShaderBytecode const& shaderBytecode,
    std::string const& entrypoint, std::string const& shaderProfile,
    std::string const& currentDirectory, D3D_SHADER_MACRO const* preprocessorMacros,
    ID3DBlob** ppBlobOut)
{
    POMDOG_ASSERT(shaderBytecode.Code != nullptr);
    POMDOG_ASSERT(shaderBytecode.ByteLength > 0);

    DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(DEBUG) && !defined(NDEBUG)
    shaderFlags |= D3DCOMPILE_DEBUG;
#endif

    HLSLCodeInclude shaderInclude(currentDirectory);
    Microsoft::WRL::ComPtr<ID3DBlob> errorBlob;

    HRESULT hr = ::D3DCompile(shaderBytecode.Code, shaderBytecode.ByteLength,
        nullptr, preprocessorMacros, &shaderInclude,
        entrypoint.c_str(), shaderProfile.c_str(), shaderFlags, 0, ppBlobOut, &errorBlob);

    if (FAILED(hr))
    {
        if (errorBlob) {
            POMDOG_THROW_EXCEPTION(std::runtime_error, StringFormat(
                "Failed to compile shader.\n"
                "error: %s",
                reinterpret_cast<LPCSTR>(errorBlob->GetBufferPointer())));
        }
        POMDOG_THROW_EXCEPTION(std::runtime_error, "Failed to compile shader.");
    }

    if (errorBlob) {
        Log::Internal(StringFormat("warning (compile shader): %s",
            reinterpret_cast<LPCSTR>(errorBlob->GetBufferPointer())));
    }
}

} // unnamed namespace
//-----------------------------------------------------------------------
Microsoft::WRL::ComPtr<ID3DBlob> HLSLCompiling::CompileShader(
    ShaderBytecode const& shaderBytecode,
    ShaderCompileOptions const& compileOptions)
{
    const auto target = ToString(compileOptions.Profile);
    POMDOG_ASSERT(!target.empty());

    std::vector<D3D_SHADER_MACRO> defines;
    defines.reserve(compileOptions.PreprocessorMacros.size());

    for (auto & macro: compileOptions.PreprocessorMacros)
    {
        if (macro.Name.empty()) {
            continue;
        }

        D3D_SHADER_MACRO shaderMacro;
        shaderMacro.Name = macro.Name.c_str();
        shaderMacro.Definition = macro.Definition.empty() ? nullptr: macro.Definition.c_str();
        defines.push_back(std::move(shaderMacro));
    }

    if (!defines.empty())
    {
        D3D_SHADER_MACRO shaderMacro;
        shaderMacro.Name = nullptr;
        shaderMacro.Definition = nullptr;
        defines.push_back(std::move(shaderMacro));
    }

    Microsoft::WRL::ComPtr<ID3DBlob> codeBlob;
    CompileFromShaderFile(shaderBytecode,
        compileOptions.EntryPoint,
        target,
        compileOptions.CurrentDirectory,
        (defines.empty() ? nullptr: defines.data()),
        &codeBlob);

    return std::move(codeBlob);
}

} // namespace Direct3D
} // namespace RenderSystem
} // namespace Detail
} // namespace Pomdog