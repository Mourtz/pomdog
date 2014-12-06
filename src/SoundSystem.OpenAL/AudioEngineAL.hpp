﻿//
//  Copyright (C) 2013-2014 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#ifndef POMDOG_AUDIOENGINEAL_4B9A3A11_27A6_4393_A5FF_F10183A42D92_HPP
#define POMDOG_AUDIOENGINEAL_4B9A3A11_27A6_4393_A5FF_F10183A42D92_HPP

#if (_MSC_VER > 1000)
#	pragma once
#endif

#include "PrerequisitesOpenAL.hpp"
#include "ContextOpenAL.hpp"
#include "../Utility/Noncopyable.hpp"

namespace Pomdog {
namespace Details {
namespace SoundSystem {
namespace OpenAL {

class AudioEngineAL final: Noncopyable {
public:
	AudioEngineAL();
	~AudioEngineAL();
	
private:
	ContextOpenAL context;
};

}// namespace OpenAL
}// namespace SoundSystem
}// namespace Details
}// namespace Pomdog

#endif // !defined(POMDOG_AUDIOENGINEAL_4B9A3A11_27A6_4393_A5FF_F10183A42D92_HPP)