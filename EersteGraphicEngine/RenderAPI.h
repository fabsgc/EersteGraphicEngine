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
        FRAME, OBJECT, LIGHT, QUAD
    };

    enum class RenderPipelineType
    {
        FORWARD, DEFERRED
    };

    struct RenderDesc
    {
        UINT Msaa;
        bool BackfaceCulling;
        bool FrustumCulling;
        bool FullScreen;
        bool VSync;
        RenderPipelineType Pipeline;

        RenderDesc()
            : Msaa(4)
            , BackfaceCulling(true)
            , FrustumCulling(true)
            , FullScreen(false)
            , VSync(false)
            , Pipeline(RenderPipelineType::FORWARD)
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
        void ClearRenderTargetView();
        void ClearDepthStencilView();

        void Initialise();

        void TurnZBufferOn();
        void TurnZBufferOff();

        Device*                     GetDevice();
        SPtr<ConstantBufferElement> GetConstantBufferPtr(ConstantBufferType type);
        RenderDesc&                 GetRenderDesc();
        ID3D11RenderTargetView*     GetRenderTargetView();
        ID3D11DepthStencilView*     GetDepthStencilView();
        UINT                        GetMSAASampleCount();
        UINT                        GetMSAASampleQuality();

    protected:
        RenderAPI(RenderAPI const&) = delete;
        RenderAPI& operator=(RenderAPI const&) = delete;

        void LoadRenderConfig();

        void Resize();

        void CreateDevice();
        void CheckMSAASupport();
        void CreateSwapChain();
        void CreateDepthStencilBuffer();
        void CreateViewport();
        void CreateConstantBuffers();
        void CreateColorSampler();
        void CreateDepthStencilState();
        void SetPrimitiveTopology();
        void SetBackfaceCulling();

    protected:
        RenderDesc                  _renderDesc;

        IDXGIDevice*                _dxgiDevice;
        IDXGIAdapter*               _dxgiAdapter;
        IDXGIFactory *              _dxgiFactory;

        Device*                     _device;

        D3D_DRIVER_TYPE             _driverType;
        D3D_FEATURE_LEVEL           _featureLevel;

        IDXGISwapChain*             _swapChain;
        ID3D11RenderTargetView*     _renderTargetView;
        ID3D11DepthStencilView*     _depthStencilView;
        ID3D11Texture2D*            _depthStencilBuffer;
        ID3D11DepthStencilState*    _depthStencilState;
        ID3D11DepthStencilState*    _depthDisabledStencilState;
        ID3D11RasterizerState*      _rasterizerState;
        D3D11_VIEWPORT              _screenViewport;

        UINT                        _4xMsaaQuality;
        UINT                        _MSAASampleCount;
        UINT                        _MSAASampleQuality;
        ID3D11SamplerState*         _colorSampler;
        ID3D11RasterizerState*      _backFaceCulling;

        SPtr<ConstantBufferElement> _frameConstantBuffer;
        SPtr<ConstantBufferElement> _objectConstantBuffer;
        SPtr<ConstantBufferElement> _lightConstantBuffer;
        SPtr<ConstantBufferElement> _quadConstantBuffer;
    };

    RenderAPI& gRenderAPI();
    RenderAPI* gRenderAPIPtr();
}