#include "Road2Material.h"
#include "ShaderManager.h"
#include "TextureManager.h"

namespace ege
{
    Road2Material::Road2Material()
        : Material()
    {
    }

    Road2Material::~Road2Material()
    {
    }

    void Road2Material::Initialise()
    {
        _shader = gShaderManager().GetPtr("default");

        _hasDiffuseTexture = true;
        _hasSpecularTexture = true;
        _hasNormalTexture = false;

        InsertTexture(0, gTextureManager().GetPtr("road-2-diffuse"));
        InsertTexture(1, gTextureManager().GetPtr("road-2-specular"));
    }

    void Road2Material::Update()
    {
    }
}