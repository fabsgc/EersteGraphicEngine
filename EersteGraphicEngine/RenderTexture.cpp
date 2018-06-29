#include "RenderTexture.h"

namespace ege
{
    RenderTexture::RenderTexture(UINT width, UINT height)
        : _renderAPI(gRenderAPI())
        , _window(gWindow())
        , _renderTargetTexture(nullptr)
        , _renderMSTargetTexture(nullptr)
        , _renderTargetView(nullptr)
        , _renderMSTargetView(nullptr)
        , _shaderResourceView(nullptr)
        , _shaderMSResourceView(nullptr)
        , _width(width)
        , _height(height)
    {
    }

    RenderTexture::~RenderTexture()
    {
        Clean();
    }

    void RenderTexture::Initialise()
    {
        EGE_ASSERT_ERROR(SUCCEEDED(CreateRenderTargetTexture()), "Can't create render target texture");
        EGE_ASSERT_ERROR(SUCCEEDED(CreateRenderMSTargetTexture()), "Can't create render ms target texture");
        EGE_ASSERT_ERROR(SUCCEEDED(CreateRenderTargetView()), "Can't create render target view");
        EGE_ASSERT_ERROR(SUCCEEDED(CreateRenderMSTargetView()), "Can't create render ms target view");
        EGE_ASSERT_ERROR(SUCCEEDED(CreateShaderResourceView()), "Can't create shader resource view");
        EGE_ASSERT_ERROR(SUCCEEDED(CreateShaderMSResourceView()), "Can't create shader ms resource view");
    }

    void RenderTexture::Resize(UINT width, UINT height)
    {
        _width  = width;
        _height = height;

        Clean();
        Initialise();
    }

    void RenderTexture::Clean()
    {
        SafeReleaseCom(_renderTargetTexture);
        SafeReleaseCom(_renderMSTargetTexture);
        SafeReleaseCom(_renderTargetView);
        SafeReleaseCom(_renderMSTargetView);
        SafeReleaseCom(_shaderResourceView);
        SafeReleaseCom(_shaderMSResourceView);
    }

    HRESULT RenderTexture::CreateRenderTargetTexture()
    {
        ID3D11Device* device = _renderAPI.GetDevice()->GetD3D11Device();

        ZeroMemory(&_renderTargetTextureDesc, sizeof(_renderTargetTextureDesc));

        _renderTargetTextureDesc.Width = _width;
        _renderTargetTextureDesc.Height = _height;
        _renderTargetTextureDesc.MipLevels = 1;
        _renderTargetTextureDesc.ArraySize = 1;
        _renderTargetTextureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        _renderTargetTextureDesc.Usage = D3D11_USAGE_DEFAULT;
        _renderTargetTextureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
        _renderTargetTextureDesc.CPUAccessFlags = 0;
        _renderTargetTextureDesc.MiscFlags = 0;
        _renderTargetTextureDesc.SampleDesc.Count = 1;

        return device->CreateTexture2D(&_renderTargetTextureDesc, NULL, &_renderTargetTexture);
    }

    HRESULT RenderTexture::CreateRenderMSTargetTexture()
    {
        ID3D11Device* device = _renderAPI.GetDevice()->GetD3D11Device();

        ZeroMemory(&_renderMSTargetTextureDesc, sizeof(_renderMSTargetTextureDesc));

        _renderMSTargetTextureDesc.Width = _width;
        _renderMSTargetTextureDesc.Height = _height;
        _renderMSTargetTextureDesc.MipLevels = 1;
        _renderMSTargetTextureDesc.ArraySize = 1;
        _renderMSTargetTextureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        _renderMSTargetTextureDesc.Usage = D3D11_USAGE_DEFAULT;
        _renderMSTargetTextureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
        _renderMSTargetTextureDesc.CPUAccessFlags = 0;
        _renderMSTargetTextureDesc.MiscFlags = 0;
        _renderMSTargetTextureDesc.SampleDesc.Count = _renderAPI.GetMSAASampleCount();
        _renderMSTargetTextureDesc.SampleDesc.Quality = _renderAPI.GetMSAASampleQuality();

        return device->CreateTexture2D(&_renderMSTargetTextureDesc, NULL, &_renderMSTargetTexture);
    }

    HRESULT RenderTexture::CreateRenderTargetView()
    {
        ID3D11Device* device = _renderAPI.GetDevice()->GetD3D11Device();

        _renderTargetViewDesc.Format = _renderTargetTextureDesc.Format;
        _renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
        _renderTargetViewDesc.Texture2D.MipSlice = 0;

        return device->CreateRenderTargetView(_renderTargetTexture, &_renderTargetViewDesc, &_renderTargetView);
    }

    HRESULT RenderTexture::CreateRenderMSTargetView()
    {
        ID3D11Device* device = _renderAPI.GetDevice()->GetD3D11Device();

        _renderMSTargetViewDesc.Format = _renderMSTargetTextureDesc.Format;
        _renderMSTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;
        _renderMSTargetViewDesc.Texture2D.MipSlice = 0;

        return device->CreateRenderTargetView(_renderMSTargetTexture, &_renderMSTargetViewDesc, &_renderMSTargetView);
    }

    HRESULT RenderTexture::CreateShaderResourceView()
    {
        ID3D11Device* device = _renderAPI.GetDevice()->GetD3D11Device();

        _shaderResourceViewDesc.Format = _renderTargetTextureDesc.Format;
        _shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        _shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
        _shaderResourceViewDesc.Texture2D.MipLevels = 1;

        return device->CreateShaderResourceView(_renderTargetTexture, &_shaderResourceViewDesc, &_shaderResourceView);
    }

    HRESULT RenderTexture::CreateShaderMSResourceView()
    {
        ID3D11Device* device = _renderAPI.GetDevice()->GetD3D11Device();

        _shaderMSResourceViewDesc.Format = _renderMSTargetTextureDesc.Format;
        _shaderMSResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMS;
        _shaderMSResourceViewDesc.Texture2D.MostDetailedMip = 0;
        _shaderMSResourceViewDesc.Texture2D.MipLevels = 1;

        return device->CreateShaderResourceView(_renderMSTargetTexture, &_shaderMSResourceViewDesc, &_shaderMSResourceView);
    }

    ID3D11Texture2D* RenderTexture::GetRenderTargetTexture()
    {
        return _renderTargetTexture;
    }

    ID3D11Texture2D* RenderTexture::GetRenderMSTargetTexture()
    {
        return _renderMSTargetTexture;
    }

    ID3D11RenderTargetView* RenderTexture::GetRenderTargetView()
    {
        return _renderTargetView;
    }

    ID3D11RenderTargetView* RenderTexture::GetRenderMSTargetView()
    {
        return _renderMSTargetView;
    }

    ID3D11ShaderResourceView* RenderTexture::GetShaderResourceView()
    {
        return _shaderResourceView;
    }

    ID3D11ShaderResourceView* RenderTexture::GetShaderMSResourceView()
    {
        return _shaderMSResourceView;
    }

    void RenderTexture::BoundNonMsTexture()
    {
        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        context->ResolveSubresource(_renderTargetTexture, 0, _renderMSTargetTexture, 0, _renderTargetTextureDesc.Format);
    }
}