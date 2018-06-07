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
        XMMATRIX World;

        XMFLOAT4 AmbientColor;

        XMFLOAT4 CameraPosition;

        XMFLOAT4 LightColor;
        XMFLOAT4 LightDirection;
        XMFLOAT4 LightPosition;
        XMFLOAT4 LightRadius;

        XMFLOAT4 SpecularColor;
        XMFLOAT4 SpecularPower;

        FrameConstantBuffer()
            : AmbientColor(XMFLOAT4(1.0f, 1.0f, 1.0f, 0.2f))
            , LightColor(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f))
            , LightDirection(XMFLOAT4(0.5f, -0.5f, 0.5f, 0.0f))
            , LightPosition(XMFLOAT4(-2.0f, 2.0f, -2.0f, 0.0f))
            , LightRadius(XMFLOAT4(5.0f, 0.0f, 0.0f, 0.0f))
            , SpecularColor(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f))
            , SpecularPower(XMFLOAT4(8.0f, 0.0f, 0.0f, 0.0f))
        {}
    };

    struct ObjectConstantBuffer: public ConstantBuffer
    {

    };

    struct LightConstantBuffer : public ConstantBuffer
    {

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