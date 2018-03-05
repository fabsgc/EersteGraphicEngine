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
        , _currentContext(nullptr)
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
        SetContexts();
        SetApplicationConfig();

        Time::StartUp();
        DynamicLibManager::StartUp();

        StartUpRenderAPI();
        StartUpRenderer();
        StartUpWindow();
        StartUpComponents();
    }

    void CoreApplication::OnShutDown()
    {
        InputHandler::ShutDown();
        Keyboard::ShutDown();
        Joypad::ShutDown();
        Mouse::ShutDown();
        Window::ShutDown();
        Time::ShutDown();
        DynamicLibManager::ShutDown();
    }

    void CoreApplication::StartUpRenderAPI()
    {
        //TODO
    }

    void CoreApplication::StartUpRenderer()
    {
        //TODO
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

        InsertComponent(gKeyboard());
        InsertComponent(gJoypad());
        InsertComponent(gMouse());
        InsertComponent(gInputHandler());
    }

    void CoreApplication::SetContexts()
    {
#ifdef EGE_CONFIG_CONTEXT_FILE
        tinyxml2::XMLDocument document;
        document.LoadFile(EGE_CONFIG_CONTEXT_FILE);

        tinyxml2::XMLElement* contextsElement = document.FirstChildElement("contexts");

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

    void CoreApplication::SetApplicationConfig()
    {
#ifdef EGE_CONFIG_APP_FILE
        tinyxml2::XMLDocument document;
        document.LoadFile(EGE_CONFIG_APP_FILE);

        _startUpDesc.WindowDesc.Width  = document.FirstChildElement("application")->FirstChildElement("window")->IntAttribute("width", 1280);
        _startUpDesc.WindowDesc.Height = document.FirstChildElement("application")->FirstChildElement("window")->IntAttribute("height", 720);
        _startUpDesc.WindowDesc.Title  = document.FirstChildElement("application")->FirstChildElement("window")->Attribute("title");
#endif
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
        InputHandler& inputHandler = static_cast<InputHandler&>(GetComponent(ComponentType::JOYPAD));
        inputHandler.Update();
    }

    void CoreApplication::InputEventHandler()
    {
        InputHandler& inputHandler = static_cast<InputHandler&>(GetComponent(ComponentType::INPUT_HANDLER));
        inputHandler.Update();
    }

    CoreApplication& gCoreApplication()
    {
        return CoreApplication::Instance();
    }
}