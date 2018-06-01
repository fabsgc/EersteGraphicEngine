#include "CubeMaterial.h"
#include "ShaderManager.h"

namespace ege
{
    CubeMaterial::CubeMaterial()
        : Material()
    {
    }

    CubeMaterial::~CubeMaterial()
    {
    }

    void CubeMaterial::Initialise()
    {
        _shader = gShaderManager().GetPtr("default");
    }

    void CubeMaterial::Update()
    {
    }
}