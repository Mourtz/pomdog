// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#ifndef POMDOG_X11ATOMCACHE_77EB19E3_HPP
#define POMDOG_X11ATOMCACHE_77EB19E3_HPP

#include <X11/X.h>

namespace Pomdog {
namespace Detail {
namespace X11 {

struct X11AtomCache {
    Atom WmDeleteWindow = None;
    Atom Utf8String = None;
    Atom NetWmName = None;
    Atom NetWmIconName = None;
};

} // namespace X11
} // namespace Detail
} // namespace Pomdog

#endif // POMDOG_X11ATOMCACHE_77EB19E3_HPP
