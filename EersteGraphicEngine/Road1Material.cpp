#include "Road1Material.h"
#include "ShaderManager.h"
#include "TextureManager.h"

namespace ege
{
    Road1Material::Road1Material()
        : Material()
    {
    }

    Road1Material::~Road1Material()
    {
    }

    void Road1Material::Initialise()
    {
        _shader = gShaderManager().GetPtr("default");

        _hasDiffuseTexture = true;
        _hasSpecularTexture = true;
        _hasNormalTexture = false;

        InsertTexture(0, gTextureManager().GetPtr("road-1-diffuse"));
        InsertTexture(1, gTextureManager().GetPtr("road-1-specular"));
    }

    void Road1Material::Update()
    {
    }
}