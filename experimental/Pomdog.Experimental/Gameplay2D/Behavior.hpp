// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#ifndef POMDOG_BEHAVIOR_00BB3FAF_HPP
#define POMDOG_BEHAVIOR_00BB3FAF_HPP

#include "Pomdog.Experimental/Gameplay/Component.hpp"
#include "Pomdog/Application/Duration.hpp"
#include <memory>

namespace Pomdog {

class GameObject;

class Behavior: public Component<Behavior> {
public:
    virtual ~Behavior() = default;

    virtual void Start(GameObject & gameObject) = 0;

    virtual void Update(GameObject & gameObject, Duration const& frameDuration) = 0;
};

}// namespace Pomdog

#endif // POMDOG_BEHAVIOR_00BB3FAF_HPP
