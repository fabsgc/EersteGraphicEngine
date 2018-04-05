#pragma once

#include "PrerequisitesCore.h"
#include "IComponentHandler.h"

namespace ege
{
    struct WINDOW_DESC
    {
        UINT32 Width;
        UINT32 Height;
        String Title;
        bool   FullScreen;

        WINDOW_DESC()
            : Width((UINT32)1280)
            , Height((UINT32)720)
            , Title("Eerste Graphic Engine")
            , FullScreen(false)
        {}
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
        void OnResize();

        void OnStartUp() override;
        void OnShutDown() override {};

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

    private:
        HRESULT InitWindow();

    private:
        HINSTANCE _hInst;
        HWND      _hWnd;

    protected:
        WINDOW_DESC _windowDesc;
    };

    Window& gWindow();
    Window* gWindowPtr();
}