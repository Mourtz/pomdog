//
//  Copyright (C) 2013 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#include "IndexBufferGL4.hpp"
#include <Pomdog/Utility/Assert.hpp>
#include <Pomdog/Graphics/BufferUsage.hpp>
#include <Pomdog/Graphics/IndexElementSize.hpp>
#include "ErrorChecker.hpp"
#include "TypesafeHelperGL4.hpp"
#include "../Utility/ScopeGuard.hpp"

namespace Pomdog {
namespace Details {
namespace RenderSystem {
namespace GL4 {
//-----------------------------------------------------------------------
template<> struct TypesafeHelperGL4::OpenGLGetTraits<IndexBufferObjectGL4>
{
	constexpr static GLenum parameter_name = GL_ELEMENT_ARRAY_BUFFER_BINDING;
};
//-----------------------------------------------------------------------
static GLenum ToIndexBufferUsage(BufferUsage bufferUsage)
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
//-----------------------------------------------------------------------
static GLsizeiptr ToIndexElementOffsetBytes(IndexElementSize elementSize)
{
	switch (elementSize)
	{
	case IndexElementSize::ThirtyTwoBits: return 4;
	case IndexElementSize::SixteenBits: return 2;
	};
#ifdef _MSC_VER
	return 1;// FUS RO DAH!!!
#endif
}
//-----------------------------------------------------------------------
IndexBufferGL4::IndexBufferGL4(void const* indices, std::size_t indexCount,
	IndexElementSize elementSize, BufferUsage bufferUsage)
	: bufferObject(0L)
	, bufferObjectEnable(false)
{
	auto const oldBufferObject = TypesafeHelperGL4::Get<IndexBufferObjectGL4>();
	ScopeGuard scope([&oldBufferObject]{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, oldBufferObject.value);
	});

	// Generate index buffer
	glGenBuffers(1, &bufferObject);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObject.value);

	#ifdef DEBUG
	ErrorChecker::CheckError("glBindBuffer", __FILE__, __LINE__);
	#endif

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ToIndexElementOffsetBytes(elementSize) * indexCount,
		static_cast<GLvoid const*>(indices),
		ToIndexBufferUsage(bufferUsage));

	#ifdef DEBUG
	ErrorChecker::CheckError("glBufferData", __FILE__, __LINE__);
	#endif
}
//-----------------------------------------------------------------------
IndexBufferGL4::~IndexBufferGL4()
{
	if (bufferObjectEnable) {
		glDeleteBuffers(1, &bufferObject);
	}
}
//-----------------------------------------------------------------------
void IndexBufferGL4::SetData(void const* source, std::size_t indexCount, IndexElementSize elementSize)
{
	POMDOG_ASSERT(source != nullptr);
	POMDOG_ASSERT(indexCount > 0);

	auto const oldBufferObject = TypesafeHelperGL4::Get<IndexBufferObjectGL4>();
	ScopeGuard scope([&oldBufferObject]{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, oldBufferObject.value);
	});

	POMDOG_ASSERT(bufferObjectEnable);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObject.value);

	#ifdef DEBUG
	ErrorChecker::CheckError("glBindBuffer", __FILE__, __LINE__);
	#endif

	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0,
		ToIndexElementOffsetBytes(elementSize) * indexCount,
		source);

	#ifdef DEBUG
	ErrorChecker::CheckError("glBufferSubData", __FILE__, __LINE__);
	#endif
}
//-----------------------------------------------------------------------
}// namespace GL4
}// namespace RenderSystem
}// namespace Details
}// namespace Pomdog