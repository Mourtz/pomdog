//
//  Copyright (C) 2013 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#ifndef POMDOG_VECTOR4_HPP
#define POMDOG_VECTOR4_HPP

#if (_MSC_VER > 1000)
#	pragma once
#endif

#include "detail/FloatingPointVector4.hpp"

namespace Pomdog {

/// @addtogroup Framework
/// @{
/// @addtogroup Math
/// @{

///@~English
/// @brief vector in four-dimensional space.
///@~Japanese
/// @brief 4 つの要素を持つベクトル（4 次元ベクトル）を定義します。
using Vector4 = Details::FloatingPointVector4<float>;

/// @}
/// @}

}// namespace Pomdog

#endif // !defined(POMDOG_VECTOR4_HPP)
