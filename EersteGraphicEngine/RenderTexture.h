#pragma once

#include "PrerequisitesCore.h"
#include "RenderAPI.h"
#include "Window.h"

namespace ege
{
    class RenderTexture
    {
    public:
        RenderTexture(UINT width = 0, UINT height = 0);
        ~RenderTexture();

        void                      Initialise();
        void                      Resize(UINT Width, UINT Height);

        ID3D11Texture2D*          GetRenderTargetTexture();
        ID3D11Texture2D*          GetRenderMSTargetTexture();
        ID3D11RenderTargetView*   GetRenderTargetView();
        ID3D11RenderTargetView*   GetRenderMSTargetView();
        ID3D11ShaderResourceView* GetShaderResourceView();
        ID3D11ShaderResourceView* GetShaderMSResourceView();

        void                      BoundNonMsTexture();

    protected:
        void                      Clean();
        HRESULT                   CreateRenderTargetTexture();
        HRESULT                   CreateRenderMSTargetTexture();
        HRESULT                   CreateRenderTargetView();
        HRESULT                   CreateRenderMSTargetView();
        HRESULT                   CreateShaderResourceView();
        HRESULT                   CreateShaderMSResourceView();

    protected:
        RenderAPI&                      _renderAPI;
        Window&                         _window;

        UINT                            _width;
        UINT                            _height;

        ID3D11Texture2D*                _renderTargetTexture;
        ID3D11Texture2D*                _renderMSTargetTexture;
        ID3D11RenderTargetView*         _renderTargetView;
        ID3D11RenderTargetView*         _renderMSTargetView;
        ID3D11ShaderResourceView*       _shaderResourceView;
        ID3D11ShaderResourceView*       _shaderMSResourceView;

        D3D11_TEXTURE2D_DESC            _renderTargetTextureDesc;
        D3D11_TEXTURE2D_DESC            _renderMSTargetTextureDesc;
        D3D11_RENDER_TARGET_VIEW_DESC   _renderTargetViewDesc;
        D3D11_RENDER_TARGET_VIEW_DESC   _renderMSTargetViewDesc;
        D3D11_SHADER_RESOURCE_VIEW_DESC _shaderResourceViewDesc;
        D3D11_SHADER_RESOURCE_VIEW_DESC _shaderMSResourceViewDesc;
    };
}