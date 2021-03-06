// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#ifndef POMDOG_STRINGHELPER_F86C26CD_HPP
#define POMDOG_STRINGHELPER_F86C26CD_HPP

#include "Pomdog/Basic/Export.hpp"
#include <string>

namespace Pomdog {

struct POMDOG_EXPORT StringHelper {
    static std::string Format(char const* format, ...)
    #if defined(__has_attribute)
    #if __has_attribute(format)
    __attribute__((__format__(printf, 1, 2)));
    #endif
    #elif __GNUC__ >= 4
    __attribute__((__format__(printf, 1, 2)));
    #else
    ;
    #endif
};

} // namespace Pomdog

#endif // POMDOG_STRINGHELPER_F86C26CD_HPP
