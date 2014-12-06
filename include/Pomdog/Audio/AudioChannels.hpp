﻿//
//  Copyright (C) 2013-2014 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#ifndef POMDOG_AUDIOCHANNELS_026C7FB5_7B97_42C1_B935_4CDE40E4B4F7_HPP
#define POMDOG_AUDIOCHANNELS_026C7FB5_7B97_42C1_B935_4CDE40E4B4F7_HPP

#if (_MSC_VER > 1000)
#	pragma once
#endif

#include <cstdint>

namespace Pomdog {

///@~Japanese
/// @brief オーディオデータのチャンネル数を示します。
enum class AudioChannels: std::uint8_t {
	///@~Japanese
	/// @brief チャンネル数1つのモノラル音声
	Mono,

	///@~Japanese
	/// @brief チャンネル数2つのステレオ音声
	Stereo,
};

}// namespace Pomdog

#endif // !defined(POMDOG_AUDIOCHANNELS_026C7FB5_7B97_42C1_B935_4CDE40E4B4F7_HPP)