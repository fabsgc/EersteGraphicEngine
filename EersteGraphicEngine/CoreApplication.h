#pragma once

#include "PrerequisitesCore.h"
#include "IComponentHandler.h"
#include "IComponent.h"
#include "Window.h"

#include "Keyboard.h"
#include "Joypad.h"
#include "Mouse.h"
#include "InputHandler.h"

#include "EventManager.h"
#include "Event.h"

#include "TaskScheduler.h"
#include "Task.h"

#include "Console.h"

namespace ege
{
    struct StartUpDescription
    {
        UINT        MaxFPS;
        WINDOW_DESC WindowDesc;
    };

    struct Context
    {
        String Name;

        Context(String name)
            : Name(name)
        {}

        bool operator==(const Context& context) const
        {
            return Name == context.Name;
        }

        bool operator==(const String& name) const
        {
            return Name == name;
        }

        bool operator <(const Context& context) const
        {
            return Name < context.Name;
        }
    };

    class CoreApplication : public IModule<CoreApplication>, public IComponentHandler
    {
    public:
        CoreApplication(const StartUpDescription& desc);
        ~CoreApplication();

        void RunMainLoop();
        void StopMainLoop();

        void Pause(bool pause);
        void Minimized(bool minimized);
        void Maximized(bool maximized);
        void Resizing(bool resizing);

        bool GetPaused();
        bool GetMinimized();
        bool GetMaximized();
        bool GetResizing();

        void OnStopRequested();
        void OnResize();

        void KeyEventHandler(MSG* message);
        void MouseEventHandler(MSG* message);
        void JoypadEventHandler();

        const Context* GetCurrentContext() const;

        template<class T = CoreApplication>
        static void StartUp(const StartUpDescription& desc)
        {
            IModule::StartUp<T>(desc);
        }

    protected:
        void OnStartUp() override;
        void OnShutDown() override;

        void StartUpRenderAPI();
        void StartUpRenderer();
        void StartUpWindow();
        void StartUpComponents();
        void StartUpEventManager();
        void StartUpDynamicLibManager();
        void StartUpTime();
        void StartUpConsole();
        void StartUpTaskScheduler();

        void SetContexts();
        void SetApplicationConfig();
        void SetComponents();
        void LimitFps();

        void SetContext(const String& name);

    protected:
        volatile bool      _runMainLoop;
        volatile bool      _paused;
        volatile bool      _minimized;
        volatile bool      _maximized;
        volatile bool      _resizing;

        StartUpDescription _startUpDesc;

        Window*	           _window;

        Vector<Context>    _contexts;
        Context*           _currentContext;
    };

    CoreApplication& gCoreApplication();
    CoreApplication* gCoreApplicationPtr();
}