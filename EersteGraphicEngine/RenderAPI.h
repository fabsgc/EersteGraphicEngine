#pragma once

#include "PrerequisitesCore.h"
#include "IComponentHandler.h"
#include "ConstantBuffer.h"
#include "IDrawable.h"
#include "Device.h"

namespace ege
{
    enum class ConstantBufferType
    {
        FRAME, OBJECT, LIGHT
    };

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

    struct FrameConstantBuffer: public ConstantBuffer
    {
        XMMATRIX View;
        XMMATRIX Projection;
        
        XMFLOAT3 CameraPosition;
        /* PADDING */ float    Padding1;

        FrameConstantBuffer()
        {}
    };

    struct ObjectConstantBuffer: public ConstantBuffer
    {
        XMMATRIX World;

        XMFLOAT4 SpecularColor;
        float    SpecularPower;
        /* PADDING */ float    Padding1[3];
        float    HasDiffuseTexture;
        /* PADDING */ float    Padding2[3];
        float    HasSpecularTexture;
        /* PADDING */ float    Padding3[3];
        float    HasNormalTexture;
        /* PADDING */ float    Padding4[3];

        ObjectConstantBuffer()
            : SpecularColor(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f))
            , SpecularPower(8.0f)
            , HasDiffuseTexture(1.0f)
            , HasSpecularTexture(1.0f)
            , HasNormalTexture(0.0f)
        {}
    };

    struct LightConstantBuffer : public ConstantBuffer
    {
        XMFLOAT4 AmbientColor;

        XMFLOAT4 LightColor;
        XMFLOAT3 LightDirection;
        /* PADDING */ float    Padding1;
        XMFLOAT3 LightPosition;
        /* PADDING */ float    Padding2;
        float    LightRadius;
        /* PADDING */ float    Padding3[3];
        float    LightType;
        /* PADDING */ float    Padding4[3];

        LightConstantBuffer()
            : AmbientColor(XMFLOAT4(1.0f, 1.0f, 1.0f, 0.2f))
            , LightColor(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f))
            , LightDirection(XMFLOAT3(0.5f, -0.5f, 0.5f))
            , LightPosition(XMFLOAT3(-2.0f, 2.0f, -2.0f))
            , LightRadius(5.0f)
        {}
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
        ID3D11Buffer*   GetConstantBuffer(ConstantBufferType type);
        ConstantBuffer* GetConstantBufferUpdate(ConstantBufferType type);

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

        ID3D11Buffer*             _frameConstantBuffer;
        ID3D11Buffer*             _objectConstantBuffer;
        ID3D11Buffer*             _lightConstantBuffer;
        FrameConstantBuffer       _frameConstantBufferUpdate;
        ObjectConstantBuffer      _objectConstantBufferUpdate;
        LightConstantBuffer       _lightConstantBufferUpdate;
    };

    RenderAPI& gRenderAPI();
    RenderAPI* gRenderAPIPtr();
}