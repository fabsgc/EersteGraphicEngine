#include "Road4.h"

#include "ModelManager.h"
#include "Road4Material.h"

namespace ege
{
    Road4::Road4()
        : Model()
    {
    }

    Road4::~Road4()
    {
    }

    void Road4::Initialise()
    {
        Build(gModelManager().GetPtr("road-4"));

        SPtr<Road4Material> material = ege_shared_ptr_new<Road4Material>();
        material->Initialise();
        SetMaterial(material);
    }

    void Road4::Update()
    {
        Model::Update();
    }
}