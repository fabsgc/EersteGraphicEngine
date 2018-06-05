#include "Material.h"

namespace ege
{
    const XMFLOAT4 Material::DefaultSpecularColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    const float    Material::DefaultSpecularPower = 8.0f;

    Material::Material()
        : _renderAPI(gRenderAPI())
        , _shader(nullptr)
        , _specularColor(DefaultSpecularColor)
        , _specularPower(DefaultSpecularPower)
    {}

    Material::Material(SPtr<Shader> shader)
        : _renderAPI(gRenderAPI())
        ,_shader(shader) 
    {}

    void Material::Initialise()
    {
    }

    void Material::Update()
    {
    }

    void Material::Apply()
    {
        if (_shader != nullptr)
        {
            _shader->Apply();
        }
        
        for (auto texture : _textures)
        {
            texture.second->Apply(texture.first);
        }

        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        ID3D11Buffer* constantBuffer = _renderAPI.GetConstantBuffer();
        ConstantBuffer* constantBufferUpdate = _renderAPI.GetConstantBufferUpdate();

        constantBufferUpdate->SpecularColor = _specularColor;
        constantBufferUpdate->SpecularPower = XMFLOAT4(_specularPower, 0.0f, 0.0f, 0.0f);
    }

    const XMFLOAT4& Material::GetSpecularColor() const
    {
        return _specularColor;
    }

    const float& Material::GetSpecularPower() const
    {
        return _specularPower;
    }

    void Material::SetSpecularColor(XMFLOAT4& specularColor)
    {
        _specularColor = specularColor;
    }

    void Material::SetSpecularPower(float specularPower)
    {
        _specularPower = specularPower;
    }
}