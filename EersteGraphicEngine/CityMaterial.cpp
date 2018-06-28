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