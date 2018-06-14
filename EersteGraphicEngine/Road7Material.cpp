#include "Road7Material.h"
#include "ShaderManager.h"
#include "TextureManager.h"

namespace ege
{
    Road7Material::Road7Material()
        : Material()
    {
    }

    Road7Material::~Road7Material()
    {
    }

    void Road7Material::Initialise()
    {
        _shader = gShaderManager().GetPtr("default");

        _hasDiffuseTexture = true;
        _hasSpecularTexture = true;
        _hasNormalTexture = false;

        InsertTexture(0, gTextureManager().GetPtr("road-7-diffuse"));
        InsertTexture(1, gTextureManager().GetPtr("road-7-specular"));
    }

    void Road7Material::Update()
    {
    }
}