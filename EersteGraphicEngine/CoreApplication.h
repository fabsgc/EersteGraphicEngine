#pragma once

#include "PrerequisitesCore.h"
#include "DynamicLibManager.h"
#include "IComponent.h"
#include "IComponentHandler.h"
#include "IModule.h"
#include "Window.h"
#include "Time.h"

#include "Keyboard.h"
#include "Joypad.h"
#include "Mouse.h"
#include "InputHandler.h"

namespace ege
{
    struct START_UP_DESC
    {
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
    };

    class CoreApplication : public IModule<CoreApplication>, public IComponentHandler
    {
    public:
        CoreApplication(const START_UP_DESC& desc);
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
        static void StartUp(const START_UP_DESC& desc)
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

        void SetContexts();
        void SetApplicationConfig();

    protected:
        volatile bool _runMainLoop;
        volatile bool _paused;
        volatile bool _minimized;
        volatile bool _maximized;
        volatile bool _resizing;

        START_UP_DESC _startUpDesc;

        Window*	      _window;

        Vector<Context> _contexts;
        Context*        _currentContext;
    };

    CoreApplication& gCoreApplication();
}