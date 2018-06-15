#include "Road4Material.h"
#include "ShaderManager.h"
#include "TextureManager.h"

namespace ege
{
    Road4Material::Road4Material()
        : Material()
    {
    }

    Road4Material::~Road4Material()
    {
    }

    void Road4Material::Initialise()
    {
        _shader = gShaderManager().GetPtr("default");

        _hasDiffuseTexture = true;
        _hasSpecularTexture = true;
        _hasNormalTexture = false;

        InsertTexture(0, gTextureManager().GetPtr("road-4-diffuse"));
        InsertTexture(1, gTextureManager().GetPtr("road-4-specular"));
    }

    void Road4Material::Update()
    {
    }
}