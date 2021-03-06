// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#ifndef POMDOG_TOGGLESWITCH_62F7E7F0_HPP
#define POMDOG_TOGGLESWITCH_62F7E7F0_HPP

#include "Control.hpp"
#include "detail/UIEventConnection.hpp"

namespace Pomdog {
namespace UI {

class ToggleSwitch: public Control, public std::enable_shared_from_this<ToggleSwitch> {
public:
    ToggleSwitch();

    bool IsOn() const;
    void IsOn(bool isOn);

    bool IsEnabled() const;
    void IsEnabled(bool isEnabled);

    std::string OnContent() const;
    void OnContent(std::string const& onContent);

    std::string OffContent() const;
    void OffContent(std::string const& offContent);

    UI::HorizontalAlignment HorizontalAlignment() const override { return UI::HorizontalAlignment::Stretch; }
    UI::VerticalAlignment VerticalAlignment() const override { return UI::VerticalAlignment::Top; }

    void OnParentChanged() override;

    void OnPointerPressed(PointerPoint const& pointerPoint) override;

    void OnPointerReleased(PointerPoint const& pointerPoint) override;

    void OnRenderSizeChanged(std::uint32_t width, std::uint32_t height) override;

    void Draw(DrawingContext & drawingContext) override;

    // Events:
    Signal<void(bool isOn)> Toggled;

private:
    class ToggleSwitchButton {
    public:
        ToggleSwitchButton(std::uint16_t width, std::uint16_t height);

        void Draw(DrawingContext & drawingContext, bool isOn, bool isEnabled);

        std::uint16_t Width;
        std::uint16_t Height;
    };

    ToggleSwitchButton button;
    Detail::UIEventConnection connection;
    std::string onContent;
    std::string offContent;
    bool isOn;
    bool isEnabled;
};

}// namespace UI
}// namespace Pomdog

#endif // POMDOG_TOGGLESWITCH_62F7E7F0_HPP
