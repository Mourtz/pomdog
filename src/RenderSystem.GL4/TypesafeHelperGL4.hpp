﻿//
//  Copyright (C) 2013 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#ifndef POMDOG_TYPESAFEHELPERGL4_8C888821_4B58_49F0_B733_396CDAF91F53_HPP
#define POMDOG_TYPESAFEHELPERGL4_8C888821_4B58_49F0_B733_396CDAF91F53_HPP

#if (_MSC_VER > 1000)
#	pragma once
#endif

#include <type_traits>
#include "OpenGLPrerequisites.hpp"
#include <Pomdog/Utility/detail/Tagged.hpp>

namespace Pomdog {
namespace Details {
namespace RenderSystem {
namespace GL4 {

namespace TypesafeHelperGL4 {

template <class TaggedClass>
struct OpenGLGetTraits {};

template <class TaggedClass> static
TaggedClass Get(OpenGLGetTraits<TaggedClass>* = nullptr)
{
	typedef typename TaggedClass::value_type value_type;

	static_assert(std::is_fundamental<value_type>::value, "");
	static_assert(std::is_integral<value_type>::value, "");

	constexpr GLenum parameterName = OpenGLGetTraits<TaggedClass>::parameter_name;

	GLint oldBuffer = 0;
	glGetIntegerv(parameterName, &oldBuffer);

	return TaggedClass(static_cast<value_type>(oldBuffer));
}

}// namespace TypesafeHelperGL4

}// namespace GL4
}// namespace RenderSystem
}// namespace Details
}// namespace Pomdog

#endif // !defined(POMDOG_TYPESAFEHELPERGL4_8C888821_4B58_49F0_B733_396CDAF91F53_HPP)