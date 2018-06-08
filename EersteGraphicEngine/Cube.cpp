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
        RotatePitch(0.01f);
        //RotateRoll(GetPosition(), 0.01f);

        Model::Update();
    }
}