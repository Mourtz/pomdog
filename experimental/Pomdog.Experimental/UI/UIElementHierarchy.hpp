// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#ifndef POMDOG_UIELEMENTHIERARCHY_ECF3A74B_HPP
#define POMDOG_UIELEMENTHIERARCHY_ECF3A74B_HPP

#include "UIElement.hpp"
#include "UIEventDispatcher.hpp"
#include <Pomdog/Pomdog.hpp>
#include <algorithm>
#include <vector>
#include <memory>

namespace Pomdog {
namespace UI {

class DrawingContext;
class GameEditorView;
class UIView;

class UIElementHierarchy {
public:
    explicit UIElementHierarchy(std::shared_ptr<GameWindow> const& window);

    void Touch(MouseState const& mouseState);

    void UpdateAnimation(Duration const& frameDuration);

    void AddChild(std::shared_ptr<UIView> const& node);

    void AddChild(std::shared_ptr<UIView> && node);

    void Draw(DrawingContext & drawingContext);

    void RenderSizeChanged(std::uint32_t width, std::uint32_t height);

    std::shared_ptr<UIEventDispatcher> Dispatcher() const;

private:
    std::shared_ptr<UIEventDispatcher> dispatcher;
    std::shared_ptr<GameEditorView> root;
};

}// namespace UI
}// namespace Pomdog

#endif // POMDOG_UIELEMENTHIERARCHY_ECF3A74B_HPP
