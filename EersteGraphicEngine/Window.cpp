#include "Window.h"
#include "CoreApplication.h"

namespace ege
{
    Window::Window(const WINDOW_DESC& desc)
       : _windowDesc(desc)
    {
    }

    void Window::OnStartUp()
    {
        HRESULT HR = InitWindow();
        EGE_ASSERT_ERROR((HR != E_FAIL), "Can't create window instance");
    }

    void Window::Update()
    {
        CoreApplication& application = gCoreApplication();
        MSG  msg;

        if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            CoreApplication& application = gCoreApplication();

            if (msg.message == WM_KEYUP || msg.message == WM_KEYDOWN)
            {
                application.KeyEventHandler(&msg);
            }
                
            if (msg.message == WM_MOUSEMOVE || msg.message == WM_LBUTTONDOWN || msg.message == WM_RBUTTONDOWN || 
                msg.message == WM_MOUSEWHEEL || msg.message == WM_MOUSEHWHEEL || msg.message == WM_LBUTTONUP ||
                msg.message == WM_RBUTTONUP || msg.message == WM_MOUSEHOVER || msg.message == WM_MOUSELEAVE)
            {
                application.MouseEventHandler(&msg);
            }
            
            if (msg.message == WM_QUIT)
            {
                application.OnStopRequested();
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            gMouse().ResetState();
            application.JoypadEventHandler();

            if (gInputHandler().GetState("QUIT") == InputHandlerState::TRIGGERED)
            {
                application.OnStopRequested();
            }
        }
    }

    HRESULT Window::InitWindow()
    {
        _hInst = GetModuleHandle(NULL);

        WNDCLASSEX wcex = {};
        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = &Window::MsgProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = _hInst;
        wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
        wcex.lpszMenuName = nullptr;
        wcex.lpszClassName = L"Eerste Engine";

        if (!RegisterClassEx(&wcex))
            return E_FAIL;

        RECT rc = { 0, 0, (LONG)_windowDesc.Width, (LONG)_windowDesc.Height };
        AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
        _hWnd = CreateWindow(L"Eerste Engine", ToWString(_windowDesc.Title).c_str(), WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, _hInst,
            nullptr);

        if (!_hWnd)
            return E_FAIL;

        ShowWindow(_hWnd, SW_SHOW);

        return S_OK;
    }

    void Window::OnResize()
    {
        gCoreApplication().OnResize();
    }

    LRESULT CALLBACK Window::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        Window& window = gWindow();
        CoreApplication& application = gCoreApplication();
        Time& time = gTime();

        PAINTSTRUCT ps;
        HDC hdc;

        switch (message)
        {
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_ACTIVATE:
            if (LOWORD(wParam) == WA_INACTIVE)
            {
                application.Pause(true);
                time.Stop();
            }
            else
            {
                application.Pause(false);
                time.Start();
            }
            break;

        case WM_ENTERSIZEMOVE:
            application.Pause(true);
            application.Resizing(true);
            time.Stop();
            break;

        case WM_EXITSIZEMOVE:
            application.Pause(false);
            application.Resizing(false);
            time.Start();
            window.OnResize();
            break;

        case WM_GETMINMAXINFO:
            ((MINMAXINFO*)lParam)->ptMinTrackSize.x = 640;
            ((MINMAXINFO*)lParam)->ptMinTrackSize.y = 365;
            return 0;

        case WM_SIZE:
            // Save the new client area dimensions.
            window.SetWindowWidth(LOWORD(lParam));
            window.SetWindowHeight(HIWORD(lParam));

            if (wParam == SIZE_MINIMIZED)
            {
                application.Pause(true);
                application.Minimized(true);
                application.Maximized(false);
            }
            else if (wParam == SIZE_MAXIMIZED)
            {
                application.Pause(false);
                application.Minimized(false);
                application.Maximized(true);
                window.OnResize();
            }
            else if (wParam == SIZE_RESTORED)
            {
                // Restoring from minimized state?
                if (application.GetMinimized())
                {
                    application.Pause(false);
                    application.Minimized(false);
                    window.OnResize();
                }
                // Restoring from maximized state?
                else if (application.GetMaximized())
                {
                    application.Pause(false);
                    application.Maximized(false);
                    window.OnResize();
                }
                else if (application.GetResizing())
                {
                    // If user is dragging the resize bars, we do not resize 
                    // the buffers here because as the user continuously 
                    // drags the resize bars, a stream of WM_SIZE messages are
                    // sent to the window, and it would be pointless (and slow)
                    // to resize for each WM_SIZE message received from dragging
                    // the resize bars.  So instead, we reset after the user is 
                    // done resizing the window and releases the resize bars, which 
                    // sends a WM_EXITSIZEMOVE message.
                }
                else // API call such as SetWindowPos or mSwapChain->SetFullscreenState.
                {
                    window.OnResize();
                }
            }
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }

        return 0;
    }

    void Window::ComputeFrameRate()
    {
        static int   frameCnt = 0;
        static float timeElapsed = 0.0f;

        frameCnt++;

        if (gTime().GetTime() - timeElapsed >= 1.0f)
        {
            WStringStream outs;
            outs.precision(6);

            outs << ToWString(_windowDesc.Title).c_str() << L"    "
                << L"FPS: " << (1.0f / gTime().GetFrameDelta()) << L"    "
                << L"Frame Time: " << (gTime().GetFrameDelta()) << L" (ms)";
            SetWindowText(_hWnd, outs.str().c_str());

            frameCnt = 0;
            timeElapsed += 1.0f;
        }
    }

    HINSTANCE& Window::GetHInst()
    {
        return _hInst;
    }

    HWND& Window::GetHWnd()
    {
        return _hWnd;
    }

    UINT Window::GetWindowHeight()
    {
        return _windowDesc.Height;
    }

    UINT Window::GetWindowWidth()
    {
        return _windowDesc.Width;
    }

    bool Window::IsFullScreen()
    {
        return _windowDesc.FullScreen;
    }

    float Window::GetAspectRatio() const
    {
        return static_cast<float>(_windowDesc.Width) / _windowDesc.Height;
    }

    void Window::SetWindowHeight(UINT width)
    {
        _windowDesc.Width = width;
    }

    void Window::SetWindowWidth(UINT height)
    {
        _windowDesc.Height = height;
    }

    void Window::SetFullScreen(bool fullscreen)
    {
        _windowDesc.FullScreen = fullscreen;
    }

    Window& gWindow()
    {
        return static_cast<Window&>(Window::Instance());
    }

    Window* gWindowPtr()
    {
        return static_cast<Window*>(Window::InstancePtr());
    }
}