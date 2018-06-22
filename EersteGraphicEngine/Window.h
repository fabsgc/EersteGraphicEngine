#pragma once

#include "PrerequisitesCore.h"
#include "IComponentHandler.h"

namespace ege
{
    struct WINDOW_DESC
    {
        UINT32 Width;
        UINT32 Height;
        UINT32 LastWidth;
        UINT32 LastHeight;
        String Title;
        bool   FullScreen;

        WINDOW_DESC()
            : Width((UINT32)1280)
            , Height((UINT32)720)
            , LastWidth(Width)
            , LastHeight(Height)
            , Title("Eerste Graphic Engine")
            , FullScreen(false)
        {}

        void SetWidth(UINT32 width)
        {
            LastWidth = Width;
            Width = width;

            EGE_LOG_DEBUG("Set Width");
        }

        void SetHeight(UINT32 height)
        {
            LastHeight = Height;
            Height = height;
        }
    };

    class Window : public IModule<Window>, public IComponentHandler
    {
    public:
        Window(const WINDOW_DESC& desc);
        ~Window() {};

        template<class T = Window>
        static void StartUp(const WINDOW_DESC& desc)
        {
            IModule::StartUp<T>(desc);
        }

        void Update();
        void ComputeFrameRate();

        void OnStartUp() override;
        void OnShutDown() override {};

        void OnResize();
        void OnFullScreen();

        void SetShowCursor(bool cursor);
        void SetClipCursor(bool clip);
        void ShowCursor();
        void ClipCursor();

        static LRESULT CALLBACK MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

        HINSTANCE& GetHInst();
        HWND&      GetHWnd();
        UINT       GetWindowHeight();
        UINT       GetWindowWidth();
        bool       IsFullScreen();
        float      GetAspectRatio() const;

        void       SetWindowHeight(UINT width);
        void       SetWindowWidth(UINT height);
        void       SetFullScreen(bool fullscreen);

    protected:
        HRESULT InitWindow();

    protected:
        HINSTANCE _hInst;
        HWND      _hWnd;

        CoreApplication& _application;
        WINDOW_DESC      _windowDesc;

        bool      _showCursor;
        bool      _clipCursor;  
    };

    Window& gWindow();
    Window* gWindowPtr();
}