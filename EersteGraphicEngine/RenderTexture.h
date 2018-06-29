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
        ID3D11RenderTargetView*   GetRenderTargetView();
        ID3D11ShaderResourceView* GetShaderResourceView();

    protected:
        void                      Clean();
        HRESULT                   CreateRenderTargetTexture();
        HRESULT                   CreateRenderTargetView();
        HRESULT                   CreateShaderResourceView();

    protected:
        RenderAPI&                      _renderAPI;
        Window&                         _window;

        UINT                            _width;
        UINT                            _height;

        ID3D11Texture2D*                _renderTargetTexture;
        ID3D11Texture2D*                _renderMSTargetTexture;
        ID3D11RenderTargetView*         _renderTargetView;
        ID3D11ShaderResourceView*       _shaderResourceView;

        D3D11_TEXTURE2D_DESC            _renderTargetTextureDesc;
        D3D11_RENDER_TARGET_VIEW_DESC   _renderTargetViewDesc;
        D3D11_SHADER_RESOURCE_VIEW_DESC _shaderResourceViewDesc;
    };
}