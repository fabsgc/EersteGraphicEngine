#include "CoreApplication.h"

#include "RenderAPI.h"
#include "Renderer.h"

#include "Keyboard.h"
#include "Joypad.h"
#include "Mouse.h"
#include "InputHandler.h"

#include "ModelManager.h"
#include "Model.h"

#include "SceneManager.h"

#include "TextureManager.h"
#include "Texture.h"

#include "TaskScheduler.h"
#include "Task.h"

#include "EventManager.h"
#include "Event.h"

#include "Console.h"

#include "ForwardRendering.h"
#include "DeferredRendering.h"

namespace ege
{
    CoreApplication::CoreApplication(const StartUpDescription& desc)
        : _runMainLoop(true)
        , _paused(false)
        , _minimized(false)
        , _maximized(false)
        , _resizing(false)
        , _window(nullptr)
        , _startUpDesc(desc)
        , _currentContext(nullptr)
    {}

    CoreApplication::~CoreApplication()
    {}

    void CoreApplication::RunMainLoop()
    {
        while (_runMainLoop)
        {
            Update();

            if (!_paused)
            {
                _window->ComputeFrameRate();
                Draw();
            }
            else
            {
                EGE_SLEEP(100);
            }
        }
    }

    void CoreApplication::Update()
    {
        if (gInputHandler().GetState("QUIT").State == InputHandlerState::TRIGGERED)
        {
            gEventManager().Execute("STOP_REQUESTED");
        }

        gTime().Update();
        _window->Update();

        if (_scene != nullptr)
        {
            _scene->Update();
        }

        gMouse().SetRelativeMovement(XMFLOAT2(0.0f, 0.0f));
    }

    void CoreApplication::Draw()
    {
        if (_renderPipeline != nullptr)
        {
            _renderPipeline->Draw();
        }

        gRenderAPI().SwapBuffers();
    }

    void CoreApplication::LimitFps()
    {
        if (_startUpDesc.MaxFPS > 0)
        {
            if (gTime().GetFrameDelta() * 1000.0f < (1.0f / _startUpDesc.MaxFPS * 1000))
            {
                float sleep = (((1.0f / _startUpDesc.MaxFPS) * 1000) - (gTime().GetFrameDelta() * 1000));
                EGE_SLEEP((DWORD)sleep);
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

    void CoreApplication::OnStartUp()
    {
        if (!XMVerifyCPUSupport())
        {
            EGE_ASSERT_ERROR(false, "Failed to verify DirectX Math library support.");
        }

        SetContexts();
        SetApplicationConfig();

        StartUpConsole();
        StartUpTime();
        StartUpTaskScheduler();
        StartUpDynamicLibManager();
        StartUpEventManager();
        StartUpWindow();
        StartUpRenderAPI();
        StartUpRenderer();
        StartUpComponents();
        StartUpTextureManager();
        StartUpModelManager();
        StartUpSceneManager();
        StartUpRenderPipeline();

        SetComponents();

        SetContext("Game");

        SceneLoader();

        RenderPipelineLoader();

        return;
    }

    void CoreApplication::OnShutDown()
    {
        SceneManager::ShutDown();
        ModelManager::ShutDown();
        TextureManager::ShutDown();
        InputHandler::ShutDown();
        Keyboard::ShutDown();
        Joypad::ShutDown();
        Mouse::ShutDown();
        Renderer::ShutDown();
        RenderAPI::ShutDown();
        Window::ShutDown();
        EventManager::ShutDown();
        DynamicLibManager::ShutDown();
        TaskScheduler::ShutDown();
        Time::ShutDown();
        Console::ShutDown();
    }

    void CoreApplication::StartUpRenderAPI()
    {
        RenderAPI::StartUp();
        _renderAPI = gRenderAPIPtr();
    }

    void CoreApplication::StartUpRenderer()
    {
        Renderer::StartUp();
    }

    void CoreApplication::StartUpWindow()
    {
        Window::StartUp(_startUpDesc.WindowDesc);
        _window = gWindowPtr();
    }

    void CoreApplication::StartUpComponents()
    {
        Keyboard::StartUp();
        Joypad::StartUp();
        Mouse::StartUp();
        InputHandler::StartUp();
    }

    void CoreApplication::StartUpEventManager()
    {
        EventManager::StartUp();

        gEventManager().Create("WINDOW_RESIZED");
        gEventManager().Create("WINDOW_FULLSCREEN");
        gEventManager().Create("STOP_REQUESTED");

        gEventManager().Suscribe("STOP_REQUESTED", std::bind(&CoreApplication::OnStopRequested, this));
    }

    void CoreApplication::StartUpDynamicLibManager()
    {
        DynamicLibManager::StartUp();
    }

    void CoreApplication::StartUpTime()
    {
        Time::StartUp();
    }

    void CoreApplication::StartUpConsole()
    {
        Console::StartUp();
    }

    void CoreApplication::StartUpTaskScheduler()
    {
        TaskScheduler::StartUp(10);
    }

    void CoreApplication::StartUpTextureManager()
    {
        TextureManager::StartUp();
    }

    void CoreApplication::StartUpModelManager()
    {
        ModelManager::StartUp();
    }

    void CoreApplication::StartUpSceneManager()
    {
        SceneManager::StartUp();
    }

    void CoreApplication::StartUpRenderPipeline()
    {
        RenderDesc& renderDesc = _renderAPI->GetRenderDesc();

        switch (renderDesc.Pipeline)
        {
        case RenderPipelineType::FORWARD:
            _renderPipeline = ege_shared_ptr_new<ForwardRendering>();
            break;

        case RenderPipelineType::DEFERRED:
            _renderPipeline = ege_shared_ptr_new<DeferredRendering>();
            break;
        }
    }

    void CoreApplication::SetContexts()
    {
#ifdef EGE_CONFIG_CONTEXT_FILE
        tinyxml2::XMLDocument document;
        document.LoadFile(EGE_CONFIG_CONTEXT_FILE);

        tinyxml2::XMLElement* contextsElement = document.FirstChildElement("contexts");
        EGE_ASSERT_ERROR((contextsElement != nullptr), "Context file malformed");

        for (tinyxml2::XMLElement* contextElement = contextsElement->FirstChildElement("context"); contextElement != nullptr; contextElement = contextElement->NextSiblingElement())
        {
            Context context(contextElement->Attribute("name"));
            _contexts.push_back(context);
        }        
#endif

        if (_contexts.size() > 0)
        {
            Context context("Default");
            _contexts.push_back(context);
        }

        _currentContext = &_contexts[0];
    }

    void CoreApplication::RenderPipelineLoader()
    {
        _renderPipeline->Initialise(_scene);
    }

    void CoreApplication::SetApplicationConfig()
    {
#ifdef EGE_CONFIG_APP_FILE
        tinyxml2::XMLDocument document;
        document.LoadFile(EGE_CONFIG_APP_FILE);

        _startUpDesc.MaxFPS = document.FirstChildElement("application")->FirstChildElement("window")->IntAttribute("fps", 60);
        _startUpDesc.UseRawInput = strcmp(document.FirstChildElement("application")->FirstChildElement("window")->Attribute("rawinput"), "true") == 0 ? true : false;
        _startUpDesc.WindowDesc.Width  = document.FirstChildElement("application")->FirstChildElement("window")->IntAttribute("width", 1280);
        _startUpDesc.WindowDesc.Height = document.FirstChildElement("application")->FirstChildElement("window")->IntAttribute("height", 720);
        _startUpDesc.WindowDesc.Title = document.FirstChildElement("application")->FirstChildElement("window")->Attribute("title");
        _startUpDesc.WindowDesc.FullScreen  = strcmp(document.FirstChildElement("application")->FirstChildElement("window")->Attribute("fullscreen"), "true") == 0 ? true : false;
#endif
    }

    void CoreApplication::SetComponents()
    {
        InsertComponent(gKeyboard());
        InsertComponent(gJoypad());
        InsertComponent(gMouse());
        InsertComponent(gInputHandler());

        _window->InsertComponent(gKeyboard());
        _window->InsertComponent(gJoypad());
        _window->InsertComponent(gMouse());
        _window->InsertComponent(gInputHandler());
    }

    void CoreApplication::KeyEventHandler(MSG* message)
    {
        Keyboard& keyboard = static_cast<Keyboard&>(GetComponent(ComponentType::KEYBOARD));
        keyboard.Update(message);
    }

    void CoreApplication::MouseEventHandler(MSG* message)
    {
        Mouse& mouse = static_cast<Mouse&>(GetComponent(ComponentType::MOUSE));
        mouse.Update(message);
    }

    void CoreApplication::JoypadEventHandler()
    {
        Joypad& joypad = static_cast<Joypad&>(GetComponent(ComponentType::JOYPAD));
        joypad.Update();
    }

    const Context* CoreApplication::GetCurrentContext() const
    {
        return _currentContext;
    }

    void CoreApplication::SetContext(const String& name)
    {
        for (auto contextIt = _contexts.begin(); contextIt != _contexts.end(); contextIt++)
        {
            if (*contextIt == name)
            {
                _currentContext = &*contextIt;
                return;
            }
        }

        EGE_ASSERT_ERROR(false, ("The context \"" + name + "\" does not exist"));
    }

    const StartUpDescription& CoreApplication::GetStartUpDescription() const
    {
        return _startUpDesc;
    }

    CoreApplication& gCoreApplication()
    {
        return CoreApplication::Instance();
    }

    CoreApplication* gCoreApplicationPtr()
    {
        return CoreApplication::InstancePtr();
    }
}