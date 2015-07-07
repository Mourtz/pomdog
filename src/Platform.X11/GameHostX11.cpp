// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#include "GameHostX11.hpp"
#include "../RenderSystem.GL4/GraphicsContextGL4.hpp"
#include "../RenderSystem.GL4/GraphicsDeviceGL4.hpp"
#include "../RenderSystem/GraphicsCommandQueueImmediate.hpp"
#include "../RenderSystem/GraphicsContext.hpp"
#include "Pomdog/Application/Game.hpp"
#include "Pomdog/Audio/AudioEngine.hpp"
#include "Pomdog/Content/AssetManager.hpp"
#include "Pomdog/Graphics/GraphicsCommandQueue.hpp"
#include "Pomdog/Graphics/GraphicsDevice.hpp"
#include "Pomdog/Graphics/PresentationParameters.hpp"
#include "Pomdog/Utility/Exception.hpp"
#include "Pomdog/Logging/Log.hpp"
#include <string>
#include <vector>
#include <chrono>
#include <thread>

namespace Pomdog {
namespace Detail {
namespace X11 {
namespace {

static bool CheckFrameBufferConfigSupport(::Display* display)
{
    int major = 0;
    int minor = 0;

    if (glXQueryVersion(display, &major, &minor) == False) {
        return false;
    }

    return (((major == 1) && (minor >= 3)) || (major >= 2));
}
//-----------------------------------------------------------------------
static GLXFBConfig ChooseFramebufferConfig(
    Display* display,
    PresentationParameters const& presentationParameters)
{
    if (!CheckFrameBufferConfigSupport(display)) {
        POMDOG_THROW_EXCEPTION(std::runtime_error,
            "GLX of version lower than 1.3.2 is not supported.");
    }

    std::vector<int> visualAttributes = {
        GLX_X_RENDERABLE, True,
        GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
        GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
        GLX_DOUBLEBUFFER, True,
        //GLX_SAMPLE_BUFFERS, 1,
        //GLX_SAMPLES, 4,
    };

    switch (presentationParameters.BackBufferFormat) {
    case SurfaceFormat::R16G16B16A16_Float:
        visualAttributes.push_back(GLX_RENDER_TYPE);
        visualAttributes.push_back(GLX_RGBA_FLOAT_BIT_ARB);
        visualAttributes.push_back(GLX_RED_SIZE);
        visualAttributes.push_back(16);
        visualAttributes.push_back(GLX_GREEN_SIZE);
        visualAttributes.push_back(16);
        visualAttributes.push_back(GLX_BLUE_SIZE);
        visualAttributes.push_back(16);
        visualAttributes.push_back(GLX_ALPHA_SIZE);
        visualAttributes.push_back(16);
        break;
    case SurfaceFormat::R32G32B32A32_Float:
        visualAttributes.push_back(GLX_RENDER_TYPE);
        visualAttributes.push_back(GLX_RGBA_FLOAT_BIT_ARB);
        visualAttributes.push_back(GLX_RED_SIZE);
        visualAttributes.push_back(32);
        visualAttributes.push_back(GLX_GREEN_SIZE);
        visualAttributes.push_back(32);
        visualAttributes.push_back(GLX_BLUE_SIZE);
        visualAttributes.push_back(32);
        visualAttributes.push_back(GLX_ALPHA_SIZE);
        visualAttributes.push_back(32);
        break;
    default:
        visualAttributes.push_back(GLX_RENDER_TYPE);
        visualAttributes.push_back(GLX_RGBA_BIT);
        visualAttributes.push_back(GLX_RED_SIZE);
        visualAttributes.push_back(8);
        visualAttributes.push_back(GLX_GREEN_SIZE);
        visualAttributes.push_back(8);
        visualAttributes.push_back(GLX_BLUE_SIZE);
        visualAttributes.push_back(8);
        visualAttributes.push_back(GLX_ALPHA_SIZE);
        visualAttributes.push_back(8);
        break;
    }

    switch (presentationParameters.DepthStencilFormat) {
    case DepthFormat::Depth16:
        visualAttributes.push_back(GLX_DEPTH_SIZE);
        visualAttributes.push_back(16);
        break;
    case DepthFormat::Depth24Stencil8:
        visualAttributes.push_back(GLX_DEPTH_SIZE);
        visualAttributes.push_back(24);
        visualAttributes.push_back(GLX_STENCIL_SIZE);
        visualAttributes.push_back(8);
        break;
    case DepthFormat::Depth32:
        visualAttributes.push_back(GLX_DEPTH_SIZE);
        visualAttributes.push_back(32);
        break;
    default:
        break;
    }

    visualAttributes.push_back(None);

    int framebufferConfigCount = 0;
    auto framebufferConfigs = glXChooseFBConfig(display, DefaultScreen(display),
        visualAttributes.data(), &framebufferConfigCount);

    if ((framebufferConfigs == nullptr) || (framebufferConfigCount <= 0)) {
        POMDOG_THROW_EXCEPTION(std::runtime_error,
            "Failed to retrieve FBConfig");
    }

    Optional<GLXFBConfig> bestConfig;
    int bestSampleCount = 0;

    for (int index = 0; index < framebufferConfigCount; ++index)
    {
        auto framebufferConfig = framebufferConfigs[index];
        auto visualInfo = glXGetVisualFromFBConfig(display, framebufferConfig);

        if (visualInfo != nullptr)
        {
            int sampleBuffers = 0;
            int sampleCount = 0;
            glXGetFBConfigAttrib(display, framebufferConfig, GLX_SAMPLE_BUFFERS, &sampleBuffers);
            glXGetFBConfigAttrib(display, framebufferConfig, GLX_SAMPLES, &sampleCount);

            if (!bestConfig || ((sampleBuffers != 0) && (sampleCount > bestSampleCount))) {
                bestConfig = framebufferConfig;
                bestSampleCount = sampleCount;
            }
        }

        XFree(visualInfo);
    }

    XFree(framebufferConfigs);

    if (!bestConfig) {
        POMDOG_THROW_EXCEPTION(std::runtime_error,
            "Cannot find any matching FBConfig");
    }

    return *bestConfig;
}

} // unnamed namespace
//-----------------------------------------------------------------------
#ifdef POMDOG_COMPILER_CLANG
#pragma mark - GameHostX11
#endif
//-----------------------------------------------------------------------
class GameHostX11::Impl {
public:
    explicit Impl(PresentationParameters const& presentationParameters);

    ~Impl();

    void Run(Game & game);

    void Exit();

private:
    void MessagePump();
    void ProcessEvent(::XEvent & event);

    void RenderFrame(Game & game);

public:
    GameClock clock;
    std::shared_ptr<X11Context> x11Context;
    std::shared_ptr<GameWindowX11> window;
    std::shared_ptr<OpenGLContextX11> openGLContext;
    std::shared_ptr<Pomdog::GraphicsDevice> graphicsDevice;
    std::shared_ptr<Pomdog::Detail::GraphicsContext> graphicsContext;
    std::shared_ptr<Pomdog::GraphicsCommandQueue> graphicsCommandQueue;
    std::shared_ptr<Pomdog::AudioEngine> audioEngine;
    std::unique_ptr<Pomdog::AssetManager> assetManager;
    std::unique_ptr<KeyboardX11> keyboard;
    MouseX11 mouse;
    Duration presentationInterval;
    bool exitRequest;
};
//-----------------------------------------------------------------------
GameHostX11::Impl::Impl(PresentationParameters const& presentationParameters)
    : exitRequest(false)
{
    POMDOG_ASSERT(presentationParameters.PresentationInterval > 0);
    presentationInterval = Duration(1.0) / presentationParameters.PresentationInterval;

    x11Context = std::make_shared<X11Context>();

    auto framebufferConfig = ChooseFramebufferConfig(
        x11Context->Display, presentationParameters);

    window = std::make_shared<GameWindowX11>(
        x11Context,
        framebufferConfig,
        presentationParameters.BackBufferWidth,
        presentationParameters.BackBufferHeight);

    openGLContext = std::make_shared<OpenGLContextX11>(window, framebufferConfig);

    if (!openGLContext->IsOpenGL3Supported()) {
        POMDOG_THROW_EXCEPTION(std::runtime_error,
            "Pomdog doesn't support versions of OpenGL lower than 3.3/4.0.");
    }

    openGLContext->MakeCurrent();

    auto const errorCode = glewInit();
    if (GLEW_OK != errorCode) {
        auto description = reinterpret_cast<char const*>(glewGetErrorString(errorCode));
        POMDOG_THROW_EXCEPTION(std::runtime_error, description);
    }

    using GL4::GraphicsContextGL4;
    using GL4::GraphicsDeviceGL4;

    graphicsDevice = std::make_shared<Pomdog::GraphicsDevice>(
        std::make_unique<GraphicsDeviceGL4>());

    graphicsContext = std::make_shared<Detail::GraphicsContext>(
        std::make_unique<GraphicsContextGL4>(openGLContext, window),
        presentationParameters);

    graphicsCommandQueue = std::make_shared<Pomdog::GraphicsCommandQueue>(
        std::make_unique<GraphicsCommandQueueImmediate>(graphicsContext));

    audioEngine = std::make_shared<Pomdog::AudioEngine>();

    keyboard = std::make_unique<KeyboardX11>(x11Context->Display);

    std::string rootDirectory = "Content";
    Detail::AssetLoaderContext loaderContext{ rootDirectory, graphicsDevice };
    assetManager = std::make_unique<Pomdog::AssetManager>(std::move(loaderContext));
}
//-----------------------------------------------------------------------
GameHostX11::Impl::~Impl()
{
    keyboard.reset();
    assetManager.reset();
    audioEngine.reset();
    graphicsCommandQueue.reset();
    graphicsContext.reset();
    graphicsDevice.reset();
    openGLContext.reset();
    window.reset();
}
//-----------------------------------------------------------------------
void GameHostX11::Impl::MessagePump()
{
    ::XLockDisplay(x11Context->Display);
    const auto eventCount = XPending(x11Context->Display);
    ::XUnlockDisplay(x11Context->Display);

    for (int index = 0; index < eventCount; ++index) {
        ::XEvent event;
        ::XLockDisplay(x11Context->Display);
        ::XNextEvent(window->NativeDisplay(), &event);
        ::XUnlockDisplay(x11Context->Display);

        ProcessEvent(event);
    }
}
//-----------------------------------------------------------------------
void GameHostX11::Impl::ProcessEvent(::XEvent & event)
{
    if (event.xany.window != window->NativeWindow()) {
        return;
    }

    switch (event.type) {
    case ClientMessage: {
        auto const& atoms = x11Context->Atoms;
        if (static_cast<Atom>(event.xclient.data.l[0]) == atoms.WmDeleteWindow) {
            Log::Internal("X11: wmDeleteMessage");
            exitRequest = true;
        }
        break;
    }
    case KeyPress:
    case KeyRelease: {
        keyboard->HandleEvent(event);
        break;
    }
    case ButtonPress:
    case ButtonRelease:
    case EnterNotify:
    case MotionNotify:
    case LeaveNotify: {
        mouse.HandleEvent(event);
        break;
    }
    default:
        break;
    }

    window->ProcessEvent(event);
}
//-----------------------------------------------------------------------
void GameHostX11::Impl::Run(Game & game)
{
    game.Initialize();

    while (!exitRequest)
    {
        clock.Tick();
        MessagePump();

        game.Update();
        RenderFrame(game);

        auto elapsedTime = clock.ElapsedTime();

        if (elapsedTime < presentationInterval) {
            auto sleepTime = (presentationInterval - elapsedTime);
            std::this_thread::sleep_for(sleepTime);
        }
    }
}
//-----------------------------------------------------------------------
void GameHostX11::Impl::Exit()
{
    exitRequest = true;
}
//-----------------------------------------------------------------------
void GameHostX11::Impl::RenderFrame(Game & game)
{
    if (!window || window->IsMinimized()) {
        // skip rendering
        return;
    }

    game.Draw();
}
//-----------------------------------------------------------------------
#ifdef POMDOG_COMPILER_CLANG
#pragma mark - GameHostX11
#endif
//-----------------------------------------------------------------------
GameHostX11::GameHostX11(PresentationParameters const& presentationParameters)
    : impl(std::make_unique<Impl>(presentationParameters))
{
}
//-----------------------------------------------------------------------
GameHostX11::~GameHostX11() = default;
//-----------------------------------------------------------------------
void GameHostX11::Run(Game & game)
{
    POMDOG_ASSERT(impl);
    impl->Run(game);
}
//-----------------------------------------------------------------------
void GameHostX11::Exit()
{
    POMDOG_ASSERT(impl);
    impl->Exit();
}
//-----------------------------------------------------------------------
std::shared_ptr<Pomdog::GameWindow> GameHostX11::Window()
{
    POMDOG_ASSERT(impl);
    return impl->window;
}
//-----------------------------------------------------------------------
std::shared_ptr<Pomdog::GameClock> GameHostX11::Clock()
{
    POMDOG_ASSERT(impl);
    auto gameHost = shared_from_this();
    std::shared_ptr<Pomdog::GameClock> sharedClock(gameHost, &impl->clock);
    return std::move(sharedClock);
}
//-----------------------------------------------------------------------
std::shared_ptr<Pomdog::GraphicsDevice> GameHostX11::GraphicsDevice()
{
    POMDOG_ASSERT(impl);
    return impl->graphicsDevice;
}
//-----------------------------------------------------------------------
std::shared_ptr<Pomdog::GraphicsCommandQueue> GameHostX11::GraphicsCommandQueue()
{
    POMDOG_ASSERT(impl);
    return impl->graphicsCommandQueue;
}
//-----------------------------------------------------------------------
std::shared_ptr<Pomdog::AudioEngine> GameHostX11::AudioEngine()
{
    POMDOG_ASSERT(impl);
    POMDOG_ASSERT(impl->audioEngine);
    return impl->audioEngine;
}
//-----------------------------------------------------------------------
std::shared_ptr<Pomdog::AssetManager> GameHostX11::AssetManager()
{
    POMDOG_ASSERT(impl);
    POMDOG_ASSERT(impl->assetManager);
    auto gameHost = shared_from_this();
    std::shared_ptr<Pomdog::AssetManager> sharedAssetManager(
        gameHost, impl->assetManager.get());
    return std::move(sharedAssetManager);
}
//-----------------------------------------------------------------------
std::shared_ptr<Pomdog::Keyboard> GameHostX11::Keyboard()
{
    POMDOG_ASSERT(impl);
    auto gameHost = shared_from_this();
    std::shared_ptr<Pomdog::Keyboard> sharedKeyboard(
        gameHost, impl->keyboard.get());
    return std::move(sharedKeyboard);
}
//-----------------------------------------------------------------------
std::shared_ptr<Pomdog::Mouse> GameHostX11::Mouse()
{
    POMDOG_ASSERT(impl);
    auto gameHost = shared_from_this();
    std::shared_ptr<Pomdog::Mouse> sharedMouse(gameHost, &impl->mouse);
    return std::move(sharedMouse);
}
//-----------------------------------------------------------------------
} // namespace X11
} // namespace Detail
} // namespace Pomdog
