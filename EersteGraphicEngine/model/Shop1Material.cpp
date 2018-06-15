#include "Shop1Material.h"
#include "ShaderManager.h"
#include "TextureManager.h"

namespace ege
{
    Shop1Material::Shop1Material()
        : Material()
    {
    }

    Shop1Material::~Shop1Material()
    {
    }

    void Shop1Material::Initialise()
    {
        _shader = gShaderManager().GetPtr("default");

        _hasDiffuseTexture = true;
        _hasSpecularTexture = true;
        _hasNormalTexture = false;

        _specularPower = 1024.0f;

        InsertTexture(0, gTextureManager().GetPtr("shop-1-diffuse"));
        InsertTexture(1, gTextureManager().GetPtr("shop-1-specular"));
    }

    void Shop1Material::Update()
    {
    }
}