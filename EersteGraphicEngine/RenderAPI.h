#pragma once

#include "PrerequisitesCore.h"
#include "IComponentHandler.h"
#include "ShaderManager.h"
#include "IDrawable.h"
#include "Device.h"
#include "Window.h"

namespace ege
{
    struct RenderDesc
    {
        UINT Msaa;
        bool BackfaceCulling;
        bool FrustumCulling;
        bool FullScreen;
        bool VSync;

        RenderDesc()
            : Msaa(4)
            , BackfaceCulling(true)
            , FrustumCulling(true)
            , FullScreen(false)
            , VSync(false)
        {}
    };

    struct ConstantBuffer
    {
        XMMATRIX View;
        XMMATRIX Projection;
        XMMATRIX World;
    };

    class RenderAPI : public IModule<RenderAPI>, public IComponentHandler, public IDrawable
    {
    public:
        RenderAPI();
        ~RenderAPI();

        void OnStartUp() override;
        void OnShutDown() override;

        void OnResize();
        void OnFullScreen();

        void Draw() override;
        void SwapBuffers();

        void Initialise();
        void Resize();

        Device*         GetDevice();
        ID3D11Buffer*   GetConstantBuffer();
        ConstantBuffer* GetConstantBufferUpdate();

    private:
        RenderAPI(RenderAPI const&) = delete;
        RenderAPI& operator=(RenderAPI const&) = delete;

        void LoadRenderConfig();

    private:
        RenderDesc                _renderDesc;

        IDXGIDevice*              _dxgiDevice;
        IDXGIAdapter*             _dxgiAdapter;
        IDXGIFactory *            _dxgiFactory;

        Device*                   _device;

        D3D_DRIVER_TYPE           _driverType;
        D3D_FEATURE_LEVEL         _featureLevel;

        IDXGISwapChain*           _swapChain;
        ID3D11RenderTargetView*   _renderTargetView;
        ID3D11DepthStencilView*   _depthStencilView;
        ID3D11Texture2D*          _depthStencilBuffer;
        ID3D11DepthStencilState*  _depthStencilState;
        ID3D11RasterizerState*    _rasterizerState;
        D3D11_VIEWPORT            _screenViewport;

        UINT                      _4xMsaaQuality;
        ID3D11SamplerState*       _colorSampler;
        ID3D11RasterizerState*    _backFaceCulling;

        ID3D11Buffer*             _constantBuffer;
        ConstantBuffer            _constantBufferUpdate;
    };

    RenderAPI& gRenderAPI();
    RenderAPI* gRenderAPIPtr();
}