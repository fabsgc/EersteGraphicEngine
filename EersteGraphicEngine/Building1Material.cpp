#include "Building1Material.h"
#include "ShaderManager.h"
#include "TextureManager.h"

namespace ege
{
    Building1Material::Building1Material()
        : Material()
    {
    }

    Building1Material::~Building1Material()
    {
    }

    void Building1Material::Initialise()
    {
        _shader = gShaderManager().GetPtr("default");

        _hasDiffuseTexture = true;
        _hasSpecularTexture = true;
        _hasNormalTexture = false;

        _specularPower = 1024.0f;

        InsertTexture(0, gTextureManager().GetPtr("building-1-diffuse"));
        InsertTexture(1, gTextureManager().GetPtr("building-1-specular"));
    }

    void Building1Material::Update()
    {
    }
}