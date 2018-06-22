#include "Cube.h"

#include "ModelManager.h"
#include "DefaultMaterial.h"

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

        SPtr<DefaultMaterial> material = ege_shared_ptr_new<DefaultMaterial>();
        material->Initialise();
        SetMaterial(material);
    }

    void Cube::Update()
    {
        Model::Update();
    }
}