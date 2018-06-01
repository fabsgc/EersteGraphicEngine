#include "Cube.h"

#include "ModelManager.h"
#include "ShaderManager.h"

namespace ege
{
    Cube::Cube()
        : Model()
    {
    }

    Cube::~Cube()
    {
    }

    void Cube::Initialise()
    {
        SetShader(gShaderManager().GetPtr("default"));
        Build(gModelManager().GetPtr("cube"));
    }
}