// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#include "VertexBufferGL4.hpp"
#include "ErrorChecker.hpp"
#include "TypesafeHelperGL4.hpp"
#include "../Utility/ScopeGuard.hpp"
#include "Pomdog/Utility/Assert.hpp"
#include "Pomdog/Graphics/BufferUsage.hpp"
#include <utility>

namespace Pomdog {
namespace Detail {
namespace RenderSystem {
namespace GL4 {
namespace {

static GLenum ToVertexBufferUsage(BufferUsage bufferUsage) noexcept
{
    switch (bufferUsage) {
    case BufferUsage::Dynamic: return GL_DYNAMIC_DRAW;
    //case BufferUsage::Dynamic: return GL_STREAM_DRAW;
    case BufferUsage::Immutable: return GL_STATIC_DRAW;
    }
#ifdef _MSC_VER
    return GL_STATIC_DRAW;
#endif
}

}// unnamed namespace
//-----------------------------------------------------------------------
template<>
struct TypesafeHelperGL4::OpenGLGetTraits<VertexBufferObjectGL4> {
    constexpr static GLenum bufferObjectBinding = GL_ARRAY_BUFFER_BINDING;
    constexpr static GLenum bufferObjectTarget = GL_ARRAY_BUFFER;
};
//-----------------------------------------------------------------------
VertexBufferGL4::VertexBufferGL4(std::size_t sizeInBytes, BufferUsage bufferUsage)
    : VertexBufferGL4(nullptr, sizeInBytes, bufferUsage)
{
    POMDOG_ASSERT(bufferUsage != BufferUsage::Immutable);
}
//-----------------------------------------------------------------------
VertexBufferGL4::VertexBufferGL4(void const* vertices, std::size_t sizeInBytes,
    BufferUsage bufferUsage)
{
    POMDOG_ASSERT(bufferUsage == BufferUsage::Immutable ? vertices != nullptr: true);

    // Generate vertex buffer
    bufferObject = ([] {
        VertexBufferObjectGL4 vertexBuffer;
        glGenBuffers(1, vertexBuffer.Data());
        return std::move(vertexBuffer);
    })();

    auto const oldBufferObject = TypesafeHelperGL4::Get<VertexBufferObjectGL4>();
    ScopeGuard scope([&oldBufferObject]{
        TypesafeHelperGL4::BindBuffer(oldBufferObject);
    });

    POMDOG_ASSERT(bufferObject);
    TypesafeHelperGL4::BindBuffer(*bufferObject);
    POMDOG_CHECK_ERROR_GL4("glBindBuffer");

    POMDOG_ASSERT(sizeInBytes > 0);
    glBufferData(GL_ARRAY_BUFFER, sizeInBytes, vertices,
        ToVertexBufferUsage(bufferUsage));
    POMDOG_CHECK_ERROR_GL4("glBufferData");
}
//-----------------------------------------------------------------------
VertexBufferGL4::~VertexBufferGL4()
{
    if (bufferObject) {
        glDeleteBuffers(1, bufferObject->Data());
    }
}
//-----------------------------------------------------------------------
void VertexBufferGL4::SetData(std::size_t offsetInBytes,
    void const* source, std::size_t sizeInBytes)
{
    POMDOG_ASSERT(source != nullptr);

    auto const oldBufferObject = TypesafeHelperGL4::Get<VertexBufferObjectGL4>();
    ScopeGuard scope([&oldBufferObject]{
        TypesafeHelperGL4::BindBuffer(oldBufferObject);
    });

    POMDOG_ASSERT(bufferObject);
    TypesafeHelperGL4::BindBuffer(*bufferObject);
    POMDOG_CHECK_ERROR_GL4("glBindBuffer");

    POMDOG_ASSERT(sizeInBytes > 0);
    glBufferSubData(GL_ARRAY_BUFFER, offsetInBytes, sizeInBytes, source);
    POMDOG_CHECK_ERROR_GL4("glBufferSubData");
}
//-----------------------------------------------------------------------
void VertexBufferGL4::BindBuffer()
{
    POMDOG_ASSERT(bufferObject);
    TypesafeHelperGL4::BindBuffer(*bufferObject);
    POMDOG_CHECK_ERROR_GL4("glBindBuffer");
}
//-----------------------------------------------------------------------
}// namespace GL4
}// namespace RenderSystem
}// namespace Detail
}// namespace Pomdog
