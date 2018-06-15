#include "Road5Material.h"
#include "ShaderManager.h"
#include "TextureManager.h"

namespace ege
{
    Road5Material::Road5Material()
        : Material()
    {
    }

    Road5Material::~Road5Material()
    {
    }

    void Road5Material::Initialise()
    {
        _shader = gShaderManager().GetPtr("default");

        _hasDiffuseTexture = true;
        _hasSpecularTexture = true;
        _hasNormalTexture = false;

        InsertTexture(0, gTextureManager().GetPtr("road-5-diffuse"));
        InsertTexture(1, gTextureManager().GetPtr("road-5-specular"));
    }

    void Road5Material::Update()
    {
    }
}