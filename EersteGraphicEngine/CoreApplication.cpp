#include "CoreApplication.h"

namespace ege
{
    CoreApplication::CoreApplication()
        : _runMainLoop(true)
    {
    }

    CoreApplication::~CoreApplication()
    {
    }

    void CoreApplication::RunMainLoop()
    {
        _runMainLoop = true;

        while (_runMainLoop)
        {
        }
    }

    void CoreApplication::StopMainLoop()
    {
        _runMainLoop = false;
    }

    void CoreApplication::OnStartUp()
    {
        DynamicLibManager::StartUp();

        StartUpRenderAPI();
        StartUpRenderer();
        StartUpWindow();
    }

    void CoreApplication::OnShutDown()
    {
    }

    void CoreApplication::StartUpRenderAPI()
    {
    }

    void CoreApplication::StartUpRenderer()
    {
    }

    void CoreApplication::StartUpWindow()
    {
    }
}