#include "Road3Material.h"
#include "ShaderManager.h"
#include "TextureManager.h"

namespace ege
{
    Road3Material::Road3Material()
        : Material()
    {
    }

    Road3Material::~Road3Material()
    {
    }

    void Road3Material::Initialise()
    {
        _shader = gShaderManager().GetPtr("default");

        _hasDiffuseTexture = true;
        _hasSpecularTexture = true;
        _hasNormalTexture = false;

        InsertTexture(0, gTextureManager().GetPtr("road-3-diffuse"));
        InsertTexture(1, gTextureManager().GetPtr("road-3-specular"));
    }

    void Road3Material::Update()
    {
    }
}