#include "Cube.h"

#include "ModelManager.h"
#include "CubeMaterial.h"

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
        SPtr<Material> material = ege_shared_ptr_new<CubeMaterial>();
        material->Initialise();
        SetMaterial(material);

        Build(gModelManager().GetPtr("cube"));
    }
}