#include "Building3Material.h"
#include "ShaderManager.h"
#include "TextureManager.h"

namespace ege
{
    Building3Material::Building3Material()
        : Material()
    {
    }

    Building3Material::~Building3Material()
    {
    }

    void Building3Material::Initialise()
    {
        _shader = gShaderManager().GetPtr("default");

        _hasDiffuseTexture = true;
        _hasSpecularTexture = true;
        _hasNormalTexture = false;

        _specularPower = 1024.0f;

        InsertTexture(0, gTextureManager().GetPtr("building-3-diffuse"));
        InsertTexture(1, gTextureManager().GetPtr("building-3-specular"));
    }

    void Building3Material::Update()
    {
    }
}