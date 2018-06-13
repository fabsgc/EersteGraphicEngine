#include "Cube.h"

#include "ModelManager.h"
#include "Road6Material.h"

#include "Road6.h"

namespace ege
{
    Road6::Road6()
        : Model()
    {
    }

    Road6::~Road6()
    {
    }

    void Road6::Initialise()
    {
        Build(gModelManager().GetPtr("road-6"));

        SPtr<Road6Material> material = ege_shared_ptr_new<Road6Material>();
        material->Initialise();
        SetMaterial(material);
    }

    void Road6::Update()
    {
        Model::Update();
    }
}