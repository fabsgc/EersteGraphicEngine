#include "Building2Material.h"
#include "ShaderManager.h"
#include "TextureManager.h"

namespace ege
{
    Building2Material::Building2Material()
        : Material()
    {
    }

    Building2Material::~Building2Material()
    {
    }

    void Building2Material::Initialise()
    {
        _shader = gShaderManager().GetPtr("default");

        _hasDiffuseTexture = true;
        _hasSpecularTexture = true;
        _hasNormalTexture = false;

        _specularPower = 1024.0f;

        InsertTexture(0, gTextureManager().GetPtr("building-2-diffuse"));
        InsertTexture(1, gTextureManager().GetPtr("building-2-specular"));
    }

    void Building2Material::Update()
    {
    }
}