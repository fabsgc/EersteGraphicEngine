#include "DefaultMaterial.h"
#include "ShaderManager.h"

namespace ege
{
    DefaultMaterial::DefaultMaterial()
        : Material()
    {
    }

    DefaultMaterial::~DefaultMaterial()
    {
    }

    void DefaultMaterial::Initialise()
    {
        _shader = gShaderManager().GetPtr("default");
    }

    void DefaultMaterial::Update()
    {
    }
}