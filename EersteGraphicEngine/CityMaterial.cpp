#include "CityMaterial.h"
#include "ShaderManager.h"
#include "TextureManager.h"

namespace ege
{
    CityMaterial::CityMaterial(String diffuseName, String specularName)
        : Material()
        , _diffuseName(diffuseName)
        , _specularName(specularName)
    {
    }

    CityMaterial::~CityMaterial()
    {
    }

    void CityMaterial::Initialise()
    {
        _shader = gShaderManager().GetPtr("forward-default");

        ConstantBufferElement* frameConstantBuffer = _renderAPI.GetConstantBuffer(ConstantBufferType::FRAME);
        ConstantBufferElement* objectConstantBuffer = _renderAPI.GetConstantBuffer(ConstantBufferType::OBJECT);
        ConstantBufferElement* lightConstantBuffer = _renderAPI.GetConstantBuffer(ConstantBufferType::LIGHT);

        _shader->InsertConstantBuffer(0, frameConstantBuffer);
        _shader->InsertConstantBuffer(1, objectConstantBuffer);
        _shader->InsertConstantBuffer(2, lightConstantBuffer);

        _hasSpecular = true;
        _hasEmit = false;
        _hasDiffuseTexture = true;
        _hasSpecularTexture = true;
        _hasNormalTexture = false;

        _specularPower = 16.0f;

        InsertTexture(0, gTextureManager().GetPtr(_diffuseName));
        InsertTexture(1, gTextureManager().GetPtr(_specularName));
    }

    void CityMaterial::Update()
    {
    }
}