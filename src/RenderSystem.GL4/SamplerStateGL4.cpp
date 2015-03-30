// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#include "SamplerStateGL4.hpp"
#include "ErrorChecker.hpp"
#include "Pomdog/Graphics/SamplerDescription.hpp"
#include "Pomdog/Utility/Assert.hpp"
#include <algorithm>
#include <utility>

namespace Pomdog {
namespace Detail {
namespace RenderSystem {
namespace GL4 {
//-----------------------------------------------------------------------
namespace {

using TextureAddressModeGL4 = Tagged<GLenum, TextureAddressMode>;

static TextureAddressModeGL4 ToTextureAddressModeGL4(TextureAddressMode const& address)
{
    switch (address) {
    case TextureAddressMode::Clamp: return TextureAddressModeGL4{ GL_CLAMP_TO_EDGE };
    case TextureAddressMode::Mirror: return TextureAddressModeGL4{ GL_MIRRORED_REPEAT };
    case TextureAddressMode::Wrap: return TextureAddressModeGL4{ GL_REPEAT };
    }
#ifdef _MSC_VER
    return TextureAddressModeGL4{ GL_REPEAT };
#endif
}

}// unnamed namespace
//-----------------------------------------------------------------------
SamplerStateGL4::SamplerStateGL4(SamplerDescription const& description)
{
    samplerObject = ([] {
        SamplerObjectGL4 sampler;
        glGenSamplers(1, sampler.Data());
        POMDOG_CHECK_ERROR_GL4("glGenSamplers");
        return std::move(sampler);
    })();

    glSamplerParameteri(samplerObject->value, GL_TEXTURE_WRAP_S, ToTextureAddressModeGL4(description.AddressU).value);
    glSamplerParameteri(samplerObject->value, GL_TEXTURE_WRAP_T, ToTextureAddressModeGL4(description.AddressV).value);
    glSamplerParameteri(samplerObject->value, GL_TEXTURE_WRAP_R, ToTextureAddressModeGL4(description.AddressW).value);

    POMDOG_CHECK_ERROR_GL4("glSamplerParameteri");

    switch (description.Filter) {
    case TextureFilter::Linear:
        glSamplerParameteri(samplerObject->value, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glSamplerParameteri(samplerObject->value, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        break;
    case TextureFilter::Point:
        glSamplerParameteri(samplerObject->value, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glSamplerParameteri(samplerObject->value, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        break;
    case TextureFilter::LinearMipPoint:
        glSamplerParameteri(samplerObject->value, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        glSamplerParameteri(samplerObject->value, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        break;
    case TextureFilter::PointMipLinear:
        glSamplerParameteri(samplerObject->value, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        glSamplerParameteri(samplerObject->value, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        break;
    case TextureFilter::MinLinearMagPointMipLinear:
        glSamplerParameteri(samplerObject->value, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glSamplerParameteri(samplerObject->value, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        break;
    case TextureFilter::MinLinearMagPointMipPoint:
        glSamplerParameteri(samplerObject->value, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        glSamplerParameteri(samplerObject->value, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        break;
    case TextureFilter::MinPointMagLinearMipLinear:
        glSamplerParameteri(samplerObject->value, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        glSamplerParameteri(samplerObject->value, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        break;
    case TextureFilter::MinPointMagLinearMipPoint:
        glSamplerParameteri(samplerObject->value, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glSamplerParameteri(samplerObject->value, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        break;
    case TextureFilter::Anisotropic:
        {
            ///@todo Not implemented:
            glSamplerParameteri(samplerObject->value, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glSamplerParameteri(samplerObject->value, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            POMDOG_CHECK_ERROR_GL4("glSamplerParameteri");

            POMDOG_ASSERT(1 <= description.MaxAnisotropy && description.MaxAnisotropy <= 16);

            GLfloat deviceMaxAnisotropy = 1.0f;

            glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &deviceMaxAnisotropy);
            POMDOG_CHECK_ERROR_GL4("glGetFloatv");

            deviceMaxAnisotropy = std::min(deviceMaxAnisotropy,
                static_cast<decltype(deviceMaxAnisotropy)>(description.MaxAnisotropy));

            glSamplerParameterf(samplerObject->value, GL_TEXTURE_MAX_ANISOTROPY_EXT, deviceMaxAnisotropy);
            POMDOG_CHECK_ERROR_GL4("glSamplerParameterf");
        }
        break;
    }

    {
        POMDOG_ASSERT(description.MinMipLevel <= description.MaxMipLevel);
        POMDOG_ASSERT(description.MaxMipLevel <= std::numeric_limits<GLfloat>::max());

        glSamplerParameterf(samplerObject->value, GL_TEXTURE_MIN_LOD, description.MaxMipLevel);
        glSamplerParameterf(samplerObject->value, GL_TEXTURE_MAX_LOD, description.MaxMipLevel);
        glSamplerParameterf(samplerObject->value, GL_TEXTURE_LOD_BIAS, description.MipMapLevelOfDetailBias);
        POMDOG_CHECK_ERROR_GL4("glSamplerParameterf");
    }
}
//-----------------------------------------------------------------------
SamplerStateGL4::~SamplerStateGL4()
{
    if (samplerObject) {
        glDeleteSamplers(1, samplerObject->Data());
        POMDOG_CHECK_ERROR_GL4("glDeleteSamplers");
    }
}
//-----------------------------------------------------------------------
void SamplerStateGL4::Apply(NativeGraphicsContext &, int index)
{
    static_assert(GL_TEXTURE19 == (GL_TEXTURE0 + 19), "");
    POMDOG_ASSERT(index >= 0);
    POMDOG_ASSERT(index <= 19);

    POMDOG_ASSERT(samplerObject);
    glBindSampler(index, samplerObject->value);
    POMDOG_CHECK_ERROR_GL4("glBindSampler");
}
//-----------------------------------------------------------------------
}// namespace GL4
}// namespace RenderSystem
}// namespace Detail
}// namespace Pomdog
