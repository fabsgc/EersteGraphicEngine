#pragma once

#define WIN32_LEAN_AND_MEAN

#include "PrerequisitesUtil.h"

#include <dxgi.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <DirectXColors.h>
#include <DirectXPackedVector.h>
#include <Windowsx.h>

#include <Xinput.h>
#include <xaudio2.h>

#include "lib/assimp/Importer.hpp"
#include "lib/assimp/Scene.h"
#include "lib/assimp/Postprocess.h"

#include "lib/tinyxml2/tinyxml2.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "xinput9_1_0.lib")
#pragma comment(lib, "xinput.lib")

#include "lib/ddstextureloader/DDSTextureLoader.h"

#include "DynamicLibManager.h"
#include "IModule.h"
#include "Time.h"

using namespace DirectX;

#if defined(EGE_DEBUG)
    #ifndef HR
    #define HR(x)               \
        {                       \
            HRESULT hr = (x);   \
            if(FAILED(hr))      \
            {                   \
                return hr;      \
            }                   \
        }
    #endif
#else
    #ifndef HR
    #define HR(x) (x)
    #endif
#endif 

namespace ege
{
    template<typename T>
    inline void SafeReleaseCom(T& ptr)
    {
        if (ptr != nullptr)
        {
            ptr->Release();
            ptr = nullptr;
        }
    }

    template<typename T>
    inline void SafeRelease(T& ptr)
    {
        if (ptr != nullptr)
        {
            delete ptr;
            ptr = nullptr;
        }
    }

    namespace Colors
    {
        XMGLOBALCONST XMFLOAT4 White          = { 1.0f, 1.0f, 1.0f, 1.0f };
        XMGLOBALCONST XMFLOAT4 Black          = { 0.0f, 0.0f, 0.0f, 1.0f };
        XMGLOBALCONST XMFLOAT4 Red            = { 1.0f, 0.0f, 0.0f, 1.0f };
        XMGLOBALCONST XMFLOAT4 Green          = { 0.0f, 1.0f, 0.0f, 1.0f };
        XMGLOBALCONST XMFLOAT4 Blue           = { 0.0f, 0.0f, 1.0f, 1.0f };
        XMGLOBALCONST XMFLOAT4 Yellow         = { 1.0f, 1.0f, 0.0f, 1.0f };
        XMGLOBALCONST XMFLOAT4 Cyan           = { 0.0f, 1.0f, 1.0f, 1.0f };
        XMGLOBALCONST XMFLOAT4 Magenta        = { 1.0f, 0.0f, 1.0f, 1.0f };
        XMGLOBALCONST XMFLOAT4 Grey           = { 0.4f, 0.4f, 0.4f, 1.0f };
        XMGLOBALCONST XMFLOAT4 Silver         = { 0.75f, 0.75f, 0.75f, 1.0f };
        XMGLOBALCONST XMFLOAT4 LightSteelBlue = { 0.69f, 0.77f, 0.87f, 1.0f };
    }

    class  IComponent;
    class  IComponentHandler;

    class  Event;
    class  EventManager;

    struct InputMap;
    class  InputHandler;
    struct JoyStick;
    struct ThumbStick;
    struct JoypadButton;
    class  Joypad;

    struct Key;
    class  Keyboard;

    struct MouseButton;
    class  Mouse;

    class  Window;
    class  IDrawable;
    class  IUpdatable;

    struct Context;
    struct StartUpDescription;
    class  CoreApplication;
}