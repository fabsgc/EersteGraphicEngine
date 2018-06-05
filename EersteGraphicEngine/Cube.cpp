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
        Build(gModelManager().GetPtr("cube"));

        SPtr<CubeMaterial> material = ege_shared_ptr_new<CubeMaterial>();
        material->Initialise();
        SetMaterial(material);
    }

    void Cube::Update()
    {
        Model::Update();
    }
}