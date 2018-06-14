#include "House1Material.h"
#include "ShaderManager.h"
#include "TextureManager.h"

namespace ege
{
    House1Material::House1Material()
        : Material()
    {
    }

    House1Material::~House1Material()
    {
    }

    void House1Material::Initialise()
    {
        _shader = gShaderManager().GetPtr("default");

        _hasDiffuseTexture = true;
        _hasSpecularTexture = true;
        _hasNormalTexture = false;

        _specularPower = 1024.0f;

        InsertTexture(0, gTextureManager().GetPtr("house-1-diffuse"));
        InsertTexture(1, gTextureManager().GetPtr("house-1-specular"));
    }

    void House1Material::Update()
    {
    }
}