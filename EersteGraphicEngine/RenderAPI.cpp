#include "RenderAPI.h"

#include "ShaderManager.h"
#include "EventManager.h"
#include "Window.h"

namespace ege
{
    RenderAPI::RenderAPI()
    {
        _driverType                = D3D_DRIVER_TYPE_HARDWARE;
        _featureLevel              = D3D_FEATURE_LEVEL_11_0;

        _swapChain                 = nullptr;
        _renderTargetView          = nullptr;
        _depthStencilView          = nullptr;
        _depthStencilBuffer        = nullptr;
        _depthStencilState         = nullptr;
        _rasterizerState           = nullptr;
        _screenViewport            = { 0 };

        _colorSampler              = nullptr;
        _backFaceCulling           = nullptr;

        _depthStencilState         = nullptr;
        _depthDisabledStencilState = nullptr;

        _frameConstantBuffer       = nullptr;
        _objectConstantBuffer      = nullptr;
        _lightConstantBuffer       = nullptr;
        _quadConstantBuffer        = nullptr;

        _MSAASampleCount          = 1;
        _MSAASampleQuality        = 0;
    }

    RenderAPI::~RenderAPI()
    {
    }

    void RenderAPI::OnStartUp()
    {
        gEventManager().Suscribe("WINDOW_RESIZED", std::bind(&RenderAPI::OnResize, this));
        gEventManager().Suscribe("WINDOW_FULLSCREEN", std::bind(&RenderAPI::OnFullScreen, this));

        LoadRenderConfig();
        Initialise();

        ShaderManager::StartUp();
    }

    void RenderAPI::OnShutDown()
    {
        ShaderManager::ShutDown();

        if (_swapChain != nullptr)
        {
            _swapChain->SetFullscreenState(FALSE, NULL);
        }

        SafeReleaseCom(_swapChain);
        SafeReleaseCom(_renderTargetView);
        SafeReleaseCom(_depthStencilView);
        SafeReleaseCom(_depthStencilBuffer);
        SafeReleaseCom(_depthStencilState);
        SafeReleaseCom(_rasterizerState);

        SafeReleaseCom(_colorSampler);
        SafeReleaseCom(_backFaceCulling);

        SafeReleaseCom(_dxgiDevice);
        SafeReleaseCom(_dxgiAdapter);
        SafeReleaseCom(_dxgiFactory);

		SafeRelease(_device);
    }

    void RenderAPI::OnResize()
    {
        Resize();
    }

    void RenderAPI::OnFullScreen()
    {
        Resize();
        _renderDesc.FullScreen = (_renderDesc.FullScreen) ? false : true;
    }

    void RenderAPI::Draw()
    {
        ClearRenderTargetView();
        ClearDepthStencilView();

		ID3D11Debug* debugDevice = nullptr;
    }

    void RenderAPI::ClearRenderTargetView()
    {
        ID3D11DeviceContext* context = _device->GetImmediateContext();
        context->ClearRenderTargetView(_renderTargetView, reinterpret_cast<const float*>(&Colors::Black));
    }

    void RenderAPI::ClearDepthStencilView()
    {
        ID3D11DeviceContext* context = _device->GetImmediateContext();
        context->ClearDepthStencilView(_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    }

    void RenderAPI::SwapBuffers()
    {
        if (_device->GetD3D11Device() != nullptr)
        {
            HRESULT hr = S_OK;

            if (_renderDesc.VSync)
            {
                hr = _swapChain->Present(1, 0);
            }
            else
            {
                hr = _swapChain->Present(0, 0);
            }

            if (FAILED(hr))
            {
                EGE_ASSERT_ERROR(false, "Error Presenting surfaces");
            }
        }
    }

    void RenderAPI::TurnZBufferOn()
    {
        _device->GetImmediateContext()->OMSetDepthStencilState(_depthStencilState, 1);
    }

    void RenderAPI::TurnZBufferOff()
    {
        _device->GetImmediateContext()->OMSetDepthStencilState(_depthDisabledStencilState, 1);
    }

    void RenderAPI::CreateDevice()
    {
        HRESULT hr = S_OK;
        UINT createDeviceFlags = 0;

#if defined(EGE_DEBUG) && defined(EGE_GRAPHIC_DEBUG) 
        createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

        D3D_DRIVER_TYPE driverTypes[] =
        {
            D3D_DRIVER_TYPE_HARDWARE,
            D3D_DRIVER_TYPE_WARP,
            D3D_DRIVER_TYPE_REFERENCE
        };

        UINT numDriverTypes = ARRAYSIZE(driverTypes);

        D3D_FEATURE_LEVEL featureLevels[] =
        {
            D3D_FEATURE_LEVEL_11_0,
            D3D_FEATURE_LEVEL_10_1,
            D3D_FEATURE_LEVEL_10_0
        };

        UINT numFeatureLevels = ARRAYSIZE(featureLevels);

        ID3D11Device* device = nullptr;

        hr = D3D11CreateDevice(nullptr, _driverType, nullptr, createDeviceFlags, featureLevels,
            numFeatureLevels, D3D11_SDK_VERSION, &device, &_featureLevel, nullptr);

        _device = new Device(device);

        EGE_ASSERT_ERROR(SUCCEEDED(hr), "Can't create device");
    }

    void RenderAPI::CheckMSAASupport()
    {
        _device->GetD3D11Device()->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &_4xMsaaQuality);
        assert(_4xMsaaQuality > 0);

        _MSAASampleCount = 4;
        _MSAASampleQuality = _4xMsaaQuality - 1;
    }

    void RenderAPI::CreateSwapChain()
    {
        HRESULT hr = S_OK;
        Window& window = gWindow();
        ID3D11Device* device = _device->GetD3D11Device();
        DXGI_SWAP_CHAIN_DESC sd;

        ZeroMemory(&sd, sizeof(sd));

        sd.BufferCount = 2;
        sd.BufferDesc.Width = window.GetWindowWidth();
        sd.BufferDesc.Height = window.GetWindowHeight();
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 0;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = window.GetHWnd();
        sd.Windowed = TRUE;
        sd.SampleDesc.Count = _MSAASampleCount;
        sd.SampleDesc.Quality = _MSAASampleQuality;
        sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

        hr = device->QueryInterface(__uuidof(IDXGIDevice), (void**)&_dxgiDevice);
        hr = _dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&_dxgiAdapter);
        hr = _dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&_dxgiFactory);
        hr = _dxgiFactory->CreateSwapChain(device, &sd, &_swapChain);

        EGE_ASSERT_ERROR(SUCCEEDED(hr), "Can't create swap chain");

        ID3D11Texture2D* pBackBuffer = nullptr;
        hr = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

        hr = device->CreateRenderTargetView(pBackBuffer, nullptr, &_renderTargetView);
        pBackBuffer->Release();

        EGE_ASSERT_ERROR(SUCCEEDED(hr), "Can't create back buffer");
    }

    void RenderAPI::CreateDepthStencilBuffer()
    {
        HRESULT hr = S_OK;
        Window& window = gWindow();
        D3D11_TEXTURE2D_DESC depthStencilDesc;
        ID3D11Device* device = _device->GetD3D11Device();

        depthStencilDesc.Width = window.GetWindowWidth();
        depthStencilDesc.Height = window.GetWindowHeight();
        depthStencilDesc.MipLevels = 1;
        depthStencilDesc.ArraySize = 1;
        depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        depthStencilDesc.SampleDesc.Count = _MSAASampleCount;
        depthStencilDesc.SampleDesc.Quality = _MSAASampleQuality;
        depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
        depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        depthStencilDesc.CPUAccessFlags = 0;
        depthStencilDesc.MiscFlags = 0;

        hr = device->CreateTexture2D(&depthStencilDesc, nullptr, &_depthStencilBuffer);
        EGE_ASSERT_ERROR(SUCCEEDED(hr), "Can't create depth stencil buffer");

        device->CreateDepthStencilView(_depthStencilBuffer, nullptr, &_depthStencilView);
        EGE_ASSERT_ERROR(SUCCEEDED(hr), "Can't create depth stencil view");
    }

    void RenderAPI::CreateViewport()
    {
        HRESULT hr = S_OK;
        Window& window = gWindow();
        ID3D11Device* device = _device->GetD3D11Device();
        ID3D11DeviceContext* context = _device->GetImmediateContext();

        // Setup the viewport
        _screenViewport.Width = (FLOAT)window.GetWindowWidth();
        _screenViewport.Height = (FLOAT)window.GetWindowHeight();
        _screenViewport.MinDepth = 0.0f;
        _screenViewport.MaxDepth = 1.0f;
        _screenViewport.TopLeftX = 0;
        _screenViewport.TopLeftY = 0;
        context->RSSetViewports(1, &_screenViewport);
    }

    void RenderAPI::CreateConstantBuffers()
    {
        HRESULT hr = S_OK;
        Window& window = gWindow();
        ID3D11Device* device = _device->GetD3D11Device();

        // Create constant buffers
        _frameConstantBuffer = ege_shared_ptr_new<ConstantBufferElement>();
        _objectConstantBuffer = ege_shared_ptr_new<ConstantBufferElement>();
        _lightConstantBuffer = ege_shared_ptr_new<ConstantBufferElement>();
        _quadConstantBuffer = ege_shared_ptr_new<ConstantBufferElement>();

        D3D11_BUFFER_DESC bdFrame;
        ZeroMemory(&bdFrame, sizeof(bdFrame));
        bdFrame.Usage = D3D11_USAGE_DEFAULT;
        bdFrame.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        bdFrame.CPUAccessFlags = 0;

        bdFrame.ByteWidth = sizeof(FrameConstantBuffer);
        hr = device->CreateBuffer(&bdFrame, nullptr, &_frameConstantBuffer->Buffer);
        _frameConstantBuffer->UpdateBuffer = ege_shared_ptr_new<FrameConstantBuffer>();

        EGE_ASSERT_ERROR(SUCCEEDED(hr), "Can't create frame constant buffer");

        bdFrame.ByteWidth = sizeof(ObjectConstantBuffer);
        hr = device->CreateBuffer(&bdFrame, nullptr, &_objectConstantBuffer->Buffer);
        _objectConstantBuffer->UpdateBuffer = ege_shared_ptr_new<ObjectConstantBuffer>();

        EGE_ASSERT_ERROR(SUCCEEDED(hr), "Can't create object constant buffer");

        bdFrame.ByteWidth = sizeof(LightConstantBuffer);
        hr = device->CreateBuffer(&bdFrame, nullptr, &_lightConstantBuffer->Buffer);
        _lightConstantBuffer->UpdateBuffer = ege_shared_ptr_new<LightConstantBuffer>();

        EGE_ASSERT_ERROR(SUCCEEDED(hr), "Can't create light constant buffer");

        bdFrame.ByteWidth = sizeof(QuadConstantBuffer);
        hr = device->CreateBuffer(&bdFrame, nullptr, &_quadConstantBuffer->Buffer);
        _quadConstantBuffer->UpdateBuffer = ege_shared_ptr_new<QuadConstantBuffer>();

        EGE_ASSERT_ERROR(SUCCEEDED(hr), "Can't create quad constant buffer");
    }

    void RenderAPI::CreateColorSampler()
    {
        HRESULT hr = S_OK;
        D3D11_SAMPLER_DESC sampDesc;
        ID3D11Device* device = _device->GetD3D11Device();
        ID3D11DeviceContext* context = _device->GetImmediateContext();

        ZeroMemory(&sampDesc, sizeof(sampDesc));
        sampDesc.Filter = D3D11_FILTER_ANISOTROPIC;
        sampDesc.MaxAnisotropy = 8;
        sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
        sampDesc.MinLOD = 0;
        sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

        hr = device->CreateSamplerState(&sampDesc, &_colorSampler);

        EGE_ASSERT_ERROR(SUCCEEDED(hr), "Can't create color sampler");

        context->VSSetSamplers(0, 1, &_colorSampler);
        context->HSSetSamplers(0, 1, &_colorSampler);
        context->DSSetSamplers(0, 1, &_colorSampler);
        context->GSSetSamplers(0, 1, &_colorSampler);
        context->PSSetSamplers(0, 1, &_colorSampler);
    }

    void RenderAPI::CreateDepthStencilState()
    {
        HRESULT hr = S_OK;
        ID3D11Device* device = _device->GetD3D11Device();
        D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc;        

        //Create a depth stencil state with depth disabled
        ZeroMemory(&depthStencilStateDesc, sizeof(depthStencilStateDesc));

        depthStencilStateDesc.DepthEnable = false;
        depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
        depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_LESS;
        depthStencilStateDesc.StencilEnable = true;
        depthStencilStateDesc.StencilReadMask = 0xFF;
        depthStencilStateDesc.StencilWriteMask = 0xFF;
        depthStencilStateDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
        depthStencilStateDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
        depthStencilStateDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
        depthStencilStateDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
        depthStencilStateDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
        depthStencilStateDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
        depthStencilStateDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
        depthStencilStateDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

        hr = device->CreateDepthStencilState(&depthStencilStateDesc, &_depthDisabledStencilState);

        EGE_ASSERT_ERROR(SUCCEEDED(hr), "Can't create depth stencil state with disabled depth");

        //Create a depth stencil state with depth enabled
        ZeroMemory(&depthStencilStateDesc, sizeof(depthStencilStateDesc));

        depthStencilStateDesc.DepthEnable = true;
        depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
        depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_LESS;
        depthStencilStateDesc.StencilEnable = true;
        depthStencilStateDesc.StencilReadMask = 0xFF;
        depthStencilStateDesc.StencilWriteMask = 0xFF;
        depthStencilStateDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
        depthStencilStateDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
        depthStencilStateDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
        depthStencilStateDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
        depthStencilStateDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
        depthStencilStateDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
        depthStencilStateDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
        depthStencilStateDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

        hr = device->CreateDepthStencilState(&depthStencilStateDesc, &_depthStencilState);

        EGE_ASSERT_ERROR(SUCCEEDED(hr), "Can't create depth stencil state with enabled depth");
    }

    void RenderAPI::SetPrimitiveTopology()
    {
        ID3D11Device* device = _device->GetD3D11Device();
        ID3D11DeviceContext* context = _device->GetImmediateContext();

        context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    }

    void RenderAPI::SetBackfaceCulling()
    {
        HRESULT hr = S_OK;
        ID3D11Device* device = _device->GetD3D11Device();
        ID3D11DeviceContext* context = _device->GetImmediateContext();

        if (_renderDesc.BackfaceCulling)
        {
            D3D11_RASTERIZER_DESC wfdescBackFaceCulling;
            ZeroMemory(&wfdescBackFaceCulling, sizeof(D3D11_RASTERIZER_DESC));
            wfdescBackFaceCulling.FillMode = D3D11_FILL_SOLID;
            wfdescBackFaceCulling.CullMode = D3D11_CULL_BACK;
            wfdescBackFaceCulling.MultisampleEnable = true;
            hr = device->CreateRasterizerState(&wfdescBackFaceCulling, &_backFaceCulling);

            EGE_ASSERT_ERROR(SUCCEEDED(hr), "Can't create back face culling rasterizer state");

            context->RSSetState(_backFaceCulling);
        }
    }

    void RenderAPI::Initialise()
    {
        CreateDevice();
        CheckMSAASupport();
        CreateSwapChain();
        CreateDepthStencilBuffer();
        CreateViewport();
        CreateConstantBuffers();
        CreateColorSampler();
        CreateDepthStencilState();
        SetPrimitiveTopology();
        SetBackfaceCulling();  
    }

    void RenderAPI::Resize()
    {
        ID3D11Device* device = _device->GetD3D11Device();
        ID3D11DeviceContext* context = _device->GetImmediateContext();

        EGE_ASSERT_ERROR((device != nullptr), "Device is not initialised");
        EGE_ASSERT_ERROR((context != nullptr), "Context is not initialised");
        EGE_ASSERT_ERROR((_swapChain != nullptr), "Swap chain is not initialised");

        SafeReleaseCom(_renderTargetView);
        SafeReleaseCom(_depthStencilView);
        SafeReleaseCom(_depthStencilBuffer);

        // Resize the swap chain and recreate the render target view.
        HR(_swapChain->ResizeBuffers(1, gWindow().GetWindowWidth(), gWindow().GetWindowHeight(), DXGI_FORMAT_R8G8B8A8_UNORM, 0), "Can't resize swap chain buffer");
        ID3D11Texture2D* pBackBuffer = nullptr;
        HR(_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer), "Can't get swap chain buffer");
        HR(device->CreateRenderTargetView(pBackBuffer, 0, &_renderTargetView), "Can't create render target view");
        SafeReleaseCom(pBackBuffer);

        CreateDepthStencilBuffer();
        CreateViewport();
    }

    void RenderAPI::LoadRenderConfig()
    {
#ifdef EGE_CONFIG_RENDER_FILE
        tinyxml2::XMLDocument document;
        document.LoadFile(EGE_CONFIG_RENDER_FILE);

        tinyxml2::XMLElement* renderElement = document.FirstChildElement("render");
        EGE_ASSERT_ERROR((renderElement != nullptr), "Render file malformed");

        for (tinyxml2::XMLElement* optionElement = renderElement->FirstChildElement("option"); optionElement != nullptr; optionElement = optionElement->NextSiblingElement())
        {
            String type  = optionElement->Attribute("type");
            String value = optionElement->Attribute("value");

            if (type == "msaa")
            {
                _renderDesc.Msaa = optionElement->IntAttribute("value");
            }
            else if (type == "back-face-culling")
            {
                _renderDesc.BackfaceCulling = (value == "true") ? true : false;
            }
            else if (type == "frustum-culling")
            {
                _renderDesc.FrustumCulling = (value == "true") ? true : false;
            }
            else if (type == "fullscreen")
            {
                _renderDesc.FullScreen = (value == "true") ? true : false;
            }
            else if (type == "vsync")
            {
                _renderDesc.VSync = (value == "true") ? true : false;
            }
            else if (type == "pipeline")
            {
                _renderDesc.Pipeline = (value == "forward") ? RenderPipelineType::FORWARD : RenderPipelineType::DEFERRED;
            }
        }
#endif
    }

    Device* RenderAPI::GetDevice()
    {
        return _device;
    }

    SPtr<ConstantBufferElement> RenderAPI::GetConstantBufferPtr(ConstantBufferType type)
    {
        switch (type)
        {
        case ConstantBufferType::FRAME:
            return _frameConstantBuffer;
            break;

        case ConstantBufferType::OBJECT:
            return _objectConstantBuffer;
            break;

        case ConstantBufferType::LIGHT:
            return _lightConstantBuffer;
            break;

        case ConstantBufferType::QUAD:
            return _quadConstantBuffer;
            break;
        }

        return _frameConstantBuffer;
    }

    RenderDesc& RenderAPI::GetRenderDesc()
    {
        return _renderDesc;
    }

    ID3D11RenderTargetView* RenderAPI::GetRenderTargetView()
    {
        return _renderTargetView;
    }

    ID3D11DepthStencilView* RenderAPI::GetDepthStencilView()
    {
        return _depthStencilView;
    }

    UINT RenderAPI::GetMSAASampleCount()
    {
        return _MSAASampleCount;
    }

    UINT RenderAPI::GetMSAASampleQuality()
    {
        return _MSAASampleQuality;
    }

    RenderAPI& gRenderAPI()
    {
        return static_cast<RenderAPI&>(RenderAPI::Instance());
    }

    RenderAPI* gRenderAPIPtr()
    {
        return static_cast<RenderAPI*>(RenderAPI::InstancePtr());
    }
}