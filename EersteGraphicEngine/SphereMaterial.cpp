#include "SphereMaterial.h"
#include "ShaderManager.h"

namespace ege
{
    SphereMaterial::SphereMaterial()
        : Material()
    {
    }

    SphereMaterial::~SphereMaterial()
    {
    }

    void SphereMaterial::Initialise()
    {
        _shader = gShaderManager().GetPtr("default");
    }

    void SphereMaterial::Update()
    {
    }
}