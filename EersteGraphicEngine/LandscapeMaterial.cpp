#include "LandscapeMaterial.h"
#include "ShaderManager.h"

namespace ege
{
    LandscapeMaterial::LandscapeMaterial()
        : Material()
    {
    }

    LandscapeMaterial::~LandscapeMaterial()
    {
    }

    void LandscapeMaterial::Initialise()
    {
        _shader = gShaderManager().GetPtr("default");
    }

    void LandscapeMaterial::Update()
    {
    }
}