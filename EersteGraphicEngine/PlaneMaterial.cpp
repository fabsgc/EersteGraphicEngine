#include "PlaneMaterial.h"
#include "ShaderManager.h"

namespace ege
{
    PlaneMaterial::PlaneMaterial()
        : Material()
    {
    }

    PlaneMaterial::~PlaneMaterial()
    {
    }

    void PlaneMaterial::Initialise()
    {
        _shader = gShaderManager().GetPtr("default");
    }

    void PlaneMaterial::Update()
    {
    }
}