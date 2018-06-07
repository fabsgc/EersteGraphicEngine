#include "RenderAPI.h"

#include "ShaderManager.h"
#include "EventManager.h"
#include "Window.h"

namespace ege
{
    RenderAPI::RenderAPI()
    {
        _driverType           = D3D_DRIVER_TYPE_HARDWARE;
        _featureLevel         = D3D_FEATURE_LEVEL_11_0;

        _swapChain            = nullptr;
        _renderTargetView     = nullptr;
        _depthStencilView     = nullptr;
        _depthStencilBuffer   = nullptr;
        _depthStencilState    = nullptr;
        _rasterizerState      = nullptr;
        _screenViewport       = { 0 };

        _colorSampler         = nullptr;
        _backFaceCulling      = nullptr;

        _frameConstantBuffer  = nullptr;
        _objectConstantBuffer = nullptr;
        _lightConstantBuffer  = nullptr;
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

        SafeReleaseCom(_frameConstantBuffer);
        SafeReleaseCom(_objectConstantBuffer);
        SafeReleaseCom(_lightConstantBuffer);

        SafeReleaseCom(_dxgiDevice);
        SafeReleaseCom(_dxgiAdapter);
        SafeReleaseCom(_dxgiFactory);
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
        ID3D11DeviceContext* context = _device->GetImmediateContext();

        context->ClearRenderTargetView(_renderTargetView, reinterpret_cast<const float*>(&Colors::LightSteelBlue));
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

    void RenderAPI::Initialise()
    {
        HRESULT hr = S_OK;
        UINT createDeviceFlags = 0;
        Window& window = gWindow();

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
        ID3D11DeviceContext* context = _device->GetImmediateContext();

        if (FAILED(hr))
        {
            EGE_ASSERT_ERROR(SUCCEEDED(hr), "Failed to initialie device");
        }

        device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &_4xMsaaQuality);
        assert(_4xMsaaQuality > 0);

        DXGI_SWAP_CHAIN_DESC sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.BufferCount = 1;
        sd.BufferDesc.Width = window.GetWindowWidth();
        sd.BufferDesc.Height = window.GetWindowHeight();
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 0;
        sd.BufferDesc.RefreshRate.Denominator = 0;
        sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = window.GetHWnd();
        sd.Windowed = TRUE;
        sd.SampleDesc.Count = 4;
        sd.SampleDesc.Quality = _4xMsaaQuality - 1;
        sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

        hr = device->QueryInterface(__uuidof(IDXGIDevice), (void**)&_dxgiDevice);
        hr = _dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&_dxgiAdapter);
        hr = _dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&_dxgiFactory);
        hr = _dxgiFactory->CreateSwapChain(device, &sd, &_swapChain);

        // Create a render target view
        ID3D11Texture2D* pBackBuffer = nullptr;
        hr = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

        if (FAILED(hr))
        {
            EGE_ASSERT_ERROR(SUCCEEDED(hr), "Failed to initialie swap chain");
        }

        hr = device->CreateRenderTargetView(pBackBuffer, nullptr, &_renderTargetView);
        pBackBuffer->Release();

        if (FAILED(hr))
        {
            EGE_ASSERT_ERROR(SUCCEEDED(hr), "Failed to initialie render target view");
        }

        //Init depth stencil and buffer
        D3D11_TEXTURE2D_DESC depthStencilDesc;

        depthStencilDesc.Width = window.GetWindowWidth();
        depthStencilDesc.Height = window.GetWindowHeight();
        depthStencilDesc.MipLevels = 1;
        depthStencilDesc.ArraySize = 1;
        depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        depthStencilDesc.SampleDesc.Count = 4;
        depthStencilDesc.SampleDesc.Quality = _4xMsaaQuality - 1;
        depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
        depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        depthStencilDesc.CPUAccessFlags = 0;
        depthStencilDesc.MiscFlags = 0;

        device->CreateTexture2D(&depthStencilDesc, nullptr, &_depthStencilBuffer);
        device->CreateDepthStencilView(_depthStencilBuffer, nullptr, &_depthStencilView);

        context->OMSetRenderTargets(1, &_renderTargetView, _depthStencilView);

        // Setup the viewport
        _screenViewport.Width = (FLOAT)window.GetWindowWidth();
        _screenViewport.Height = (FLOAT)window.GetWindowHeight();
        _screenViewport.MinDepth = 0.0f;
        _screenViewport.MaxDepth = 1.0f;
        _screenViewport.TopLeftX = 0;
        _screenViewport.TopLeftY = 0;
        context->RSSetViewports(1, &_screenViewport);

        // Set primitive topology
        context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        // Create constant buffers
        D3D11_BUFFER_DESC bdFrame;
        ZeroMemory(&bdFrame, sizeof(bdFrame));
        bdFrame.Usage = D3D11_USAGE_DEFAULT;
        bdFrame.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        bdFrame.CPUAccessFlags = 0;

        bdFrame.ByteWidth = sizeof(FrameConstantBuffer);
        hr = device->CreateBuffer(&bdFrame, nullptr, &_frameConstantBuffer);

        bdFrame.ByteWidth = sizeof(ObjectConstantBuffer);
        hr = device->CreateBuffer(&bdFrame, nullptr, &_objectConstantBuffer);

        bdFrame.ByteWidth = sizeof(LightConstantBuffer);
        hr = device->CreateBuffer(&bdFrame, nullptr, &_lightConstantBuffer);

        //Set constant buffers for each type of shader
        context->VSSetConstantBuffers(0, 1, &_frameConstantBuffer);
        context->HSSetConstantBuffers(0, 1, &_frameConstantBuffer);
        context->DSSetConstantBuffers(0, 1, &_frameConstantBuffer);
        context->GSSetConstantBuffers(0, 1, &_frameConstantBuffer);
        context->PSSetConstantBuffers(0, 1, &_frameConstantBuffer);

        context->VSSetConstantBuffers(1, 1, &_objectConstantBuffer);
        context->HSSetConstantBuffers(1, 1, &_objectConstantBuffer);
        context->DSSetConstantBuffers(1, 1, &_objectConstantBuffer);
        context->GSSetConstantBuffers(1, 1, &_objectConstantBuffer);
        context->PSSetConstantBuffers(1, 1, &_objectConstantBuffer);

        context->VSSetConstantBuffers(2, 1, &_objectConstantBuffer);
        context->HSSetConstantBuffers(2, 1, &_objectConstantBuffer);
        context->DSSetConstantBuffers(2, 1, &_objectConstantBuffer);
        context->GSSetConstantBuffers(2, 1, &_objectConstantBuffer);
        context->PSSetConstantBuffers(2, 1, &_objectConstantBuffer);
        
        //Create Color Sampler
        D3D11_SAMPLER_DESC sampDesc;
        ZeroMemory(&sampDesc, sizeof(sampDesc));
        sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
        sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
        sampDesc.MinLOD = 0;
        sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

        hr = device->CreateSamplerState(&sampDesc, &_colorSampler);
        context->VSSetSamplers(0, 1, &_colorSampler);
        context->HSSetSamplers(0, 1, &_colorSampler);
        context->DSSetSamplers(0, 1, &_colorSampler);
        context->GSSetSamplers(0, 1, &_colorSampler);
        context->PSSetSamplers(0, 1, &_colorSampler);

        if (_renderDesc.BackfaceCulling)
        {
            D3D11_RASTERIZER_DESC wfdescBackFaceCulling;
            ZeroMemory(&wfdescBackFaceCulling, sizeof(D3D11_RASTERIZER_DESC));
            wfdescBackFaceCulling.FillMode = D3D11_FILL_SOLID;
            wfdescBackFaceCulling.CullMode = D3D11_CULL_BACK;
            hr = device->CreateRasterizerState(&wfdescBackFaceCulling, &_backFaceCulling);

            context->RSSetState(_backFaceCulling);
        }
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

        //Init depth stencil and buffer
        D3D11_TEXTURE2D_DESC depthStencilDesc;

        depthStencilDesc.Width = gWindow().GetWindowWidth();
        depthStencilDesc.Height = gWindow().GetWindowHeight();
        depthStencilDesc.MipLevels = 1;
        depthStencilDesc.ArraySize = 1;
        depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        depthStencilDesc.SampleDesc.Count = 4;
        depthStencilDesc.SampleDesc.Quality = _4xMsaaQuality - 1;;
        depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
        depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        depthStencilDesc.CPUAccessFlags = 0;
        depthStencilDesc.MiscFlags = 0;

        device->CreateTexture2D(&depthStencilDesc, nullptr, &_depthStencilBuffer);
        device->CreateDepthStencilView(_depthStencilBuffer, nullptr, &_depthStencilView);

        context->OMSetRenderTargets(1, &_renderTargetView, _depthStencilView);

        // Setup the viewport
        _screenViewport.TopLeftX = 0;
        _screenViewport.TopLeftY = 0;
        _screenViewport.Width = static_cast<float>(gWindow().GetWindowWidth());
        _screenViewport.Height = static_cast<float>(gWindow().GetWindowHeight());
        _screenViewport.MinDepth = 0.0f;
        _screenViewport.MaxDepth = 1.0f;
        context->RSSetViewports(1, &_screenViewport);
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
        }
#endif
    }

    Device* RenderAPI::GetDevice()
    {
        return _device;
    }

    ID3D11Buffer*   RenderAPI::GetConstantBuffer(ConstantBufferType type)
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
        }

        return _frameConstantBuffer;
    }

    ConstantBuffer* RenderAPI::GetConstantBufferUpdate(ConstantBufferType type)
    {
        switch (type)
        {
        case ConstantBufferType::FRAME:
            return &_frameConstantBufferUpdate;
            break;

        case ConstantBufferType::OBJECT:
            return &_objectConstantBufferUpdate;
            break;

        case ConstantBufferType::LIGHT:
            return &_lightConstantBufferUpdate;
            break;
        }

        return &_frameConstantBufferUpdate;
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