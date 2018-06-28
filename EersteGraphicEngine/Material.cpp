#include "Material.h"

namespace ege
{
    const XMFLOAT4 Material::DefaultSpecularColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    const float    Material::DefaultSpecularPower = 8.0f;
    const float    Material::DefaultEmitPower     = 0.0f;

    Material::Material()
        : _renderAPI(gRenderAPI())
        , _shader(nullptr)
        , _specularColor(DefaultSpecularColor)
        , _specularPower(DefaultSpecularPower)
        , _emitPower(DefaultEmitPower)
        , _hasSpecular(false)
        , _hasEmit(false)
        , _hasDiffuseTexture(false)
        , _hasSpecularTexture(false)
        , _hasNormalTexture(false)
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
        ConstantBufferElement* constantBuffer = _renderAPI.GetConstantBuffer(ConstantBufferType::OBJECT);
        ObjectConstantBuffer* constantBufferUpdate = (ObjectConstantBuffer*)&*constantBuffer->UpdateBuffer;

        constantBufferUpdate->SpecularColor      = _specularColor;
        constantBufferUpdate->SpecularPower      = _specularPower;
        constantBufferUpdate->EmitPower          = _emitPower;
        constantBufferUpdate->HasSpecular        = _hasSpecular;
        constantBufferUpdate->HasEmit            = _hasEmit;
        constantBufferUpdate->HasDiffuseTexture  = _hasDiffuseTexture;
        constantBufferUpdate->HasSpecularTexture = _hasSpecularTexture;
        constantBufferUpdate->HasNormalTexture   = _hasNormalTexture;
    }

    const XMFLOAT4& Material::GetSpecularColor() const
    {
        return _specularColor;
    }

    const float& Material::GetSpecularPower() const
    {
        return _specularPower;
    }

    const float& Material::GetEmitPower() const
    {
        return _emitPower;
    }

    void Material::SetSpecularColor(XMFLOAT4& specularColor)
    {
        _specularColor = specularColor;
    }

    void Material::SetSpecularPower(float specularPower)
    {
        _specularPower = specularPower;
    }

    void Material::SetEmitPower(float emitPower)
    {
        _emitPower = emitPower;
    }

    void Material::InsertTexture(UINT slot, SPtr<Texture> texture)
    {
        _textures.insert(Pair<UINT, SPtr<Texture>>(slot, texture));
    }
}