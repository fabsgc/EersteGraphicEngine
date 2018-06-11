#pragma once

#include "PrerequisitesCore.h"
#include "IComponentHandler.h"
#include "IComponent.h"
#include "IUpdatable.h"
#include "IDrawable.h"
#include "Window.h"

#include "Scene.h"

namespace ege
{
    struct StartUpDescription
    {
        UINT        MaxFPS;
        bool        UseRawInput;
        WINDOW_DESC WindowDesc;

        StartUpDescription()
            : MaxFPS(0)
            , UseRawInput(false)
        {}
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

        bool operator<(const Context& context) const
        {
            return Name < context.Name;
        }
    };

    class CoreApplication : public IModule<CoreApplication>, public IComponentHandler, public IUpdatable, public IDrawable
    {
    public:
        CoreApplication(const StartUpDescription& desc);
        ~CoreApplication();

        virtual void RunMainLoop();
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

        void KeyEventHandler(MSG* message);
        void MouseEventHandler(MSG* message);
        void JoypadEventHandler();

        const Context* GetCurrentContext() const;

        template<class T = Application>
        static void StartUp(const StartUpDescription& desc)
        {
            IModule::StartUp<T>(desc);
        }

        void Update() override;
        void Draw() override;

        const StartUpDescription& GetStartUpDescription() const;

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
        void StartUpTextureManager();
        void StartUpModelManager();
        void StartUpSceneManager();

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

        SPtr<Scene>        _scene;
    };

    CoreApplication& gCoreApplication();
    CoreApplication* gCoreApplicationPtr();
}