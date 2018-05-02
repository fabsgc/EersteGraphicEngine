#pragma once

#include "PrerequisitesCore.h"
#include "IComponentHandler.h"
#include "ShaderManager.h"
#include "IDrawable.h"
#include "D3D11Device.h"
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

    class D3D11RenderAPI : public IModule<D3D11RenderAPI>, public IComponentHandler, public IDrawable
    {
    public:
        D3D11RenderAPI();
        ~D3D11RenderAPI();

        void OnStartUp() override;
        void OnShutDown() override;

        void OnResize();
        void OnFullScreen();

        void Draw() override;
        void SwapBuffers();

        void Initialise();
        void Resize();

        D3D11Device* GetDevice();

    private:
        D3D11RenderAPI(D3D11RenderAPI const&) = delete;
        D3D11RenderAPI& operator=(D3D11RenderAPI const&) = delete;

        void LoadRenderConfig();

    private:
        RenderDesc                _renderDesc;

        IDXGIDevice*              _dxgiDevice;
        IDXGIAdapter*             _dxgiAdapter;
        IDXGIFactory *            _dxgiFactory;

        D3D11Device*              _device;

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

    D3D11RenderAPI& gD3D11RenderAPI();
    D3D11RenderAPI* gD3D11RenderAPIPtr();
}