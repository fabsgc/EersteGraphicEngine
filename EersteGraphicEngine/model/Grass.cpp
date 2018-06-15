#include "Grass.h"

#include "ModelManager.h"
#include "GrassMaterial.h"

namespace ege
{
    Grass::Grass()
        : Model()
    {
    }

    Grass::~Grass()
    {
    }

    void Grass::Initialise()
    {
        Build(gModelManager().GetPtr("grass"));

        SPtr<GrassMaterial> material = ege_shared_ptr_new<GrassMaterial>();
        material->Initialise();
        SetMaterial(material);
    }

    void Grass::Update()
    {
        Model::Update();
    }
}