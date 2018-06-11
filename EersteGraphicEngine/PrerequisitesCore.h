#pragma once

#if defined(EGE_WIN_SDK_7)
#   define WIN32_LEAN_AND_MEAN
#   define _WIN32_WINNT _WIN32_WINNT_WIN7
#   pragma warning(push)
#   pragma warning( disable : 4005 )
#elif defined(EGE_WIN_SDK_8)
#   define WIN32_LEAN_AND_MEAN
#   define _WIN32_WINNT _WIN32_WINNT_WIN8
#elif defined(EGE_WIN_SDK_10)
#   define WIN32_LEAN_AND_MEAN
#   define _WIN32_WINNT _WIN32_WINNT_WIN10
#endif

#include "PrerequisitesUtil.h"

#include <dxgi.h>
#include <d3d11_1.h>

#include <DirectXMath.h>
#include <DirectXColors.h>
#include <DirectXPackedVector.h>

#include <Windowsx.h>
#include <Xinput.h>

#if defined(EGE_WIN_SDK_7)
#   include <F:\softwares\Microsoft DirectX SDK (June 2010)\Include\d3dx11.h>
#   include <F:\softwares\Microsoft DirectX SDK (June 2010)\Include\d3dcompiler.h>
#   include <F:\softwares\Microsoft DirectX SDK (June 2010)\Include\comdecl.h>
#   include <F:\softwares\Microsoft DirectX SDK (June 2010)\Include\xaudio2.h>
#   include <F:\softwares\Microsoft DirectX SDK (June 2010)\Include\xaudio2fx.h>
#   include <F:\softwares\Microsoft DirectX SDK (June 2010)\Include\xapofx.h>
#   include <F:\softwares\Microsoft DirectX SDK (June 2010)\Include\x3daudio.h>
#   pragma warning(pop)
#   pragma comment(lib,"d3dx11.lib")
#   pragma comment(lib,"x3daudio.lib")
#   pragma comment(lib,"xapofx.lib")
#elif defined(EGE_WIN_SDK_8) || defined(EGE_WIN_SDK_10)
#   include <d3dcompiler.h>
#   include <xaudio2.h>
#   include <xaudio2fx.h>
#   include <x3daudio.h>
#   include <xapofx.h>
#   pragma comment(lib,"xaudio2.lib")
#endif

#include "assimp/Importer.hpp"
#include "assimp/Scene.h"
#include "assimp/Postprocess.h"

#include "tinyxml2.h"

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
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
    #define HR(x, message)                           \
        {                                            \
            HRESULT hr = (x);                        \
            if(FAILED(hr))                           \
            {                                        \
                EGE_ASSERT_ERROR(false, message);    \
            }                                        \
        }
    #endif
#else
    #ifndef HR
    #define HR(x, message) (x)
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
    class  IMoveable;

    struct Context;
    struct StartUpDescription;
    class  CoreApplication;

    struct RenderDesc;
    struct ConstantBuffer;
    class  RenderAPI;
    class  Device;
    class  Geometry;
    class  ShaderManager;
    struct ShaderConfig;
    class  Shader;
    struct VertexDesc;

    class  Scene;
    class  Node;
    class  IEntity;
    class  SceneLoader;
    class  SceneManager;

    class  ModelManager;
    class  ModelLoader;
    struct ModelDesc;
    class  Model;

    class  Material;
    class  MaterialManager;

    class  Light;
    class  SpotLight;
    class  PointLight;
    class  AmbientLight;
    class  DirectionalLight;
    class  LightSchema;

    class  Camera;
    class  Frustum;
    class  PerspectiveCamera;
    class  OrthographicCamera;
    class  FlyingCamera;
    class  FirstPersonCamera;
    class  ThirdPersonCamera;
}