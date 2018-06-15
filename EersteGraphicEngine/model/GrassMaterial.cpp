#include "GrassMaterial.h"
#include "ShaderManager.h"
#include "TextureManager.h"

namespace ege
{
    GrassMaterial::GrassMaterial()
        : Material()
    {
    }

    GrassMaterial::~GrassMaterial()
    {
    }

    void GrassMaterial::Initialise()
    {
        _shader = gShaderManager().GetPtr("default");

        _hasDiffuseTexture = true;
        _hasSpecularTexture = true;
        _hasNormalTexture = false;

        InsertTexture(0, gTextureManager().GetPtr("grass-diffuse"));
        InsertTexture(1, gTextureManager().GetPtr("grass-specular"));
    }

    void GrassMaterial::Update()
    {
    }
}