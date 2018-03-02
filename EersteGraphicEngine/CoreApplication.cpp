#include "CoreApplication.h"

namespace ege
{
    CoreApplication::CoreApplication(const START_UP_DESC& desc)
        : _runMainLoop(true)
        , _paused(false)
        , _minimized(false)
        , _maximized(false)
        , _resizing(false)
        , _window(nullptr)
        , _startUpDesc(desc)
    {
    }

    CoreApplication::~CoreApplication()
    {
    }

    void CoreApplication::RunMainLoop()
    {
        while (_runMainLoop)
        {
            _window->Update();

            if (!_paused)
            {
                gTime().Update();
                _window->ComputeFrameRate();
            }
            else
            {
                EGE_SLEEP(100);
            }
        }
    }

    void CoreApplication::StopMainLoop()
    {
        gTime().Update();
        _runMainLoop = false;
    }

    void CoreApplication::Pause(bool pause)
    {
        _paused = pause;
    }

    void CoreApplication::Minimized(bool minimized)
    {
        _minimized = minimized;
    }

    void CoreApplication::Maximized(bool maximized)
    {
        _maximized = maximized;
    }

    void CoreApplication::Resizing(bool resizing)
    {
        _resizing = resizing;
    }

    bool CoreApplication::GetPaused()
    {
        return _paused;
    }

    bool CoreApplication::GetMinimized()
    {
        return _minimized;
    }

    bool CoreApplication::GetMaximized()
    {
        return _maximized;
    }

    bool CoreApplication::GetResizing()
    {
        return _resizing;
    }

    void CoreApplication::OnStopRequested()
    {
        _runMainLoop = false;
    }

    void CoreApplication::OnResize()
    {
    }

    void CoreApplication::OnStartUp()
    {
        Time::StartUp();
        DynamicLibManager::StartUp();

        StartUpRenderAPI();
        StartUpRenderer();
        StartUpWindow();
    }

    void CoreApplication::OnShutDown()
    {
        Time::ShutDown();
        DynamicLibManager::ShutDown();
        Window::ShutDown();
    }

    void CoreApplication::StartUpRenderAPI()
    {
    }

    void CoreApplication::StartUpRenderer()
    {
    }

    void CoreApplication::StartUpWindow()
    {
        Window::StartUp(_startUpDesc.WindowDesc);
        _window = gWindowPtr();
    }

    CoreApplication& gCoreApplication()
    {
        return CoreApplication::Instance();
    }
}