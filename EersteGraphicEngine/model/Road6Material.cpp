#include "Road6Material.h"
#include "ShaderManager.h"
#include "TextureManager.h"

namespace ege
{
    Road6Material::Road6Material()
        : Material()
    {
    }

    Road6Material::~Road6Material()
    {
    }

    void Road6Material::Initialise()
    {
        _shader = gShaderManager().GetPtr("default");

        _hasDiffuseTexture = true;
        _hasSpecularTexture = true;
        _hasNormalTexture = false;

        InsertTexture(0, gTextureManager().GetPtr("road-6-diffuse"));
        InsertTexture(1, gTextureManager().GetPtr("road-6-specular"));
    }

    void Road6Material::Update()
    {
    }
}