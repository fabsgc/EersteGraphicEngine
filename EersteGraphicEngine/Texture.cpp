#include "Texture.h"

namespace ege
{
    Texture::Texture(String filePath)
        : _renderAPI(gRenderAPI())
        , _filePath(filePath)
        , _texture(nullptr)
    {}

    Texture::~Texture()
    {
        SafeReleaseCom(_texture);
    }

    void Texture::Initialise()
    {
        ID3D11Device* device = _renderAPI.GetDevice()->GetD3D11Device();
        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        WString str = ToWString(_filePath);

        HRESULT hr = CreateDDSTextureFromFile(device, str.c_str(), nullptr, &_texture);

        EGE_ASSERT_ERROR((SUCCEEDED(hr)), ("Can't load texture from file : " + _filePath));
    }

    void Texture::Apply(UINT slot)
    {
        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        context->PSSetShaderResources(slot, 1, &_texture);
    }
}