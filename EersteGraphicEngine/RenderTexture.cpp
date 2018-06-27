#include "RenderTexture.h"

namespace ege
{
    RenderTexture::RenderTexture(UINT width, UINT height)
        : _renderAPI(gRenderAPI())
        , _window(gWindow())
        , _renderTargetTexture(nullptr)
        , _renderTargetView(nullptr)
        , _shaderResourceView(nullptr)
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
        EGE_ASSERT_ERROR(SUCCEEDED(CreateRenderTargetView()), "Can't create render target view");
        EGE_ASSERT_ERROR(SUCCEEDED(CreateShaderResourceView()), "Can't create shader resource view");
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
        SafeReleaseCom(_renderTargetView);
        SafeReleaseCom(_shaderResourceView);
    }

    HRESULT RenderTexture::CreateRenderTargetTexture()
    {
        ID3D11Device* device = _renderAPI.GetDevice()->GetD3D11Device();

        ZeroMemory(&_renderTargetTextureDesc, sizeof(_renderTargetTextureDesc));

        _renderTargetTextureDesc.Width = _width;
        _renderTargetTextureDesc.Height = _height;
        _renderTargetTextureDesc.MipLevels = 1;
        _renderTargetTextureDesc.ArraySize = 1;
        _renderTargetTextureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
        _renderTargetTextureDesc.SampleDesc.Count = 1;
        _renderTargetTextureDesc.Usage = D3D11_USAGE_DEFAULT;
        _renderTargetTextureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
        _renderTargetTextureDesc.CPUAccessFlags = 0;
        _renderTargetTextureDesc.MiscFlags = 0;

        return device->CreateTexture2D(&_renderTargetTextureDesc, NULL, &_renderTargetTexture);
    }

    HRESULT RenderTexture::CreateRenderTargetView()
    {
        ID3D11Device* device = _renderAPI.GetDevice()->GetD3D11Device();

        _renderTargetViewDesc.Format = _renderTargetTextureDesc.Format;
        _renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
        _renderTargetViewDesc.Texture2D.MipSlice = 0;

        return device->CreateRenderTargetView(_renderTargetTexture, &_renderTargetViewDesc, &_renderTargetView);
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

    ID3D11Texture2D* RenderTexture::GetRenderTargetTexture()
    {
        return _renderTargetTexture;
    }

    ID3D11RenderTargetView* RenderTexture::GetRenderTargetView()
    {
        return _renderTargetView;
    }

    ID3D11ShaderResourceView* RenderTexture::GetResourceView()
    {
        return _shaderResourceView;
    }
}