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

    struct LightDesc
    {
        XMFLOAT4 LightColor;
        XMFLOAT3 LightDirection;
        /* PADDING */ float    Padding1;
        XMFLOAT3 LightPosition;
        float    LightRadius;
        float    LightInnerAngle;
        float    LightOuterAngle;
        UINT     LightType;
        /* PADDING */ float    Padding2;

        LightDesc()
            : LightColor(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f))
            , LightDirection(XMFLOAT3(1.0f, 1.0f, 1.0f))
            , LightPosition(XMFLOAT3(1.0f, 1.0f, 1.0f))
            , LightRadius(5.0f)
            , LightInnerAngle(0.5f)
            , LightOuterAngle(0.1f)
            , LightType(0)
        {}
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
        float    EmitPower;
        BOOL     HasDiffuseTexture;
        BOOL     HasSpecularTexture;
        BOOL     HasNormalTexture;
        /* PADDING */ float    Padding1[3];

        ObjectConstantBuffer()
            : SpecularColor(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f))
            , SpecularPower(8.0f)
            , EmitPower(0.0f)
            , HasDiffuseTexture(true)
            , HasSpecularTexture(true)
            , HasNormalTexture(true)
        {}
    };

    struct LightConstantBuffer : public ConstantBuffer
    {
        XMFLOAT4  AmbientColor;
        UINT      LightIndex;
        /* PADDING */ float    Padding1[3];
        LightDesc Lights[8];

        LightConstantBuffer()
            : AmbientColor(XMFLOAT4(1.0f, 1.0f, 1.0f, 0.2f))
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

    protected:
        RenderAPI(RenderAPI const&) = delete;
        RenderAPI& operator=(RenderAPI const&) = delete;

        void LoadRenderConfig();

    protected:
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