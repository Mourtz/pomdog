// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#ifndef POMDOG_BOOTSTRAPPERWIN32_4778D685_HPP
#define POMDOG_BOOTSTRAPPERWIN32_4778D685_HPP

#include "Pomdog/Platform/Win32/PrerequisitesWin32.hpp"
#include "Pomdog/Graphics/SurfaceFormat.hpp"
#include "Pomdog/Graphics/DepthFormat.hpp"
#include "Pomdog/Basic/Export.hpp"
#include <memory>
#include <functional>

namespace Pomdog {

class Game;
class GameHost;

namespace Win32 {

class POMDOG_EXPORT Bootstrap {
public:
    void SetInstance(HINSTANCE hInstance) noexcept;

    void SetCommandShow(int cmdShow) noexcept;

    void SetIcon(HICON icon) noexcept;

    void SetIconSmall(HICON iconSmall) noexcept;

    void SetSurfaceFormat(SurfaceFormat surfaceFormat) noexcept;

    void SetDepthFormat(DepthFormat depthFormat) noexcept;

    void SetPresentationInterval(int presentationInterval) noexcept;

    void SetBackBufferSize(int width, int height) noexcept;

    void SetFullScreen(bool isFullScreen) noexcept;

    void SetOpenGLEnabled(bool openGLEnabled) noexcept;

    void OnError(std::function<void(std::exception const&)> onError);

    void Run(std::function<std::unique_ptr<Game>(
        std::shared_ptr<GameHost> const&)> const& createApp);

private:
    std::function<void(std::exception const&)> onError;
    HINSTANCE hInstance = nullptr;
    int cmdShow = SW_SHOWDEFAULT;
    HICON icon = nullptr;
    HICON iconSmall = nullptr;
    int presentationInterval = 60;
    int backBufferWidth = 800;
    int backBufferHeight = 480;
    SurfaceFormat surfaceFormat = SurfaceFormat::R8G8B8A8_UNorm;
    DepthFormat depthFormat = DepthFormat::Depth24Stencil8;
    bool isFullScreen = false;
    bool openGLEnabled = false;
};

} // namespace Win32
} // namespace Pomdog

#endif // POMDOG_BOOTSTRAPPERWIN32_4778D685_HPP
