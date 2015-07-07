// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#ifndef POMDOG_OPENGLCONTEXTX11_7F7BD17E_HPP
#define POMDOG_OPENGLCONTEXTX11_7F7BD17E_HPP

#include "../RenderSystem.GL4/OpenGLContext.hpp"
#include "../RenderSystem.GL4/OpenGLPrerequisites.hpp"
#include <GL/glx.h>
#include <memory>

namespace Pomdog {
namespace Detail {
namespace X11 {

class GameWindowX11;

class OpenGLContextX11 final : public GL4::OpenGLContext {
public:
    OpenGLContextX11() = delete;

    OpenGLContextX11(
        std::shared_ptr<GameWindowX11> const& window,
        GLXFBConfig const& framebufferConfig);

    ~OpenGLContextX11();

    void MakeCurrent() override;

    void ClearCurrent() override;

    void SwapBuffers() override;

    bool IsOpenGL3Supported() const noexcept;

private:
    std::shared_ptr<GameWindowX11> window;
    ::GLXContext glxContext;
    bool isOpenGL3Supported;
};

} // namespace X11
} // namespace Detail
} // namespace Pomdog

#endif // POMDOG_OPENGLCONTEXTX11_7F7BD17E_HPP
